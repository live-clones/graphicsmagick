/*
% Copyright (C) 2023-2026 GraphicsMagick Group
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                       H   H  EEEEE  I  FFFFF                                %
%                       H   H  E      I  F                                    %
%                       HHHHH  EEEEE  I  FFFF                                 %
%                       H   H  E      I  F                                    %
%                       H   H  EEEEE  I  F                                    %
%                                                                             %
%           Read HEIF/HEIC/AVIF image formats using libheif.                  %
%                                                                             %
%           Initial version contributed by Tobias Mark, 2021.                 %
%           Since developed by Bob Friesenhahn.                               %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* Status: Support for reading a single image.
* Ubuntu 22.04 LTS comes with 1.17.6 (Dec 20, 2023)!
* Debian 12 Backports provides 1.19.7 (March 3, 2025)
* Maybe limit support to version 1.17.6 (Dec 20, 2023) or later?
* But 1.20.0 (July 1, 2025) introduces support for sequences!
* Meanwhile, 1.14.0 is required to compile.
*
* Nokia technical publication on HEIF: https://nokiatech.github.io/heif/technical.html
*
* Yet to be done:
*
*   o Read/render HEIF tiles directly.
*   o Possibly support reading directly from file (heif_context_read_from_file())
*     rather than an in-memory BLOB.
*   o Support selecting to read HEIF depth image.
*   o Use HEIF transform properties to evaluate image orientation (requires 1.17).
*   o Provide user control over chroma upsampling options.
*   o Support reading sequences (requires 1.20).
*
*   o Write HEIF (HEIC, AVIF, more?)
*/

#include "magick/studio.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/colormap.h"
#include "magick/log.h"
#include "magick/constitute.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/profile.h"
#include "magick/resource.h"
#include "magick/utility.h"
#include "magick/resource.h"
#include "magick/static.h"

#if defined(HasHEIF)

/* Set to 1 to enable the currently non-functional progress monitor callbacks */
#define HEIF_ENABLE_PROGRESS_MONITOR 0

#if defined(HAVE_LIBHEIF_HEIF_SEQUENCES_H)
/* Set to 1 to enable use of <libheif/heif_sequences.h> APIs */
#define HEIF_SUPPORT_SEQUENCES 1
#endif /* if defined(HAVE_LIBHEIF_HEIF_SEQUENCES_H) */

/*
  Libheif added LIBHEIF_MAKE_VERSION in 1.14.0 (October 31, 2021).
  Duplicate its definition so we can detect versions lower than
  1.14.0.
 */
#if !defined(LIBHEIF_HAVE_VERSION)
#define LIBHEIF_MAKE_VERSION(h, m, l) (((h) << 24 | (m) << 16 | (l) << 8) | 0)
#define LIBHEIF_HAVE_VERSION(h, m, l) (LIBHEIF_NUMERIC_VERSION >= LIBHEIF_MAKE_VERSION(h, m, l))
#endif /* if !defined(LIBHEIF_HAVE_VERSION) */

#if LIBHEIF_NUMERIC_VERSION < LIBHEIF_HAVE_VERSION(1,14,0)
#  error "Libheif must be at least 1.14.0!"
#endif

/* FIXME: It would be nice to use MagickSizeStrToInt64(), but it does
   not provide error status */
#define MagickAttributeToU32(image_info, magick, name, out_val)         \
  {                                                                     \
    const char *string_value;                                           \
    if ((string_value = AccessDefinition(image_info,magick,name)))      \
      {                                                                 \
        unsigned int ui_value;                                          \
        if (MagickAtoUIChk(string_value, &ui_value) != MagickFail)      \
          {                                                             \
            out_val = ui_value;                                         \
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),         \
                                  "security limits: %s = "              \
                                  "%" MAGICK_UINTMAX_F "u", name,       \
                                  (magick_uintmax_t) out_val);          \
          }                                                             \
      }                                                                 \
  }

/* Rely on the compiler to remove unused code */

/* FIXME: It would be nice to use MagickSizeStrToInt64(), but it does
   not provide error status */
#define MagickAttributeToU64(image_info, magick, name, out_val)         \
  {                                                                     \
    const char *string_value;                                           \
    if ((string_value = AccessDefinition(image_info,magick,name)))      \
    {                                                                   \
      if (sizeof(long) == 64)                                           \
        {                                                               \
          unsigned long ul_value;                                       \
          if (MagickAtoULChk(string_value, &ul_value) != MagickFail)    \
            {                                                           \
              out_val = ul_value;                                       \
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),       \
                                    "security limits: %s = "            \
                                    "%" MAGICK_UINTMAX_F "u", name,     \
                                    (magick_uintmax_t) out_val);        \
            }                                                           \
        }                                                               \
      else                                                              \
        {                                                               \
          unsigned long long ull_value;                                 \
          if (MagickAtoULLChk(string_value, &ull_value) != MagickFail)  \
            {                                                           \
              out_val = ull_value;                                      \
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),       \
                                    "security limits: %s = "            \
                                    "%" MAGICK_UINTMAX_F "u", name,     \
                                    (magick_uintmax_t) out_val);        \
            }                                                           \
        }                                                               \
    }                                                                   \
  }

#include <libheif/heif.h>
#if defined(HEIF_SUPPORT_SEQUENCES) && HEIF_SUPPORT_SEQUENCES
#include <libheif/heif_sequences.h>
#endif /* if defined(HEIF_SUPPORT_SEQUENCES) */
static MagickBool heif_initialized = MagickFalse;

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s H E I F                                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsHEIF returns True if the image format type, identified by the
%  magick string, is supported by this HEIF reader.
%
%  The format of the IsHEIF  method is:
%
%      MagickBool IsHEIF(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsHEIF returns MagickTrue if the image format type is HEIF.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static MagickBool IsHEIF(const unsigned char *magick,const size_t length)
{
  enum heif_filetype_result
    heif_filetype;

  MagickBool
    status = MagickFalse;

  if ((length < 12) || (length > (size_t) INT_MAX))
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Data is too short (%zu bytes)", length);
      return status;
    }

  heif_filetype = heif_check_filetype(magick, (int) length);
  switch (heif_filetype)
    {
    case heif_filetype_yes_supported:
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Data is HEIF (supported by libheif)");
      status = MagickTrue;
      break;
    case heif_filetype_yes_unsupported:
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Data is HEIF (unsupported by libheif)");
      status = MagickTrue;
      break;
    case heif_filetype_maybe:
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Data may be HEIF");
      status = MagickTrue;
      break;
    case heif_filetype_no:
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Data not HEIF");
      status = MagickFalse;
      break;
    default:
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "Unexpected enum value %d",
                            (int) heif_filetype);
      status = MagickFalse;
    }
  return status;
}
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d H E I F I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ReadHEIFImage() reads an image in the HEIF image format.
%
%  The format of the ReadHEIFImage method is:
%
%      Image *ReadHEIFImage(const ImageInfo *image_info,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image_info: the image info.
%
%    o exception: return any errors or warnings in this structure.
%
*/

#define NATIVE_PLANAR_DECODE 1

#define HEIFReadCleanup()                                              \
  do                                                                   \
    {                                                                  \
      MagickFreeResourceLimitedMemory(heif_item_id *,item_ids);        \
      if (heif_image)                                                  \
        heif_image_release(heif_image);                                \
      if (heif_image_handle)                                           \
        heif_image_handle_release(heif_image_handle);                  \
      if (heif)                                                        \
        heif_context_free(heif);                                       \
      if (decode_options)                                              \
        heif_decoding_options_free(decode_options);                    \
      if (in_buf_allocated)                                            \
        MagickFreeResourceLimitedMemory(unsigned char *,in_buf);       \
    } while (0);

#define ThrowHEIFReaderException(code_,reason_,image_) \
  do                                                   \
    {                                                  \
      HEIFReadCleanup();                               \
      ThrowReaderException(code_,reason_,image_);      \
    } while (0);

/*
  Read metadata (Exif and XMP)
*/
static MagickPassFail ReadMetadata(struct heif_image_handle *heif_image_handle,
                                   Image *image, const MagickBool ignore_transformations)
{
  int
    count,
    i;

  heif_item_id
    *ids;

  struct heif_error
    err;

  /* Get number of metadata blocks attached to image */
  count=heif_image_handle_get_number_of_metadata_blocks(heif_image_handle,
                                                        /*type_filter*/ NULL);
  if (count==0)
    return MagickPass;

  ids=MagickAllocateResourceLimitedArray(heif_item_id *,count,sizeof(*ids));
  if (ids == (heif_item_id *) NULL)
    ThrowBinaryException(ResourceLimitError,MemoryAllocationFailed,(char *) NULL);

  /* Get list of metadata block ids */
  count=heif_image_handle_get_list_of_metadata_block_IDs(heif_image_handle, NULL,
                                                         ids,count);

  /* For each block id ... */
  for (i=0; i < count; i++)
    {
      const char
        *content_type,
        *profile_name;

      size_t
        exif_pad = 0,
        profile_size;

      unsigned char
        *profile;

      /* Access string indicating the type of the metadata (e.g. "Exif") */
      profile_name=heif_image_handle_get_metadata_type(heif_image_handle,ids[i]);

      /* Access string indicating the content type */
      content_type=heif_image_handle_get_metadata_content_type(heif_image_handle,ids[i]);

      /* Get the size of the raw metadata, as stored in the HEIF file */
      profile_size=heif_image_handle_get_metadata_size(heif_image_handle,ids[i]);

      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Profile \"%s\" with content type \"%s\""
                              " and size %" MAGICK_SIZE_T_F "u bytes",
                              profile_name ? profile_name : "(null)",
                              content_type ? content_type : "(null)",
                              (MAGICK_SIZE_T) profile_size);

      if (NULL != profile_name && profile_size > 0)
        {
          if (strncmp(profile_name,"Exif",4) == 0)
            exif_pad=2;

          /* Allocate memory for profile */
          profile=MagickAllocateResourceLimitedArray(unsigned char*,profile_size+exif_pad,
                                                     sizeof(*profile));
          if (profile == (unsigned char*) NULL)
            {
              MagickFreeResourceLimitedMemory(heif_item_id *,ids);
              ThrowBinaryException(ResourceLimitError,MemoryAllocationFailed,(char *) NULL);
            }

          /*
            Copy metadata into 'profile' buffer. For Exif data, you
            probably have to skip the first four bytes of the data,
            since they indicate the offset to the start of the TIFF
            header of the Exif data.
          */
          err=heif_image_handle_get_metadata(heif_image_handle,ids[i],profile+exif_pad);

          if (err.code != heif_error_Ok)
            {
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "heif_image_handle_get_metadata() reports error \"%s\"",
                                      err.message);
              MagickFreeResourceLimitedMemory(unsigned char *,profile);
              MagickFreeResourceLimitedMemory(heif_item_id *,ids);
              ThrowBinaryException(CorruptImageError,
                                   AnErrorHasOccurredReadingFromFile,image->filename);
            }

          if (strncmp(profile_name,"Exif",4) == 0 && profile_size > 4)
            {
              /* Parse and skip offset to TIFF header */
              unsigned char *p = profile;
              magick_uint32_t offset;

              /* Big-endian offset decoding */
              offset = (magick_uint32_t) p[exif_pad+0] << 24 |
                (magick_uint32_t) p[exif_pad+1] << 16 |
                (magick_uint32_t) p[exif_pad+2] << 8 |
                (magick_uint32_t) p[exif_pad+3];

              /*
                If the TIFF header offset is not zero, then need to
                move the TIFF data forward to the correct offset.
              */
              profile_size -= 4;
              if (offset > 0 && offset < profile_size)
                {
                  profile_size -= offset;

                  /* Strip any EOI marker if payload starts with a JPEG marker */
                  if (profile_size > 2 &&
                      (memcmp(p+exif_pad+4,"\xff\xd8",2) == 0 ||
                       memcmp(p+exif_pad+4,"\xff\xe1",2) == 0) &&
                      memcmp(p+exif_pad+4+profile_size-2,"\xff\xd9",2) == 0)
                    profile_size -= 2;

                  (void) memmove(p+exif_pad+4,p+exif_pad+4+offset,profile_size);
                }

              p[0]='E';
              p[1]='x';
              p[2]='i';
              p[3]='f';
              p[4]='\0';
              p[5]='\0';

              SetImageProfile(image,"EXIF",profile,profile_size+exif_pad+4);

              /*
                Retrieve image orientation from EXIF and store in
                image.
              */
              {
                const ImageAttribute
                  *attribute;

                attribute = GetImageAttribute(image,"EXIF:Orientation");
                if ((attribute != (const ImageAttribute *) NULL) &&
                    (attribute->value != (char *) NULL))
                  {
                    int
                      orientation;

                    orientation=MagickAtoI(attribute->value);
                    if ((orientation > UndefinedOrientation) &&
                        (orientation <= LeftBottomOrientation))
                      image->orientation=(OrientationType) orientation;
                  }
              }
            }
          else
            {
              if (NULL != content_type && strncmp(content_type,"application/rdf+xml",19) == 0)
                SetImageProfile(image,"XMP",profile,profile_size);
            }
          /*
            Only apply Exif orientation if ignore-transformations is true
            since HEIF native transformations will handle orientation otherwise
          */
          if (strncmp(profile_name,"Exif",4) == 0)
            {
              if (ignore_transformations)
                {
                  const ImageAttribute *attribute = GetImageAttribute(image,"EXIF:Orientation");
                  if (attribute && attribute->value)
                    {
                      SetImageAttribute(image,"EXIF:Orientation","1");
                      image->orientation = UndefinedOrientation;
                    }
                }
            }
          MagickFreeResourceLimitedMemory(unsigned char *,profile);
        }
    }
  MagickFreeResourceLimitedMemory(heif_item_id *,ids);
  return MagickPass;
}


/*
  Read Color Profile
*/
static MagickPassFail ReadColorProfile(struct heif_image_handle *heif_image_handle,
                                       Image *image)
{
  struct heif_error
    err;

  enum heif_color_profile_type
    profile_type; /* 4 chars encoded into enum by 'heif_fourcc()' */

  unsigned char
    *profile;

  profile_type = heif_image_handle_get_color_profile_type(heif_image_handle);

  if (heif_color_profile_type_not_present == profile_type)
    return MagickPass;

  if (image->logging && (heif_color_profile_type_not_present !=profile_type))
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Found color profile of type \"%c%c%c%c\"",
                          ((char) ((unsigned int) profile_type >> 24) & 0xff),
                          ((char) ((unsigned int) profile_type >> 16) & 0xff),
                          ((char) ((unsigned int) profile_type >> 8) & 0xff),
                          ((char) ((unsigned int) profile_type) & 0xff));

  if (heif_color_profile_type_prof == profile_type)
    {
      size_t profile_size;

      profile_size = heif_image_handle_get_raw_color_profile_size(heif_image_handle);

      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Reading ICC profile with size %" MAGICK_SIZE_T_F "u bytes...",
                              (MAGICK_SIZE_T) profile_size);

      if (profile_size > 0)
        {
          /* Allocate 'profile' buffer for profile */
          profile=MagickAllocateResourceLimitedArray(unsigned char*,profile_size,
                                                     sizeof(*profile));

          if (profile == (unsigned char*) NULL)
            ThrowBinaryException(ResourceLimitError,MemoryAllocationFailed,(char *) NULL);

          /* Copy ICC profile to 'profile' buffer */
          err = heif_image_handle_get_raw_color_profile(heif_image_handle,
                                                        profile);
          if (err.code != heif_error_Ok)
            {
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "heif_image_handle_get_raw_color_profile() reports error \"%s\"",
                                      err.message);
              MagickFreeResourceLimitedMemory(unsigned char *,profile);
              ThrowBinaryException(CorruptImageError,
                                   AnErrorHasOccurredReadingFromFile,image->filename);

            }
          SetImageProfile(image,"ICM",profile,profile_size);
          MagickFreeResourceLimitedMemory(unsigned char *,profile);
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "  done reading ICC profile");
        }
    }
  return MagickPass;
}

/*
  This progress monitor implementation is tentative since it is not invoked

  According to libheif issue 161
  (https://github.com/strukturag/libheif/issues/161) progress monitor
  does not actually work since the decoders it depends on do not
  support it.

  Libheif issue 546 (https://github.com/strukturag/libheif/pull/546)
  suggests changing the return type of on_progress and start_progress
  to "bool" so that one can implement cancellation support.
 */
typedef struct ProgressUserData_
{
  ExceptionInfo *exception;
  Image *image;
  enum heif_progress_step step;
  unsigned long int progress;
  unsigned long int max_progress;

} ProgressUserData;

#if HEIF_ENABLE_PROGRESS_MONITOR
/* Called when progress monitor starts.  The 'max_progress' parameter indicates the maximum value of progress */
static void start_progress(enum heif_progress_step step, int max_progress, void* progress_user_data)
{
  ProgressUserData *context= (ProgressUserData *) progress_user_data;
  Image *image=context->image;
  context->step = step;
  context->progress = 0;
  context->max_progress = max_progress;
  if (context->image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "start_progress: step=%d, max_progress=%d",step, max_progress);
  MagickMonitorFormatted(context->progress,context->max_progress,&image->exception,
                         "[%s] Loading image: %lux%lu...  ",
                         image->filename,
                         image->columns,image->rows);
}

/* Called for each step of progress.  The 'progress' parameter represents the progress within the span of 'max_progress' */
static void on_progress(enum heif_progress_step step, int progress, void* progress_user_data)
{
  ProgressUserData *context = (ProgressUserData *) progress_user_data;
  Image *image=context->image;
  context->step = step;
  context->progress = progress;
  if (context->image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "on_progress: step=%d, progress=%d",step, progress);
  MagickMonitorFormatted(context->progress,context->max_progress,&image->exception,
                         "[%s] Loading image: %lux%lu...  ",
                         image->filename,
                         image->columns,image->rows);
}

/* Called when progress monitor stops */
static void end_progress(enum heif_progress_step step, void* progress_user_data)
{
  ProgressUserData *context = (ProgressUserData *) progress_user_data;
  context->step = step;
  if (context->image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "end_progress: step=%d",step);
}

#endif /* if HEIF_ENABLE_PROGRESS_MONITOR */

/*
  Apply security limits
 */
static MagickPassFail apply_security_limits(const ImageInfo *image_info,
                                            struct heif_context *heif_context)
{
#if LIBHEIF_NUMERIC_VERSION >= LIBHEIF_MAKE_VERSION(1,19,0)
  struct heif_security_limits
    *security_limits;

  magick_uintmax_t
    memory_limit,
    width_limit,
    height_limit,
    pixels_limit;

  security_limits=heif_context_get_security_limits(heif_context);

  memory_limit = (magick_uintmax_t) GetMagickResourceLimit(MemoryResource);
  security_limits->max_memory_block_size = (uint64_t) memory_limit;
  security_limits->max_total_memory = (uint64_t) memory_limit;
  width_limit = (magick_uintmax_t) GetMagickResourceLimit(WidthResource);
  if (width_limit > INT_MAX)
    width_limit = INT_MAX;
  height_limit = (magick_uintmax_t) GetMagickResourceLimit(HeightResource);
  if (height_limit > INT_MAX)
    height_limit = INT_MAX;
  pixels_limit = (magick_uintmax_t) GetMagickResourceLimit(PixelsResource);
  if ((width_limit < pixels_limit) && (height_limit < pixels_limit) &&
      (width_limit*height_limit < pixels_limit))
    pixels_limit = width_limit*height_limit;

  security_limits->max_image_size_pixels = (uint64_t) pixels_limit;

  /*
    Version 1 interface has:

    uint64_t max_image_size_pixels;
    uint64_t max_number_of_tiles;
    uint32_t max_bayer_pattern_pixels;
    uint32_t max_items;

    uint32_t max_color_profile_size;
    uint64_t max_memory_block_size;

    uint32_t max_components;

    uint32_t max_iloc_extents_per_item;
    uint32_t max_size_entity_group;

    uint32_t max_children_per_box; // for all boxes that are not covered by other limits

    and the version 2 interface adds:

    uint64_t max_total_memory;
    uint32_t max_sample_description_box_entries;
    uint32_t max_sample_group_description_box_entries;

  */
  /* version 1 interface */
  MagickAttributeToU64(image_info,"heif","max-image-size-pixels",
                       security_limits->max_image_size_pixels);

  MagickAttributeToU64(image_info,"heif","max-number-of-tiles",
                       security_limits->max_number_of_tiles);

  MagickAttributeToU32(image_info,"heif","max-bayer-pattern-pixels",
                       security_limits->max_bayer_pattern_pixels);

  MagickAttributeToU32(image_info,"heif","max-items",
                       security_limits->max_items);

  MagickAttributeToU32(image_info,"heif","max-color-profile-size",
                       security_limits->max_color_profile_size);

  MagickAttributeToU64(image_info,"heif","max-memory-block-size",
                       security_limits->max_memory_block_size);

  MagickAttributeToU32(image_info,"heif","max-components",
                       security_limits->max_components);

  MagickAttributeToU32(image_info,"heif","max-iloc-extents-per-item",
                       security_limits->max_iloc_extents_per_item);

  MagickAttributeToU32(image_info,"heif","max-size-entity-group",
                       security_limits->max_size_entity_group);

  MagickAttributeToU32(image_info,"heif","max-children-per-box",
                       security_limits->max_children_per_box);

  /* version 2 interface */

  /* Added in 1.13.0, September 2, 2022 */
  MagickAttributeToU64(image_info,"heif","max-total-memory",
                       security_limits->max_total_memory);

  /* Added in 1.13.0, September 2, 2022 */
  MagickAttributeToU32(image_info,"heif","max-sample-description-box-entries",
                       security_limits->max_sample_description_box_entries);

  /* Added in 1.17.6? ?*/
  MagickAttributeToU32(image_info,"heif","max-sample-group-description-box-entries",
                       security_limits->max_sample_group_description_box_entries);

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "security limits:"
                        /* version 1 interface */
                        "  max_image_size_pixels = %" MAGICK_UINTMAX_F "u"","
                        "  max_number_of_tiles = %" MAGICK_UINTMAX_F "u"","
                        "  max_bayer_pattern_pixels = %" MAGICK_UINTMAX_F "u"","
                        "  max_items = %" MAGICK_UINTMAX_F "u"","
                        "  max_color_profile_size = %" MAGICK_UINTMAX_F "u"","
                        "  max_memory_block_size = %" MAGICK_UINTMAX_F "u"","
                        "  max_components = %" MAGICK_UINTMAX_F "u"","
                        "  max_iloc_extents_per_item = %" MAGICK_UINTMAX_F "u"","
                        "  max_size_entity_group = %" MAGICK_UINTMAX_F "u"","
                        "  max_children_per_box = %" MAGICK_UINTMAX_F "u"","
                        /* version 2 interface */
                        "  max_total_memory = %" MAGICK_UINTMAX_F "u"","
                        "  max_sample_description_box_entries = %" MAGICK_UINTMAX_F "u"","
                        "  max_sample_group_description_box_entries = %" MAGICK_UINTMAX_F "u",
                        /* version 1 interface */
                        (magick_uintmax_t) security_limits->max_image_size_pixels,
                        (magick_uintmax_t) security_limits->max_number_of_tiles,
                        (magick_uintmax_t) security_limits->max_bayer_pattern_pixels,
                        (magick_uintmax_t) security_limits->max_items,
                        (magick_uintmax_t) security_limits->max_color_profile_size,
                        (magick_uintmax_t) security_limits->max_memory_block_size,
                        (magick_uintmax_t) security_limits->max_components,
                        (magick_uintmax_t) security_limits->max_iloc_extents_per_item,
                        (magick_uintmax_t) security_limits->max_size_entity_group,
                        (magick_uintmax_t) security_limits->max_children_per_box,
                        /* version 2 interface */
                        (magick_uintmax_t) security_limits->max_total_memory,
                        (magick_uintmax_t) security_limits->max_sample_description_box_entries,
                        (magick_uintmax_t) security_limits->max_sample_group_description_box_entries
                        );
#else
  {
    /* DEPRECATED: Add an image size limit based on maximum_width ^ 2 */
    magick_int64_t width_limit = GetMagickResourceLimit(WidthResource);
    if (MagickResourceInfinity != width_limit)
      {
        if (width_limit > INT_MAX)
          width_limit =  INT_MAX;
        /* Added in libheif 1.4.0 */
        heif_context_set_maximum_image_size_limit(heif, (int) width_limit);
      }
  }

#endif /* if LIBHEIF_NUMERIC_VERSION >= LIBHEIF_MAKE_VERSION(1,19,0) */

  return MagickPass;
}

/*
  libheif/color-conversion/colorconversion.cc provides this to output to
  an ostream, but our code is not C++!

  std::ostream& operator<<(std::ostream& ostr, heif_colorspace c)
*/
static const char *HEIF_colorspace_to_string(const enum heif_colorspace c)
{
  const char *s = "unknown";

  switch (c)
    {
    case heif_colorspace_undefined:
      s = "undefined";
      break;
    case heif_colorspace_YCbCr:
      s = "YCbCr";
      break;
    case heif_colorspace_RGB:
      s = "RGB";
      break;
    case heif_colorspace_monochrome:
      s = "monochrome";
      break;
    case heif_colorspace_nonvisual:
      s = "nonvisual";
      break;
#if 0
      /* Git commit cb6e524 added on 2/24/26 */
    case heif_colorspace_filter_array:
      s = "filter_array";
      break;
#endif
    }

  return s;
}

static ColorspaceType HEIF_colorspace_to_ColorspaceType(const enum heif_colorspace c)
{
  ColorspaceType t = UndefinedColorspace;

  switch (c)
    {
    case heif_colorspace_undefined:
      t = UndefinedColorspace;
      break;
    case heif_colorspace_YCbCr:
      t = YUVColorspace;
      break;
    case heif_colorspace_RGB:
      t = RGBColorspace;
      break;
    case heif_colorspace_monochrome:
      t = GRAYColorspace;
      break;
    case heif_colorspace_nonvisual:
      t = UndefinedColorspace;
      break;
    }

  return t;
}

static const char *HEIF_chroma_to_string(const enum heif_chroma c)
{
  const char *s = "unknown";

  switch (c)
    {
    case heif_chroma_undefined:
      s = "undefined";
      break;
    case heif_chroma_monochrome:
      s = "monochrome";
      break;
    case heif_chroma_420:
      s = "420";
      break;
    case heif_chroma_422:
      s = "422";
      break;
    case heif_chroma_444:
      s = "444";
      break;
    case heif_chroma_interleaved_RGB:
      s = "interleaved_RGB";
      break;
    case heif_chroma_interleaved_RGBA:
      s = "interleaved_RGBA";
      break;
    case heif_chroma_interleaved_RRGGBB_BE:
      s = "interleaved_RRGGBB_BE";
      break;
    case heif_chroma_interleaved_RRGGBBAA_BE:
      s = "interleaved_RRGGBBAA_BE";
      break;
    case heif_chroma_interleaved_RRGGBB_LE:
      s = "interleaved_RRGGBB_LE";
      break;
    case heif_chroma_interleaved_RRGGBBAA_LE:
      s = "interleaved_RRGGBBAA_LE";
      break;
    }

  return s;
}

static const char *HEIF_channel_to_string(const enum heif_channel c)
{
  const char *s = "unknown";

  switch (c)
    {
    case heif_channel_Y:
      s = "Y";
      break;
    case heif_channel_Cb:
      s = "Cb";
      break;
    case heif_channel_Cr:
      s = "Cr";
      break;
    case heif_channel_R:
      s = "R";
      break;
    case heif_channel_G:
      s = "G";
      break;
    case heif_channel_B:
      s = "B";
      break;
    case heif_channel_Alpha:
      s = "Alpha";
      break;
    case heif_channel_interleaved:
      s = "interleaved";
      break;
    case heif_channel_filter_array:
      s = "filter_array";
      break;
    case heif_channel_depth:
      s = "channel_depth";
      break;
    case heif_channel_disparity:
      s = "disparity";
      break;
#if 0
#if LIBHEIF_NUMERIC_VERSION > LIBHEIF_HAVE_VERSION(1,21,3)
      /* Added by changeset b4326c42 on 2/12/26 after v1.21.2 */
    case heif_channel_unknown:
      s = "unknown";
      break;
#endif /* if LIBHEIF_NUMERIC_VERSION > LIBHEIF_HAVE_VERSION(1,21,3) */
#endif
    default:
      s = "unknown";
      break;
    }

  return s;
}

static MagickPassFail ReadHEIFImageFrame(heif_image_handle* heif_image_handle,
                                         struct heif_decoding_options *decode_options,
                                         Image *image,
                                         const ImageInfo *image_info,
                                         ExceptionInfo *exception)
{
#define HEIFReadImageFrameCleanup()             \
  do                                            \
    {                                           \
      if (heif_image)                           \
        heif_image_release(heif_image);         \
    } while (0);

#define ThrowHEIFThrowReadImageFrameException(code_,reason_,image_)     \
  do                                                                    \
    {                                                                   \
      HEIFReadImageFrameCleanup();                                      \
      if (code_ > exception->severity)                                  \
        {                                                               \
          ThrowException(&(image_)->exception,code_,reason_,(image_)->filename); \
          CopyException(exception,&(image_)->exception);                \
        }                                                               \
      return(MagickFail);                                               \
    } while (0);

  struct heif_image
    *heif_image = NULL;

  PixelPacket
    *q;

  long
    x,
    y;

  int
    bits_per_pixel;

  struct heif_error
    heif_status;

#if HEIF_ENABLE_PROGRESS_MONITOR
  ProgressUserData
    progress_user_data;
#endif

  enum heif_colorspace
    heif_colorspace,
    preferred_colorspace = heif_colorspace_undefined;

  enum heif_chroma
    preferred_chroma = heif_chroma_undefined;

  /*
    Note: Those values are preliminary but likely the upper bound
    The real image values might be rotated or cropped due to transformations

    heif_image_handle APIs are declared in heif_image_handle.h
  */
  image->depth=8;
  /*
    This function only works for YCbCr-based images.  We only use it
    in ping mode since otherwise it screws up the depth in the Q8
    build (due to scaling in libheif).
  */
  if (image_info->ping)
    {
      bits_per_pixel=heif_image_handle_get_luma_bits_per_pixel(heif_image_handle);
      if (image->logging)
        if (bits_per_pixel < 0)
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Image has undefined bit-depth!");
      if (bits_per_pixel > 0)
        image->depth=(unsigned int) bits_per_pixel;
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Depth: %u", image->depth);
    }

  image->columns=heif_image_handle_get_width(heif_image_handle);
  image->rows=heif_image_handle_get_height(heif_image_handle);
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Geometry: %lux%lu", image->columns, image->rows);
  image->matte=MagickFalse;
  if (heif_image_handle_has_alpha_channel(heif_image_handle))
    image->matte=MagickTrue;
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Matte: %s", image->matte ? "True" : "False");
  heif_status=heif_image_handle_get_preferred_decoding_colorspace(heif_image_handle,
                                                                  &preferred_colorspace,
                                                                  &preferred_chroma);
  if (heif_status.code != heif_error_Ok)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "heif_image_handle_get_preferred_decoding_colorspace() reports error \"%s\"",
                              heif_status.message);
      ThrowHEIFThrowReadImageFrameException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
    }
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Preferred colorspace: %s, "
                          "Preferred chroma: %s",
                          HEIF_colorspace_to_string(preferred_colorspace),
                          HEIF_chroma_to_string(preferred_chroma));

  /* Read EXIF and XMP profile */
  if (!ReadMetadata(heif_image_handle, image, decode_options->ignore_transformations))
    {
      CopyException(exception,&image->exception);
      HEIFReadImageFrameCleanup();
      return MagickFail;
    }

  /* Read ICC profile */
  if (!ReadColorProfile(heif_image_handle, image))
    {
      CopyException(exception,&image->exception);
      HEIFReadImageFrameCleanup();
      return MagickFail;
    }

  /*
    When applying transformations the whole image has to be read to
    get the real dimensions. We no longer read the whole image because
    it makes 'identify' extremely slow for large files.

    The user should specify:

    -define heif:ignore-transformations=false

    in order to force reading much of the image to get fully accurate
    information.
  */
  if (image_info->ping && decode_options->ignore_transformations)
    {
      HEIFReadImageFrameCleanup();
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Returning early without pixels due to ping mode...");
      return MagickPass;
    }


  /*
    Be prepared to handle images on per-plane basis. Upscale
    subsampled chroma if necessary.
  */
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Decoding image...");

  {
    enum heif_chroma heif_chroma_decode=preferred_chroma;
    enum heif_colorspace heif_colorspace_decode=preferred_colorspace;
    /* Upscale chroma if necessary */
    if ((heif_chroma_decode == heif_chroma_420) || (heif_chroma_decode == heif_chroma_422))
      heif_chroma_decode=heif_chroma_444;
    /* Use planar mode until interleaved is implemented */
    else if (heif_colorspace_decode == heif_colorspace_RGB
             /* heif_chroma_decode != heif_chroma_monochrome */)
      heif_chroma_decode=heif_chroma_444;

    /* FIXME: Add control over whether to return original YBbCr or RGB */
#if 1
    if (heif_colorspace_decode == heif_colorspace_YCbCr)
      {
        const char *string_value;
        MagickBool preserve_colorspace = MagickFalse;
        /*
          Use heif:preserve-colorspace=true or
          heif:preserve-colorspace=1 to return the image in the
          original colorspace.  This prevents the conversion of a
          YCbCr image to RGB.  GraphicsMagick will usually
          automatically YCbCr image to RGB when necessary but explicit
          conversion to RGB colorspace may sometimes be
          necessary. Preserving the original colorspace is useful in
          case YCbCr is needed, or to avoid quality loss when the
          output will be in YCbCr.
        */
        if ((string_value = AccessDefinition(image_info,"heif","preserve-colorspace")))
          {
            if ((LocaleCompare(string_value,"true") == 0) ||
                (LocaleCompare(string_value,"yes") == 0) ||
                (LocaleCompare(string_value,"1") == 0))
              preserve_colorspace = MagickTrue;
          }
        if (preserve_colorspace == MagickFalse)
          heif_colorspace_decode=heif_colorspace_RGB;
      }
#endif

    if (image->logging && IsEventLogged(CoderEvent))
      {
#if 1
        /* See libheif/api/libheif/heif_tiling.h */
        heif_image_tiling tiling;
        (void) memset(&tiling,0,sizeof(tiling));
        heif_status=heif_image_handle_get_image_tiling(heif_image_handle, decode_options->ignore_transformations, &tiling);
        if (heif_status.code != heif_error_Ok)
          {
            if (image->logging)
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "heif_image_handle_get_image_tiling() reports error \"%s\"",
                                    heif_status.message);
            ThrowHEIFThrowReadImageFrameException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
          }
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Tiling: version %d, num_columns=%u, num_rows=%u,"
                              " tile_width=%u, tile_height=%u, image_width=%u, image_height=%u,"
                              " top_offset=%u, left_offset=%u, number_of_extra_dimensions=%u",
                              tiling.version, tiling.num_columns, tiling.num_rows,
                              tiling.tile_width, tiling.tile_height, tiling.image_width, tiling.image_height,
                              tiling.top_offset, tiling.left_offset,
                              tiling.number_of_extra_dimensions);
#endif
#if 0
        /* From heif_dec.cc decode_image_tiles() */
        for (uint32_t ty = 0; ty < tiling.num_rows; ty++)
          for (uint32_t tx = 0; tx < tiling.num_columns; tx++)
            {
              /*
                heif_image* image;
                heif_error err;
                err = heif_image_handle_decode_image_tile(handle,
                &image,
                encoder->colorspace(has_alpha),
                encoder->chroma(has_alpha, bit_depth),
                decode_options, tx, ty);
                heif_error heif_image_handle_decode_image_tile(const heif_image_handle* in_handle,
                heif_image** out_img,
                enum heif_colorspace colorspace,
                enum heif_chroma chroma,
                const heif_decoding_options* options,
                uint32_t tile_x, uint32_t tile_y);
                heif_image_release(image);
              */
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Tile %u,%u: (x1=%u y1=%u x2=%u y2=%u)",
                                    tx, ty, tx*tiling.tile_width, ty*tiling.tile_height,
                                    ((tx+1)*tiling.tile_width)-1, ((ty+1)*tiling.tile_height)-1);
            }
#endif
      }

    heif_status=heif_decode_image(heif_image_handle,
                                  &heif_image,
                                  heif_colorspace_decode, /* Chose preferred colorspace */
                                  heif_chroma_decode,
                                  decode_options);
  }
  if (heif_status.code == heif_error_Memory_allocation_error)
    ThrowHEIFThrowReadImageFrameException(ResourceLimitError,MemoryAllocationFailed,image);
  if (heif_status.code != heif_error_Ok)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "heif_decode_image() reports error \"%s\"",
                              heif_status.message);
      ThrowHEIFThrowReadImageFrameException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
    }
  if (heif_image == (struct heif_image *) NULL)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "heif_decode_image() reports heif_error_Ok but failed to return an image!");
      ThrowHEIFThrowReadImageFrameException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
    }

  /*
    Trace decoding warnings
  */
  if (image->logging && IsEventLogged(CoderEvent))
    {
      int i;

      for (i = 0;; i++)
        {
          int n;
          n = heif_image_get_decoding_warnings(heif_image,i,&heif_status, 1);
          if (n == 0)
            break;
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "Warning: %s", heif_status.message);
        }
    }

  /*
    Update image properties
  */
  image->columns=heif_image_get_primary_width(heif_image);
  image->rows=heif_image_get_primary_height(heif_image);
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Geometry: %lux%lu",
                          image->columns,image->rows);
  heif_colorspace=heif_image_get_colorspace(heif_image);
  image->colorspace=HEIF_colorspace_to_ColorspaceType(heif_colorspace);
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "HEIF colorspace: %s",
                          HEIF_colorspace_to_string(heif_colorspace));

  if (image_info->ping)
    {
      HEIFReadImageFrameCleanup();
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Returning without pixels due to ping mode...");
      return MagickPass;
    }

  if (CheckImagePixelLimits(image, exception) != MagickPass)
    {
      HEIFReadImageFrameCleanup();
      return MagickFail;
    }

  {

    typedef union
    {
      const uint8_t *u8;
      const uint16_t *u16;
      const uint32_t *u32;
    } magick_plane_t;

    const char *
      heif_channel_str;

    const char *
      heif_chroma_format_str;

    enum heif_chroma
      heif_chroma_format;

    heif_chroma_format = heif_image_get_chroma_format(heif_image);
    heif_chroma_format_str = HEIF_chroma_to_string(heif_chroma_format);

    switch (heif_image_get_colorspace(heif_image))
      {
      case heif_colorspace_YCbCr:
        {
          /*
            Decode YCbCr(A) pixels
          */

          static const enum heif_channel channels_YCbCrA[4] =
            { heif_channel_Y, heif_channel_Cb, heif_channel_Cr, heif_channel_Alpha };

          magick_plane_t
            planes[4];

          magick_plane_t
            line[4];

          size_t
            row_stride[4];

          int
            channel_bits_per_pixel[4];

          int
            channel_bits_per_pixel_range[4];

          unsigned long
            channel_max_value_given_bits[4];

          unsigned int
            channel_index,
            num_channels;

          enum heif_channel heif_channel;

          num_channels = image->matte ? 4 : 3;

          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Decoding %u planes for YCbCr colorspace (chroma %s)",
                                  num_channels, heif_chroma_format_str);

          for (channel_index = 0; channel_index < num_channels; channel_index++)
            {
              heif_channel = channels_YCbCrA[channel_index];
              heif_channel_str = HEIF_channel_to_string(heif_channel);
              planes[channel_index].u8 = heif_image_get_plane_readonly2(heif_image,
                                                                        heif_channel,
                                                                        &row_stride[channel_index]);
              if (planes[channel_index].u8 == (const uint8_t*) NULL)
                {
                  if (image->logging)
                    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                          "heif_image_get_plane_readonly2() returned NULL"
                                          " for channel index %u (channel %s)!",
                                          channel_index,heif_channel_str);
                  ThrowHEIFThrowReadImageFrameException(CorruptImageError,
                                                        AnErrorHasOccurredReadingFromFile, image);
                }
              channel_bits_per_pixel[channel_index] = heif_image_get_bits_per_pixel(heif_image,
                                                                                    heif_channel);
              channel_bits_per_pixel_range[channel_index] = heif_image_get_bits_per_pixel_range(heif_image,
                                                                                                heif_channel);
              channel_max_value_given_bits[channel_index] = MaxValueGivenBits(channel_bits_per_pixel_range[channel_index]);
              if ((int) image->depth < channel_bits_per_pixel_range[channel_index])
                image->depth=(unsigned int) channel_bits_per_pixel_range[channel_index];
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "  channel %s row stride %zu (%d bits in %d bit quantum)",
                                      heif_channel_str, row_stride[channel_index],
                                      channel_bits_per_pixel_range[channel_index],
                                      channel_bits_per_pixel[channel_index]);
            }

          /* Transfer pixels to image, using row stride to find start of each row. */
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Transferring pixels to magick image...");
          for (y=0; y < (long)image->rows; y++)
            {
              q=SetImagePixelsEx(image,0,y,image->columns,1,exception);
              if (q == (PixelPacket *) NULL)
                {
                  HEIFReadImageFrameCleanup();
                  return MagickFail;
                }
              for (channel_index = 0; channel_index < num_channels; channel_index++)
                line[channel_index].u8=planes[channel_index].u8+y*row_stride[channel_index];
              for (x=0; x < (long)image->columns; x++)
                {
                  for (channel_index = 0; channel_index < num_channels; channel_index++)
                    {
                      uint32_t
                        sample = 0;

                      Quantum
                        quantum=0;

                      /*
                        Get sample
                      */
                      switch(channel_bits_per_pixel[channel_index])
                        {
                        case 8:
                          sample = *line[channel_index].u8;
                          line[channel_index].u8++;
                          break;
                        case 16:
                          sample = *line[channel_index].u16;
                          line[channel_index].u16++;
                          break;
                        case 32:
                          sample = *line[channel_index].u32;
                          line[channel_index].u32++;
                          break;
                        }

                      /*
                        Scale sample to quantum
                      */
                      if (channel_bits_per_pixel_range[channel_index] == 8)
                        {
                          quantum=ScaleCharToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 8)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] == 16)
                        {
                          quantum=ScaleShortToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 16)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] == 32)
                        {
                          quantum=ScaleLongToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 32)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }

                      /*
                        Assign quantum to PixelPacket
                      */
                      switch (channel_index)
                        {
                        case 0:
                          SetYSample(q,quantum);
                          if (num_channels != 4)
                            SetOpacitySample(q,OpaqueOpacity);
                          break;
                        case 1:
                          SetCbSample(q,quantum);
                          break;
                        case 2:
                          SetCrSample(q,quantum);
                          break;
                        case 3:
                          SetOpacitySample(q,MaxRGB-quantum);
                          break;
                        }
                    }
                  q++;
                }
              if (!SyncImagePixelsEx(image,exception))
                {
                  HEIFReadImageFrameCleanup();
                  return MagickFail;
                }
            }
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "  done!");
        }
        break;
      case heif_colorspace_RGB:
        {
          /*
            Decode RGB(A) pixels
          */
          static const enum heif_channel
            channels_RGBA[4] =
            { heif_channel_R, heif_channel_G, heif_channel_B, heif_channel_Alpha };

          magick_plane_t
            planes[4];

          magick_plane_t
            line[4];

          size_t
            row_stride[4];

          int
            channel_bits_per_pixel[4];

          int
            channel_bits_per_pixel_range[4];

          unsigned long
            channel_max_value_given_bits[4];

          unsigned int
            channel_index,
            num_channels=0;

          enum heif_channel
            heif_channel;

          num_channels = image->matte ? 4 : 3;

          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Decoding %u planes for RGB colorspace (chroma %s)",
                                  num_channels, heif_chroma_format_str);

          for (channel_index = 0; channel_index < num_channels; channel_index++)
            {
              heif_channel = channels_RGBA[channel_index];
              heif_channel_str = HEIF_channel_to_string(heif_channel);
              planes[channel_index].u8 = heif_image_get_plane_readonly2(heif_image,
                                                                        heif_channel,
                                                                        &row_stride[channel_index]);
              if (planes[channel_index].u8 == (const uint8_t*) NULL)
                {
                  if (image->logging)
                    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                          "heif_image_get_plane_readonly2() returned NULL"
                                          " for channel index %u (channel %s)!",
                                          channel_index,heif_channel_str);
                  ThrowHEIFThrowReadImageFrameException(CorruptImageError,
                                                        AnErrorHasOccurredReadingFromFile, image);
                }
              channel_bits_per_pixel[channel_index] = heif_image_get_bits_per_pixel(heif_image,
                                                                                    heif_channel);
              channel_bits_per_pixel_range[channel_index] = heif_image_get_bits_per_pixel_range(heif_image,
                                                                                                heif_channel);
              channel_max_value_given_bits[channel_index] = MaxValueGivenBits(channel_bits_per_pixel_range[channel_index]);
              if ((int) image->depth < channel_bits_per_pixel_range[channel_index])
                image->depth=(unsigned int) channel_bits_per_pixel_range[channel_index];
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "  channel %s row stride %zu (%d bits in %d bit quantum)",
                                      heif_channel_str, row_stride[channel_index],
                                      channel_bits_per_pixel_range[channel_index],
                                      channel_bits_per_pixel[channel_index]);
            }

          /* Transfer pixels to image, using row stride to find start of each row. */
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Transferring pixels to magick image...");
          for (y=0; y < (long)image->rows; y++)
            {
              q=SetImagePixelsEx(image,0,y,image->columns,1,exception);
              if (q == (PixelPacket *) NULL)
                {
                  HEIFReadImageFrameCleanup();
                  return MagickFail;
                }
              for (channel_index = 0; channel_index < num_channels; channel_index++)
                line[channel_index].u8=planes[channel_index].u8+y*row_stride[channel_index];
              for (x=0; x < (long)image->columns; x++)
                {
                  for (channel_index = 0; channel_index < num_channels; channel_index++)
                    {
                      uint32_t
                        sample = 0;

                      Quantum
                        quantum=0;

                      /*
                        Get sample
                      */
                      switch(channel_bits_per_pixel[channel_index])
                        {
                        case 8:
                          sample = *line[channel_index].u8;
                          line[channel_index].u8++;
                          break;
                        case 16:
                          sample = *line[channel_index].u16;
                          line[channel_index].u16++;
                          break;
                        case 32:
                          sample = *line[channel_index].u32;
                          line[channel_index].u32++;
                          break;
                        }

                      /*
                        Scale sample to quantum
                      */
                      if (channel_bits_per_pixel_range[channel_index] == 8)
                        {
                          quantum=ScaleCharToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 8)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] == 16)
                        {
                          quantum=ScaleShortToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 16)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] == 32)
                        {
                          quantum=ScaleLongToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 32)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }

                      /*
                        Assign quantum to PixelPacket
                      */
                      switch (channel_index)
                        {
                        case 0:
                          SetRedSample(q,quantum);
                          if (num_channels != 4)
                            SetOpacitySample(q,OpaqueOpacity);
                          break;
                        case 1:
                          SetGreenSample(q,quantum);
                          break;
                        case 2:
                          SetBlueSample(q,quantum);
                          break;
                        case 3:
                          SetOpacitySample(q,MaxRGB-quantum);
                          break;
                        }
                    }
                  q++;
                }
              if (!SyncImagePixelsEx(image,exception))
                {
                  HEIFReadImageFrameCleanup();
                  return MagickFail;
                }
            }
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "  done!");

        }
        break;
      case heif_colorspace_monochrome:
        {
          /*
            Decode Y(A) pixels
          */
          static const enum heif_channel channels_YA[4] =
            { heif_channel_Y, heif_channel_Alpha };

          magick_plane_t
            planes[2];

          magick_plane_t
            line[2];

          size_t
            row_stride[2];

          int
            channel_bits_per_pixel[2];

          int
            channel_bits_per_pixel_range[2];

          unsigned long
            channel_max_value_given_bits[2];

          unsigned int
            channel_index,
            num_channels;

          enum heif_channel heif_channel;

          num_channels = image->matte ? 2 : 1;

          assert(heif_image_get_chroma_format(heif_image) == heif_chroma_monochrome);

          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Decoding %u plane%s for monochrome colorspace (chroma %s)",
                                  num_channels, num_channels > 1 ? "s" : "", heif_chroma_format_str);

          for (channel_index = 0; channel_index < num_channels; channel_index++)
            {
              heif_channel = channels_YA[channel_index];
              heif_channel_str = HEIF_channel_to_string(heif_channel);
              planes[channel_index].u8 = heif_image_get_plane_readonly2(heif_image,
                                                                        heif_channel,
                                                                        &row_stride[channel_index]);
              if (planes[channel_index].u8 == (const uint8_t*) NULL)
                {
                  if (image->logging)
                    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                          "heif_image_get_plane_readonly2() returned NULL"
                                          " for channel index %u (channel %s)!",
                                          channel_index,heif_channel_str);
                  ThrowHEIFThrowReadImageFrameException(CorruptImageError,
                                                        AnErrorHasOccurredReadingFromFile, image);
                }
              channel_bits_per_pixel[channel_index] = heif_image_get_bits_per_pixel(heif_image,
                                                                                    heif_channel);
              channel_bits_per_pixel_range[channel_index] = heif_image_get_bits_per_pixel_range(heif_image,
                                                                                                heif_channel);
              channel_max_value_given_bits[channel_index] = MaxValueGivenBits(channel_bits_per_pixel_range[channel_index]);
              if ((int) image->depth < channel_bits_per_pixel_range[channel_index])
                image->depth=(unsigned int) channel_bits_per_pixel_range[channel_index];
              heif_channel_str = HEIF_channel_to_string(heif_channel);
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "  channel %s row stride %zu (%d bits in %d bit quantum)",
                                      heif_channel_str, row_stride[channel_index],
                                      channel_bits_per_pixel_range[channel_index],
                                      channel_bits_per_pixel[channel_index]);
            }

          /* Transfer pixels to image, using row stride to find start of each row. */
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Transferring pixels to magick image...");
          for (y=0; y < (long)image->rows; y++)
            {
              q=SetImagePixelsEx(image,0,y,image->columns,1,exception);
              if (q == (PixelPacket *) NULL)
                {
                  HEIFReadImageFrameCleanup();
                  return MagickFail;
                }
              for (channel_index = 0; channel_index < num_channels; channel_index++)
                line[channel_index].u8=planes[channel_index].u8+y*row_stride[channel_index];
              for (x=0; x < (long)image->columns; x++)
                {
                  for (channel_index = 0; channel_index < num_channels; channel_index++)
                    {
                      uint32_t
                        sample = 0;

                      Quantum
                        quantum=0;

                      /*
                        Get sample
                      */
                      switch(channel_bits_per_pixel[channel_index])
                        {
                        case 8:
                          sample = *line[channel_index].u8;
                          line[channel_index].u8++;
                          break;
                        case 16:
                          sample = *line[channel_index].u16;
                          line[channel_index].u16++;
                          break;
                        case 32:
                          sample = *line[channel_index].u32;
                          line[channel_index].u32++;
                          break;
                        }

                      /*
                        Scale sample to quantum
                      */
                      if (channel_bits_per_pixel_range[channel_index] == 8)
                        {
                          quantum=ScaleCharToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 8)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] == 16)
                        {
                          quantum=ScaleShortToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 16)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] == 32)
                        {
                          quantum=ScaleLongToQuantum(sample);
                        }
                      else if (channel_bits_per_pixel_range[channel_index] < 32)
                        {
                          quantum=ScaleAnyToQuantum(sample,channel_max_value_given_bits[channel_index]);
                        }

                      /*
                        Assign quantum to PixelPacket
                      */
                      switch (channel_index)
                        {
                        case 0:
                          SetGraySample(q,quantum);
                          if (num_channels != 2)
                            SetOpacitySample(q,OpaqueOpacity);
                          break;
                        case 1:
                          SetOpacitySample(q,MaxRGB-quantum);
                          break;
                        }
                    }
                  q++;
                }
              if (!SyncImagePixelsEx(image,exception))
                {
                  HEIFReadImageFrameCleanup();
                  return MagickFail;
                }
            }
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "  done!");
        }
        break;
      case heif_colorspace_nonvisual:
        /* No visual channels */
      default:
        /* Should never reach here. */
        break;
      }
  }

  HEIFReadImageFrameCleanup();

  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Image depth: %u", image->depth);

  return MagickPass;
}

static Image *ReadHEIFImage(const ImageInfo *image_info,
                            ExceptionInfo *exception)
{
  Image
    *image;

  struct heif_context
    *heif = NULL;

  struct heif_image_handle
    *heif_image_handle = NULL;

  struct heif_image
    *heif_image = NULL;

  struct heif_decoding_options
    *decode_options = NULL;

  const char
    *value;

  unsigned char
    *in_buf = NULL;

  heif_item_id
    *item_ids = NULL;

  const char *
    magick;

  size_t
    in_len = 0;

  struct heif_error
    heif_status;

  int
#if defined(HEIF_SUPPORT_SEQUENCES) && HEIF_SUPPORT_SEQUENCES
    has_sequence,
#endif /* if defined(HEIF_SUPPORT_SEQUENCES) && HEIF_SUPPORT_SEQUENCES */
    number_of_top_level_images;

  char
    fourcc[5];

  heif_item_id
    primary_image_id;

#if HEIF_ENABLE_PROGRESS_MONITOR
  ProgressUserData
    progress_user_data;
#endif

  MagickBool
    in_buf_allocated=MagickFalse;

  MagickPassFail
    status;

  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);

  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "ImageInfo magick = %s", image_info->magick);
  /*
    Open image file.
  */
  image=AllocateImage(image_info);
  if (image == (Image *) NULL)
    ThrowReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  if (OpenBlob(image_info,image,ReadBinaryBlobMode,exception) == MagickFail)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);

  if (!heif_initialized)
    {
      /* heif_init() accepts a 'struct heif_init_params *' argument */
      heif_init((struct heif_init_params *) NULL);
      heif_initialized = MagickTrue;
    }


  /* Add decoding options support */
  decode_options = heif_decoding_options_alloc();
  if (decode_options == (struct heif_decoding_options*) NULL)
    ThrowHEIFReaderException(ResourceLimitError,MemoryAllocationFailed,image);

  decode_options->ignore_transformations = image_info->ping ? MagickTrue : MagickFalse;
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                        "Initial ignore_transformations = %s",
                        decode_options->ignore_transformations ? "True" : "False");
#if HEIF_ENABLE_PROGRESS_MONITOR
  progress_user_data.exception = exception;
  progress_user_data.image = image;
  progress_user_data.max_progress = 0;
  progress_user_data.progress = 0;
#endif

#if HEIF_ENABLE_PROGRESS_MONITOR
  decode_options->start_progress = start_progress;
  decode_options->on_progress = on_progress;
  decode_options->end_progress = end_progress;
  decode_options->progress_user_data = &progress_user_data;
#endif /* if HEIF_ENABLE_PROGRESS_MONITOR */

  /* version 2 decode options */

  /* Let libheif do the scaling from deep images if QuantumDepth == 8 */
#if QuantumDepth == 8
  decode_options->convert_hdr_to_8bit = 1;
#endif /* if QuantumDepth == 8 */


  in_len=GetBlobSize(image);
  in_buf=GetBlobStreamData(image);
  if (in_buf == (unsigned char *) NULL)
    {
      /*
        Read the whole input file into a memory blob
      */
     in_buf=MagickAllocateResourceLimitedArray(unsigned char *,in_len,sizeof(*in_buf));
      if (in_buf == (unsigned char *) NULL)
        ThrowHEIFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
      in_buf_allocated=MagickTrue;

      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Reading file into in-memory blob...");
      if (ReadBlob(image,in_len,in_buf) != in_len)
        ThrowHEIFReaderException(CorruptImageError, UnexpectedEndOfFile, image);
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "  Done!");
    }
  else
    {
      /*
        Accessing memory-mapped input file or blob memory directly.
      */
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Input accessed as in-memory blob");
    }

  /* Init HEIF-Decoder handles */
  heif=heif_context_alloc();

  /* Apply security limits */
  (void) apply_security_limits(image_info,heif);

  /* Header sanity check */
  if (!IsHEIF(in_buf, in_len))
    ThrowHEIFReaderException(CorruptImageError, ImproperImageHeader, image);

  /* Test file header for format, and update image magick string */
  magick="HEIF";
  if (heif_has_compatible_brand(in_buf, in_len, "avci") == 1)
    magick="AVCI";
  else if (heif_has_compatible_brand(in_buf, in_len, "avif") == 1)
    magick="AVIF";
  else if (heif_has_compatible_brand(in_buf, in_len, "heix") == 1)
    magick="HEIC";
  else if (heif_has_compatible_brand(in_buf, in_len, "heic") == 1)
    magick="HEIC";
  else if (heif_has_compatible_brand(in_buf, in_len, "mp41") == 1)
    magick="MP4";
  else if (heif_has_compatible_brand(in_buf, in_len, "mp42") == 1)
    magick="MP4";
  (void) strlcpy(image->magick,magick,sizeof(image->magick));
   if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Assigned magick: %s", magick);

  /*
    Trace some information about the file
  */
  if (image->logging)
    {
      {
        /* Log main brand */
        (void) memset(fourcc,0,sizeof(fourcc));
        heif_brand_to_fourcc(heif_read_main_brand(in_buf, in_len), fourcc);
        fourcc[4]=0;
        if (fourcc[0] == 0)
          {
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Failed to read main brand!");
          }
        else
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                "HEIF Brand: \"%s\"", fourcc);
      }
      {
        /* Log compatible brands */
        heif_brand2* brands = NULL;
        int nBrands = 0;
        heif_status = heif_list_compatible_brands(in_buf, in_len, &brands, &nBrands);
        if (heif_status.code == heif_error_Ok)
          {
            char
              *compatible_brands;

            const size_t
              compatible_brands_alloc = 6*(nBrands+1);

            compatible_brands=MagickAllocateClearedMemory(char *,compatible_brands_alloc);
            if (compatible_brands == (char *) NULL)
              ThrowHEIFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
            {
              int
                i;

              for (i = 0; i < nBrands; i++)
                {
                  heif_brand_to_fourcc(brands[i], fourcc);
                  fourcc[4]=0;
                  if (i > 0)
                    (void) strlcat(compatible_brands,", ",compatible_brands_alloc);
                  (void) strlcat(compatible_brands,fourcc,compatible_brands_alloc);
                }
            }
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Compatible HEIF brands: %s", compatible_brands);
            MagickFreeMemory(compatible_brands);
          }
        else
          {
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Failed to read compatible HEIF brands!");
          }
        heif_free_list_of_compatible_brands(brands);
      }
      {
        /* Log MIME type */
        const char *mime_type = heif_get_file_mime_type(in_buf, in_len);
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "MIME Type: %s",
                              mime_type == (const char *) NULL ? "unknown" : mime_type);
      }
    } /* if (image->logging) */

  /*
    Allow the user to enable transformations (e.g. the image might be rotated).
  */
  if ((value=AccessDefinition(image_info,"heif","ignore-transformations")))
    {
      if (LocaleCompare(value,"FALSE") == 0)
        decode_options->ignore_transformations = MagickFalse;
      else if (LocaleCompare(value,"TRUE") == 0)
        decode_options->ignore_transformations = MagickTrue;
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "Updated ignore-transformations: %s",
                              decode_options->ignore_transformations ? "True" : "False");
    }


  heif_status=heif_context_read_from_memory_without_copy(heif, in_buf, in_len, NULL);
  if (heif_status.code == heif_error_Unsupported_filetype
      || heif_status.code == heif_error_Unsupported_feature)
    ThrowHEIFReaderException(CoderError, ImageTypeNotSupported, image);
  if (heif_status.code != heif_error_Ok)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "heif_context_read_from_memory_without_copy() reports error \"%s\"",
                              heif_status.message);
      ThrowHEIFReaderException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
    }

#if defined(HEIF_SUPPORT_SEQUENCES) && HEIF_SUPPORT_SEQUENCES
  has_sequence = heif_context_has_sequence(heif);
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Has sequence: %c", has_sequence ? 'Y' : 'N');
#endif /* if defined(HEIF_SUPPORT_SEQUENCES) && HEIF_SUPPORT_SEQUENCES */

  /* Get the number of top level images */
  number_of_top_level_images=heif_context_get_number_of_top_level_images(heif);
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Number of top level images: %d",
                          number_of_top_level_images);
  if (number_of_top_level_images <= 0)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "heif_context_get_number_of_top_level_images() reports %d \"%s\"",
                              number_of_top_level_images, heif_status.message);
      ThrowHEIFReaderException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
    }

  /* Get the primary image id */
  heif_status=heif_context_get_primary_image_ID(heif,&primary_image_id);
  if (heif_status.code != heif_error_Ok)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "heif_context_get_primary_image_ID() reports error \"%s\"",
                              heif_status.message);
      ThrowHEIFReaderException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
    }
  if (image->logging)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Primary image id: %d", primary_image_id);

  /* Get a handle for the primary image id */
  heif_status=heif_context_get_image_handle(heif, primary_image_id, &heif_image_handle);
  if (heif_status.code == heif_error_Memory_allocation_error)
    ThrowHEIFReaderException(ResourceLimitError, MemoryAllocationFailed, image);
  if (heif_status.code != heif_error_Ok)
    {
      if (image->logging)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                              "heif_context_get_image_handle() reports error \"%s\"",
                              heif_status.message);
      ThrowHEIFReaderException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
    }

  status=ReadHEIFImageFrame(heif_image_handle,decode_options,image,image_info,exception);

  heif_image_handle_release(heif_image_handle);
  heif_image_handle=(struct heif_image_handle *) NULL;

  /*
    Read any additional top-level images
  */
  if ((status != MagickFail) && (number_of_top_level_images > 1))
    {
      int
        item_num;

      item_ids=MagickAllocateResourceLimitedArray(heif_item_id *,number_of_top_level_images,
                                                  sizeof(*item_ids));
      if (item_ids == (heif_item_id *) NULL)
        ThrowHEIFReaderException(ResourceLimitError, MemoryAllocationFailed, image);

      heif_context_get_list_of_top_level_image_IDs(heif,item_ids,number_of_top_level_images);

      for (item_num=0; item_num < number_of_top_level_images; item_num++)
        {
          if (image->logging)
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "Image index %d: image id %d",
                                  item_num, item_ids[item_num]);

          /* Skip the primary image we already read. Hopefully this
             was also the first image in the top level image list. */
          if (item_ids[item_num] == primary_image_id)
            {
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "Item %d matches primary image id %d (skipping)",
                                      item_num, primary_image_id);
              continue;
            }

          /*
            Allocate next image structure.
          */
          AllocateNextImage(image_info,image);
          image=SyncNextImageInList(image);
          (void) strlcpy(image->magick,magick,sizeof(image->magick));

          /* Get HEIF image handle */
          heif_status=heif_context_get_image_handle(heif, item_ids[item_num],&heif_image_handle);
          if (heif_status.code == heif_error_Memory_allocation_error)
            ThrowHEIFReaderException(ResourceLimitError, MemoryAllocationFailed, image);
          if (heif_status.code != heif_error_Ok)
            {
              if (image->logging)
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "heif_context_get_image_handle() reports error \"%s\"",
                                      heif_status.message);
              ThrowHEIFReaderException(CorruptImageError, AnErrorHasOccurredReadingFromFile, image);
            }

          /* Read the HEIF frame */
          status=ReadHEIFImageFrame(heif_image_handle,decode_options,image,image_info,exception);

          /* Release the HEIF image handle */
          heif_image_handle_release(heif_image_handle);
          heif_image_handle=(struct heif_image_handle *) NULL;

          if (status == MagickFail)
            break;

          /* Quit if no more scenes requested */
          if (image_info->subrange != 0)
            if (image->scene >= (image_info->subimage+image_info->subrange-1))
              break;
        }
      MagickFreeResourceLimitedMemory(heif_item_id *,item_ids);
    }

  HEIFReadCleanup();
  CloseBlob(image);
  if (status == MagickFail)
    {
      DestroyImageList(image);
      image=(Image *) NULL;
    }

  return image;
}

#endif /* HasHEIF */

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r H E I F I m a g e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterHEIFImage adds attributes for the HEIF image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format and a brief
%  description of the format.
%
%  The format of the RegisterHEIFImage method is:
%
%      RegisterHEIFImage(void)
%
*/
ModuleExport void RegisterHEIFImage(void)
{
#if defined(HasHEIF)
  static char
    version[20];

  static const MagickBool
    need_seekable_stream=MagickFalse; /* Currently use in memory blob */

  MagickInfo
    *entry;

  unsigned int
    heif_major,
    heif_minor,
    heif_revision;

  int encoder_version=heif_get_version_number();
  heif_major=(encoder_version >> 16) & 0xff;
  heif_minor=(encoder_version >> 8) & 0xff;
  heif_revision=encoder_version & 0xff;
  *version='\0';
  (void) snprintf(version, sizeof(version),
                  "heif v%u.%u.%u", heif_major,
                  heif_minor, heif_revision);

  /* AVCI (H.264) */
  if (heif_have_decoder_for_format(heif_compression_AVC)/* || */
      /* heif_have_encoder_for_format(heif_compression_AVC) */)
    {
      entry=SetMagickInfo("AVCI");
      entry->decoder=(DecoderHandler) ReadHEIFImage;
      entry->magick=(MagickHandler) IsHEIF;
      entry->description="Advanced Video Coding Image Format";
      entry->adjoin=MagickFalse;
      entry->seekable_stream=need_seekable_stream;
      if (*version != '\0')
        entry->version=version;
      entry->module="HEIF";
      entry->coder_class=PrimaryCoderClass;
      entry->extension_treatment=ObeyExtensionTreatment;
      (void) RegisterMagickInfo(entry);
    }

  /* AVIF / heif_compression_AV1 */
  if (heif_have_decoder_for_format(heif_compression_AV1)/* || */
      /* heif_have_encoder_for_format(heif_compression_AV1) */)
    {
      entry=SetMagickInfo("AVIF");
      entry->decoder=(DecoderHandler) ReadHEIFImage;
      entry->magick=(MagickHandler) IsHEIF;
      entry->description="AV1 Image Format";
      entry->adjoin=MagickFalse;
      entry->seekable_stream=need_seekable_stream;
      if (*version != '\0')
        entry->version=version;
      entry->module="HEIF";
      entry->coder_class=PrimaryCoderClass;
      entry->extension_treatment=ObeyExtensionTreatment;
      (void) RegisterMagickInfo(entry);
    }

  /*
    This entry is used for anything which looks like HEIF, but is not
    one of our directly supported subformats.
  */
  entry=SetMagickInfo("HEIF");
  entry->decoder=(DecoderHandler) ReadHEIFImage;
  entry->magick=(MagickHandler) IsHEIF;
  entry->description="High Efficiency Image Format";
  entry->adjoin=MagickFalse;
  entry->seekable_stream=need_seekable_stream;
  if (*version != '\0')
    entry->version=version;
  entry->module="HEIF";
  entry->coder_class=PrimaryCoderClass;
  entry->extension_treatment=ObeyExtensionTreatment;
  (void) RegisterMagickInfo(entry);

  /* HEIC (H.265) / heif_compression_HEVC */
  if (heif_have_decoder_for_format(heif_compression_HEVC) /* || */
      /* heif_have_encoder_for_format(heif_compression_HEVC) */)
    {
      entry=SetMagickInfo("HEIC");
      entry->decoder=(DecoderHandler) ReadHEIFImage;
      entry->magick=(MagickHandler) IsHEIF;
      entry->description="High-Efficiency Image Codec in HEIF";
      entry->adjoin=MagickFalse;
      entry->seekable_stream=need_seekable_stream;
      if (*version != '\0')
        entry->version=version;
      entry->module="HEIF";
      entry->coder_class=PrimaryCoderClass;
      entry->extension_treatment=ObeyExtensionTreatment;
      (void) RegisterMagickInfo(entry);

      /* Libheif supports some MP4 files */
      entry=SetMagickInfo("MP4");
      entry->decoder=(DecoderHandler) ReadHEIFImage;
      entry->magick=(MagickHandler) IsHEIF;
      entry->description="MPEG-4 Part 14 in HEIF";
      entry->adjoin=MagickFalse;
      entry->seekable_stream=need_seekable_stream;
      if (*version != '\0')
        entry->version=version;
      entry->module="HEIF";
      entry->coder_class=PrimaryCoderClass;
      entry->extension_treatment=ObeyExtensionTreatment;
      (void) RegisterMagickInfo(entry);
    }

  /* MP4 (H.264, H.265) / heif_compression_HEVC */
  /*
    Since HEIF image sequences are very similar to MP4 video, libheif
    can also read and write MP4 video (without audio) with all
    supported codecs.

    heif_context_has_sequence() will return if input is a sequence.
    Note that a file can contain still images and a sequence at the
    same time.

    heif_compression_HEVC is H.265, heif_compression_AVC is H.264, and
    heif_compression_AV1 is AV1

    video/mp4 or application/mp4
  */
#if 0
  if (heif_have_decoder_for_format(heif_compression_HEVC) ||
      heif_have_decoder_for_format(heif_compression_AVC) ||
      heif_have_decoder_for_format(heif_compression_AV1))
    {
      entry=SetMagickInfo("MP4");
      entry->decoder=(DecoderHandler) ReadHEIFImage;
      entry->magick=(MagickHandler) IsHEIF;
      entry->description="MP4 video container (HVEC, AVC, or AV1 compression)";
      entry->adjoin=MagickFalse;
      entry->seekable_stream=need_seekable_stream;
      if (*version != '\0')
        entry->version=version;
      entry->module="HEIF";
      entry->coder_class=UnstableCoderClass;
      entry->extension_treatment=HintExtensionTreatment;
      (void) RegisterMagickInfo(entry);
    }
#endif

#endif /* HasHEIF */
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r H E I F I m a g e                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterHEIFImage removes format registrations made by the
%  HEIF module from the list of supported formats.
%
%  The format of the UnregisterHEIFImage method is:
%
%      UnregisterHEIFImage(void)
%
*/
ModuleExport void UnregisterHEIFImage(void)
{
#if defined(HasHEIF)
  (void) UnregisterMagickInfo("AVCI");
  (void) UnregisterMagickInfo("AVIF");
  (void) UnregisterMagickInfo("HEIC");
  (void) UnregisterMagickInfo("HEIF");
  (void) UnregisterMagickInfo("MP4");
  if (heif_initialized)
    heif_deinit();
#endif /* HasHEIF */
}
