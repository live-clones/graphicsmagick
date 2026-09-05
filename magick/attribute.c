/*
% Copyright (C) 2003-2026 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%        AAA   TTTTT  TTTTT  RRRR   IIIII  BBBB   U   U  TTTTT  EEEEE         %
%       A   A    T      T    R   R    I    B   B  U   U    T    E             %
%       AAAAA    T      T    RRRR     I    BBBB   U   U    T    EEE           %
%       A   A    T      T    R R      I    B   B  U   U    T    E             %
%       A   A    T      T    R  R   IIIII  BBBB    UUU     T    EEEEE         %
%                                                                             %
%                                                                             %
%              Methods to Get/Set/Destroy Image Text Attributes               %
%                                                                             %
%                                                                             %
%                             Software Design                                 %
%                               John Cristy                                   %
%                              February 2000                                  %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  The Attributes methods gets, sets, or destroys attributes associated
%  with a particular image (e.g. comments, copyright, author, etc).
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/log.h"
#include "magick/profile.h"
#include "magick/render.h"
#include "magick/tempfile.h"
#include "magick/utility.h"

/*
  Forward declarations.
*/
static void DestroyImageAttribute(ImageAttribute *attribute);

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C l o n e I m a g e A t t r i b u t e s                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CloneImageAttributes() copies the text attributes from one image to another.
%  Any text attributes in the destination image are preserved.
%  CloneImageAttributes returns MagickPass if all of the attribututes are
%  successfully cloned or MagickFail if there is a memory allocation error.
%
%  The format of the CloneImageAttributes method is:
%
%      MagickPassFail CloneImageAttributes(Image* clone_image,
%                                          const Image* original_image)
%
%  A description of each parameter follows:
%
%    o clone_image: The destination image.
%
%    o original_image: The source image.
%
%
*/
MagickExport MagickPassFail
CloneImageAttributes(Image* clone_image,
                     const Image* original_image)
{
  MagickPassFail
    status;

  ImageAttribute
    *cloned_attribute,
    *cloned_attributes;

  const ImageAttribute
    *attribute;

  status = MagickPass;

  /*
    Search for tail of list (if any)
  */
  if ((cloned_attributes=clone_image->attributes))
    {
      for( ;
          cloned_attributes->next != (ImageAttribute *) NULL;
          cloned_attributes=cloned_attributes->next);
    }

  attribute=GetImageAttribute(original_image,(char *) NULL);
  for ( ; attribute != (const ImageAttribute *) NULL;
        attribute=attribute->next)
    {
      /*
        Construct AttributeInfo to append.
      */
      cloned_attribute=MagickAllocateMemory(ImageAttribute *,
                                            sizeof(ImageAttribute));
      if (cloned_attribute == (ImageAttribute *) NULL)
        {
          status = MagickFail;
          break;
        }
      cloned_attribute->key=AcquireString(attribute->key);
      cloned_attribute->length=attribute->length;
      cloned_attribute->value=
        MagickAllocateMemory(char *,cloned_attribute->length+1);
      cloned_attribute->previous=(ImageAttribute *) NULL;
      cloned_attribute->next=(ImageAttribute *) NULL;
      if ((cloned_attribute->value == (char *) NULL) ||
          (cloned_attribute->key == (char *) NULL))
        {
          DestroyImageAttribute(cloned_attribute);
          status = MagickFail;
          break;
        }
      (void) strlcpy(cloned_attribute->value,attribute->value,cloned_attribute->length+1);

      if (cloned_attributes == (ImageAttribute *) NULL)
        {
          /*
            Start list
          */
          cloned_attributes=cloned_attribute;
          clone_image->attributes=cloned_attributes;
        }
      else
        {
          /*
            Append to list
          */
          cloned_attributes->next=cloned_attribute;
          cloned_attribute->previous=cloned_attributes;
          cloned_attributes=cloned_attribute;
        }
    }

  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D e s t r o y I m a g e A t t r i b u t e s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyImageAttributes() deallocates memory associated with the image
%  attribute list.
%
%  The format of the DestroyImageAttributes method is:
%
%      DestroyImageAttributes(Image *image)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%
*/
static void
DestroyImageAttribute(ImageAttribute *attribute)
{
  if (attribute == (ImageAttribute *) NULL)
    return;
  MagickFreeMemory(attribute->value);
  MagickFreeMemory(attribute->key);
  (void) memset(attribute,0xbf,sizeof(ImageAttribute));
  MagickFreeMemory(attribute);
}
MagickExport void DestroyImageAttributes(Image *image)
{
  ImageAttribute
    *attribute;

  register ImageAttribute
    *p;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  for (p=image->attributes; p != (ImageAttribute *) NULL; )
    {
      attribute=p;
      p=p->next;
      DestroyImageAttribute(attribute);
    }
  image->attributes=(ImageAttribute *) NULL;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e A t t r i b u t e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImageAttribute() searches the list of image attributes and returns
%  a pointer to the attribute if it exists otherwise NULL.
%
%  The format of the GetImageAttribute method is:
%
%      const ImageAttribute *GetImageAttribute(const Image *image,
%        const char *key)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o key:  These character strings are the name of an image attribute to
%      return.
%
%
*/

static unsigned int
GenerateIPTCAttribute(Image *image,const char *key)
{
#if 0
  static const struct
  {
    char *name;
    int   dataset;
    int   record;
  }
#define IPTC_ATTRIBUTE(dataset,record,name) {name,dataset,record}
  IPTCAttributes[] =
  {
    IPTC_ATTRIBUTE(2,5,"Image Name"),
    IPTC_ATTRIBUTE(2,7,"Edit Status"),
    IPTC_ATTRIBUTE(2,10,"Priority"),
    IPTC_ATTRIBUTE(2,15,"Category"),
    IPTC_ATTRIBUTE(2,20,"Supplemental Category"),
    IPTC_ATTRIBUTE(2,22,"Fixture Identifier"),
    IPTC_ATTRIBUTE(2,25,"Keyword"),
    IPTC_ATTRIBUTE(2,30,"Release Date"),
    IPTC_ATTRIBUTE(2,35,"Release Time"),
    IPTC_ATTRIBUTE(2,40,"Special Instructions"),
    IPTC_ATTRIBUTE(2,45,"Reference Service"),
    IPTC_ATTRIBUTE(2,47,"Reference Date"),
    IPTC_ATTRIBUTE(2,50,"Reference Number"),
    IPTC_ATTRIBUTE(2,55,"Created Date"),
    IPTC_ATTRIBUTE(2,60,"Created Time"),
    IPTC_ATTRIBUTE(2,65,"Originating Program"),
    IPTC_ATTRIBUTE(2,70,"Program Version"),
    IPTC_ATTRIBUTE(2,75,"Object Cycle"),
    IPTC_ATTRIBUTE(2,80,"Byline"),
    IPTC_ATTRIBUTE(2,85,"Byline Title"),
    IPTC_ATTRIBUTE(2,90,"City"),
    IPTC_ATTRIBUTE(2,95,"Province State"),
    IPTC_ATTRIBUTE(2,100,"Country Code"),
    IPTC_ATTRIBUTE(2,101,"Country"),
    IPTC_ATTRIBUTE(2,103,"Original Transmission Reference"),
    IPTC_ATTRIBUTE(2,105,"Headline"),
    IPTC_ATTRIBUTE(2,110,"Credit"),
    IPTC_ATTRIBUTE(2,115,"Source"),
    IPTC_ATTRIBUTE(2,116,"Copyright String"),
    IPTC_ATTRIBUTE(2,120,"Caption"),
    IPTC_ATTRIBUTE(2,121,"Local Caption"),
    IPTC_ATTRIBUTE(2,122,"Caption Writer"),
    IPTC_ATTRIBUTE(2,200,"Custom Field 1"),
    IPTC_ATTRIBUTE(2,201,"Custom Field 2"),
    IPTC_ATTRIBUTE(2,202,"Custom Field 3"),
    IPTC_ATTRIBUTE(2,203,"Custom Field 4"),
    IPTC_ATTRIBUTE(2,204,"Custom Field 5"),
    IPTC_ATTRIBUTE(2,205,"Custom Field 6"),
    IPTC_ATTRIBUTE(2,206,"Custom Field 7"),
    IPTC_ATTRIBUTE(2,207,"Custom Field 8"),
    IPTC_ATTRIBUTE(2,208,"Custom Field 9"),
    IPTC_ATTRIBUTE(2,209,"Custom Field 10"),
    IPTC_ATTRIBUTE(2,210,"Custom Field 11"),
    IPTC_ATTRIBUTE(2,211,"Custom Field 12"),
    IPTC_ATTRIBUTE(2,212,"Custom Field 13"),
    IPTC_ATTRIBUTE(2,213,"Custom Field 14"),
    IPTC_ATTRIBUTE(2,214,"Custom Field 15"),
    IPTC_ATTRIBUTE(2,215,"Custom Field 16"),
    IPTC_ATTRIBUTE(2,216,"Custom Field 17"),
    IPTC_ATTRIBUTE(2,217,"Custom Field 18"),
    IPTC_ATTRIBUTE(2,218,"Custom Field 19"),
    IPTC_ATTRIBUTE(2,219,"Custom Field 20")
  };
#endif

  const unsigned char
    *profile;

  char
    *attribute;

  size_t
    attribute_length,
    profile_length;

  register long
    i;

  int
    count,
    dataset,
    record;

  MagickPassFail
    status = MagickFail;

  if ((profile=GetImageProfile(image,"IPTC",&profile_length)) == 0)
    return(MagickFail);
  if (profile_length < 5U)
    {
      if (image->logging)
        LogMagickEvent(TransformEvent,GetMagickModule(),
                       "IPTC profile is too short (%zu)!",
                       profile_length);
      return(MagickFail);
    }
  count=sscanf(key,"IPTC:%d:%d",&dataset,&record);
  if (count != 2)
    return(MagickFail);
  for (i=0; i < (long) profile_length; i++)
    {
      if (profile[i] != 0x1cU)
        continue;
      if ((profile_length - (size_t) i) < 5U)
        {
          LogMagickEvent(TransformEvent,GetMagickModule(),
                         "IPTC profile, remaining length is too short!");
          return(MagickFail);
        }
      if (profile[i+1] != dataset)
        {
          /* fprintf(stderr,"Skipping dataset %d\n",profile[i+1]); */
          continue;
        }
      if (profile[i+2] != record)
        {
          /* fprintf(stderr,"Skipping record %d\n",profile[i+2]); */
          continue;
        }
      attribute_length=(size_t) profile[i+3] << 8;
      attribute_length|=(size_t) profile[i+4];
      if (0 == attribute_length)
        {
          LogMagickEvent(TransformEvent,GetMagickModule(),
                         "IPTC profile attribute has zero length!");
          continue;
        }
      else if (attribute_length >= (profile_length - (size_t) i - 5U))
        {
          LogMagickEvent(TransformEvent,GetMagickModule(),
                         "IPTC profile attribute extends beyond profile bounds!");
          continue;
        }
      attribute_length += 1;
      attribute=MagickAllocateResourceLimitedMemory(char *,attribute_length);
      if (attribute == (char *) NULL)
        {
          LogMagickEvent(TransformEvent,GetMagickModule(),
                         "IPTC profile, failed to allocate %zu bytes!", attribute_length);
          continue;
        }
      (void) strlcpy(attribute,(char *) profile+(size_t)i+5U,attribute_length);
      status = SetImageAttribute(image,key,(const char *) attribute);
      MagickFreeResourceLimitedMemory(char *,attribute);
      break;
    }
  return status;
}

static unsigned char
ReadByte(unsigned char **p,size_t *length)
{
  unsigned char
    c;

  if (*length < 1)
    return(0xff);
  c=(*(*p)++);
  (*length)--;
  return(c);
}

static magick_int32_t
ReadMSBLong(unsigned char **p,size_t *length)
{
  int
    c;

  union
  {
    magick_uint32_t u;
    magick_int32_t s;
  } value;

  register unsigned int
    i;

  unsigned char
    buffer[4];

  if (*length < 4)
    return(-1);
  for (i=0; i < 4; i++)
  {
    c=(*(*p)++);
    (*length)--;
    buffer[i]=(unsigned char) c;
  }
  value.u=(magick_uint32_t) (buffer[0] & 0xff) << 24;
  value.u|=(magick_uint32_t) buffer[1] << 16;
  value.u|=(magick_uint32_t) buffer[2] << 8;
  value.u|=(magick_uint32_t) buffer[3];
  return(value.s);
}

static magick_int32_t
ReadMSBShort(unsigned char **p,size_t *length)
{
  int
    c;

  union
  {
    magick_uint32_t u;
    magick_int32_t s;
  } value;

  register unsigned int
    i;

  unsigned char
    buffer[2];

  if (*length < 2)
    return(-1);
  for (i=0; i < 2; i++)
  {
    c=(*(*p)++);
    (*length)--;
    buffer[i]=(unsigned char) c;
  }
  value.u=(magick_uint32_t) (buffer[0] & 0xff) << 8;
  value.u|=(magick_uint32_t) buffer[1];
  return(value.s);
}

/*
  Advance 'blob' by 'amount' or the amount remaining in 'length'.
  Decrement 'length' by 'amount' or to zero.
*/
static inline size_t AdvanceBlob(const size_t amount, size_t length, unsigned char **blob)
{
  if (length > amount)
    {
      *blob+=amount;
      length-=amount;
    }
  else
    {
      *blob+=length;
      length=0U;
    }
  return length;
}

static char *
TracePSClippingPath(unsigned char *blob,size_t length,
                    const unsigned long columns,
                    const unsigned long rows)
{
  char
    *path,
    *message;

  int
    knot_count,
    selector;

  long
    x,
    y;

  PointInfo
    first[3],       /* First Bezier knot in sub-path */
    last[3],        /* Last seen Bezier knot in sub-path */
    point[3];       /* Current Bezier knot in sub-path */

  register long
    i;

  unsigned int
    in_subpath;

  ARG_NOT_USED(columns);
  ARG_NOT_USED(rows);

  first[0].x=first[0].y=first[1].x=first[1].y=0;
  last[1].x=last[1].y=last[2].x=last[2].y=0;
  path=AllocateString((char *) NULL);
  if (path == (char *) NULL)
    return((char *) NULL);
  message=AllocateString((char *) NULL);

  MagickFormatString(message,MaxTextExtent,"/ClipImage {\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"/c {curveto} bind def\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"/l {lineto} bind def\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"/m {moveto} bind def\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"/v {currentpoint 6 2 roll curveto} bind def\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"/y {2 copy curveto} bind def\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"/z {closepath} bind def\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"newpath\n");
  (void) ConcatenateString(&path,message);

  knot_count=0;
  in_subpath=False;

  /*
    Open and closed subpaths are all closed in the following
    parser loop as there's no way for the polygon renderer
    to render an open path to a masking image.

    The clipping path format is defined in "Adobe Photoshop File
    Formats Specification" version 6.0 downloadable from adobe.com.
  */
  while (length > 0)
    {
      selector=ReadMSBShort(&blob,&length);
      switch (selector)
        {
        case 0:
        case 3:
          {
            if (knot_count == 0)
              {
                /*
                  Expected subpath length record
                */
                knot_count=ReadMSBShort(&blob,&length);
                length=AdvanceBlob(22U,length,&blob);
              }
            else
              {
                length=AdvanceBlob(24U,length,&blob);
              }
            break;
          }
        case 1:
        case 2:
        case 4:
        case 5:
          {
            if (knot_count == 0)
              {
                /*
                  Unexpected subpath knot
                */
                length=AdvanceBlob(24U,length,&blob);
              }
            else
              {
                /*
                  Add sub-path knot
                */
                for (i=0; i < 3; i++)
                  {
                    y=ReadMSBLong(&blob,&length);
                    x=ReadMSBLong(&blob,&length);
                    point[i].x=(double) x/4096/4096;
                    point[i].y=1.0-(double) y/4096/4096;
                  }
                if (!in_subpath)
                  {
                    MagickFormatString(message,MaxTextExtent,"%.6f %.6f m\n",
                                 point[1].x,point[1].y);
                    for (i=0; i < 3; i++)
                      {
                        first[i]=point[i];
                        last[i]=point[i];
                      }
                  }
                else
                  {
                    /*
                      Handle special cases when Bezier curves are used
                      to describe corners and straight lines. This
                      special handling is desirable to bring down the
                      size in bytes of the clipping path data.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (point[0].x == point[1].x) &&
                        (point[0].y == point[1].y))
                      {
                        /*
                          First control point equals first anchor
                          point and last control point equals last
                          anchor point. Straight line between anchor
                          points.
                        */
                        MagickFormatString(message,MaxTextExtent,"%.6f %.6f l\n",
                                     point[1].x,point[1].y);
                      }
                    else if ((last[1].x == last[2].x) &&
                             (last[1].y == last[2].y))
                      {
                        /* First control point equals first anchor point */
                        MagickFormatString(message,MaxTextExtent,"%.6f %.6f %.6f %.6f v\n",
                                     point[0].x,point[0].y,
                                     point[1].x,point[1].y);
                      }
                    else if ((point[0].x == point[1].x) &&
                             (point[0].y == point[1].y))
                      {
                        /* Last control point equals last anchor point. */
                        MagickFormatString(message,MaxTextExtent,"%.6f %.6f %.6f %.6f y\n",
                                     last[2].x,last[2].y,
                                     point[1].x,point[1].y);
                      }
                    else
                      {
                        /* The full monty */
                        MagickFormatString(message,MaxTextExtent,
                                     "%.6f %.6f %.6f %.6f %.6f %.6f c\n",
                                     last[2].x,last[2].y,point[0].x,
                                     point[0].y,point[1].x,
                                     point[1].y);
                      }
                    for (i=0; i < 3; i++)
                      last[i]=point[i];
                  }
                (void) ConcatenateString(&path,message);
                in_subpath=True;
                knot_count--;
                /*
                  Close the subpath if there are no more knots.
                */
                if (knot_count == 0)
                  {
                    /*
                      Same special handling as above except we compare
                      to the first point in the path and close the
                      path.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (first[0].x == first[1].x) &&
                        (first[0].y == first[1].y))
                      {
                        MagickFormatString(message,MaxTextExtent,"%.6f %.6f l z\n",
                                     first[1].x,first[1].y);
                      }
                    else if ((last[1].x == last[2].x) &&
                             (last[1].y == last[2].y))
                      {
                        MagickFormatString(message,MaxTextExtent,"%.6f %.6f %.6f %.6f v z\n",
                                     first[0].x,first[0].y,
                                     first[1].x,first[1].y);
                      }
                    else if ((first[0].x == first[1].x) &&
                             (first[0].y == first[1].y))
                      {
                        MagickFormatString(message,MaxTextExtent,"%.6f %.6f %.6f %.6f y z\n",
                                     last[2].x,last[2].y,
                                     first[1].x,first[1].y);
                      }
                    else
                      {
                        MagickFormatString(message,MaxTextExtent,
                                     "%.6f %.6f %.6f %.6f %.6f %.6f c z\n",
                                     last[2].x,last[2].y,
                                     first[0].x,first[0].y,
                                     first[1].x,first[1].y);
                      }
                    (void) ConcatenateString(&path,message);
                    in_subpath=False;
                  }
              }
            break;
          }
        case 6:
        case 7:
        case 8:
        default:
          {
            length=AdvanceBlob(24U,length,&blob);
            break;
          }
        }
    }
  /*
    Returns an empty PS path if the path has no knots.
  */
  MagickFormatString(message,MaxTextExtent,"eoclip\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"} bind def");
  (void) ConcatenateString(&path,message);
  MagickFreeMemory(message);
  return(path);
}

static char *
TraceSVGClippingPath(unsigned char *blob,
                     size_t length,
                     const unsigned long columns,
                     const unsigned long rows)
{
  char
    *path,
    *message;

  int
    knot_count,
    selector;

  long
    x,
    y;

  PointInfo
    first[3],
    last[3],
    point[3];

  register long
    i;

  unsigned int
    in_subpath;

  first[0].x=first[0].y=first[1].x=first[1].y=0;
  last[1].x=last[1].y=last[2].x=last[2].y=0;
  path=AllocateString((char *) NULL);
  if (path == (char *) NULL)
    return((char *) NULL);
  message=AllocateString((char *) NULL);

  MagickFormatString(message,MaxTextExtent,"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"<svg width=\"%lu\" height=\"%lu\">\n",columns,rows);
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"<g>\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"<path style=\"fill:#00000000;stroke:#00000000;");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"stroke-width:0;stroke-antialiasing:false\" d=\"\n");
  (void) ConcatenateString(&path,message);

  knot_count=0;
  in_subpath=False;

  /*
    Open and closed subpaths are all closed in the following parser
    loop as there's no way for the polygon renderer to render an open
    path to a masking image.

    The clipping path format is defined in "Adobe Photoshop File
    Formats Specification" version 6.0 downloadable from adobe.com.
  */
  while (length > 0)
    {
      selector=ReadMSBShort(&blob,&length);
      switch (selector)
        {
        case 0:
        case 3:
          {
            if (knot_count == 0)
              {
                /*
                  Expected subpath length record
                */
                knot_count=ReadMSBShort(&blob,&length);
                length=AdvanceBlob(22U,length,&blob);
              }
            else
              {
                length=AdvanceBlob(24U,length,&blob);
              }
            break;
          }
        case 1:
        case 2:
        case 4:
        case 5:
          {
            if (knot_count == 0)
              {
                /*
                  Unexpected subpath knot
                */
                length=AdvanceBlob(24U,length,&blob);
              }
            else
              {
                /*
                  Add sub-path knot
                */
                for (i=0; i < 3; i++)
                  {
                    y=ReadMSBLong(&blob,&length);
                    x=ReadMSBLong(&blob,&length);
                    point[i].x=(double) x*columns/4096.0/4096.0;
                    point[i].y=(double) y*rows/4096.0/4096.0;
                  }
                if (!in_subpath)
                  {
                    MagickFormatString(message,MaxTextExtent,"M %.6f,%.6f\n",
                                 point[1].x,point[1].y);
                    for (i=0; i < 3; i++)
                      {
                        first[i]=point[i];
                        last[i]=point[i];
                      }
                  }
                else
                  {
                    /*
                      Handle special case when Bezier curves are used
                      to describe straight lines.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (point[0].x == point[1].x) &&
                        (point[0].y == point[1].y))
                      {
                        /*
                          First control point equals first anchor
                          point and last control point equals last
                          anchor point. Straight line between anchor
                          points.
                        */
                        MagickFormatString(message,MaxTextExtent,"L %.6f,%.6f\n",
                                     point[1].x,point[1].y);
                      }
                    else
                      {
                        MagickFormatString(message,MaxTextExtent,
                                     "C %.6f,%.6f %.6f,%.6f %.6f,%.6f\n",
                                     last[2].x,last[2].y,
                                     point[0].x,point[0].y,
                                     point[1].x,point[1].y);
                      }
                    for (i=0; i < 3; i++)
                      last[i]=point[i];
                  }
                (void) ConcatenateString(&path,message);
                in_subpath=True;
                knot_count--;
                /*
                  Close the subpath if there are no more knots.
                */
                if (knot_count == 0)
                  {
                    /*
                      Same special handling as above except we compare
                      to the first point in the path and close the
                      path.
                    */
                    if ((last[1].x == last[2].x) &&
                        (last[1].y == last[2].y) &&
                        (first[0].x == first[1].x) &&
                        (first[0].y == first[1].y))
                      {
                        MagickFormatString(message,MaxTextExtent,
                                     "L %.6f,%.6f Z\n",first[1].x,first[1].y);
                      }
                    else
                      {
                        MagickFormatString(message,MaxTextExtent,
                                     "C %.6f,%.6f %.6f,%.6f %.6f,%.6f Z\n",
                                     last[2].x,last[2].y,
                                     first[0].x,first[0].y,
                                     first[1].x,first[1].y);
                        (void) ConcatenateString(&path,message);
                      }
                    in_subpath=False;
                  }
              }
            break;
          }
        case 6:
        case 7:
        case 8:
        default:
          {
            length=AdvanceBlob(24U,length,&blob);
            break;
          }
        }
    }
  /*
    Returns an empty SVG image if the path has no knots.
  */
  MagickFormatString(message,MaxTextExtent,"\"/>\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"</g>\n");
  (void) ConcatenateString(&path,message);
  MagickFormatString(message,MaxTextExtent,"</svg>\n");
  (void) ConcatenateString(&path,message);
  MagickFreeMemory(message);
  return(path);
}

static int
Generate8BIMAttribute(Image *image,const char *key)
{
  char
    *attribute,
    name[MaxTextExtent],
    format[MaxTextExtent],
    *resource;

  int
    id,
    start,
    stop,
    sub_number;

  register long
    i;

  size_t
    length;

  unsigned char
    *info;

  unsigned int
    status;

  long
    count;

  const unsigned char
    *profile;

  size_t
    profile_length;

  if ((profile=GetImageProfile(image,"IPTC",&profile_length)) == 0)
    return(MagickFail);

  /*
    There may be spaces in resource names, but there are no newlines,
    so use a newline as terminator to get the full name.
  */
  count=sscanf(key,"8BIM:%d,%d:%[^\n]\n%[^\n]",&start,&stop,name,format);
  if ((count != 2) && (count != 3) && (count != 4))
    return(MagickFail);
  if (count < 4)
    (void)strlcpy(format,"SVG",sizeof(format));
  if (count < 3)
    *name='\0';
  sub_number=1;
  if (*name == '#')
    sub_number=MagickAtoL(&name[1]);
  sub_number=Max(sub_number,1);
  resource=(char *) NULL;

  status=False;
  length=profile_length;
  /*
    FIXME: following cast should not be necessary but info can't be
    const due to odd function design.
  */
  info=(unsigned char *) profile;

  while ((length > 0) && (status == False))
    {
      if (ReadByte(&info,&length) != '8')
        continue;
      if (ReadByte(&info,&length) != 'B')
        continue;
      if (ReadByte(&info,&length) != 'I')
        continue;
      if (ReadByte(&info,&length) != 'M')
        continue;
      id=ReadMSBShort(&info,&length);
      if (id < start)
        continue;
      if (id > stop)
        continue;
      if (resource != (char *)NULL)
        MagickFreeMemory(resource);
      count=ReadByte(&info,&length);
      if ((count > 0) && ((size_t) count <= length))
        {
          resource=(char *) MagickAllocateMemory(char *,
                                                 (size_t) count+MaxTextExtent);
          if (resource != (char *) NULL)
            {
              for (i=0; i < count; i++)
                resource[i]=(char) ReadByte(&info,&length);
              resource[count]='\0';
            }
        }
      if (!(count & 0x01))
        (void) ReadByte(&info,&length);
      count=ReadMSBLong(&info,&length);
      /*
        ReadMSBLong() can return negative values such as -1 or any
        other negative value.  Make sure that it is in range.
      */
      if ((count < 0) || ((size_t) count > length))
        {
          length=0; /* Quit loop */
          continue;
        }
      if ((*name != '\0') && (*name != '#'))
        {
          if ((resource == (char *) NULL) ||
              (LocaleCompare(name,resource) != 0))
            {
              /*
                No name match, scroll forward and try next resource.
              */
              info+=count;
              length-=count;
              continue;
            }
        }
      if ((*name == '#') && (sub_number != 1))
        {
          /*
            No numbered match, scroll forward and try next resource.
          */
          sub_number--;
          info+=count;
          length-=count;
          continue;
        }
      /*
        We have the resource of interest.
      */
      attribute=(char *) MagickAllocateMemory(char *,
                                              (size_t) count+MaxTextExtent);
      if (attribute != (char *) NULL)
        {
          (void) memcpy(attribute,(char *) info,(size_t) count);
          attribute[count]='\0';
          info+=count;
          length-=count;
          if ((id <= 1999) || (id >= 2999))
            {
              (void) SetImageAttribute(image,key,(const char *) attribute);
            }
          else
            {
              char
                *path;
              if (LocaleCompare("SVG",format) == 0)
                path=TraceSVGClippingPath((unsigned char *) attribute,count,
                                          image->columns,image->rows);
              else
                path=TracePSClippingPath((unsigned char *) attribute,count,
                                         image->columns,image->rows);
              (void) SetImageAttribute(image,key,(const char *) path);
              MagickFreeMemory(path);
            }
          MagickFreeMemory(attribute);
          status=True;
        }
    }
  if (resource != (char *)NULL)
    MagickFreeMemory(resource);
  return(status);
}

#define DE_STACK_SIZE  16
#define EXIF_DELIMITER  "\n"
#define EXIF_NUM_FORMATS  12
#define EXIF_FMT_NOTYPE 0       /* Not yet assigned, unknown */
#define EXIF_FMT_BYTE  1        /* An 8-bit unsigned integer. */
#define EXIF_FMT_ASCII  2       /* An 8-bit byte containing one 7-bit ASCII code. NUL terminated */
#define EXIF_FMT_USHORT  3      /* A 16-bit (2-byte) unsigned integer */
#define EXIF_FMT_ULONG  4       /* A 32-bit (4-byte) unsigned intege */
#define EXIF_FMT_URATIONAL  5   /* Two LONGs. The first LONG is the numerator and the second LONG expresses the denominator. */
#define EXIF_FMT_SBYTE  6
#define EXIF_FMT_UNDEFINED  7   /* An 8-bit byte that may take any value depending on the field definition. */
#define EXIF_FMT_SSHORT  8
#define EXIF_FMT_SLONG  9       /* A 32-bit (4-byte) signed integer (2's complement notation). */
#define EXIF_FMT_SRATIONAL  10  /* Two SLONGs. The first SLONG is the numerator and the second SLONG is the denominator. */
#define EXIF_FMT_SINGLE  11
#define EXIF_FMT_DOUBLE  12
#define EXIF_TAG_START  0x0100
#define EXIF_TAG_STOP  0xFFFF
#define TAG_EXIF_OFFSET  0x8769
#define TAG_INTEROP_OFFSET  0xa005
#define GPS_TAG_START 0x0000
#define GPS_TAG_STOP  0x001F
#define GPS_OFFSET 0x8825
#define GPS_LATITUDE 0x0002
#define GPS_LONGITUDE 0x0004
#define GPS_TIMESTAMP 0x0007
#define MAX_TAGS_PER_IFD 1024 /* Maximum tags allowed per IFD */
#define EXIF_ORIENTATION 0x0112
#define AnyCount -1

/* Bit-field flags for supporting OR logic to represent tags which accept multiple types */
#define F_NOTYPE     0x0000  /* Not yet assigned, unknown */
#define F_BYTE       0x0002  /* An 8-bit unsigned integer. */
#define F_ASCII      0x0004  /* An 8-bit byte containing one 7-bit ASCII code. NUL terminated (count includes NUL). */
#define F_SHORT      0x0008  /* A 16-bit (2-byte) unsigned integer */
#define F_LONG       0x0010  /* A 32-bit (4-byte) unsigned intege */
#define F_RATIONAL   0x0020  /* Two LONGs. The first LONG is the numerator and the second LONG expresses the denominator. */
#define F_SBYTE      0x0040  /* An 8-bit signed integer. */
#define F_UNDEFINED  0x0080  /* An 8-bit byte that may take any value depending on the field definition. */
#define F_SSHORT     0x0100  /* A 16-bit (2-byte) signed integer */
#define F_SLONG      0x0200  /* A 32-bit (4-byte) signed integer (2's complement notation). */
#define F_SRATIONAL  0x0400  /* Two SLONGs. The first SLONG is the numerator and the second SLONG is the denominator. */
#define F_SINGLE     0x0800  /* Single IEEE floating point value (32 bit) */
#define F_DOUBLE     0x1000  /* Double IEEE floating point value (64 bit) */

typedef struct _IFDTagTableType
{
  /* TIFF IFD tag number */
  unsigned short
    tag;

   /* Accepted tag formats declared by a standard */
  short
    format;

  /* Other formats for the tag discovered to be in use (likely due to a bug) */
  short
    format_alt;

  /* Expected component count. -1 == Any, 0 == not set yet */
  short
    count;

  /* Tag description */
  const char
    description[36];

  /*
    Add tag format and component numbers
    https://www.media.mit.edu/pia/Research/deepview/exif.html
  */
} IFDTagTableType;

#define TAG_INFO(tag,format,format_alt,count,description) {tag,format,format_alt,count,description}

/* https://en.wikipedia.org/wiki/Exif */
/* Microsoft Windows GDI+ tags are documented at https://learn.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-constant-property-tags-in-numerical-order */

static IFDTagTableType
tag_table[] =
  {
    /*
      GPS Info IFD tags. These should be in a separate numeric space
      from EXIF/TIFF tags!
    */
    TAG_INFO(0x0000, F_BYTE, F_NOTYPE, 4, "GPSVersionID"), /* GPS IFD */
    TAG_INFO(0x0001, F_ASCII, F_NOTYPE, 2, "GPSLatitudeRef"), /* GPS IFD */
    TAG_INFO(0x0002, F_RATIONAL, F_NOTYPE, 3, "GPSLatitude"), /* GPS IFD */
    TAG_INFO(0x0003, F_ASCII, F_NOTYPE, 2, "GPSLongitudeRef"), /* GPS IFD */
    TAG_INFO(0x0004, F_RATIONAL, F_NOTYPE, 3, "GPSLongitude"), /* GPS IFD */
    TAG_INFO(0x0005, F_BYTE, F_NOTYPE, 1, "GPSAltitudeRef"), /* GPS IFD */
    TAG_INFO(0x0006, F_RATIONAL, F_NOTYPE, 1, "GPSAltitude"), /* GPS IFD */
    TAG_INFO(0x0007, F_RATIONAL, F_NOTYPE, 3, "GPSTimeStamp"), /* GPS IFD */
    TAG_INFO(0x0008, F_ASCII, F_NOTYPE, AnyCount, "GPSSatellites"), /* GPS IFD */
    TAG_INFO(0x0009, F_ASCII, F_NOTYPE, 2, "GPSStatus"), /* GPS IFD */
    TAG_INFO(0x000A, F_ASCII, F_NOTYPE, 2, "GPSMeasureMode"), /* GPS IFD */
    TAG_INFO(0x000B, F_RATIONAL, F_NOTYPE, 1, "GPSDOP"), /* GPS IFD */
    TAG_INFO(0x000C, F_ASCII, F_NOTYPE, 2, "GPSSpeedRef"), /* GPS IFD */
    TAG_INFO(0x000D, F_RATIONAL, F_NOTYPE, 1, "GPSSpeed"), /* GPS IFD */
    TAG_INFO(0x000E, F_ASCII, F_NOTYPE, 2, "GPSTrackRef"), /* GPS IFD */
    TAG_INFO(0x000F, F_RATIONAL, F_NOTYPE, 1, "GPSTrack"), /* GPS IFD */
    TAG_INFO(0x0010, F_ASCII, F_NOTYPE, 2, "GPSImgDirectionRef"), /* GPS IFD */
    TAG_INFO(0x0011, F_RATIONAL, F_NOTYPE, 1, "GPSImgDirection"), /* GPS IFD */
    TAG_INFO(0x0012, F_ASCII, F_NOTYPE, 0, "GPSMapDatum"), /* GPS IFD */
    TAG_INFO(0x0013, F_ASCII, F_NOTYPE, 2, "GPSDestLatitudeRef"), /* GPS IFD */
    TAG_INFO(0x0014, F_RATIONAL, F_NOTYPE, 3, "GPSDestLatitude"), /* GPS IFD */
    TAG_INFO(0x0015, F_ASCII, F_NOTYPE, 2, "GPSDestLongitudeRef"), /* GPS IFD */
    TAG_INFO(0x0016, F_RATIONAL, F_NOTYPE, 3, "GPSDestLongitude"), /* GPS IFD */
    TAG_INFO(0x0017, F_ASCII, F_NOTYPE, 2, "GPSDestBearingRef"), /* GPS IFD */
    TAG_INFO(0x0018, F_RATIONAL, F_NOTYPE, 1, "GPSDestBearing"), /* GPS IFD */
    TAG_INFO(0x0019, F_ASCII, F_NOTYPE, 2, "GPSDestDistanceRef"), /* GPS IFD */
    TAG_INFO(0x001A, F_RATIONAL, F_NOTYPE, 1, "GPSDestDistance"), /* GPS IFD */
    TAG_INFO(0x001B, F_UNDEFINED, F_NOTYPE, AnyCount, "GPSProcessingMethod"), /* GPS IFD */
    TAG_INFO(0x001C, F_UNDEFINED, F_NOTYPE, AnyCount, "GPSAreaInformation"), /* GPS IFD */
    TAG_INFO(0x001D, F_ASCII, F_NOTYPE, 11, "GPSDateStamp"), /* GPS IFD */
    TAG_INFO(0x001E, F_SHORT, F_NOTYPE, 1, "GPSDifferential"), /* GPS IFD */
    TAG_INFO(0x001F, F_RATIONAL, F_NOTYPE, 1, "GPSHPositioningError"), /* GPS IFD */

    TAG_INFO(0x0100, F_SHORT | F_LONG, F_SLONG, 1, "ImageWidth"),
    TAG_INFO(0x0101, F_SHORT | F_LONG, F_SLONG, 1, "ImageLength"),
    TAG_INFO(0x0102, F_SHORT, F_NOTYPE, AnyCount /* Could be 1, 3, 4! */, "BitsPerSample"),
    TAG_INFO(0x0103, F_SHORT, F_NOTYPE, 1, "Compression"),
    TAG_INFO(0x0106, F_SHORT, F_NOTYPE, 1, "PhotometricInterpretation"),
    TAG_INFO(0x010A, F_SHORT, F_NOTYPE, 1, "FillOrder"),
    TAG_INFO(0x010D, F_ASCII, F_NOTYPE, AnyCount, "DocumentName"),
    TAG_INFO(0x010E, F_ASCII, F_NOTYPE, AnyCount, "ImageDescription"),
    TAG_INFO(0x010F, F_ASCII, F_NOTYPE, AnyCount, "Make"),
    TAG_INFO(0x0110, F_ASCII, F_NOTYPE, AnyCount, "Model"),
    TAG_INFO(0x0111, F_SHORT | F_LONG, F_NOTYPE, 0, "StripOffsets"),
    TAG_INFO(0x0112, F_SHORT, F_SLONG, 1, "Orientation"),
    TAG_INFO(0x0115, F_SHORT, F_NOTYPE, 1, "SamplesPerPixel"),
    TAG_INFO(0x0116, F_SHORT | F_LONG, F_NOTYPE, 1, "RowsPerStrip"),
    TAG_INFO(0x0117, F_LONG  | F_SHORT, F_NOTYPE, 0, "StripByteCounts"),
    TAG_INFO(0x0118, F_SHORT, F_NOTYPE, 0, "MinSampleValue"),
    TAG_INFO(0x0119, F_SHORT, F_NOTYPE, 0, "MaxSampleValue"),
    TAG_INFO(0x011A, F_RATIONAL, F_NOTYPE, 1, "XResolution"),
    TAG_INFO(0x011B, F_RATIONAL, F_NOTYPE, 1, "YResolution"),
    TAG_INFO(0x011C, F_SHORT, F_NOTYPE, 1, "PlanarConfiguration"),
    TAG_INFO(0x011D, F_ASCII, F_NOTYPE, 0, "PageName"),
    TAG_INFO(0x011E, F_RATIONAL, F_NOTYPE, 1, "XPosition"),
    TAG_INFO(0x011F, F_RATIONAL, F_NOTYPE, 1, "YPosition"),

    TAG_INFO(0x0120, F_LONG, F_NOTYPE, AnyCount, "FreeOffsets"), /* Defunct feature */
    TAG_INFO(0x0121, F_LONG, F_NOTYPE, AnyCount, "FreeByteCounts"), /* Defunct feature */
    TAG_INFO(0x0122, F_SHORT, F_NOTYPE, 1, "GrayResponseUnit"),
    TAG_INFO(0x0123, F_SHORT, F_NOTYPE, 0 /* 2**BitsPerSample */, "GrayResponseCurve"),
    TAG_INFO(0x0124, F_LONG, F_NOTYPE, 1, "T4Options"),
    TAG_INFO(0x0125, F_LONG, F_NOTYPE, 1, "T6Options"),
    TAG_INFO(0x0128, F_SHORT, F_NOTYPE, 1, "ResolutionUnit"),
    TAG_INFO(0x012D, F_SHORT, F_NOTYPE, 3*256  /* (1 or 3) * (1 << BitsPerSample) */, "TransferFunction"),
    TAG_INFO(0x0131, F_ASCII, F_NOTYPE, AnyCount, "Software"),
    TAG_INFO(0x0132, F_ASCII, F_NOTYPE, 21 /* 20+NUL? TIFF spec says 20 */, "DateTime"),
    TAG_INFO(0x013B, F_ASCII, F_NOTYPE, AnyCount, "Artist"),
    TAG_INFO(0x013C, F_ASCII, F_NOTYPE, AnyCount, "HostComputer"),
    TAG_INFO(0x013D, F_SHORT, F_NOTYPE, 0, "Predictor"),
    TAG_INFO(0x013E, F_RATIONAL, F_NOTYPE, 2, "WhitePoint"),
    TAG_INFO(0x013F, F_RATIONAL, F_NOTYPE, 6, "PrimaryChromaticities"),
    TAG_INFO(0x0140, F_SHORT, F_NOTYPE, 0 /* 3 * (2**BitsPerSample) */, "ColorMap"),
    TAG_INFO(0x0141, F_SHORT, F_NOTYPE, 2, "HalfToneHints"),
    TAG_INFO(0x0142, F_SHORT | F_LONG, F_NOTYPE, AnyCount /* TBD */, "TileWidth"),
    TAG_INFO(0x0143, F_SHORT | F_LONG, F_NOTYPE, AnyCount /* TBD */, "TileLength"),
    TAG_INFO(0x0144, F_LONG, F_NOTYPE, AnyCount /* TBD */, "TileOffsets"),
    TAG_INFO(0x0145, F_SHORT | F_LONG, F_NOTYPE, AnyCount /* TBD */, "TileByteCounts"),
    TAG_INFO(0x014A, F_LONG, F_NOTYPE, 1, "SubIFD"),
    TAG_INFO(0x014C, F_SHORT, F_NOTYPE, 1, "InkSet"),
    TAG_INFO(0x014D, F_ASCII, F_NOTYPE, AnyCount, "InkNames"),
    TAG_INFO(0x014E, F_SHORT, F_NOTYPE, 1, "NumberOfInks"),
    TAG_INFO(0x0150, F_BYTE | F_SHORT, F_NOTYPE, 0 /* 2, or 2*SamplesPerPixel */, "DotRange"),
    TAG_INFO(0x0151, F_ASCII, F_NOTYPE, AnyCount, "TargetPrinter"),
    TAG_INFO(0x0152, F_SHORT, F_NOTYPE, 0, "ExtraSample"),
    TAG_INFO(0x0153, F_SHORT, F_NOTYPE, 0, "SampleFormat"),
    TAG_INFO(0x0154, F_BYTE | F_SHORT | F_LONG | F_SRATIONAL | F_DOUBLE, F_NOTYPE, 0, "SMinSampleValue"), /* BYTE or SHORT or LONG or RATIONAL or DOUBLE */
    TAG_INFO(0x0155, F_BYTE | F_SHORT | F_LONG | F_SRATIONAL | F_DOUBLE, F_NOTYPE, 0, "SMaxSampleValue"), /* BYTE or SHORT or LONG or RATIONAL or DOUBLE */
    TAG_INFO(0x0156, F_SHORT, F_NOTYPE, 6, "TransferRange"),
    TAG_INFO(0x0157, F_BYTE, F_NOTYPE, AnyCount, "ClipPath"),
    TAG_INFO(0x0158, F_LONG, F_NOTYPE, 1, "XClipPathUnits"),
    TAG_INFO(0x0159, F_LONG, F_NOTYPE, 1, "YClipPathUnits"),
    TAG_INFO(0x015A, F_SHORT, F_NOTYPE, 1, "Indexed"),
    TAG_INFO(0x015B, F_UNDEFINED, F_NOTYPE, 0, "JPEGTables"),
    TAG_INFO(0x015F, F_SHORT, F_NOTYPE, 0, "OPIProxy"),
    TAG_INFO(0x0200, F_SHORT, F_NOTYPE, 1, "JPEGProc"),
    TAG_INFO(0x0201, F_LONG, F_NOTYPE, 1, "JPEGInterchangeFormat"),
    TAG_INFO(0x0202, F_LONG, F_NOTYPE, 1, "JPEGInterchangeFormatLength"),
    TAG_INFO(0x0203, F_SHORT, F_NOTYPE, 1, "JPEGRestartInterval"),
    TAG_INFO(0x0205, F_SHORT, F_NOTYPE, 0, "JPEGLosslessPredictors"),
    TAG_INFO(0x0206, F_SHORT, F_NOTYPE, 0, "JPEGPointTransforms"),
    TAG_INFO(0x0207, F_LONG, F_NOTYPE, 0, "JPEGQTables"),
    TAG_INFO(0x0208, F_LONG, F_NOTYPE, 0, "JPEGDCTables"),
    TAG_INFO(0x0209, F_LONG, F_NOTYPE, 0, "JPEGACTables"),
    TAG_INFO(0x0211, F_RATIONAL, F_NOTYPE, 3, "YCbCrCoefficients"),
    TAG_INFO(0x0212, F_SHORT, F_NOTYPE, 2, "YCbCrSubSampling"),
    TAG_INFO(0x0213, F_SHORT, F_NOTYPE, 1, "YCbCrPositioning"),
    TAG_INFO(0x0214, F_RATIONAL, F_NOTYPE, 0 /* 2*SamplesPerPixel */, "ReferenceBlackWhite"),
    TAG_INFO(0x02BC, F_NOTYPE, F_NOTYPE, 0, "ExtensibleMetadataPlatform"), /* XMP */
    TAG_INFO(0x0301, F_NOTYPE, F_NOTYPE, 0, "Gamma"),
    TAG_INFO(0x0302, F_NOTYPE, F_NOTYPE, 0, "ICCProfileDescriptor"),
    TAG_INFO(0x0303, F_NOTYPE, F_NOTYPE, 0, "SRGBRenderingIntent"),
    TAG_INFO(0x0320, F_NOTYPE, F_NOTYPE, 0, "ImageTitle"),

    /*
      Interoperability IFD tags.  These should be in a separate
      numeric space from EXIF/TIFF tags!
    */
    TAG_INFO(0x1000, F_NOTYPE, F_NOTYPE, 0, "RelatedImageFileFormat"), /* Exif Interoperability IFD */
    TAG_INFO(0x1001, F_SHORT | F_LONG, F_NOTYPE, 0, "RelatedImageWidth"), /* Exif Interoperability IFD */
    TAG_INFO(0x1002, F_SHORT | F_LONG, F_NOTYPE, 0, "RelatedImageLength"), /* Exif Interoperability IFD */

    TAG_INFO(0x5001, F_SHORT, F_NOTYPE, 1, "ResolutionXUnit"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5002, F_SHORT, F_NOTYPE, 1, "ResolutionYUnit"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5003, F_SHORT, F_NOTYPE, 1, "ResolutionXLengthUnit"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5004, F_SHORT, F_NOTYPE, 1, "ResolutionYLengthUnit"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5005, F_ASCII, F_NOTYPE, AnyCount /* Number of flags */, "PrintFlags"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5006, F_SHORT, F_NOTYPE, 1, "PrintFlagsVersion"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5007, F_BYTE, F_NOTYPE, 1, "PrintFlagsCrop"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5008, F_LONG, F_NOTYPE, 1, "PrintFlagsBleedWidth"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5009, F_SHORT, F_NOTYPE, 1, "PrintFlagsBleedWidthScale"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x500A, F_RATIONAL, F_NOTYPE, 1, "HalftoneLPI"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x500B, F_SHORT, F_NOTYPE, 1, "HalftoneLPIUnit"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x500C, F_RATIONAL, F_NOTYPE, 1, "HalftoneDegree"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x500D, F_SHORT, F_NOTYPE, 1, "HalftoneShape"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x500E, F_LONG, F_NOTYPE, 1, "HalftoneMisc"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x500F, F_BYTE, F_NOTYPE, 1, "HalftoneScreen"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5010, F_SHORT, F_NOTYPE, AnyCount, "JPEGQuality"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5011, F_UNDEFINED, F_NOTYPE, AnyCount, "GridSize"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5012, F_LONG, F_NOTYPE, 1, "ThumbnailFormat"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5013, F_LONG, F_NOTYPE, 1, "ThumbnailWidth"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5014, F_LONG, F_NOTYPE, 1, "ThumbnailHeight"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5015, F_SHORT, F_NOTYPE, 1, "ThumbnailColorDepth"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5016, F_SHORT, F_NOTYPE, 1, "ThumbnailPlanes"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5017, F_LONG, F_NOTYPE, 1, "ThumbnailRawBytes"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5018, F_LONG, F_NOTYPE, 1, "ThumbnailSize"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5019, F_LONG, F_NOTYPE, 1, "ThumbnailCompressedSize"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x501A, F_UNDEFINED, F_NOTYPE, 0, "ColorTransferFunction"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x501B, F_BYTE, F_NOTYPE, 0, "ThumbnailData"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5020, F_LONG | F_SHORT, F_NOTYPE, 1, "ThumbnailImageWidth"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5021, F_LONG | F_SHORT, F_NOTYPE, 1, "ThumbnailImageHeight"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5022, F_SHORT, F_NOTYPE, 1, "ThumbnailBitsPerSample"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5023, F_SHORT, F_NOTYPE, 1, "ThumbnailCompression"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5024, F_SHORT, F_NOTYPE, 1, "ThumbnailPhotometricInterp"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5025, F_ASCII, F_NOTYPE, AnyCount, "ThumbnailImageDescription"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5026, F_ASCII, F_NOTYPE, AnyCount, "ThumbnailEquipMake"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5027, F_ASCII, F_NOTYPE, AnyCount, "ThumbnailEquipModel"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5028, F_LONG | F_SHORT, F_NOTYPE, 0, "ThumbnailStripOffsets"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5029, F_SHORT, F_NOTYPE, 1, "ThumbnailOrientation"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x502A, F_SHORT, F_NOTYPE, 1, "ThumbnailSamplesPerPixel"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x502B, F_LONG | F_SHORT, F_NOTYPE, 1, "ThumbnailRowsPerStrip"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x502C, F_LONG | F_SHORT, F_NOTYPE, 0, "ThumbnailStripBytesCount"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x502D, F_SHORT /* type provided by ThumbnailResolutionUnit */, F_NOTYPE, 0, "ThumbnailResolutionX"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x502E, F_SHORT /* type provided by ThumbnailResolutionUnit */, F_NOTYPE, 0, "ThumbnailResolutionY"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x502F, F_SHORT, F_NOTYPE, 1, "ThumbnailPlanarConfig"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5030, F_SHORT, F_NOTYPE, 1, "ThumbnailResolutionUnit"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5031, F_SHORT, F_NOTYPE, 0, "ThumbnailTransferFunction"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5032, F_ASCII, F_NOTYPE, AnyCount, "ThumbnailSoftwareUsed"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5033, F_ASCII, F_NOTYPE, AnyCount, "ThumbnailDateTime"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5034, F_ASCII, F_NOTYPE, AnyCount, "ThumbnailArtist"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5035, F_RATIONAL, F_NOTYPE, 2, "ThumbnailWhitePoint"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5036, F_RATIONAL, F_NOTYPE, 6, "ThumbnailPrimaryChromaticities"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5037, F_RATIONAL, F_NOTYPE, 3, "ThumbnailYCbCrCoefficients"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5038, F_SHORT, F_NOTYPE, 2, "ThumbnailYCbCrSubsampling"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5039, F_SHORT, F_NOTYPE, 1, "ThumbnailYCbCrPositioning"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x503A, F_RATIONAL, F_NOTYPE, 6, "ThumbnailRefBlackWhite"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x503B, F_ASCII, F_NOTYPE, AnyCount, "ThumbnailCopyRight"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5090, F_SHORT, F_NOTYPE, 64, "LuminanceTable"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5091, F_SHORT, F_NOTYPE, 64, "ChrominanceTable"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5100, F_LONG, F_NOTYPE, 0, "FrameDelay"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5101, F_SHORT, F_NOTYPE, 1, "LoopCount"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5102, F_BYTE, F_NOTYPE, 0, "GlobalPalette"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5103, F_BYTE, F_NOTYPE, 1, "IndexBackground"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5104, F_BYTE, F_NOTYPE, 1, "IndexTransparent"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5110, F_BYTE, F_NOTYPE, 0, "PixelUnit"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5111, F_LONG, F_NOTYPE, 1, "PixelPerUnitX"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5112, F_LONG, F_NOTYPE, 1, "PixelPerUnitY"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x5113, F_BYTE, F_NOTYPE, AnyCount, "PaletteHistogram"), /* Microsoft Windows GDI+ */
    TAG_INFO(0x800D, F_ASCII, F_NOTYPE, AnyCount, "ImageID"), /* Adobe OPI */
    TAG_INFO(0x80E3, F_NOTYPE, F_NOTYPE, 0, "Matteing"),
    TAG_INFO(0x80E4, F_NOTYPE, F_NOTYPE, 0, "DataType"),
    TAG_INFO(0x80E5, F_NOTYPE, F_NOTYPE, 0, "ImageDepth"),
    TAG_INFO(0x80E6, F_NOTYPE, F_NOTYPE, 0, "TileDepth"),
    TAG_INFO(0x828D, F_SHORT, F_NOTYPE, 0, "CFARepeatPatternDim"),
    TAG_INFO(0x828E, F_BYTE, F_NOTYPE, 0, "CFAPattern"),
    TAG_INFO(0x828F, F_RATIONAL, F_NOTYPE, 0, "BatteryLevel"),
    TAG_INFO(0x8298, F_ASCII, F_NOTYPE, AnyCount, "Copyright"),
    TAG_INFO(0x829A, F_RATIONAL, F_NOTYPE, 1, "ExposureTime"),
    TAG_INFO(0x829D, F_RATIONAL, F_NOTYPE, 1, "FNumber"),
    TAG_INFO(0x83BB, F_LONG, F_NOTYPE, 0, "IPTC/NAA"),
    TAG_INFO(0x84E3, F_NOTYPE, F_NOTYPE, 0, "IT8RasterPadding"),
    TAG_INFO(0x84E5, F_NOTYPE, F_NOTYPE, 0, "IT8ColorTable"),
    TAG_INFO(0x8649, F_NOTYPE, F_NOTYPE, 0, "ImageResourceInformation"),
    TAG_INFO(0x8769, F_LONG, F_NOTYPE, 1, "ExifOffset"), /* Exif IFD Pointer */
    TAG_INFO(0x8773, F_BYTE, F_NOTYPE, AnyCount, "InterColorProfile"), /* ICCProfile */
    TAG_INFO(0x8822, F_SHORT, F_NOTYPE, 1, "ExposureProgram"),
    TAG_INFO(0x8824, F_ASCII, F_NOTYPE, AnyCount, "SpectralSensitivity"),
    TAG_INFO(0x8825, F_LONG /* TBD */, F_SLONG, 1, "GPSInfo"), /* Offset to GPS IFD */
    TAG_INFO(0x8827, F_SHORT, F_NOTYPE, AnyCount, "PhotographicSensitivity"), /* Was "ISOSpeedRatings" */
    TAG_INFO(0x8828, F_UNDEFINED, F_NOTYPE, AnyCount, "OECF"),
    TAG_INFO(0x8830, F_SHORT, F_NOTYPE, 1, "SensitivityType"),
    TAG_INFO(0x8831, F_LONG, F_NOTYPE, 1, "StandardOutputSensitivity"),
    TAG_INFO(0x8832, F_LONG, F_NOTYPE, 1, "RecommendedExposureIndex"),
    TAG_INFO(0x8833, F_LONG, F_NOTYPE, 1, "ISOSpeed"),
    TAG_INFO(0x8834, F_LONG, F_NOTYPE, 1, "ISOSpeedLatitudeyyy"),
    TAG_INFO(0x8835, F_LONG, F_NOTYPE, 1, "ISOSpeedLatitudezzz"),
    TAG_INFO(0x9000, F_UNDEFINED, F_NOTYPE, 4, "ExifVersion"), /* e.g. "0300" without NUL */
    TAG_INFO(0x9003, F_ASCII, F_NOTYPE, 20, "DateTimeOriginal"),
    TAG_INFO(0x9004, F_ASCII, F_NOTYPE, 20, "DateTimeDigitized"),
    TAG_INFO(0x9010, F_ASCII, F_NOTYPE, 7, "OffsetTime"),
    TAG_INFO(0x9011, F_ASCII, F_NOTYPE, 7, "OffsetTimeOriginal"),
    TAG_INFO(0x9012, F_ASCII, F_NOTYPE, 7, "OffsetTimeDigitized"),
    TAG_INFO(0x9101, F_UNDEFINED, F_NOTYPE, 4, "ComponentsConfiguration"),
    TAG_INFO(0x9102, F_RATIONAL, F_NOTYPE, 1, "CompressedBitsPerPixel"),
    TAG_INFO(0x9201, F_SRATIONAL /* TBD */, F_RATIONAL, 1, "ShutterSpeedValue"),
    TAG_INFO(0x9202, F_RATIONAL, F_NOTYPE, 1, "ApertureValue"),
    TAG_INFO(0x9203, F_SRATIONAL, F_NOTYPE, 1, "BrightnessValue"),
    TAG_INFO(0x9204, F_SRATIONAL /* TBD */, F_RATIONAL, 1, "ExposureBiasValue"),
    TAG_INFO(0x9205, F_RATIONAL, F_NOTYPE, 1, "MaxApertureValue"),
    TAG_INFO(0x9206, F_RATIONAL, F_NOTYPE, 1, "SubjectDistance"),
    TAG_INFO(0x9207, F_SHORT, F_NOTYPE, 1, "MeteringMode"),
    TAG_INFO(0x9208, F_SHORT, F_NOTYPE, 1, "LightSource"),
    TAG_INFO(0x9209, F_SHORT, F_NOTYPE, 1, "Flash"),
    TAG_INFO(0x920A, F_RATIONAL, F_NOTYPE, 1, "FocalLength"),
    TAG_INFO(0x9214, F_SHORT, F_NOTYPE, AnyCount /* 2 or 3 or 4 */, "SubjectArea"),
    TAG_INFO(0x927C, F_UNDEFINED, F_NOTYPE, AnyCount, "MakerNote"),
    TAG_INFO(0x9286, F_UNDEFINED, F_NOTYPE, AnyCount, "UserComment"),
    TAG_INFO(0x9290, F_ASCII, F_NOTYPE, AnyCount, "SubSecTime"),
    TAG_INFO(0x9291, F_ASCII, F_NOTYPE, AnyCount, "SubSecTimeOriginal"),
    TAG_INFO(0x9292, F_ASCII, F_NOTYPE, AnyCount, "SubSecTimeDigitized"),
    TAG_INFO(0x9400, F_SRATIONAL, F_NOTYPE, 1, "Temperature"),
    TAG_INFO(0x9401, F_RATIONAL, F_NOTYPE, 1, "Humidity"),
    TAG_INFO(0x9402, F_RATIONAL, F_NOTYPE, 1, "Pressure"),
    TAG_INFO(0x9403, F_SRATIONAL, F_NOTYPE, 1, "WaterDepth"),
    TAG_INFO(0x9404, F_RATIONAL, F_NOTYPE, 1, "Acceleration"),
    TAG_INFO(0x9405, F_SRATIONAL, F_NOTYPE, 1, "CameraElevationAngle "),
    TAG_INFO(0x9C9B, F_BYTE, F_NOTYPE, AnyCount, "WinXP-Title"),     /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9C, F_BYTE, F_NOTYPE, AnyCount, "WinXP-Comments"),  /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9D, F_BYTE, F_NOTYPE, AnyCount, "WinXP-Author"),    /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9E, F_BYTE, F_NOTYPE, AnyCount, "WinXP-Keywords"),  /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0x9C9F, F_BYTE, F_NOTYPE, AnyCount, "WinXP-Subject"),   /* Win XP specific, UTF-16 Unicode */
    TAG_INFO(0xA000, F_UNDEFINED, F_NOTYPE, 4, "FlashPixVersion"),
    TAG_INFO(0xA001, F_SHORT , F_NOTYPE, 1, "ColorSpace"),
    TAG_INFO(0xA002, F_SHORT | F_LONG /* TBD */, F_SLONG, 1, "PixelXDimension"), /* Was "ExifImageWidth" */
    TAG_INFO(0xA003, F_SHORT | F_LONG /* TBD */, F_SLONG, 1, "PixelYDimension"), /* Was "ExifImageLength" */
    TAG_INFO(0xA004, F_ASCII, F_NOTYPE, 13, "RelatedSoundFile"),
    TAG_INFO(0xA005, F_LONG, F_NOTYPE, 0, "InteroperabilityOffset"), /* Interoperability IFD Pointer */
    TAG_INFO(0xA20B, F_RATIONAL, F_NOTYPE, 1, "FlashEnergy"),
    TAG_INFO(0xA20C, F_UNDEFINED, F_NOTYPE, AnyCount, "SpatialFrequencyResponse"),
    TAG_INFO(0xA20D, F_NOTYPE, F_NOTYPE, 0, "Noise"),
    TAG_INFO(0xA20E, F_RATIONAL, F_NOTYPE, 1, "FocalPlaneXResolution"),
    TAG_INFO(0xA20F, F_RATIONAL, F_NOTYPE, 1, "FocalPlaneYResolution"),
    TAG_INFO(0xA210, F_SHORT, F_NOTYPE, 1, "FocalPlaneResolutionUnit"),
    TAG_INFO(0xA211, F_NOTYPE, F_NOTYPE, 0, "ImageNumber"),
    TAG_INFO(0xA212, F_NOTYPE, F_NOTYPE, 0, "SecurityClassification"),
    TAG_INFO(0xA213, F_NOTYPE, F_NOTYPE, 0, "ImageHistory"),
    TAG_INFO(0xA214, F_SHORT, F_NOTYPE, 2, "SubjectLocation"),
    TAG_INFO(0xA215, F_RATIONAL, F_NOTYPE, 1, "ExposureIndex"),
    TAG_INFO(0xA216, F_NOTYPE, F_NOTYPE, 0, "TIFF_EPStandardID"),
    TAG_INFO(0xA217, F_SHORT, F_BYTE, 1, "SensingMethod"),
    TAG_INFO(0xA300, F_UNDEFINED, F_BYTE, AnyCount /* varies (0,1,2,3), TBD */, "FileSource"),
    TAG_INFO(0xA301, F_UNDEFINED, F_BYTE, 1, "SceneType"),
    TAG_INFO(0xA302, F_UNDEFINED, F_NOTYPE, AnyCount, "CFAPattern"),
    TAG_INFO(0xA401, F_SHORT, F_NOTYPE, 1, "CustomRendered"),
    TAG_INFO(0xA402, F_SHORT, F_NOTYPE, 1, "ExposureMode"),
    TAG_INFO(0xA403, F_SHORT, F_NOTYPE, 1, "WhiteBalance"),
    TAG_INFO(0xA404, F_RATIONAL, F_NOTYPE, 1, "DigitalZoomRatio"),
    TAG_INFO(0xA405, F_SHORT, F_NOTYPE, 1, "FocalLengthIn35mmFilm"),
    TAG_INFO(0xA406, F_SHORT, F_NOTYPE, 1, "SceneCaptureType"),
    TAG_INFO(0xA407, F_SHORT, F_NOTYPE, 1, "GainControl"),
    TAG_INFO(0xA408, F_SHORT, F_NOTYPE, 1, "Contrast"),
    TAG_INFO(0xA409, F_SHORT, F_NOTYPE, 1, "Saturation"),
    TAG_INFO(0xA40A, F_SHORT, F_NOTYPE, 1, "Sharpness"),
    TAG_INFO(0xA40B, F_UNDEFINED, F_NOTYPE, AnyCount, "DeviceSettingDescription"),
    TAG_INFO(0xA40C, F_SHORT, F_NOTYPE, 1, "SubjectDistanceRange"),
    TAG_INFO(0xA420, F_ASCII, F_NOTYPE, 33, "ImageUniqueID"),
    TAG_INFO(0xA430, F_ASCII, F_NOTYPE, AnyCount, "CameraOwnerName"),
    TAG_INFO(0xA431, F_ASCII, F_NOTYPE, AnyCount, "BodySerialNumber"),
    TAG_INFO(0xA432, F_RATIONAL, F_NOTYPE, 4, "LensSpecification"),
    TAG_INFO(0xA433, F_ASCII, F_NOTYPE, AnyCount, "LensMake"),
    TAG_INFO(0xA434, F_ASCII, F_NOTYPE, AnyCount, "LensModel"),
    TAG_INFO(0xA435, F_ASCII, F_NOTYPE, AnyCount, "LensSerialNumber"),
    TAG_INFO(0xA436, F_ASCII, F_NOTYPE, AnyCount, "ImageTitle"),
    TAG_INFO(0xA437, F_ASCII, F_NOTYPE, AnyCount, "Photographer"),
    TAG_INFO(0xA438, F_ASCII, F_NOTYPE, AnyCount, "ImageEditor"),
    TAG_INFO(0xA439, F_ASCII, F_NOTYPE, AnyCount, "CameraFirmware"),
    TAG_INFO(0xA43A, F_ASCII, F_NOTYPE, AnyCount, "RAWDevelopingSoftware"),
    TAG_INFO(0xA43B, F_ASCII, F_NOTYPE, AnyCount, "ImageEditingSoftware"),
    TAG_INFO(0xA43C, F_ASCII, F_NOTYPE, AnyCount, "MetadataEditingSoftware"),
    TAG_INFO(0xA460, F_SHORT, F_NOTYPE, 1, "CompositeImage"),
    TAG_INFO(0xA461, F_SHORT, F_NOTYPE, 2, "SourceImageNumberOfCompositeImage"),
    TAG_INFO(0xA462, F_UNDEFINED, F_NOTYPE, AnyCount, "SourceExposureTimesOfCompositeImage"),
    TAG_INFO(0xA500, F_RATIONAL, F_NOTYPE, 1, "Gamma")
  };

/* Set to non-zero in order to use bsearch rather than linear search. */
#if !defined(EXIF_USE_BSEARCH)
#define EXIF_USE_BSEARCH 1
#endif /* !defined(EXIF_USE_BSEARCH) */

#if EXIF_USE_BSEARCH
/*
  Compare two IFDTagTableType entries by tag
*/
static int IFDTagTableTypeCompare(const void *l, const void *r)
{
  const IFDTagTableType * restrict lp = (const IFDTagTableType *) l;
  const IFDTagTableType * restrict rp = (const IFDTagTableType *) r;
  int sense;
  unsigned int lptag = lp->tag;
  unsigned int rptag = rp->tag;

  if (lptag > rptag)
    sense = 1;
  else if (lptag < rptag)
    sense = -1;
  else
    sense = 0;

  return sense;
}
#endif /* if EXIF_USE_BSEARCH */

/*
  Find EXIF table entry matching tag
*/
static const IFDTagTableType *
FindEXIFTableEntryByTag(const unsigned int t,
                        const IFDTagTableType *tag_table,
                        const size_t tag_table_entries) MAGICK_FUNC_PURE;

static const IFDTagTableType *
FindEXIFTableEntryByTag(const unsigned int t,
                        const IFDTagTableType *tag_table,
                        const size_t tag_table_entries)
{
  const IFDTagTableType *key_p = (IFDTagTableType *) NULL;

#if EXIF_USE_BSEARCH
  IFDTagTableType key = TAG_INFO(0x0000, F_NOTYPE, F_NOTYPE, 0, "");

  key.tag = t;

  key_p=(const IFDTagTableType*) bsearch((const void *) &key,(void *) tag_table,tag_table_entries,
                                         sizeof(tag_table[0]),IFDTagTableTypeCompare);
#else
  register unsigned int
    ttt;

  size_t
    i;

  for (i=0; i < tag_table_entries; i++)
    {
      ttt = tag_table[i].tag;
      if (ttt == t)
        {
          key_p = &tag_table[i];
          break;
        }
      else if (ttt > t)
        {
          break;
        }
    }
#endif /* if EXIF_USE_BSEARCH */

  return key_p;
}

/*
  Convert an EXIF IFD tag ID to a tag description

  An EXIF IFD tag value to be translated, and a buffer of at least
  MaxTextExtent length are passed as arguments.  For convenience, the
  converted string is returned.
*/

static const char *
EXIFIfdTagToDescription(unsigned int t, char *tag_description)
{
  const IFDTagTableType *key_p;

  key_p = FindEXIFTableEntryByTag(t, tag_table, ArraySize(tag_table));
  if (key_p != (IFDTagTableType *) NULL)
    {
      (void) strlcpy(tag_description,key_p->description,MaxTextExtent);
      return tag_description;
    }
#if 0
  unsigned int
    i;

  for (i=0; i < ArraySize(tag_table); i++)
    {
      if (tag_table[i].tag == t)
        {
          (void) strlcpy(tag_description,tag_table[i].description,MaxTextExtent);
          return tag_description;
        }
      else if (tag_table[i].tag > t)
        {
          break;
        }
    }
#endif

  MagickFormatString(tag_description,MaxTextExtent,"0x%04X",t);
  return tag_description;
}

/*
  Convert an EXIF IFD tag description to a tag ID.
*/
static int
EXIFIfdTagDescriptionToTagId(const char *description)
{
  unsigned int
    i;

  for (i=0; i < sizeof(tag_table)/sizeof(tag_table[0]); i++)
    if (LocaleCompare(tag_table[i].description,description) == 0)
      return tag_table[i].tag;

  return -1;
}

/*
  Convert a TIFF IFD field value type to string description
*/
static const char *
EXIFIfdFieldTypeToStr(unsigned int f)
{
  const char
    *str="unknown";

  switch (f)
    {
    case EXIF_FMT_BYTE:
      str="BYTE";
      break;
    case EXIF_FMT_ASCII:
      str="STRING";
      break;
    case EXIF_FMT_USHORT:
      str="SHORT";
      break;
    case EXIF_FMT_ULONG:
      str="LONG";
      break;
    case EXIF_FMT_URATIONAL:
      str="RATIONAL";
      break;
    case EXIF_FMT_SBYTE:
      str="SBYTE";
      break;
    case EXIF_FMT_UNDEFINED:
      str="UNDEFINED";
      break;
    case EXIF_FMT_SSHORT:
      str="SSHORT";
      break;
    case EXIF_FMT_SLONG:
      str="SLONG";
      break;
    case EXIF_FMT_SRATIONAL:
      str="SRATIONAL";
      break;
    case EXIF_FMT_SINGLE:
      str="SINGLE";
      break;
    case EXIF_FMT_DOUBLE:
      str="DOUBLE";
      break;
    }

  return str;
}

static const unsigned int
  format_bytes[] =
  {
    0,
    1, /* BYTE */
    1, /* STRING / ASCII */
    2, /* USHORT */
    4, /* ULONG */
    8, /* URATIONAL */
    1, /* SBYTE */
    1, /* UNDEFINED */
    2, /* SSHORT */
    4, /* SLONG */
    8, /* SRATIONAL */
    4, /* SINGLE / FLOAT */
    8  /* DOUBLE */
  };

/*
  Translate from EXIF_FMT_FOO to F_FOO bit-field flag.
*/
static unsigned int ExifFmtToFmtBits(unsigned int f)
{
  unsigned int
    bits;

    switch (f)
    {
    case EXIF_FMT_NOTYPE:
    default:
      bits=F_NOTYPE;
      break;
    case EXIF_FMT_BYTE:
      bits=F_BYTE;
      break;
    case EXIF_FMT_ASCII:
      bits=F_ASCII;
      break;
    case EXIF_FMT_USHORT:
      bits=F_SHORT;
      break;
    case EXIF_FMT_ULONG:
      bits=F_LONG;
      break;
    case EXIF_FMT_URATIONAL:
      bits=F_RATIONAL;
      break;
    case EXIF_FMT_SBYTE:
      bits=F_SBYTE;
      break;
    case EXIF_FMT_UNDEFINED:
      bits=F_UNDEFINED;
      break;
    case EXIF_FMT_SSHORT:
      bits=F_SSHORT;
      break;
    case EXIF_FMT_SLONG:
      bits=F_SLONG;
      break;
    case EXIF_FMT_SRATIONAL:
      bits=F_SRATIONAL;
      break;
    case EXIF_FMT_SINGLE:
      bits=F_SINGLE;
      break;
    case EXIF_FMT_DOUBLE:
      bits=F_DOUBLE;
      break;
    }
    return bits;
}

/*
  Get the expected bit-field bits for format and use it to verify if
  it is an expected format (a bit matches).
*/
typedef enum
  {
    ExifFmtGood,
    ExifFmtFishy,
    ExifFmtBad
  } ExifFmtStatus;

static ExifFmtStatus ValidateExifFmtAgainstBitField(const IFDTagTableType *key_p,const unsigned int fmt)
{
  ExifFmtStatus
    status;

  if (key_p->format & ExifFmtToFmtBits(fmt))
    {
      /* Totally good! */
      status=ExifFmtGood;
    }
  else if ((key_p->format | key_p->format_alt) & ExifFmtToFmtBits(fmt))
    {
      /* Fishy */
      status=ExifFmtFishy;
    }
  else
    {
      /* Bad */
      status=ExifFmtBad;
    }
  return status;
}

static magick_int16_t
Read16s(int morder,unsigned char *ishort)
{
  union
  {
    magick_uint16_t u;
    magick_int16_t s;
  } value;

  if (morder)
    value.u=((magick_uint16_t) ishort[0] << 8) | ishort[1];
  else
    value.u=((magick_uint16_t) ishort[1] << 8) | ishort[0];
  return(value.s);
}

static magick_uint16_t
Read16u(int morder,unsigned char *ishort)
{
  magick_uint16_t
    value;

  if (morder)
    value=((magick_uint16_t) ishort[0] << 8)
      | (magick_uint16_t) ishort[1];
  else
    value=((magick_uint16_t) ishort[1] << 8)
      | (magick_uint16_t) ishort[0];
  return(value);
}

static magick_int32_t
Read32s(int morder,unsigned char *ilong)
{
  union
  {
    magick_uint32_t u;
    magick_int32_t s;
  } value;

  if (morder)
    value.u=((magick_uint32_t) ilong[0] << 24)
      | ((magick_uint32_t) ilong[1] << 16)
      | ((magick_uint32_t) ilong[2] << 8)
      | ((magick_uint32_t) ilong[3]);
  else
    value.u=((magick_uint32_t) ilong[3] << 24)
      | ((magick_uint32_t) ilong[2] << 16)
      | ((magick_uint32_t) ilong[1] << 8 )
      | ((magick_uint32_t) ilong[0]);
  return(value.s);
}

static magick_uint32_t
Read32u(int morder, unsigned char *ilong)
{
  magick_uint32_t
    value;

  if (morder)
    value=((magick_uint32_t) ilong[0] << 24)
      | ((magick_uint32_t) ilong[1] << 16)
      | ((magick_uint32_t) ilong[2] << 8)
      | ((magick_uint32_t) ilong[3]);
  else
    value=((magick_uint32_t) ilong[3] << 24)
      | ((magick_uint32_t) ilong[2] << 16)
      | ((magick_uint32_t) ilong[1] << 8 )
      | ((magick_uint32_t) ilong[0]);

  return value;
}

static void
Write16u(int morder, void *location, magick_uint16_t value)
{
  char
    *pval;

  pval = (char *)location;
  if (morder)
    {
      *pval++ = (char)((value >> 8) & 0xff);
      *pval++ = (char)(value & 0xff);
    }
  else
    {
      *pval++ = (char)(value & 0xff);
      *pval++ = (char)((value >> 8) & 0xff);
    }
}

static int
GenerateEXIFAttribute(Image *image,const char *specification)
{
  char
    *final,
    *key,
    tag_description[MaxTextExtent],
    *value;

  int
    id,
    morder,
    all;

  int
    tag;

  register size_t
    i;

  size_t
    length;

  unsigned int
    level,
    offset;

  unsigned int
    gpsoffset;

  unsigned char
    *tiffp,
    *tiffp_max,
    *ifdstack[DE_STACK_SIZE],
    *ifdp,
    *info;

  unsigned int
    de,
    destack[DE_STACK_SIZE],
    nde;

  const unsigned char
    *profile_info;

  size_t
    profile_length;

  MagickBool
    logging,
    gpsfoundstack[DE_STACK_SIZE],
    gpsfound;

  MagickBool
    debug=MagickFalse;

  assert((ArraySize(format_bytes)-1) == EXIF_NUM_FORMATS);
  logging=IsEventLogged(TransformEvent);
  {
    const char *
      env_value;

    /*
      Allow enabling debug of EXIF tags
    */
    if ((env_value=getenv("MAGICK_DEBUG_EXIF")))
      {
        if (LocaleCompare(env_value,"TRUE") == 0)
          debug=MagickTrue;
      }
  }
  gpsfound=MagickFalse;
  gpsoffset=0;
  /*
    Determine if there is any EXIF data available in the image.
  */
  value=(char *) NULL;
  final=AllocateString("");
  profile_info=GetImageProfile(image,"EXIF",&profile_length);
  if (profile_info == 0)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "No EXIF profile present");
      goto generate_attribute_failure;
    }
  if (logging && debug)
    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                          "EXIF: profile_info=%p, profile_length=%" MAGICK_SIZE_T_F "u",
                          profile_info, (MAGICK_SIZE_T) profile_length);
  /*
    If EXIF data exists, then try to parse the request for a tag in
    the form "EXIF:key".
  */
  key=(char *) NULL;
  if (strlen(specification) > 5)
    {
      key=(char *) &specification[5]; /* "EXIF:key" */
    }
  else
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "No EXIF:key found");
      goto generate_attribute_failure;
    }
  while (isspace((int) (*key)))
    key++;
  all=0;
  tag=(-1);
  switch(*key)
    {
      /*
        Caller has asked for all the tags in the EXIF data.
      */
    case '*':
      {
        tag=0;
        all=1; /* return the data in description=value format */
        break;
      }
    case '!':
      {
        tag=0;
        all=2; /* return the data in tageid=value format */
        break;
      }
      /*
        Check for a hex based tag specification first.
      */
    case '#':
      {
        char
          c;

        size_t
          n;

        tag=0;
        key++;
        n=strlen(key);
        if (n != 4)
          {
            if (logging)
              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                    "EXIF: Hex tag not 4 bytes");
            goto generate_attribute_failure;
          }
        else
          {
            /*
              Parse tag specification as a hex number.
            */
            n/=4;
            do
              {
                for (i=n; i > 0; i--)
                  {
                    c=(*key++);
                    tag<<=4;
                    if ((c >= '0') && (c <= '9'))
                      tag|=c-'0';
                    else
                      if ((c >= 'A') && (c <= 'F'))
                        tag|=c-('A'-10);
                      else
                        if ((c >= 'a') && (c <= 'f'))
                          tag|=c-('a'-10);
                        else
                          {
                            if (logging)
                              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                    "EXIF: Failed to parse hex tag");
                            goto generate_attribute_failure;
                          }
                  }
              } while (*key != '\0');
          }
        break;
      }
    default:
      {
        /*
          Try to match the text with a tag name instead.
        */
        tag=EXIFIfdTagDescriptionToTagId(key);
        if (logging && debug)
          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                "EXIF: Found tag %d for key \"%s\"",tag,key);
        break;
      }
    }
  if (tag < 0)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: Negative tag value!");
      goto generate_attribute_failure;;
    }
  length=profile_length;
  info=(unsigned char *) profile_info;
  while (length != 0)
    {
      if (ReadByte(&info,&length) != 0x45)
        continue;
      if (ReadByte(&info,&length) != 0x78)
        continue;
      if (ReadByte(&info,&length) != 0x69)
        continue;
      if (ReadByte(&info,&length) != 0x66)
        continue;
      if (ReadByte(&info,&length) != 0x00)
        continue;
      if (ReadByte(&info,&length) != 0x00)
        continue;
      break;
    }
  if (length < 16)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: Tag length length < 16 (have %" MAGICK_SIZE_T_F "u )",
                              (MAGICK_SIZE_T)length);
      goto generate_attribute_failure;
    }
  tiffp=info;
  tiffp_max=tiffp+length;
  id=Read16u(0,tiffp);
  morder=0;
  if (id == 0x4949) /* LSB */
    morder=0;
  else
    if (id == 0x4D4D) /* MSB */
      morder=1;
    else
      {
        if (logging)
          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                "EXIF: Unknown byte order (%04x)",
                                morder);
        goto generate_attribute_failure;
      }
  if (Read16u(morder,tiffp+2) != 0x002a)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: Expected 0x002a!");
      goto generate_attribute_failure;
    }
  /*
    This is the offset to the first IFD.
  */
  offset=Read32u(morder,tiffp+4);
  if (offset >= length)
    {
      if (logging)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: Offset (%u) is > length (%" MAGICK_SIZE_T_F "u)!",
                              offset, (MAGICK_SIZE_T) length);
      goto generate_attribute_failure;
    }
  /*
    Set the pointer to the first IFD and follow it were it leads.
  */
  ifdp=tiffp+offset;
  level=0;
  de=0U;
  do
    {
      /*
        If there is anything on the stack then pop it off.
      */
      if (level > 0)
        {
          level--;
          ifdp=ifdstack[level];
          de=destack[level];
          gpsfound=gpsfoundstack[level];
        }
      /*
        Determine how many entries there are in the current IFD.
        Limit the number of entries parsed to MAX_TAGS_PER_IFD.
      */
      if ((ifdp < tiffp) || (ifdp+2 > tiffp_max))
        {
          if (logging)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: ifdp out of range!");
          goto generate_attribute_failure;
        }
      nde=Read16u(morder,ifdp);
      if (logging && debug)
        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                              "EXIF: IFD at offset %" MAGICK_SSIZE_T_F "d has %u tags",
                              (MAGICK_SSIZE_T) (ifdp-tiffp), nde);
      if (nde > MAX_TAGS_PER_IFD)
        {
          nde=MAX_TAGS_PER_IFD;
          if (logging && debug)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: Limiting IFD at offset %" MAGICK_SSIZE_T_F "d to %u tags!",
                                  (MAGICK_SSIZE_T) (ifdp-tiffp), nde);
        }
      for (; de < nde; de++)
        {
          size_t
            n;

          unsigned int
            c,
            f,
            t;

          unsigned char
            *pde,
            *pval;

          pde=(unsigned char *) (ifdp+2+(12*(size_t) de));
          if (logging && debug)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: PDE offset %" MAGICK_SSIZE_T_F "d", (MAGICK_SSIZE_T) (pde-ifdp));
          if ((pde < tiffp) || (pde + 12 > tiffp_max))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Invalid Exif, entry is beyond metadata limit.");
              goto generate_attribute_failure;
            }
          t=Read16u(morder,pde); /* get tag value */
          f=Read16u(morder,pde+2); /* get the format */
          if (logging && debug)
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "EXIF: Tag %u, Format %u", t, f);
          if (((size_t) f >= ArraySize(format_bytes)) || (format_bytes[f] == 0))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Invalid Exif, unsupported format %u.",(unsigned) f);
              break;
            }
          c=Read32u(morder,pde+4); /* get number of components */
          n=MagickArraySize(c,format_bytes[f]);
          if (logging && debug)
            {
              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                    "EXIF: %u components, %u bytes per component", c,format_bytes[f]);
            }
          if ((c > length) || (n > length) || ((n == 0) && (c != 0) && (format_bytes[f] != 0)))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Invalid Exif, too many components (%u components).",c);
              goto generate_attribute_failure;
            }
          if (n <= 4)
            {
              pval=(unsigned char *) pde+8;
            }
          else
            {
              size_t
                oval;

              /*
                The directory entry contains an offset.
              */
              oval=Read32u(morder,pde+8);
              if ((oval > length) || ((oval+n) > length)) /* Impossibly long! */
                {
                  if (logging && debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "EXIF: Invalid Exif directory entry!"
                                          " (offset %" MAGICK_SIZE_T_F "u, %" MAGICK_SIZE_T_F "u components)",
                                          (MAGICK_SIZE_T) oval, (MAGICK_SIZE_T) n);
                  continue;
                }
              pval=(unsigned char *)(tiffp+oval);
            }

          if ((pval < tiffp) || (pval > tiffp_max))
            {
              if (logging)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                      (MAGICK_SSIZE_T) (pval-tiffp));
              goto generate_attribute_failure;
            }

          if (gpsfound)
            {
              if (/* (t < GPS_TAG_START) || */ (t > GPS_TAG_STOP))
                {
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "EXIF: Skipping bogus GPS IFD tag %d ...",t);
                  continue;
                }
            }
          else
            {
              if ((t < EXIF_TAG_START) || ( t > EXIF_TAG_STOP))
                {
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "EXIF: Skipping bogus EXIF IFD tag %d ...",t);
                  continue;
                }
            }

          /* if (logging && debug) */
          {
            const char *ifd_type;
            int valid = MagickTrue;

            if (gpsfound)
              ifd_type="GPS";
            else
              ifd_type="EXIF";

            /*
              Enable logging via:

              MAGICK_DEBUG=transform MAGICK_DEBUG_EXIF=TRUE gm convert file.jpg -format '%[EXIF:*]' info:-
            */

            {
              /*
                For a given IFD type and tag, validate that the claimed format and components are valid.
              */
              const IFDTagTableType *key_p = FindEXIFTableEntryByTag(t,tag_table,ArraySize(tag_table));
              if (key_p)
                {
                  /* Validate format */
                  ExifFmtStatus fmt_status = ValidateExifFmtAgainstBitField(key_p,f);

                  switch (fmt_status)
                    {
                    case ExifFmtGood:
                      break;
                    case ExifFmtFishy:
                      /* Support tracing tags which use the wrong field type */
                      if (logging)
                        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                              "%s IFD: TagVal=%d (0x%04x) TagDescr=\"%s\" Fishy field type %d (%s)",
                                              ifd_type,
                                              t,t,
                                              EXIFIfdTagToDescription(t,tag_description), f, EXIFIfdFieldTypeToStr(f));
                      break;
                    case ExifFmtBad:
                      valid=MagickFalse;
                      break;
                    }

                  /* Validate number of components */
                  if (!((key_p->count == AnyCount) || (key_p->count <= 0) || (c <= (unsigned int) key_p->count)))
                    {
                      if (logging)
                        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                              "%s IFD: TagVal=%d (0x%04x) TagDescr=\"%s\" Expected %u components (have %u)",
                                              ifd_type,
                                              t,t,
                                              EXIFIfdTagToDescription(t,tag_description), (unsigned int) key_p->count, c);
                      valid=MagickFalse;
                    }
                }
            }

            if (logging)
              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                    "%s IFD: TagVal=%d (0x%04x) TagDescr=\"%s\" Format=%d "
                                    "FormatDescr=\"%s\" Components=%u Valid=%s",
                                    ifd_type,
                                    t,t,
                                    EXIFIfdTagToDescription(t,tag_description),f,
                                    EXIFIfdFieldTypeToStr(f),c,
                                    valid == MagickFail ? "No" : "Yes");
            if (valid != MagickTrue)
              {
                if (logging & debug)
                  (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                        "Skipping bogus %s tag %d (0x%04X) ...",ifd_type,t,t);
                continue;
              }
          }


          /*
            Return values for all the tags, or for a specific requested tag.

            Tags from the GPS sub-IFD are in a bit of a chicken and
            egg situation in that the tag for the GPS sub-IFD will not
            be seen unless we pass that tag through so it can be
            processed.  So we pass the GPS_OFFSET tag through, but if
            it was not requested, then we don't return a string value
            for it.
          */
          if (all || (tag == (int) t) || (GPS_OFFSET == t))
            {
              char
                s[MaxTextExtent];

              switch (f)
                {
                case EXIF_FMT_SBYTE:
                  {
                    /* 8-bit signed integer */
                    MagickFormatString(s,sizeof(s),"%d",(int) (*(char *) pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_BYTE:
                  {
                    /* 8-bit unsigned integer */
                    value=MagickAllocateMemory(char *,n+1);
                    if (value != (char *) NULL)
                      {
                        unsigned int
                          a;

                        for (a=0; a < n; a++)
                          {
                            value[a]='.';
                            if (isprint((int) pval[a]))
                              value[a]=pval[a];
                          }
                        value[a]='\0';
                        break;
                      }
#if 0
                    printf("format %u, length %u\n",f,n);
                    MagickFormatString(s,sizeof(s),"%ld",(long) (*(unsigned char *) pval));
                    value=AllocateString(s);
#endif
                    break;
                  }
                case EXIF_FMT_SSHORT:
                  {
                    /* 16-bit signed integer */
                    if (((pval < tiffp) || (pval+sizeof(magick_uint16_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    MagickFormatString(s,sizeof(s),"%hd",Read16u(morder,pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_USHORT:
                  {
                    /* 16-bit unsigned integer */
                    if ((pval < tiffp) || ((pval+sizeof(magick_uint16_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    MagickFormatString(s,sizeof(s),"%hu",Read16s(morder,pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_ULONG:
                  {
                    if ((pval < tiffp) || ((pval+sizeof(magick_uint32_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    offset=Read32u(morder,pval);
                    /*
                      Only report value if this tag was requested.
                    */
                    if (all || (tag == (int) t))
                      {
                        MagickFormatString(s,sizeof(s),"%u",offset);
                        value=AllocateString(s);
                      }
                    if (GPS_OFFSET == t)
                      {
                        gpsoffset=offset;
                      }
                    break;
                  }
                case EXIF_FMT_SLONG:
                  {
                    if ((pval < tiffp) || ((pval+sizeof(magick_uint32_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    MagickFormatString(s,sizeof(s),"%d",(int) Read32s(morder,pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_URATIONAL:
                  {
                    if (gpsfound &&
                        (t == GPS_LATITUDE ||
                         t == GPS_LONGITUDE ||
                         t == GPS_TIMESTAMP))
                      {
                        if ((pval < tiffp) || ((pval+6*sizeof(magick_uint32_t)) > tiffp_max))
                          {
                            if (logging)
                              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                    "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                    (MAGICK_SSIZE_T) (pval-tiffp));
                            goto generate_attribute_failure;
                          }
                        MagickFormatString(s,MaxTextExtent,"%u/%u,%u/%u,%u/%u"
                                     ,(unsigned) Read32u(morder,pval),
                                     (unsigned) Read32u(morder,4+pval)
                                     ,(unsigned) Read32u(morder,8+pval),
                                     (unsigned) Read32u(morder,12+pval)
                                     ,(unsigned) Read32u(morder,16+pval),
                                     (unsigned) Read32u(morder,20+pval)
                                     );
                      }
                    else
                      {
                        if ((pval < tiffp) || ((pval+2*sizeof(magick_uint32_t)) > tiffp_max))
                          {
                            if (logging)
                              (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                    "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                    (MAGICK_SSIZE_T) (pval-tiffp));
                            goto generate_attribute_failure;
                          }
                        MagickFormatString(s,sizeof(s),"%u/%u"
                                     ,(unsigned) Read32u(morder,pval),
                                     (unsigned) Read32u(morder,4+pval)
                                     );
                      }
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_SRATIONAL:
                  {
                    if ((pval < tiffp) || ((pval+2*sizeof(magick_uint32_t)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    MagickFormatString(s,sizeof(s),"%d/%d",(int) Read32s(morder,pval),
                                 (int) Read32s(morder,4+pval));
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_SINGLE:
                  {
                    float fval;
                    if ((pval < tiffp) || ((pval+sizeof(float)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    (void) memcpy(&fval,pval,sizeof(fval));
                    MagickFormatString(s,sizeof(s),"%f",(double) fval);
                    value=AllocateString(s);
                    break;
                  }
                case EXIF_FMT_DOUBLE:
                  {
                    double dval;
                    if ((pval < tiffp) || ((pval+sizeof(double)) > tiffp_max))
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    (void) memcpy(&dval,pval,sizeof(dval));
                    MagickFormatString(s,sizeof(s),"%f",dval);
                    value=AllocateString(s);
                    break;
                  }
                default:
                case EXIF_FMT_UNDEFINED:
                case EXIF_FMT_ASCII:
                  {
                    unsigned int
                      a;

                    size_t
                      allocation_size;

                    MagickBool
                      binary=MagickFalse;

                    if (logging)
                      (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                            "EXIF: pval=%p (offset=%" MAGICK_SSIZE_T_F "d), n=%" MAGICK_SIZE_T_F "u",
                                            pval, (MAGICK_SSIZE_T) (pval-tiffp), (MAGICK_SIZE_T) n);

                    if ((pval < tiffp) || (pval+n) > tiffp_max)
                      {
                        if (logging)
                          (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                                "EXIF: Offset %" MAGICK_SSIZE_T_F "d out of valid range!",
                                                (MAGICK_SSIZE_T) (pval-tiffp));
                        goto generate_attribute_failure;
                      }
                    allocation_size=n+1;
                    for (a=0; a < n; a++)
                      {
                        if (!(isprint((int) pval[a])))
                          allocation_size += 3;
                      }

                    value=MagickAllocateMemory(char *,allocation_size);
                    if (value != (char *) NULL)
                      {
                        i=0;
                        for (a=0; a < n; a++)
                          {
                            if ((f == EXIF_FMT_ASCII) && (pval[a] == '\0'))
                              break;
                            if ((isprint((int) pval[a])) ||
                                ((pval[a] == '\0') &&
                                 (a == (n-1) && (!binary))))
                              {
                                value[i++]=pval[a];
                              }
                            else
                              {
                                i += snprintf(&value[i],(allocation_size-i),"\\%03o",
                                              (unsigned int) pval[a]);
                                binary |= MagickTrue;
                              }
                          }
                        value[i]='\0';
                      }
                    break;
                  }
                }
              if (value != (char *) NULL)
                {
                  const char
                    *description;

                  if (strlen(final) != 0)
                    (void) ConcatenateString(&final,EXIF_DELIMITER);
                  description=(const char *) NULL;
                  switch (all)
                    {
                    case 1:
                      {
                        description=EXIFIfdTagToDescription(t,tag_description);
                        MagickFormatString(s,sizeof(s),"%.1024s=",description);
                        (void) ConcatenateString(&final,s);
                        break;
                      }
                    case 2:
                      {
                        MagickFormatString(s,sizeof(s),"#%04x=",t);
                        (void) ConcatenateString(&final,s);
                        break;
                      }
                    }
                  (void) ConcatenateString(&final,value);
                  MagickFreeMemory(value);
                }
            }
          if (t == GPS_OFFSET && (gpsoffset != 0))
            {
              if ((gpsoffset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Push our current directory state onto the stack.
                  */
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+gpsoffset;
                  destack[level]=0;
                  gpsfoundstack[level]=MagickTrue;
                  level++;
                }
              gpsoffset=0;
              break; /* break out of the for loop */
            }

          if ((t == TAG_EXIF_OFFSET) || (t == TAG_INTEROP_OFFSET))
            {
              offset=Read32u(morder,pval);
              if (logging & debug)
                (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                      "EXIF: %s at offset %u",
                                      t == TAG_EXIF_OFFSET ? "TAG_EXIF_OFFSET" :
                                      "TAG_INTEROP_OFFSET", offset);
              if ((offset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Check that we are not being directed to read an
                    IFD that we are already parsing and quit in order
                    to avoid a loop.
                  */
                  unsigned char *new_ifdp = tiffp+offset;
                  MagickBool dup_ifd = MagickFalse;

                  if (new_ifdp == ifdp)
                    {
                      dup_ifd = MagickTrue;
                    }
                  else
                    {
                      for (i=0; i < level; i++)
                        {
                          if (ifdstack[i] == new_ifdp)
                            {
                              dup_ifd = MagickTrue;
                              break;
                            }
                        }
                    }
                  if (dup_ifd)
                    {
                      if (logging)
                        (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                              "EXIF: Duplicate IFD detected, quitting to avoid loop!");
                      goto generate_attribute_failure;
                    }

                  /*
                    Push our current directory state onto the stack.
                  */
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "ifdstack[%u]=%p", level, ifdp);
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+offset;
                  if (logging & debug)
                    (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                          "ifdstack[%u]=%p", level, ifdp);
                  destack[level]=0;
                  gpsfoundstack[level]=MagickFalse;
                  level++;
                }
              break; /* break out of the for loop */
            }
        }
    } while (level > 0);
  if (strlen(final) == 0)
    (void) ConcatenateString(&final,"unknown");

  (void) SetImageAttribute(image,specification,(const char *) NULL);
  (void) SetImageAttribute(image,specification,(const char *) final);
  MagickFreeMemory(final);
  return(MagickPass);
 generate_attribute_failure:
  MagickFreeMemory(final);
  return MagickFail;
}

/*
  Generate an aggregate attribute result based on a wildcard
  specification like "foo:*".
*/
static int
GenerateWildcardAttribute(Image *image,const char *key)
{
  char
    *result=NULL;

  size_t
    key_length=0;

  register ImageAttribute
    *p = (ImageAttribute *) NULL;

  MagickPassFail
    status=MagickFail;

  /*
    Support a full "*" wildcard.
  */
  if (strcmp("*",key) == 0)
    {
      (void) GenerateIPTCAttribute((Image *) image,"IPTC:*");
      (void) Generate8BIMAttribute((Image *) image,"8BIM:*");
      (void) GenerateEXIFAttribute((Image *) image,"EXIF:*");
    }

  key_length=strlen(key)-1;
  for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
    if (LocaleNCompare(key,p->key,key_length) == 0)
      {
        char
          s[MaxTextExtent];

        if (result != NULL)
          (void) ConcatenateString(&result,"\n");
        MagickFormatString(s,sizeof(s),"%.512s=%.1024s",p->key,p->value);
        (void) ConcatenateString(&result,s);
      }

  if (result != NULL)
    {
      status=SetImageAttribute(image,key,result);
      MagickFreeMemory(result);
    }
  return status;
}

MagickExport const ImageAttribute *
GetImageAttribute(const Image *image,const char *key)
{
  register ImageAttribute
    *p = (ImageAttribute *) NULL;

  size_t
    key_length=0;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);

  /*
    If key is null, then return a pointer to the attribute list.
  */
  if (key == (char *) NULL)
    return(image->attributes);

  key_length=strlen(key);

  for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
    if (LocaleCompare(key,p->key) == 0)
      return(p);

  if (LocaleNCompare("IPTC:",key,5) == 0)
    {
      /*
        Create an attribute named "IPTC:*" with all matching
        key=values and return it.
      */
      if (GenerateIPTCAttribute((Image *) image,key) == MagickPass)
        return(GetImageAttribute(image,key));
    }
  else if (LocaleNCompare("8BIM:",key,5) == 0)
    {
      /*
        Create an attribute named "8BIM:*" with all matching
        key=values and return it.
      */
      if (Generate8BIMAttribute((Image *) image,key) == MagickPass)
        return(GetImageAttribute(image,key));
    }
  else if (LocaleNCompare("EXIF:",key,5) == 0)
    {
      /*
        Create an attribute named "EXIF:*" with all matching
        key=values and return it.
      */
      if (GenerateEXIFAttribute((Image *) image,key) == MagickPass)
        return(GetImageAttribute(image,key));
    }
  else if ((key_length >=2) && (key[key_length-1] == '*'))
    {
      /*
        Create an attribute named "foo:*" with all matching
        key=values and return it.
      */
      if (GenerateWildcardAttribute((Image *) image,key) == MagickPass)
        return(GetImageAttribute(image,key));
    }
  else if ((key_length ==1) && (key[0] == '*'))
    {
      /*
        Create an attribute named "*" with all key=values and return
        it.
      */
      if (GenerateWildcardAttribute((Image *) image,key) == MagickPass)
        return(GetImageAttribute(image,key));
    }
  return(p);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t I m a g e C l i p p i n g P a t h A t t r i b u t e                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method GetImageClippingPathAttribute searches the list of image attributes
%  and returns a pointer to a clipping path if it exists otherwise NULL.
%
%  The format of the GetImageClippingPathAttribute method is:
%
%      const ImageAttribute *GetImageClippingPathAttribute(const Image *image)
%
%  A description of each parameter follows:
%
%    o attribute:  Method GetImageClippingPathAttribute returns the clipping
%      path if it exists otherwise NULL.
%
%    o image: The image.
%
%
*/
MagickExport const ImageAttribute *
GetImageClippingPathAttribute(const Image *image)
{
  /* Get the name of the clipping path, if any.  The clipping path
     length is indicated by the first character of the Pascal
     string. */
  const ImageAttribute *path_name = GetImageAttribute(image, "8BIM:2999,2999");
  if ((path_name != (const ImageAttribute *) NULL) &&
      (path_name->length > 2) &&
      ((size_t) path_name->value[0] < path_name->length))
    {
      static const char clip_prefix[] = "8BIM:1999,2998";
      char attr_name[271];
      /*sprintf(attr_name, "%s:%.255s", clip_prefix, path_name->value+1);*/
      sprintf(attr_name, "%s:%.*s", clip_prefix, Min(255,(int) path_name->length-1),
              path_name->value+1);
      return GetImageAttribute(image, attr_name);
    }
  return NULL;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   G e t I m a g e I n f o A t t r i b u t e                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  GetImageInfoAttribute() returns a "fake" attribute based on data in the
%  image info or image structures.
%
%  The format of the GetImageInfoAttribute method is:
%
%      const ImageAttribute *GetImageAttribute(const ImageInfo *image_info,
%        const Image *image,const char *key)
%
%  A description of each parameter follows:
%
%    o attribute:  Method GetImageInfoAttribute returns the attribute if it
%      exists otherwise NULL.
%
%    o image_info: The imageInfo.
%
%    o image: The image.
%
%    o key:  These character strings are the name of an image attribute to
%      return.
%
*/
MagickExport const ImageAttribute *
GetImageInfoAttribute(const ImageInfo *image_info,const Image *image,
                      const char *key)
{
  char
    attribute[MaxTextExtent],
    filename[MaxTextExtent];

  attribute[0]='\0';
  switch(*(key))
    {
    case 'b':
      {
        if (LocaleNCompare("base",key,2) == 0)
          {
            GetPathComponent(image->magick_filename,BasePath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'd':
      {
        if (LocaleNCompare("depth",key,2) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"%u",image->depth);
            break;
          }
        if (LocaleNCompare("directory",key,2) == 0)
          {
            GetPathComponent(image->magick_filename,HeadPath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'e':
      {
        if (LocaleNCompare("extension",key,2) == 0)
          {
            GetPathComponent(image->magick_filename,ExtensionPath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'g':
      {
        if (LocaleNCompare("group",key,2) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"0x%lx",image_info->group);
            break;
          }
        break;
      }
    case 'h':
      {
        if (LocaleNCompare("height",key,2) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"%lu",
                         image->magick_rows ? image->magick_rows : 256L);
            break;
          }
        break;
      }
    case 'i':
      {
        if (LocaleNCompare("input",key,2) == 0)
          {
            (void) strlcpy(attribute,image->filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'm':
      {
        if (LocaleNCompare("magick",key,2) == 0)
          {
            (void) strlcpy(attribute,image->magick,MaxTextExtent);
            break;
          }
        break;
      }
    case 'n':
      {
        if (LocaleNCompare("name",key,2) == 0)
          {
            /* What should this really be? */
            GetPathComponent(image->magick_filename,BasePath,filename);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 's':
      {
        if (LocaleNCompare("size",key,2) == 0)
          {
            char
              format[MaxTextExtent];

            FormatSize(GetBlobSize(image),format);
            MagickFormatString(attribute,sizeof(attribute),"%.1024s",format);
            break;
          }
        if (LocaleNCompare("scene",key,2) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"%lu",image->scene);
            if (image_info->subrange != 0)
              MagickFormatString(attribute,sizeof(attribute),"%lu",image_info->subimage);
            break;
          }
        if (LocaleNCompare("scenes",key,6) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"%lu",
                         (unsigned long) GetImageListLength(image));
            break;
          }
        break;
      }
    case 'o':
      {
        if (LocaleNCompare("output",key,2) == 0)
          {
            (void) strlcpy(attribute,image_info->filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'p':
      {
        if (LocaleNCompare("page",key,2) == 0)
          {
            register const Image
              *p;

            unsigned int
              page;

            p=image;
            for (page=1; p->previous != (Image *) NULL; page++)
              p=p->previous;
            MagickFormatString(attribute,sizeof(attribute),"%u",page);
            break;
          }
        break;
      }
    case 'u':
      {
        if (LocaleNCompare("unique",key,2) == 0)
          {
            (void) strlcpy(filename,image_info->unique,MaxTextExtent);
            if (*filename == '\0')
              if(!AcquireTemporaryFileName(filename))
                return((ImageAttribute *) NULL);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    case 'w':
      {
        if (LocaleNCompare("width",key,2) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"%lu",
                         image->magick_columns ? image->magick_columns : 256L);
            break;
          }
        break;
      }
    case 'x':
      {
        if (LocaleNCompare("xresolution",key,2) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"%g",image->x_resolution);
            break;
          }
        break;
      }
    case 'y':
      {
        if (LocaleNCompare("yresolution",key,2) == 0)
          {
            MagickFormatString(attribute,sizeof(attribute),"%g",image->y_resolution);
            break;
          }
        break;
      }
    case 'z':
      {
        if (LocaleNCompare("zero",key,2) == 0)
          {
            (void) strlcpy(filename,image_info->zero,MaxTextExtent);
            if (*filename == '\0')
              if(!AcquireTemporaryFileName(filename))
                return((ImageAttribute *) NULL);
            (void) strlcpy(attribute,filename,MaxTextExtent);
            break;
          }
        break;
      }
    }
  if (strlen(image->magick_filename) != 0)
    return(GetImageAttribute(image,key));
  return((ImageAttribute *) NULL);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t I m a g e A t t r i b u t e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetImageAttribute() searches the list of image attributes and replaces the
%  attribute value.  If it is not found in the list, the attribute name
%  and value is added to the list.   If the attribute exists in the list,
%  the value is concatenated to the attribute.  SetImageAttribute returns
%  True if the attribute is successfully concatenated or added to the list,
%  otherwise False.  If the value is NULL, the matching key is deleted
%  from the list.
%
%  There is special handling for the EXIF:Orientation attribute. Setting this
%  attribute will also update the EXIF tag in the image's EXIF profile to the
%  given value provided an EXIF profile exists and has an existing EXIF
%  orientation tag and the attribute value is a valid orientation
%  (see orientationType). The attribute value will be set regardless of
%  whether the EXIF profile was successfully updated. The new
%  EXIF:Orientation attribute replaces the existing value rather than
%  being concatenated to it as when setting other attributes.
%
%  The 'comment' and 'label' attributes are treated specially in that
%  embedded format specifications are translated according to the formatting
%  rules of TranslateText().
%
%  The format of the SetImageAttribute method is:
%
%      unsigned int SetImageAttribute(Image *image,const char *key,
%        const char *value)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o key,value:  These character strings are the name and value of an image
%      attribute to replace or add to the list.
%
%
*/

/*
  Find the location of an EXIF attribute in an EXIF profile. The EXIF attribute
  to be found is specified as its numeric tag value (see tag_table). Returns
  a pointer to the attribute in the EXIF profile or NULL if missing or there
  is an error parsing the profile. Returns the EXIF profile byte order if the
  morderp parameter is not NULL.
*/

static unsigned char *
FindEXIFAttribute(const unsigned char *profile_info,
                  const size_t profile_length,
                  const unsigned short tag, int *morderp)
{
  char
    tag_description[MaxTextExtent];

  int
    id,
    level,
    morder;

  size_t
    length;

  unsigned long
    offset;

  unsigned char
    *tiffp,
    *tiffp_max,
    *ifdstack[DE_STACK_SIZE],
    *ifdp,
    *info,
    *attribp;

  unsigned int
    de,
    destack[DE_STACK_SIZE],
    nde;

  MagickBool
    gpsfoundstack[DE_STACK_SIZE],
    gpsfound;

  MagickBool
    debug=MagickFalse;

  attribp = (unsigned char *)NULL;

  assert((ArraySize(format_bytes)-1) == EXIF_NUM_FORMATS);

  {
    const char *
      env_value;

    /*
      Allow enabling debug of EXIF tags
    */
    if ((env_value=getenv("MAGICK_DEBUG_EXIF")))
      {
        if (LocaleCompare(env_value,"TRUE") == 0)
          debug=MagickTrue;
      }
  }
  gpsfound=MagickFalse;
  length=profile_length;
  info=(unsigned char *) profile_info;
  while (length != 0)
    {
      if (ReadByte(&info,&length) != 0x45)
        continue;
      if (ReadByte(&info,&length) != 0x78)
        continue;
      if (ReadByte(&info,&length) != 0x69)
        continue;
      if (ReadByte(&info,&length) != 0x66)
        continue;
      if (ReadByte(&info,&length) != 0x00)
        continue;
      if (ReadByte(&info,&length) != 0x00)
        continue;
      break;
    }
  if (length < 16)
    goto find_attribute_failure;
  tiffp=info;
  tiffp_max=tiffp+length;
  id=Read16u(0,tiffp);
  morder=0;
  if (id == 0x4949) /* LSB */
    morder=0;
  else
    if (id == 0x4D4D) /* MSB */
      morder=1;
    else
      goto find_attribute_failure;
  if (morderp)
    *morderp = morder;
  if (Read16u(morder,tiffp+2) != 0x002a)
    goto find_attribute_failure;
  /*
    This is the offset to the first IFD.
  */
  offset=Read32u(morder,tiffp+4);
  if (offset >= length)
    goto find_attribute_failure;
  /*
    Set the pointer to the first IFD and follow it were it leads.
  */
  ifdp=tiffp+offset;
  level=0;
  de=0U;
  do
    {
      /*
        If there is anything on the stack then pop it off.
      */
      if (level > 0)
        {
          level--;
          ifdp=ifdstack[level];
          de=destack[level];
          gpsfound=gpsfoundstack[level];
        }
      /*
        Determine how many entries there are in the current IFD.
        Limit the number of entries parsed to MAX_TAGS_PER_IFD.
      */
      if ((ifdp < tiffp) || (ifdp+2 > tiffp_max))
        goto find_attribute_failure;
      nde=Read16u(morder,ifdp);
      if (nde > MAX_TAGS_PER_IFD)
        nde=MAX_TAGS_PER_IFD;
      for (; de < nde; de++)
        {
          size_t
            n;

          unsigned int
            c,
            f,
            t;

          unsigned char
            *pde,
            *pval;


          pde=(unsigned char *) (ifdp+2+(12*(size_t) de));
          if (pde + 12 > tiffp + length)
            {
              if (debug)
                fprintf(stderr, "EXIF: Invalid Exif, entry is beyond metadata limit.\n");
              goto find_attribute_failure;
            }
          t=Read16u(morder,pde); /* get tag value */
          f=Read16u(morder,pde+2); /* get the format */
          if ((size_t) f >= ArraySize(format_bytes))
            break;
          c=Read32u(morder,pde+4); /* get number of components */
          n=MagickArraySize(c,format_bytes[f]);
          if ((n == 0) && (c != 0) && (format_bytes[f] != 0))
            {
              if (debug)
                fprintf(stderr, "EXIF: Invalid Exif, too many components (%u).\n",c);
              goto find_attribute_failure;
            }
          if (n <= 4)
            pval=(unsigned char *) pde+8;
          else
            {
              unsigned long
                oval;

              /*
                The directory entry contains an offset.
              */
              oval=Read32u(morder,pde+8);
              if ((oval+n) > length)
                continue;
              pval=(unsigned char *)(tiffp+oval);
            }

          if (debug)
            {
              fprintf(stderr,
                      "EXIF: TagVal=%d  TagDescr=\"%s\" Format=%d  "
                      "FormatDescr=\"%s\"  Components=%u\n",t,
                      EXIFIfdTagToDescription(t,tag_description),f,
                      EXIFIfdFieldTypeToStr(f),c);
            }

          if (gpsfound)
            {
              if (/* (t < GPS_TAG_START) || */ (t > GPS_TAG_STOP))
                {
                  if (debug)
                    fprintf(stderr,
                            "EXIF: Skipping bogus GPS IFD tag %d (0x%04X) ...\n",t,t);
                  continue;
                }
            }
          else
            {
              if ((t < EXIF_TAG_START) || ( t > EXIF_TAG_STOP))
                {
                  if (debug)
                    fprintf(stderr,
                            "EXIF: Skipping bogus EXIF IFD tag %d (0x%04X) ...\n",t,t);
                  continue;
                }
            }

          /*
            Return values for all the tags, or for a specific requested tag.

            Tags from the GPS sub-IFD are in a bit of a chicken and
            egg situation in that the tag for the GPS sub-IFD will not
            be seen unless we pass that tag through so it can be
            processed.  So we pass the GPS_OFFSET tag through, but if
            it was not requested, then we don't return a string value
            for it.
          */
          if (tag == t)
            {
              attribp = pde;
              break;
            }

          if (t == GPS_OFFSET)
            {
              offset=Read32u(morder,pval);
              if ((offset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Push our current directory state onto the stack.
                  */
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+offset;
                  destack[level]=0;
                  gpsfoundstack[level]=MagickTrue;
                  level++;
                }
              break; /* break out of the for loop */
            }

          if ((t == TAG_EXIF_OFFSET) || (t == TAG_INTEROP_OFFSET))
            {
              offset=Read32u(morder,pval);
              if ((offset < length) && (level < (DE_STACK_SIZE-2)))
                {
                  /*
                    Push our current directory state onto the stack.
                  */
                  ifdstack[level]=ifdp;
                  de++; /* bump to the next entry */
                  destack[level]=de;
                  gpsfoundstack[level]=gpsfound;
                  level++;
                  /*
                    Push new state onto of stack to cause a jump.
                  */
                  ifdstack[level]=tiffp+offset;
                  destack[level]=0;
                  gpsfoundstack[level]=MagickFalse;
                  level++;
                }
              break; /* break out of the for loop */
            }
        }
    } while (!attribp && (level > 0));
  return attribp;
 find_attribute_failure:
  return (unsigned char *)NULL;
}

/*
  SetEXIFOrientation() updates the EXIF orientation tag in the image's EXIF
  profile to the value provided. Returns MagickPass on success or MagickFail
  if either there is no EXIF profile in the image, there was an error parsing
  the EXIF profile, there was no existing EXIF orientation attribute in
  the EXIF profile or there was a memory allocation error.
*/

static MagickPassFail
SetEXIFOrientation(Image *image, const int orientation)
{
  MagickPassFail
    result;

  const unsigned char
    *current_profile;

  size_t
    profile_length;

  unsigned char
    *orientp,
    *pval,
    *new_profile;

  int
    morder,
    current_orientation;

  unsigned short
    f;

  unsigned long
    c;

  if (orientation < TopLeftOrientation || orientation > LeftBottomOrientation)
    return(MagickFail);

  current_profile=GetImageProfile(image,"EXIF",&profile_length);
  if (current_profile == 0)
    return(MagickFail);

  /* Clone profile so orientation can be set */
  new_profile = MagickAllocateMemory(unsigned char *,profile_length);
  if (new_profile == 0)
    return(MagickFail);

  result = MagickFail;
  memcpy(new_profile, current_profile, profile_length);
  orientp = FindEXIFAttribute(new_profile, profile_length,
                              (unsigned short)EXIF_ORIENTATION, &morder);
  if (orientp)
    {
      /* Make sure EXIF orientation attribute is valid */
      f=Read16u(morder,orientp+2); /* get the format */
      c=Read32u(morder,orientp+4); /* get number of components */
      if ((f == EXIF_FMT_USHORT) && (c == 1))
        {
          pval=(unsigned char *) orientp+8;
          current_orientation=(int)Read16u(morder, pval);
          if (current_orientation != (unsigned short)orientation)
            {
              Write16u(morder, pval, orientation);
              Write16u(morder, pval+2, 0);
              result=SetImageProfile(image,"EXIF",new_profile,profile_length);
            }
          else
            result = MagickPass;
        }
    }
  MagickFreeMemory(new_profile);

  return result;
}

MagickExport MagickPassFail
SetImageAttribute(Image *image,const char *key,const char *value)
{
  ImageAttribute
    *attribute;

  register ImageAttribute
    *p;

  /*
    Initialize new attribute.
  */
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if ((key == (const char *) NULL) || (*key == '\0'))
    return(MagickFail);

  if (value == (const char *) NULL)
    {
      /*
        Delete attribute from the image attributes list.
      */
      for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
        if (LocaleCompare(key,p->key) == 0)
          break;
      if (p == (ImageAttribute *) NULL)
        return(MagickFail);
      if (p->previous != (ImageAttribute *) NULL)
        p->previous->next=p->next;
      else
        {
          image->attributes=p->next;
          if (p->next != (ImageAttribute *) NULL)
            p->next->previous=(ImageAttribute *) NULL;
        }
      if (p->next != (ImageAttribute *) NULL)
        p->next->previous=p->previous;
      attribute=p;
      DestroyImageAttribute(attribute);
      return(MagickPass);
    }
  attribute=MagickAllocateMemory(ImageAttribute *,sizeof(ImageAttribute));
  if (attribute == (ImageAttribute *) NULL)
    return(MagickFail);
  attribute->key=AllocateString(key);
  attribute->length=strlen(value);
  attribute->value=MagickAllocateMemory(char *,attribute->length+1);
  if (attribute->value != (char *) NULL)
    (void) strlcpy(attribute->value,value,attribute->length+1);
  if ((attribute->value == (char *) NULL) ||
      (attribute->key == (char *) NULL))
    {
      DestroyImageAttribute(attribute);
      return(MagickFail);
    }

  attribute->previous=(ImageAttribute *) NULL;
  attribute->next=(ImageAttribute *) NULL;
  if (image->attributes == (ImageAttribute *) NULL)
    {
      image->attributes=attribute;
      return(MagickPass);
    }
  for (p=image->attributes; p != (ImageAttribute *) NULL; p=p->next)
    {
      if (LocaleCompare(attribute->key,p->key) == 0)
        {
          size_t
            min_l,
            realloc_l;

          if (LocaleCompare(attribute->key,"EXIF:Orientation") == 0)
            {
              int
                orientation = 0;

              /*
                Special handling for EXIF orientation tag.
                If new value differs from existing value,
                EXIF profile is updated as well if it exists and
                is valid. Don't append new value to existing value,
                replace it instead.
              */
              if ((MagickAtoIChk(value, &orientation) == MagickPass) &&
                  (orientation > 0 || orientation <= (int)LeftBottomOrientation))
                {
                  SetEXIFOrientation(image, orientation);
                }
              /* Assign changed value to attribute in list */
              if (LocaleCompare(p->value, attribute->value) != 0)
                {
                  MagickFreeMemory(p->value);
                  p->value=attribute->value;
                  attribute->value = (char *) NULL;
                }
              DestroyImageAttribute(attribute);
              return(MagickPass);
            }
          else
            {
              /*
                Extend existing text string.
              */
              min_l=p->length+attribute->length+1;
              for (realloc_l=2; realloc_l <= min_l; realloc_l *= 2)
                { /* nada */};
              MagickReallocMemory(char *,p->value,realloc_l);
              if (p->value != (char *) NULL)
                {
                  (void) memcpy(p->value+p->length,attribute->value,min_l-p->length-1);
                  p->length += attribute->length;
                  p->value[p->length] = '\0';
                }
              DestroyImageAttribute(attribute);
            }
          if (p->value != (char *) NULL)
            return(MagickPass);
          (void) SetImageAttribute(image,key,NULL);
          return(MagickFail);
        }
      if (p->next == (ImageAttribute *) NULL)
        break;
    }
  /*
    Place new attribute at the end of the attribute list.
  */
  attribute->previous=p;
  p->next=attribute;
  return(MagickPass);
}
