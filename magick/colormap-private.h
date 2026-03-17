/*
  Copyright (C) 2003-2026 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio
  Copyright 1991-1999 E. I. du Pont de Nemours and Company

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Colormap Methods
*/

#define VerifyColormapIndexWithColors(status,image,index,colors)        \
{ \
  if (index >= colors) \
    { \
      if ((status != MagickFail) && (image->exception.severity < CorruptImageError)) \
        { \
          char \
            colormapIndexBuffer[MaxTextExtent]; \
          \
          MagickFormatString(colormapIndexBuffer, sizeof(colormapIndexBuffer), \
                       "index %" MAGICK_SIZE_T_F "u >= %u colors, %.1024s", \
                       (MAGICK_SIZE_T) index, (unsigned int) colors, image->filename); \
          errno=0; \
          ThrowException(&image->exception,CorruptImageError, \
                         InvalidColormapIndex,colormapIndexBuffer); \
        } \
      index=0U; \
      status=MagickFail; \
    } \
}

#define VerifyColormapIndex(status,image,index) \
{ \
  VerifyColormapIndexWithColors(status,image,index,image->colors)       \
}

extern MagickExport unsigned int
  MagickConstrainColormapIndex(Image *image, unsigned int index) MAGICK_FUNC_DEPRECATED;

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
