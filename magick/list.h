/*
  Copyright (C) 2003-2026 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  ImageMagick Image List Methods.
*/
#ifndef _MAGICK_LIST_H
#define _MAGICK_LIST_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern MagickExport Image
  *CloneImageList(const Image *images,ExceptionInfo *exception),
  *GetFirstImageInList(const Image *images) MAGICK_FUNC_PURE,
  *GetImageFromList(const Image *images,const long offset) MAGICK_FUNC_PURE,
  *GetLastImageInList(const Image *images) MAGICK_FUNC_PURE,
  *GetNextImageInList(const Image *images) MAGICK_FUNC_PURE,
  *GetPreviousImageInList(const Image *images) MAGICK_FUNC_PURE,
  **ImageListToArray(const Image *images, ExceptionInfo *exception) MAGICK_FUNC_NONNULL(2),
  *NewImageList(void) MAGICK_FUNC_CONST,
  *RemoveLastImageFromList(Image **images) MAGICK_FUNC_NONNULL(),
  *RemoveFirstImageFromList(Image **images) MAGICK_FUNC_NONNULL(),
  *SplitImageList(Image *images),
  *SyncNextImageInList(const Image *images);

extern MagickExport long
  GetImageIndexInList(const Image *images) MAGICK_FUNC_PURE;

extern MagickExport unsigned long
  GetImageListLength(const Image *images) MAGICK_FUNC_PURE;

extern MagickExport void
  AppendImageToList(Image **images,Image *image),
  DeleteImageFromList(Image **images) MAGICK_FUNC_NONNULL(),
  DestroyImageList(Image *images),
  InsertImageInList(Image **images,Image *image) MAGICK_FUNC_NONNULL(),
  PrependImageToList(Image **images,Image *image),
  ReplaceImageInList(Image **images,Image *image) MAGICK_FUNC_NONNULL(),
  ReverseImageList(Image **images) MAGICK_FUNC_NONNULL(),
  SpliceImageIntoList(Image **images,const unsigned long length,Image *splice) MAGICK_FUNC_NONNULL();

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
