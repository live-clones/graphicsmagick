/* Copyright (C) 2003-2026 GraphicsMagick Group */
/* SPDX-License-Identifier: MIT */
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%               DDDD   RRRR    AAA   W   W  IIIII  N   N    GGGG              %
%               D   D  R   R  A   A  W   W    I    NN  N   G                  %
%               D   D  RRRR   AAAAA  W   W    I    N N N   G  GG              %
%               D   D  R R    A   A  W W W    I    N  NN   G   G              %
%               DDDD   R  R   A   A   W W   IIIII  N   N    GGG               %
%                                                                             %
%                         W   W   AAA   N   N  DDDD                           %
%                         W   W  A   A  NN  N  D   D                          %
%                         W W W  AAAAA  N N N  D   D                          %
%                         WW WW  A   A  N  NN  D   D                          %
%                         W   W  A   A  N   N  DDDD                           %
%                                                                             %
%                                                                             %
%                 GraphicsMagick Image Vector Drawing Methods                 %
%                                                                             %
%                              Software Design                                %
%                              Bob Friesenhahn                                %
%                                March 2002                                   %
%                                                                             %
%                                                                             %
%  Copyright (C) 2003 ImageMagick Studio, a non-profit organization dedicated %
%  to making software imaging solutions freely available.                     %
%                                                                             %
%  Permission is hereby granted, free of charge, to any person obtaining a    %
%  copy of this software and associated documentation files ("ImageMagick"),  %
%  to deal in ImageMagick without restriction, including without limitation   %
%  the rights to use, copy, modify, merge, publish, distribute, sublicense,   %
%  and/or sell copies of ImageMagick, and to permit persons to whom the       %
%  ImageMagick is furnished to do so, subject to the following conditions:    %
%                                                                             %
%  The above copyright notice and this permission notice shall be included in %
%  all copies or substantial portions of ImageMagick.                         %
%                                                                             %
%  The software is provided "as is", without warranty of any kind, express or %
%  implied, including but not limited to the warranties of merchantability,   %
%  fitness for a particular purpose and noninfringement.  In no event shall   %
%  ImageMagick Studio be liable for any claim, damages or other liability,    %
%  whether in an action of contract, tort or otherwise, arising from, out of  %
%  or in connection with ImageMagick or the use or other dealings in          %
%  ImageMagick.                                                               %
%                                                                             %
%  Except as contained in this notice, the name of the ImageMagick Studio     %
%  shall not be used in advertising or otherwise to promote the sale, use or  %
%  other dealings in ImageMagick without prior written authorization from the %
%  ImageMagick Studio.                                                        %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

/*
  Include declarations.
*/
#define MAGICK_EXCLUDE_DRAWING_WAND_MACROS 1
#include "magick/studio.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/draw.h"
#include "magick/enum_strings.h"
#include "magick/error.h"
#include "magick/gem.h"
#include "magick/list.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "wand/magick_wand.h"
#include "wand/wand_private.h"

/*
  Define declarations.
*/
#define CurrentContext  (drawing_wand->graphic_context[drawing_wand->index])

/*
  Typedef declarations.
*/

/*
  Forward declarations.
*/


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C l o n e D r a w i n g W a n d                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  CloneDrawingWand() returns a new drawing wand which is a full (deep) copy
%  of an existing drawing wand.
%
%  The format of the  CloneDrawingWand method is:
%
%      DrawingWand *CloneDrawingWand(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand to copy
%
*/
WandExport DrawingWand *MagickCloneDrawingWand(const DrawingWand *drawing_wand)
{
  return DrawCloneContext(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D e s t r o y D r a w i n g W a n d                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyDrawingWand() frees all resources associated with the drawing
%  wand. Once the drawing wand has been freed, it should not be used
%  any further unless it re-allocated.
%
%  The format of the  DestroyDrawingWand method is:
%
%      void  DestroyDrawingWand(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand to destroy.
%
*/
WandExport void MagickDestroyDrawingWand(DrawingWand *drawing_wand)
{
  DrawDestroyContext(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w A n n o t a t i o n                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawAnnotation() draws text on the image.
%
%  The format of the DrawAnnotation method is:
%
%      void DrawAnnotation(DrawingWand *drawing_wand,const double x,
%        const double y,const unsigned char *text)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: x ordinate to left of text
%
%    o y: y ordinate to text baseline
%
%    o text: text to draw
%
*/
WandExport void MagickDrawAnnotation(DrawingWand *drawing_wand,const double x,
  const double y,const unsigned char *text)
{
  DrawAnnotation(drawing_wand,x,y,text);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w A f f i n e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawAffine() adjusts the current affine transformation matrix with
%  the specified affine transformation matrix. Note that the current affine
%  transform is adjusted rather than replaced.
%
%  The format of the DrawAffine method is:
%
%      void DrawAffine(DrawingWand *drawing_wand,const AffineMatrix *affine)
%
%  A description of each parameter follows:
%
%    o drawing_wand: Drawing drawing_wand
%
%    o affine: Affine matrix parameters
%
*/
WandExport void MagickDrawAffine(DrawingWand *drawing_wand,
  const AffineMatrix *affine)
{
  DrawAffine(drawing_wand,affine);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w A l l o c a t e W a n d                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawAllocateWand() allocates an initial drawing wand which is an
%  opaque handle required by the remaining drawing methods.
%
%  The format of the DrawAllocateWand method is:
%
%      DrawingWand *DrawAllocateWand(const DrawInfo *draw_info,Image *image)
%
%  A description of each parameter follows:
%
%    o draw_info: Initial drawing defaults. Set to NULL to use
%                 GraphicsMagick defaults.
%
%    o image: The image to draw on.
%
*/
WandExport DrawingWand *MagickDrawAllocateWand(const DrawInfo *draw_info,Image *image)
{
  return DrawAllocateContext(draw_info,image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w A r c                                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawArc() draws an arc falling within a specified bounding rectangle on the
%  image.
%
%  The format of the DrawArc method is:
%
%      void DrawArc(DrawingWand *drawing_wand,const double sx,const double sy,
%        const double ex,const double ey,const double sd,const double ed)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o sx: starting x ordinate of bounding rectangle
%
%    o sy: starting y ordinate of bounding rectangle
%
%    o ex: ending x ordinate of bounding rectangle
%
%    o ey: ending y ordinate of bounding rectangle
%
%    o sd: starting degrees of rotation
%
%    o ed: ending degrees of rotation
%
*/
WandExport void MagickDrawArc(DrawingWand *drawing_wand,const double sx,
  const double sy,const double ex,const double ey,const double sd,
  const double ed)
{
  DrawArc(drawing_wand,sx,sy,ex,ey,sd,ed);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w B e z i e r                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawBezier() draws a bezier curve through a set of points on the image.
%
%  The format of the DrawBezier method is:
%
%      void DrawBezier(DrawingWand *drawing_wand,
%        const unsigned long number_coordinates,const PointInfo *coordinates)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o number_coordinates: number of coordinates
%
%    o coordinates: coordinates
%
*/
WandExport void MagickDrawBezier(DrawingWand *drawing_wand,
  const unsigned long number_coordinates,const PointInfo *coordinates)
{
  DrawBezier(drawing_wand,number_coordinates,coordinates);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w C i r c l e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawCircle() draws a circle on the image.
%
%  The format of the DrawCircle method is:
%
%      void DrawCircle(DrawingWand *drawing_wand,const double ox,
%        const double oy,const double px, const double py)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o ox: origin x ordinate
%
%    o oy: origin y ordinate
%
%    o px: perimeter x ordinate
%
%    o py: perimeter y ordinate
%
*/
WandExport void MagickDrawCircle(DrawingWand *drawing_wand,const double ox,
  const double oy,const double px,const double py)
{
  DrawCircle(drawing_wand,ox,oy,px,py);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w C l e a r E x c e p t i o n                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawClearException() clears any existing exception from the drawing wand.
%
%  The format of the DrawClearException method is:
%
%      PassFail DrawClearException(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport MagickBool MagickDrawClearException(DrawingWand *drawing_wand)
{
  return DrawClearException(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t C l i p P a t h                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetClipPath() obtains the current clipping path ID. The value returned
%  must be deallocated by the user when it is no longer needed.
%
%  The format of the DrawGetClipPath method is:
%
%      char *DrawGetClipPath(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport char *MagickDrawGetClipPath(const DrawingWand *drawing_wand)
{
  return DrawGetClipPath(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t C l i p P a t h                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetClipPath() associates a named clipping path with the image.  Only
%  the areas drawn on by the clipping path will be modified as long as it
%  remains in effect.
%
%  The format of the DrawSetClipPath method is:
%
%      void DrawSetClipPath(DrawingWand *drawing_wand,const char *clip_path)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o clip_path: name of clipping path to associate with image
%
*/
WandExport void MagickDrawSetClipPath(DrawingWand *drawing_wand,
  const char *clip_path)
{
  DrawSetClipPath(drawing_wand,clip_path);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t C l i p R u l e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetClipRule() returns the current polygon fill rule to be used by the
%  clipping path.
%
%  The format of the DrawGetClipRule method is:
%
%     FillRule DrawGetClipRule(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport FillRule MagickDrawGetClipRule(const DrawingWand *drawing_wand)
{
  return DrawGetClipRule(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t C l i p R u l e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetClipRule() set the polygon fill rule to be used by the clipping path.
%
%  The format of the DrawSetClipRule method is:
%
%      void DrawSetClipRule(DrawingWand *drawing_wand,const FillRule fill_rule)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o fill_rule: fill rule (EvenOddRule or NonZeroRule)
%
*/
WandExport void MagickDrawSetClipRule(DrawingWand *drawing_wand,
  const FillRule fill_rule)
{
  DrawSetClipRule(drawing_wand,fill_rule);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t C l i p U n i t s                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetClipUnits() returns the interpretation of clip path units.
%
%  The format of the DrawGetClipUnits method is:
%
%      ClipPathUnits DrawGetClipUnits(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport ClipPathUnits MagickDrawGetClipUnits(const DrawingWand *drawing_wand)
{
  return  DrawGetClipUnits(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t E x c e p t i o n                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetException() obtains error information associated with the last
%  exception (if any).  If an exception did occur, an allocated text string
%  is returned which contains a detailed description of the exception.  This
%  string must be deallocated by the user once it is no longer needed.
%
%  The format of the DrawGetException method is:
%
%      char *DrawGetException(const DrawingWand *drawing_wand,
%                             ExceptionType *severity)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o severity: Enumeration corresponding to last thrown exception.
%
*/
WandExport char *MagickDrawGetException(const DrawingWand *drawing_wand,
                                        ExceptionType *severity)
{
  return DrawGetException(drawing_wand,severity);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t C l i p U n i t s                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetClipUnits() sets the interpretation of clip path units.
%
%  The format of the DrawSetClipUnits method is:
%
%      void DrawSetClipUnits(DrawingWand *drawing_wand,
%        const ClipPathUnits clip_units)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o clip_units: units to use (UserSpace, UserSpaceOnUse, or ObjectBoundingBox)
%
*/
WandExport void MagickDrawSetClipUnits(DrawingWand *drawing_wand,
  const ClipPathUnits clip_units)
{
  return DrawSetClipUnits(drawing_wand,clip_units);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w C o l o r                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawColor() draws color on image using the current fill color, starting at
%  specified position, and using specified paint method. The available paint
%  methods are:
%
%    PointMethod: Recolors the target pixel
%    ReplaceMethod: Recolor any pixel that matches the target pixel.
%    FloodfillMethod: Recolors target pixels and matching neighbors.
%    FillToBorderMethod: Recolor target pixels and neighbors not matching
$      border color.
%    ResetMethod: Recolor all pixels.
%
%  The format of the DrawColor method is:
%
%      void DrawColor(DrawingWand *drawing_wand,const double x,const double y,
%        const PaintMethod paintMethod)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: x ordinate
%
%    o y: y ordinate
%
%    o paintMethod: paint method
%
*/
WandExport void MagickDrawColor(DrawingWand *drawing_wand,const double x,
  const double y,const PaintMethod paintMethod)
{
  return DrawColor(drawing_wand,x,y,paintMethod);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w C o m m e n t                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawComment() adds a comment to a vector output stream.
%
%  The format of the DrawComment method is:
%
%      void DrawComment(DrawingWand *drawing_wand,const char *comment)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o comment: comment text
%
*/
WandExport void MagickDrawComment(DrawingWand *drawing_wand,const char* comment)
{
  return DrawComment(drawing_wand,comment);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w E l l i p s e                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawEllipse() draws an ellipse on the image.
%
%  The format of the DrawEllipse method is:
%
%       void DrawEllipse(DrawingWand *drawing_wand,const double ox,
%         const double oy,const double rx,const double ry,const double start,
%         const double end)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o ox: origin x ordinate
%
%    o oy: origin y ordinate
%
%    o rx: radius in x
%
%    o ry: radius in y
%
%    o start: starting rotation in degrees
%
%    o end: ending rotation in degrees
%
*/
WandExport void MagickDrawEllipse(DrawingWand *drawing_wand,const double ox,
  const double oy,const double rx,const double ry,const double start,
  const double end)
{
  return DrawEllipse(drawing_wand,ox,oy,rx,ry,start,end);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F i l l C o l o r                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFillColor() returns the fill color used for drawing filled objects.
%
%  The format of the DrawGetFillColor method is:
%
%      void DrawGetFillColor(const DrawingWand *drawing_wand,
%        PixelWand *fill_color)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o fill_color: Return the fill color.
%
*/
WandExport void MagickDrawGetFillColor(const DrawingWand *drawing_wand,
  PixelWand *fill_color)
{
  PixelPacket fill=DrawGetFillColor(drawing_wand);
  PixelSetQuantumColor(fill_color,&fill);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F i l l C o l o r                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFillColor() sets the fill color to be used for drawing filled objects.
%
%  The format of the DrawSetFillColor method is:
%
%      void DrawSetFillColor(DrawingWand *drawing_wand,
%        const PixelWand *fill_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o fill_wand: fill wand.
%
*/
WandExport void MagickDrawSetFillColor(DrawingWand *drawing_wand,
  const PixelWand *fill_wand)
{
  PixelPacket
    fill_color;

  assert(drawing_wand != (DrawingWand *) NULL);
  assert(fill_wand != (const PixelWand *) NULL);
  PixelGetQuantumColor(fill_wand,&fill_color);
  DrawSetFillColor(drawing_wand,&fill_color);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F i l l P a t t e r n U R L                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFillPatternURL() sets the URL to use as a fill pattern for filling
%  objects. Only local URLs ("#identifier") are supported at this time. These
%  local URLs are normally created by defining a named fill pattern with
%  DrawPushPattern/DrawPopPattern.
%
%  The format of the DrawSetFillPatternURL method is:
%
%      void DrawSetFillPatternURL(DrawingWand *drawing_wand,
%        const char *fill_url)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o fill_url: URL to use to obtain fill pattern.
%
*/
WandExport void MagickDrawSetFillPatternURL(DrawingWand *drawing_wand,
  const char* fill_url)
{
  DrawSetFillPatternURL(drawing_wand,fill_url);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F i l l O p a c i t y                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFillOpacity() returns the opacity used when drawing using the fill
%  color or fill texture.  Fully opaque is 1.0.
%
%  The format of the DrawGetFillOpacity method is:
%
%      double DrawGetFillOpacity(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport double MagickDrawGetFillOpacity(const DrawingWand *drawing_wand)
{
  return DrawGetFillOpacity(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F i l l O p a c i t y                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFillOpacity() sets the opacity to use when drawing using the fill
%  color or fill texture.  Fully opaque is 1.0.
%
%  The format of the DrawSetFillOpacity method is:
%
%      void DrawSetFillOpacity(DrawingWand *drawing_wand,
%        const double fill_opacity)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o fill_opacity: fill opacity
%
*/
WandExport void MagickDrawSetFillOpacity(DrawingWand *drawing_wand,
  const double fill_opacity)
{
  DrawSetFillOpacity(drawing_wand,fill_opacity);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F i l l R u l e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFillRule() returns the fill rule used while drawing polygons.
%
%  The format of the DrawGetFillRule method is:
%
%      FillRule DrawGetFillRule(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport FillRule MagickDrawGetFillRule(const DrawingWand *drawing_wand)
{
  return DrawGetFillRule(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F i l l R u l e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFillRule() sets the fill rule to use while drawing polygons.
%
%  The format of the DrawSetFillRule method is:
%
%      void DrawSetFillRule(DrawingWand *drawing_wand,const FillRule fill_rule)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o fill_rule: fill rule (EvenOddRule or NonZeroRule)
%
*/
WandExport void MagickDrawSetFillRule(DrawingWand *drawing_wand,
  const FillRule fill_rule)
{
  DrawSetFillRule(drawing_wand,fill_rule);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F o n t                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFont() returns a null-terminaged string specifying the font used
%  when annotating with text. The value returned must be freed by the user
%  when no longer needed.
%
%  The format of the DrawGetFont method is:
%
%      char *DrawGetFont(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport char *MagickDrawGetFont(const DrawingWand *drawing_wand)
{
  return DrawGetFont(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F o n t                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFont() sets the fully-sepecified font to use when annotating with
%  text.
%
%  The format of the DrawSetFont method is:
%
%      void DrawSetFont(DrawingWand *drawing_wand,const char *font_name)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o font_name: font name
%
*/
WandExport void MagickDrawSetFont(DrawingWand *drawing_wand,const char *font_name)
{
  DrawSetFont(drawing_wand,font_name);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F o n t F a m i l y                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFontFamily() returns the font family to use when annotating with text.
%  The value returned must be freed by the user when it is no longer needed.
%
%  The format of the DrawGetFontFamily method is:
%
%      char *DrawGetFontFamily(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport char *MagickDrawGetFontFamily(const DrawingWand *drawing_wand)
{
  return DrawGetFontFamily(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F o n t F a m i l y                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFontFamily() sets the font family to use when annotating with text.
%
%  The format of the DrawSetFontFamily method is:
%
%      void DrawSetFontFamily(DrawingWand *drawing_wand,const char *font_family)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o font_family: font family
%
*/
WandExport void MagickDrawSetFontFamily(DrawingWand *drawing_wand,
  const char *font_family)
{
  DrawSetFontFamily(drawing_wand,font_family);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F o n t S i z e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFontSize() returns the font pointsize used when annotating with text.
%
%  The format of the DrawGetFontSize method is:
%
%      double DrawGetFontSize(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport double MagickDrawGetFontSize(const DrawingWand *drawing_wand)
{
  return DrawGetFontSize(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F o n t S i z e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFontSize() sets the font pointsize to use when annotating with text.
%
%  The format of the DrawSetFontSize method is:
%
%      void DrawSetFontSize(DrawingWand *drawing_wand,const double pointsize)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o pointsize: text pointsize
%
*/
WandExport void MagickDrawSetFontSize(DrawingWand *drawing_wand,
  const double pointsize)
{
  DrawSetFontSize(drawing_wand,pointsize);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F o n t S t r e t c h                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFontStretch() returns the font stretch used when annotating with text.
%
%  The format of the DrawGetFontStretch method is:
%
%      StretchType DrawGetFontStretch(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport StretchType MagickDrawGetFontStretch(const DrawingWand *drawing_wand)
{
  return DrawGetFontStretch(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F o n t S t r e t c h                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFontStretch() sets the font stretch to use when annotating with text.
%  The AnyStretch enumeration acts as a wild-card "don't care" option.
%
%  The format of the DrawSetFontStretch method is:
%
%      void DrawSetFontStretch(DrawingWand *drawing_wand,
%        const StretchType font_stretch)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o font_stretch: font stretch (NormalStretch, UltraCondensedStretch,
%                    CondensedStretch, SemiCondensedStretch,
%                    SemiExpandedStretch, ExpandedStretch,
%                    ExtraExpandedStretch, UltraExpandedStretch, AnyStretch)
%
*/
WandExport void MagickDrawSetFontStretch(DrawingWand *drawing_wand,
  const StretchType font_stretch)
{
  DrawSetFontStretch(drawing_wand,font_stretch);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F o n t S t y l e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFontStyle() returns the font style used when annotating with text.
%
%  The format of the DrawGetFontStyle method is:
%
%      StyleType DrawGetFontStyle(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport StyleType MagickDrawGetFontStyle(const DrawingWand *drawing_wand)
{
  return DrawGetFontStyle(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F o n t S t y l e                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFontStyle() sets the font style to use when annotating with text.
%  The AnyStyle enumeration acts as a wild-card "don't care" option.
%
%  The format of the DrawSetFontStyle method is:
%
%      void DrawSetFontStyle(DrawingWand *drawing_wand,const StyleType style)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o style: font style (NormalStyle, ItalicStyle, ObliqueStyle, AnyStyle)
%
*/
WandExport void MagickDrawSetFontStyle(DrawingWand *drawing_wand,
  const StyleType style)
{
  DrawSetFontStyle(drawing_wand,style);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t F o n t W e i g h t                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetFontWeight() returns the font weight used when annotating with text.
%
%  The format of the DrawGetFontWeight method is:
%
%      unsigned long DrawGetFontWeight(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport unsigned long MagickDrawGetFontWeight(const DrawingWand *drawing_wand)
{
  return DrawGetFontWeight(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t F o n t W e i g h t                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetFontWeight() sets the font weight to use when annotating with text.
%
%  The format of the DrawSetFontWeight method is:
%
%      void DrawSetFontWeight(DrawingWand *drawing_wand,
%        const unsigned long font_weight)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o font_weight: font weight (valid range 100-900)
%
*/
WandExport void MagickDrawSetFontWeight(DrawingWand *drawing_wand,
  const unsigned long font_weight)
{
  DrawSetFontWeight(drawing_wand,font_weight);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t G r a v i t y                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetGravity() returns the text placement gravity used when annotating
%  with text.
%
%  The format of the DrawGetGravity method is:
%
%      GravityType DrawGetGravity(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport GravityType MagickDrawGetGravity(const DrawingWand *drawing_wand)
{
  return DrawGetGravity(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t G r a v i t y                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetGravity() sets the text placement gravity to use when annotating
%  with text.
%
%  The format of the DrawSetGravity method is:
%
%      void DrawSetGravity(DrawingWand *drawing_wand,const GravityType gravity)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o gravity: positioning gravity (NorthWestGravity, NorthGravity,
%               NorthEastGravity, WestGravity, CenterGravity,
%               EastGravity, SouthWestGravity, SouthGravity,
%               SouthEastGravity)
%
*/
WandExport void MagickDrawSetGravity(DrawingWand *drawing_wand,
  const GravityType gravity)
{
  DrawSetGravity(drawing_wand,gravity);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w C o m p o s i t e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawComposite() composites an image onto the current image, using the
%  specified composition operator, specified position, and at the specified
%  size.
%
%  The format of the DrawComposite method is:
%
%      void DrawComposite(DrawingWand *drawing_wand,
%        const CompositeOperator composite_operator,const double x,
%        const double y,const double width,const double height,
%        const Image *image)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o composite_operator: composition operator
%
%    o x: x ordinate of top left corner
%
%    o y: y ordinate of top left corner
%
%    o width: Width to resize image to prior to compositing.  Specify zero to
%             use existing width.
%
%    o height: Height to resize image to prior to compositing.  Specify zero
%             to use existing height.
%
%    o image: Image to composite
%
*/
WandExport void MagickDrawComposite(DrawingWand *drawing_wand,
  const CompositeOperator composite_operator,const double x,const double y,
  const double width,const double height,const Image *image)

{
  DrawComposite(drawing_wand,composite_operator,x,y,width,height,image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w L i n e                                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawLine() draws a line on the image using the current stroke color,
%  stroke opacity, and stroke width.
%
%  The format of the DrawLine method is:
%
%      void DrawLine(DrawingWand *drawing_wand,const double sx,const double sy,
%        const double ex,const double ey)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o sx: starting x ordinate
%
%    o sy: starting y ordinate
%
%    o ex: ending x ordinate
%
%    o ey: ending y ordinate
%
*/
WandExport void MagickDrawLine(DrawingWand *drawing_wand,const double sx,
  const double sy,const double ex,const double ey)
{
  DrawLine(drawing_wand,sx,sy,ex,ey);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w M a t t e                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawMatte() paints on the image's opacity channel in order to set effected
%  pixels to transparent.
%  to influence the opacity of pixels. The available paint
%  methods are:
%
%    PointMethod: Select the target pixel
%    ReplaceMethod: Select any pixel that matches the target pixel.
%    FloodfillMethod: Select the target pixel and matching neighbors.
%    FillToBorderMethod: Select the target pixel and neighbors not matching
%                        border color.
%    ResetMethod: Select all pixels.
%
%  The format of the DrawMatte method is:
%
%      void DrawMatte(DrawingWand *drawing_wand,const double x,const double y,
%        const PaintMethod paint_method)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: x ordinate
%
%    o y: y ordinate
%
%    o paint_method:
%
*/
WandExport void MagickDrawMatte(DrawingWand *drawing_wand,const double x,
  const double y,const PaintMethod paint_method)
{
  DrawMatte(drawing_wand,x,y,paint_method);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h C l o s e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathClose() adds a path element to the current path which closes the
%  current subpath by drawing a straight line from the current point to the
%  current subpath's most recent starting point (usually, the most recent
%  moveto point).
%
%  The format of the DrawPathClose method is:
%
%      void DrawPathClose(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPathClose(DrawingWand *drawing_wand)
{
  DrawPathClose(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h C u r v e T o A b s o l u t e                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToAbsolute() draws a cubic Bezier curve from the current
%  point to (x,y) using (x1,y1) as the control point at the beginning of
%  the curve and (x2,y2) as the control point at the end of the curve using
%  absolute coordinates. At the end of the command, the new current point
%  becomes the final (x,y) coordinate pair used in the polybezier.
%
%  The format of the DrawPathCurveToAbsolute method is:
%
%      void DrawPathCurveToAbsolute(DrawingWand *drawing_wand,const double x1,
%        const double y1,const double x2,const double y2,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x1: x ordinate of control point for curve beginning
%
%    o y1: y ordinate of control point for curve beginning
%
%    o x2: x ordinate of control point for curve ending
%
%    o y2: y ordinate of control point for curve ending
%
%    o x: x ordinate of the end of the curve
%
%    o y: y ordinate of the end of the curve
%
*/

/* static void MagickDrawPathCurveTo(DrawingWand *drawing_wand,const DrawPathMode mode, */
/*   const double x1,const double y1,const double x2,const double y2, */
/*   const double x,const double y) */
/* { */
/*   DrawPathCurveToRelative(drawing_wand,mode,x1,y1,x2,y2,x,y); */
/* } */

WandExport void MagickDrawPathCurveToAbsolute(DrawingWand *drawing_wand,
  const double x1,const double y1,const double x2,const double y2,
  const double x,const double y)
{
  DrawPathCurveToAbsolute(drawing_wand,x1,y1,x2,y2,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h C u r v e T o R e l a t i v e                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToRelative() draws a cubic Bezier curve from the current
%  point to (x,y) using (x1,y1) as the control point at the beginning of
%  the curve and (x2,y2) as the control point at the end of the curve using
%  relative coordinates. At the end of the command, the new current point
%  becomes the final (x,y) coordinate pair used in the polybezier.
%
%  The format of the DrawPathCurveToRelative method is:
%
%      void DrawPathCurveToRelative(DrawingWand *drawing_wand,const double x1,
%        const double y1,const double x2,const double y2,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x1: x ordinate of control point for curve beginning
%
%    o y1: y ordinate of control point for curve beginning
%
%    o x2: x ordinate of control point for curve ending
%
%    o y2: y ordinate of control point for curve ending
%
%    o x: x ordinate of the end of the curve
%
%    o y: y ordinate of the end of the curve
%
*/
WandExport void MagickDrawPathCurveToRelative(DrawingWand *drawing_wand,
  const double x1,const double y1,const double x2,const double y2,
  const double x,const double y)
{
  DrawPathCurveToRelative(drawing_wand,x1,y1,x2,y2,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                                %
%                                                                                %
%                                                                                %
%   D r a w P a t h C u r v e T o Q u a d r a t i c B e z i e r A b s o l u t e  %
%                                                                                %
%                                                                                %
%                                                                                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToQuadraticBezierAbsolute() draws a quadratic Bezier curve
%  from the current point to (x,y) using (x1,y1) as the control point using
%  absolute coordinates. At the end of the command, the new current point
%  becomes the final (x,y) coordinate pair used in the polybezier.
%
%  The format of the DrawPathCurveToQuadraticBezierAbsolute method is:
%
%      void DrawPathCurveToQuadraticBezierAbsolute(DrawingWand *drawing_wand,
%        const double x1,const double y1,onst double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x1: x ordinate of the control point
%
%    o y1: y ordinate of the control point
%
%    o x: x ordinate of final point
%
%    o y: y ordinate of final point
%
*/

/* static void MagickDrawPathCurveToQuadraticBezier(DrawingWand *drawing_wand, */
/*   const DrawPathMode mode,const double x1,double y1,const double x,const double y) */
/* { */
/*   DrawPathCurveToQuadraticBezierRelative(drawing_wand,mode,x1,y1,x,y); */
/* } */

WandExport void MagickDrawPathCurveToQuadraticBezierAbsolute(
  DrawingWand *drawing_wand,const double x1,const double y1,const double x,
  const double y)
{
  DrawPathCurveToQuadraticBezierAbsolute(drawing_wand,x1,y1,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                                 %
%                                                                                 %
%                                                                                 %
%   D r a w P a t h C u r v e T o Q u a d r a t i c B e z i e r R e l a t i v e   %
%                                                                                 %
%                                                                                 %
%                                                                                 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToQuadraticBezierRelative() draws a quadratic Bezier curve
%  from the current point to (x,y) using (x1,y1) as the control point using
%  relative coordinates. At the end of the command, the new current point
%  becomes the final (x,y) coordinate pair used in the polybezier.
%
%  The format of the DrawPathCurveToQuadraticBezierRelative method is:
%
%      void DrawPathCurveToQuadraticBezierRelative(DrawingWand *drawing_wand,
%        const double x1,const double y1,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x1: x ordinate of the control point
%
%    o y1: y ordinate of the control point
%
%    o x: x ordinate of final point
%
%    o y: y ordinate of final point
%
*/
WandExport void MagickDrawPathCurveToQuadraticBezierRelative(
  DrawingWand *drawing_wand,const double x1,const double y1,const double x,
  const double y)
{
  DrawPathCurveToQuadraticBezierRelative(drawing_wand,x1,y1,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                                             %
%                                                                                             %
%                                                                                             %
%   D r a w P a t h C u r v e T o Q u a d r a t i c B e z i e r S m o o t h A b s o l u t e   %
%                                                                                             %
%                                                                                             %
%                                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToQuadraticBezierSmoothAbsolute() draws a quadratic
%  Bezier curve (using absolute coordinates) from the current point to
%  (x,y). The control point is assumed to be the reflection of the
%  control point on the previous command relative to the current
%  point. (If there is no previous command or if the previous command was
%  not a DrawPathCurveToQuadraticBezierAbsolute,
%  DrawPathCurveToQuadraticBezierRelative,
%  DrawPathCurveToQuadraticBezierSmoothAbsolute or
%  DrawPathCurveToQuadraticBezierSmoothRelative, assume the control point
%  is coincident with the current point.). At the end of the command, the
%  new current point becomes the final (x,y) coordinate pair used in the
%  polybezier.
%
%  The format of the DrawPathCurveToQuadraticBezierSmoothAbsolute method is:
%
%      void DrawPathCurveToQuadraticBezierSmoothAbsolute(
%        DrawingWand *drawing_wand,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: x ordinate of final point
%
%    o y: y ordinate of final point
%
*/

/* static void MagickDrawPathCurveToQuadraticBezierSmooth(DrawingWand *drawing_wand, */
/*   const DrawPathMode mode,const double x,const double y) */
/* { */
/*   DrawPathCurveToQuadraticBezierSmoothRelative(drawing_wand,mode,x,y); */
/* } */

WandExport void MagickDrawPathCurveToQuadraticBezierSmoothAbsolute(
  DrawingWand *drawing_wand,const double x,const double y)
{
  DrawPathCurveToQuadraticBezierSmoothAbsolute(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                                             %
%                                                                                             %
%                                                                                             %
%   D r a w P a t h C u r v e T o Q u a d r a t i c B e z i e r S m o o t h R e l a t i v e   %
%                                                                                             %
%                                                                                             %
%                                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToQuadraticBezierSmoothRelative() draws a quadratic
%  Bezier curve (using relative coordinates) from the current point to
%  (x,y). The control point is assumed to be the reflection of the
%  control point on the previous command relative to the current
%  point. (If there is no previous command or if the previous command was
%  not a DrawPathCurveToQuadraticBezierAbsolute,
%  DrawPathCurveToQuadraticBezierRelative,
%  DrawPathCurveToQuadraticBezierSmoothAbsolute or
%  DrawPathCurveToQuadraticBezierSmoothRelative, assume the control point
%  is coincident with the current point.). At the end of the command, the
%  new current point becomes the final (x,y) coordinate pair used in the
%  polybezier.
%
%  The format of the DrawPathCurveToQuadraticBezierSmoothRelative method is:
%
%      void DrawPathCurveToQuadraticBezierSmoothRelative(
%        DrawingWand *drawing_wand,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: x ordinate of final point
%
%    o y: y ordinate of final point
%
%
*/
WandExport void MagickDrawPathCurveToQuadraticBezierSmoothRelative(
  DrawingWand *drawing_wand,const double x,const double y)
{
  DrawPathCurveToQuadraticBezierSmoothRelative(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h C u r v e T o S m o o t h A b s o l u t e                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToSmoothAbsolute() draws a cubic Bezier curve from the
%  current point to (x,y) using absolute coordinates. The first control
%  point is assumed to be the reflection of the second control point on
%  the previous command relative to the current point. (If there is no
%  previous command or if the previous command was not an
%  DrawPathCurveToAbsolute, DrawPathCurveToRelative,
%  DrawPathCurveToSmoothAbsolute or DrawPathCurveToSmoothRelative, assume
%  the first control point is coincident with the current point.) (x2,y2)
%  is the second control point (i.e., the control point at the end of the
%  curve). At the end of the command, the new current point becomes the
%  final (x,y) coordinate pair used in the polybezier.
%
%  The format of the DrawPathCurveToSmoothAbsolute method is:
%
%      void DrawPathCurveToSmoothAbsolute(DrawingWand *drawing_wand,
%        const double x2const double y2,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x2: x ordinate of second control point
%
%    o y2: y ordinate of second control point
%
%    o x: x ordinate of termination point
%
%    o y: y ordinate of termination point
%
%
*/
/* static void MagickDrawPathCurveToSmooth(DrawingWand *drawing_wand, */
/*   const DrawPathMode mode,const double x2,const double y2, */
/*   const double x,const double y) */
/* { */
/*   DrawPathCurveToSmoothRelative(drawing_wand,mode,x2,y2,x,y); */
/* } */

WandExport void MagickDrawPathCurveToSmoothAbsolute(DrawingWand *drawing_wand,
  const double x2,const double y2,const double x,const double y)
{
  DrawPathCurveToSmoothAbsolute(drawing_wand,x2,y2,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h C u r v e T o S m o o t h R e l a t i v e                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathCurveToSmoothRelative() draws a cubic Bezier curve from the
%  current point to (x,y) using relative coordinates. The first control
%  point is assumed to be the reflection of the second control point on
%  the previous command relative to the current point. (If there is no
%  previous command or if the previous command was not an
%  DrawPathCurveToAbsolute, DrawPathCurveToRelative,
%  DrawPathCurveToSmoothAbsolute or DrawPathCurveToSmoothRelative, assume
%  the first control point is coincident with the current point.) (x2,y2)
%  is the second control point (i.e., the control point at the end of the
%  curve). At the end of the command, the new current point becomes the
%  final (x,y) coordinate pair used in the polybezier.
%
%  The format of the DrawPathCurveToSmoothRelative method is:
%
%      void DrawPathCurveToSmoothRelative(DrawingWand *drawing_wand,
%        const double x2,const double y2,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x2: x ordinate of second control point
%
%    o y2: y ordinate of second control point
%
%    o x: x ordinate of termination point
%
%    o y: y ordinate of termination point
%
%
*/
WandExport void MagickDrawPathCurveToSmoothRelative(DrawingWand *drawing_wand,
  const double x2,const double y2,const double x,const double y)
{
  DrawPathCurveToSmoothRelative(drawing_wand,x2,y2,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h E l l i p t i c A r c A b s o l u t e                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathEllipticArcAbsolute() draws an elliptical arc from the current
%  point to (x, y) using absolute coordinates. The size and orientation
%  of the ellipse are defined by two radii (rx, ry) and an
%  xAxisRotation, which indicates how the ellipse as a whole is rotated
%  relative to the current coordinate system. The center (cx, cy) of the
%  ellipse is calculated automatically to satisfy the constraints imposed
%  by the other parameters. largeArcFlag and sweepFlag contribute to the
%  automatic calculations and help determine how the arc is drawn. If
%  largeArcFlag is true then draw the larger of the available arcs. If
%  sweepFlag is true, then draw the arc matching a clock-wise rotation.
%
%  The format of the DrawPathEllipticArcAbsolute method is:
%
%      void DrawPathEllipticArcAbsolute(DrawingWand *drawing_wand,
%        const double rx,const double ry,const double x_axis_rotation,
%        unsigned int large_arc_flag,unsigned int sweep_flag,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o rx: x radius
%
%    o ry: y radius
%
%    o x_axis_rotation: indicates how the ellipse as a whole is rotated
%                       relative to the current coordinate system
%
%    o large_arc_flag: If non-zero (true) then draw the larger of the
%                      available arcs
%
%    o sweep_flag: If non-zero (true) then draw the arc matching a
%                  clock-wise rotation
%
%
*/
/* static void MagickDrawPathEllipticArc(DrawingWand *drawing_wand, const DrawPathMode mode, */
/*   const double rx,const double ry,const double x_axis_rotation, */
/*   unsigned int large_arc_flag,unsigned int sweep_flag,const double x, */
/*   const double y) */
/* { */
/*   DrawPathEllipticArcRelative(drawing_wand,mode,rx,ry,x_axis_rotation,large_arc_flag, */
/*                       sweep_flag,x,y); */
/* } */

WandExport void MagickDrawPathEllipticArcAbsolute(DrawingWand *drawing_wand,
  const double rx,const double ry,const double x_axis_rotation,
  unsigned int large_arc_flag,unsigned int sweep_flag,const double x,
  const double y)
{
  DrawPathEllipticArcAbsolute(drawing_wand,rx,ry,x_axis_rotation,large_arc_flag,
                              sweep_flag,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h E l l i p t i c A r c R e l a t i v e                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathEllipticArcRelative() draws an elliptical arc from the current
%  point to (x, y) using relative coordinates. The size and orientation
%  of the ellipse are defined by two radii (rx, ry) and an
%  xAxisRotation, which indicates how the ellipse as a whole is rotated
%  relative to the current coordinate system. The center (cx, cy) of the
%  ellipse is calculated automatically to satisfy the constraints imposed
%  by the other parameters. largeArcFlag and sweepFlag contribute to the
%  automatic calculations and help determine how the arc is drawn. If
%  largeArcFlag is true then draw the larger of the available arcs. If
%  sweepFlag is true, then draw the arc matching a clock-wise rotation.
%
%  The format of the DrawPathEllipticArcRelative method is:
%
%      void DrawPathEllipticArcRelative(DrawingWand *drawing_wand,
%        const double rx,const double ry,const double x_axis_rotation,
%        unsigned int large_arc_flag,unsigned int sweep_flag,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o rx: x radius
%
%    o ry: y radius
%
%    o x_axis_rotation: indicates how the ellipse as a whole is rotated
%                       relative to the current coordinate system
%
%    o large_arc_flag: If non-zero (true) then draw the larger of the
%                      available arcs
%
%    o sweep_flag: If non-zero (true) then draw the arc matching a
%                  clock-wise rotation
%
*/
WandExport void MagickDrawPathEllipticArcRelative(DrawingWand *drawing_wand,
  const double rx,const double ry,const double x_axis_rotation,
  unsigned int large_arc_flag,unsigned int sweep_flag,const double x,
  const double y)
{
  DrawPathEllipticArcRelative(drawing_wand,rx,ry,x_axis_rotation,
                              large_arc_flag,sweep_flag,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h F i n i s h                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathFinish() terminates the current path.
%
%  The format of the DrawPathFinish method is:
%
%      void DrawPathFinish(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPathFinish(DrawingWand *drawing_wand)
{
  DrawPathFinish(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h L i n e T o A b s o l u t e                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathLineToAbsolute() draws a line path from the current point to the
%  given coordinate using absolute coordinates. The coordinate then becomes
%  the new current point.
%
%  The format of the DrawPathLineToAbsolute method is:
%
%      void DrawPathLineToAbsolute(DrawingWand *drawing_wand,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: target x ordinate
%
%    o y: target y ordinate
%
*/
/* static void MagickDrawPathLineTo(DrawingWand *drawing_wand,const DrawPathMode mode, */
/*   const double x,const double y) */
/* { */
/*   DrawPathLineToRelative(drawing_wand,mode,x,y); */
/* } */

WandExport void MagickDrawPathLineToAbsolute(DrawingWand *drawing_wand,
  const double x,const double y)
{
  DrawPathLineToAbsolute(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h L i n e T o R e l a t i v e                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathLineToRelative() draws a line path from the current point to the
%  given coordinate using relative coordinates. The coordinate then becomes
%  the new current point.
%
%  The format of the DrawPathLineToRelative method is:
%
%      void DrawPathLineToRelative(DrawingWand *drawing_wand,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: target x ordinate
%
%    o y: target y ordinate
%
*/
WandExport void MagickDrawPathLineToRelative(DrawingWand *drawing_wand,
  const double x,const double y)
{
  DrawPathLineToRelative(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                                %
%                                                                                %
%                                                                                %
%   D r a w P a t h L i n e T o H o r i z o n t a l A b s o l u t e              %
%                                                                                %
%                                                                                %
%                                                                                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathLineToHorizontalAbsolute() draws a horizontal line path from the
%  current point to the target point using absolute coordinates.  The target
%  point then becomes the new current point.
%
%  The format of the DrawPathLineToHorizontalAbsolute method is:
%
%      void DrawPathLineToHorizontalAbsolute(DrawingWand *drawing_wand,
%        const PathMode mode,const double x)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: target x ordinate
%
*/

/* static void MagickDrawPathLineToHorizontal(DrawingWand *drawing_wand, */
/*   const DrawPathMode mode,const double x) */
/* { */
/*   DrawPathLineToHorizontalRelative(drawing_wand,mode,x); */
/* } */

WandExport void MagickDrawPathLineToHorizontalAbsolute(DrawingWand *drawing_wand,
  const double x)
{
  DrawPathLineToHorizontalAbsolute(drawing_wand,x);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                                %
%                                                                                %
%                                                                                %
%   D r a w P a t h L i n e T o H o r i z o n t a l R e l a t i v e              %
%                                                                                %
%                                                                                %
%                                                                                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathLineToHorizontalRelative() draws a horizontal line path from the
%  current point to the target point using relative coordinates.  The target
%  point then becomes the new current point.
%
%  The format of the DrawPathLineToHorizontalRelative method is:
%
%      void DrawPathLineToHorizontalRelative(DrawingWand *drawing_wand,
%        const double x)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: target x ordinate
%
*/
WandExport void MagickDrawPathLineToHorizontalRelative(DrawingWand *drawing_wand,
  const double x)
{
  DrawPathLineToHorizontalRelative(drawing_wand,x);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h L i n e T o V e r t i c a l A b s o l u t e               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathLineToVerticalAbsolute() draws a vertical line path from the
%  current point to the target point using absolute coordinates.  The target
%  point then becomes the new current point.
%
%  The format of the DrawPathLineToVerticalAbsolute method is:
%
%      void DrawPathLineToVerticalAbsolute(DrawingWand *drawing_wand,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o y: target y ordinate
%
*/

/* static void MagickDrawPathLineToVertical(DrawingWand *drawing_wand, */
/*   const DrawPathMode mode,const double y) */
/* { */
/*   DrawPathLineToVerticalRelative(drawing_wand,mode,y); */
/* } */

WandExport void MagickDrawPathLineToVerticalAbsolute(DrawingWand *drawing_wand,
  const double y)
{
  DrawPathLineToVerticalAbsolute(drawing_wand,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h L i n e T o V e r t i c a l R e l a t i v e               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathLineToVerticalRelative() draws a vertical line path from the
%  current point to the target point using relative coordinates.  The target
%  point then becomes the new current point.
%
%  The format of the DrawPathLineToVerticalRelative method is:
%
%      void DrawPathLineToVerticalRelative(DrawingWand *drawing_wand,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o y: target y ordinate
%
*/
WandExport void MagickDrawPathLineToVerticalRelative(DrawingWand *drawing_wand,
  const double y)
{
  DrawPathLineToVerticalRelative(drawing_wand,y);
}
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h M o v e T o A b s o l u t e                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathMoveToAbsolute() starts a new sub-path at the given coordinate
%  using absolute coordinates. The current point then becomes the
%  specified coordinate.
%
%  The format of the DrawPathMoveToAbsolute method is:
%
%      void DrawPathMoveToAbsolute(DrawingWand *drawing_wand,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: target x ordinate
%
%    o y: target y ordinate
%
*/
/* static void MagickDrawPathMoveTo(DrawingWand *drawing_wand,const DrawPathMode mode, */
/*   const double x,const double y) */
/* { */
/*   DrawPathMoveToRelative(drawing_wand,mode,x,y); */
/* } */

WandExport void MagickDrawPathMoveToAbsolute(DrawingWand *drawing_wand,
  const double x,const double y)
{
  DrawPathMoveToAbsolute(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h M o v e T o R e l a t i v e                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathMoveToRelative() starts a new sub-path at the given coordinate
%  using relative coordinates. The current point then becomes the
%  specified coordinate.
%
%  The format of the DrawPathMoveToRelative method is:
%
%      void DrawPathMoveToRelative(DrawingWand *drawing_wand,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: target x ordinate
%
%    o y: target y ordinate
%
*/
WandExport void MagickDrawPathMoveToRelative(DrawingWand *drawing_wand,
  const double x,const double y)
{
  DrawPathMoveToRelative(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P a t h S t a r t                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPathStart() declares the start of a path drawing list which is terminated
%  by a matching DrawPathFinish() command. All other DrawPath commands must
%  be enclosed between a DrawPathStart() and a DrawPathFinish() command. This
%  is because path drawing commands are subordinate commands and they do not
%  function by themselves.
%
%  The format of the DrawPathStart method is:
%
%      void DrawPathStart(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPathStart(DrawingWand *drawing_wand)
{
  DrawPathStart(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P e e k G r a p h i c C o n t e x t                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPeekGraphicContext() returns a copy of the the DrawInfo structure at
%  the head of the drawing context stack. The user is responsible for
%  deallocating the returned object using DestroyDrawInfo.
%
%  The format of the DrawPeekGraphicContext method is:
%
%      DrawInfo *DrawPeekGraphicContext(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport DrawInfo *MagickDrawPeekGraphicContext(const DrawingWand *drawing_wand)
{
  /*
    FIXME: The Wand API user should not need to use a function outside
    of the wand API for cleanup.  An alternative is to return a const
    pointer and advise the user that the returned pointer may become
    obsolete.
  */

  return DrawPeekGraphicContext(drawing_wand);}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P o i n t                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPoint() draws a point using the current stroke color and stroke
%  thickness at the specified coordinates.
%
%  The format of the DrawPoint method is:
%
%      void DrawPoint(DrawingWand *drawing_wand,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: target x coordinate
%
%    o y: target y coordinate
%
*/
WandExport void MagickDrawPoint(DrawingWand *drawing_wand,const double x,
  const double y)
{
  DrawPoint(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P o l y g o n                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPolygon() draws a polygon using the current stroke, stroke width, and
%  fill color or texture, using the specified array of coordinates.
%
%  The format of the DrawPolygon method is:
%
%      void DrawPolygon(DrawingWand *drawing_wand,
%        const unsigned long number_coordinates,const PointInfo *coordinates)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o number_coordinates: number of coordinates
%
%    o coordinates: coordinate array
%
*/
WandExport void MagickDrawPolygon(DrawingWand *drawing_wand,
  const unsigned long number_coordinates,const PointInfo *coordinates)
{
  DrawPolygon(drawing_wand,number_coordinates,coordinates);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P o l y l i n e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPolyline() draws a polyline using the current stroke, stroke width, and
%  fill color or texture, using the specified array of coordinates.
%
%  The format of the DrawPolyline method is:
%
%      void DrawPolyline(DrawingWand *drawing_wand,
%        const unsigned long number_coordinates,const PointInfo *coordinates)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o number_coordinates: number of coordinates
%
%    o coordinates: coordinate array
%
*/
WandExport void MagickDrawPolyline(DrawingWand *drawing_wand,
  const unsigned long number_coordinates,const PointInfo *coordinates)
{
  DrawPolyline(drawing_wand,number_coordinates,coordinates);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P o p C l i p P a t h                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPopClipPath() terminates a clip path definition.
%
%  The format of the DrawPopClipPath method is:
%
%      void DrawPopClipPath(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPopClipPath(DrawingWand *drawing_wand)
{
  DrawPopClipPath(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P o p D e f s                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPopDefs() terminates a definition list
%
%  The format of the DrawPopDefs method is:
%
%      void DrawPopDefs(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPopDefs(DrawingWand *drawing_wand)
{
  DrawPopDefs(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P o p G r a p h i c C o n t e x t                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPopGraphicContext() destroys the current drawing_wand returning to the
%  previously pushed drawing wand. Multiple drawing wand  may exist. It is an
%  error to attempt to pop more drawing_wands than have been pushed, and it is
%  proper form to pop all drawing_wands which have been pushed.
%
%  The format of the DrawPopGraphicContext method is:
%
%      void DrawPopGraphicContext(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPopGraphicContext(DrawingWand *drawing_wand)
{
  DrawPopGraphicContext(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P o p P a t t e r n                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPopPattern() terminates a pattern definition.
%
%  The format of the DrawPopPattern method is:
%
%      void DrawPopPattern(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPopPattern(DrawingWand *drawing_wand)
{
  DrawPopPattern(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P u s h C l i p P a t h                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPushClipPath() starts a clip path definition which is comprized of
%  any number of drawing commands and terminated by a DrawPopClipPath()
%  command.
%
%  The format of the DrawPushClipPath method is:
%
%      void DrawPushClipPath(DrawingWand *drawing_wand,const char *clip_path_id)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o clip_path_id: string identifier to associate with the clip path for
%      later use.
%
*/
WandExport void MagickDrawPushClipPath(DrawingWand *drawing_wand,
  const char *clip_path_id)
{
  DrawPushClipPath(drawing_wand,clip_path_id);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P u s h D e f s                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPushDefs() indicates that commands up to a terminating DrawPopDefs()
%  command create named elements (e.g. clip-paths, textures, etc.) which
%  may safely be processed earlier for the sake of efficiency.
%
%  The format of the DrawPushDefs method is:
%
%      void DrawPushDefs(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPushDefs(DrawingWand *drawing_wand)
{
  DrawPushDefs(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P u s h G r a p h i c C o n t e x t                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPushGraphicContext() clones the current drawing wand to create a
%  new drawing wand. The original drawing drawing_wand(s) may be returned to
%  by invoking DrawPopGraphicContext().  The drawing wands are stored on a
%  drawing wand stack.  For every Pop there must have already been an
%  equivalent Push.
%
%  The format of the DrawPushGraphicContext method is:
%
%      void DrawPushGraphicContext(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport void MagickDrawPushGraphicContext(DrawingWand *drawing_wand)
{
  DrawPushGraphicContext(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w P u s h P a t t e r n                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawPushPattern() indicates that subsequent commands up to a
%  DrawPopPattern() command comprise the definition of a named pattern.
%  The pattern space is assigned top left corner coordinates, a width
%  and height, and becomes its own drawing space.  Anything which can
%  be drawn may be used in a pattern definition.
%  Named patterns may be used as stroke or brush definitions.
%
%  The format of the DrawPushPattern method is:
%
%      void DrawPushPattern(DrawingWand *drawing_wand,const char *pattern_id,
%        const double x,const double y,const double width,const double height)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o pattern_id: pattern identification for later reference
%
%    o x: x ordinate of top left corner
%
%    o y: y ordinate of top left corner
%
%    o width: width of pattern space
%
%    o height: height of pattern space
%
*/
WandExport void MagickDrawPushPattern(DrawingWand *drawing_wand,
  const char *pattern_id,const double x,const double y,const double width,
  const double height)
{
  DrawPushPattern(drawing_wand,pattern_id,x,y,width,height);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w R e c t a n g l e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawRectangle() draws a rectangle given two coordinates and using
%  the current stroke, stroke width, and fill settings.
%
%  The format of the DrawRectangle method is:
%
%      void DrawRectangle(DrawingWand *drawing_wand,const double x1,
%        const double y1,const double x2,const double y2)
%
%  A description of each parameter follows:
%
%    o x1: x ordinate of first coordinate
%
%    o y1: y ordinate of first coordinate
%
%    o x2: x ordinate of second coordinate
%
%    o y2: y ordinate of second coordinate
%
*/
WandExport void MagickDrawRectangle(DrawingWand *drawing_wand,const double x1,
  const double y1,const double x2,const double y2)
{
  DrawRectangle(drawing_wand,x1,y1,x2,y2);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w R e n d e r                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawRender() renders all preceding drawing commands onto the image.
%  This function is deprecated.  Use DrawImage() instead.
%
%  The format of the DrawRender method is:
%
%      unsigned int DrawRender(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport unsigned int MagickDrawRender(const DrawingWand *drawing_wand)
{
  return DrawRender(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w R o t a t e                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawRotate() applies the specified rotation to the current coordinate space.
%
%  The format of the DrawRotate method is:
%
%      void DrawRotate(DrawingWand *drawing_wand,const double degrees)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o degrees: degrees of rotation
%
*/
WandExport void MagickDrawRotate(DrawingWand *drawing_wand,const double degrees)
{
  DrawRotate(drawing_wand,degrees);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w R o u n d R e c t a n g l e                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawRoundRectangle() draws a rounted rectangle given two coordinates,
%  x & y corner radiuses and using the current stroke, stroke width,
%  and fill settings.
%
%  The format of the DrawRoundRectangle method is:
%
%      void DrawRoundRectangle(DrawingWand *drawing_wand,double x1,double y1,
%        double x2,double y2,double rx,double ry)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x1: x ordinate of first coordinate
%
%    o y1: y ordinate of first coordinate
%
%    o x2: x ordinate of second coordinate
%
%    o y2: y ordinate of second coordinate
%
%    o rx: radius of corner in horizontal direction
%
%    o ry: radius of corner in vertical direction
%
*/
WandExport void MagickDrawRoundRectangle(DrawingWand *drawing_wand,double x1,
  double y1,double x2,double y2,double rx,double ry)
{
  DrawRoundRectangle(drawing_wand,x1,y1,x2,y2,rx,ry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S c a l e                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawScale() adjusts the scaling factor to apply in the horizontal and
%  vertical directions to the current coordinate space.
%
%  The format of the DrawScale method is:
%
%      void DrawScale(DrawingWand *drawing_wand,const double x,const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: horizontal scale factor
%
%    o y: vertical scale factor
%
*/
WandExport void MagickDrawScale(DrawingWand *drawing_wand,const double x,
  const double y)
{
  DrawScale(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S k e w X                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSkewX() skews the current coordinate system in the horizontal
%  direction.
%
%  The format of the DrawSkewX method is:
%
%      void DrawSkewX(DrawingWand *drawing_wand,const double degrees)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o degrees: number of degrees to skew the coordinates
%
*/
WandExport void MagickDrawSkewX(DrawingWand *drawing_wand,const double degrees)
{
  DrawSkewX(drawing_wand,degrees);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S k e w Y                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSkewY() skews the current coordinate system in the vertical
%  direction.
%
%  The format of the DrawSkewY method is:
%
%      void DrawSkewY(DrawingWand *drawing_wand,const double degrees)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o degrees: number of degrees to skew the coordinates
%
*/
WandExport void MagickDrawSkewY(DrawingWand *drawing_wand,const double degrees)
{
  DrawSkewY(drawing_wand,degrees);
}
#if 0

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t o p C o l o r                                           %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStopColor() sets the stop color and offset for gradients
%
%  The format of the DrawSetStopColor method is:
%
%      void DrawSetStopColor(DrawingWand *drawing_wand,
%        const PixelPacket *stop_color,const double offset)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o stop_color:
%
%    o offset:
%
*/
/* This is gradient stuff so it shouldn't be supported yet */
WandExport void MagickDrawSetStopColor(DrawingWand *drawing_wand,
  const PixelPacket * stop_color,const double offset)
{
  DrawSetStopColor(drawing_wand,stop_color,offset);
}
#endif

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e C o l o r                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeColor() returns the color used for stroking object outlines.
%
%  The format of the DrawGetStrokeColor method is:
%
%      void DrawGetStrokeColor(const DrawingWand *drawing_wand,
$        PixelWand *stroke_color)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o stroke_color: Return the stroke color.
%
*/
WandExport void MagickDrawGetStrokeColor(const DrawingWand *drawing_wand,
  PixelWand *stroke_color)
{
  PixelPacket packet=DrawGetStrokeColor(drawing_wand);
  PixelSetQuantumColor(stroke_color,&packet);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e C o l o r                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeColor() sets the color used for stroking object outlines.
%
%  The format of the DrawSetStrokeColor method is:
%
%      void DrawSetStrokeColor(DrawingWand *drawing_wand,
%        const PixelWand *stroke_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o stroke_wand: stroke wand.
%
*/
WandExport void MagickDrawSetStrokeColor(DrawingWand *drawing_wand,
  const PixelWand *stroke_wand)
{
  PixelPacket
    stroke_color;

  assert(drawing_wand != (DrawingWand *) NULL);
  assert(stroke_wand != (const PixelWand *) NULL);
  PixelGetQuantumColor(stroke_wand,&stroke_color);
  DrawSetStrokeColor(drawing_wand,&stroke_color);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e P a t t e r n U R L                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokePatternURL() sets the pattern used for stroking object outlines.
%
%  The format of the DrawSetStrokePatternURL method is:
%
%      void DrawSetStrokePatternURL(DrawingWand *drawing_wand,
%        const char *stroke_url)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o stroke_url: URL specifying pattern ID (e.g. "#pattern_id")
%
*/
WandExport void MagickDrawSetStrokePatternURL(DrawingWand *drawing_wand,
  const char *stroke_url)
{
  DrawSetStrokePatternURL(drawing_wand,stroke_url);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e A n t i a l i a s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeAntialias() returns the current stroke antialias setting.
%  Stroked outlines are antialiased by default.  When antialiasing is disabled
%  stroked pixels are thresholded to determine if the stroke color or
%  underlying canvas color should be used.
%
%  The format of the DrawGetStrokeAntialias method is:
%
%      unsigned int DrawGetStrokeAntialias(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport unsigned int MagickDrawGetStrokeAntialias(const DrawingWand *drawing_wand)
{
  return DrawGetStrokeAntialias(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e A n t i a l i a s                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeAntialias() controls whether stroked outlines are antialiased.
%  Stroked outlines are antialiased by default.  When antialiasing is disabled
%  stroked pixels are thresholded to determine if the stroke color or
%  underlying canvas color should be used.
%
%  The format of the DrawSetStrokeAntialias method is:
%
%      void DrawSetStrokeAntialias(DrawingWand *drawing_wand,
%        const unsigned int stroke_antialias)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o stroke_antialias: set to false (zero) to disable antialiasing
%
*/
WandExport void MagickDrawSetStrokeAntialias(DrawingWand *drawing_wand,
  const unsigned int stroke_antialias)
{
  DrawSetStrokeAntialias(drawing_wand,stroke_antialias);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e D a s h A r r a y                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeDashArray() returns an array representing the pattern of
%  dashes and gaps used to stroke paths (see DrawSetStrokeDashArray). The
%  array must be freed once it is no longer required by the user.
%
%  The format of the DrawGetStrokeDashArray method is:
%
%      double *DrawGetStrokeDashArray(const DrawingWand *drawing_wand,
%        unsigned long *number_elements)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o number_elements: address to place number of elements in dash array
%
% */
WandExport double *MagickDrawGetStrokeDashArray(const DrawingWand *drawing_wand,
  unsigned long *number_elements)
{
  return DrawGetStrokeDashArray(drawing_wand,number_elements);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e D a s h A r r a y                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeDashArray() specifies the pattern of dashes and gaps used to
%  stroke paths. The stroke dash array represents an array of numbers that
%  specify the lengths of alternating dashes and gaps in pixels. If an odd
%  number of values is provided, then the list of values is repeated to yield
%  an even number of values. To remove an existing dash array, pass a zero
%  number_elements argument and null dash_array.
%  A typical stroke dash array might contain the members 5 3 2.
%
%  The format of the DrawSetStrokeDashArray method is:
%
%      void DrawSetStrokeDashArray(DrawingWand *drawing_wand,
%        const unsigned long number_elements,const double *dash_array)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o number_elements: number of elements in dash array
%
%    o dash_array: dash array values
%
% */
WandExport void MagickDrawSetStrokeDashArray(DrawingWand *drawing_wand,
  const unsigned long number_elements,const double *dash_array)
{
  DrawSetStrokeDashArray(drawing_wand,number_elements,dash_array);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e D a s h O f f s e t                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeDashOffset() returns the offset into the dash pattern to
%  start the dash.
%
%  The format of the DrawGetStrokeDashOffset method is:
%
%      double DrawGetStrokeDashOffset(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport double MagickDrawGetStrokeDashOffset(const DrawingWand *drawing_wand)
{
  return DrawGetStrokeDashOffset(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e D a s h O f f s e t                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeDashOffset() specifies the offset into the dash pattern to
%  start the dash.
%
%  The format of the DrawSetStrokeDashOffset method is:
%
%      void DrawSetStrokeDashOffset(DrawingWand *drawing_wand,
%        const double dash_offset)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o dash_offset: dash offset
%
*/
WandExport void MagickDrawSetStrokeDashOffset(DrawingWand *drawing_wand,
  const double dash_offset)
{
  DrawSetStrokeDashOffset(drawing_wand,dash_offset);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e L i n e C a p                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeLineCap() returns the shape to be used at the end of
%  open subpaths when they are stroked. Values of LineCap are
%  UndefinedCap, ButtCap, RoundCap, and SquareCap.
%
%  The format of the DrawGetStrokeLineCap method is:
%
%      LineCap DrawGetStrokeLineCap(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
% */
WandExport LineCap MagickDrawGetStrokeLineCap(const DrawingWand *drawing_wand)
{
  return DrawGetStrokeLineCap(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e L i n e C a p                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeLineCap() specifies the shape to be used at the end of
%  open subpaths when they are stroked. Values of LineCap are
%  UndefinedCap, ButtCap, RoundCap, and SquareCap.
%
%  The format of the DrawSetStrokeLineCap method is:
%
%      void DrawSetStrokeLineCap(DrawingWand *drawing_wand,
%        const LineCap linecap)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o linecap: linecap style
%
% */
WandExport void MagickDrawSetStrokeLineCap(DrawingWand *drawing_wand,
  const LineCap linecap)
{
  DrawSetStrokeLineCap(drawing_wand,linecap);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e L i n e J o i n                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeLineJoin() returns the shape to be used at the
%  corners of paths (or other vector shapes) when they are
%  stroked. Values of LineJoin are UndefinedJoin, MiterJoin, RoundJoin,
%  and BevelJoin.
%
%  The format of the DrawGetStrokeLineJoin method is:
%
%      LineJoin DrawGetStrokeLineJoin(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
% */
WandExport LineJoin MagickDrawGetStrokeLineJoin(const DrawingWand *drawing_wand)
{
  return DrawGetStrokeLineJoin(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e L i n e J o i n                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeLineJoin() specifies the shape to be used at the
%  corners of paths (or other vector shapes) when they are
%  stroked. Values of LineJoin are UndefinedJoin, MiterJoin, RoundJoin,
%  and BevelJoin.
%
%  The format of the DrawSetStrokeLineJoin method is:
%
%      void DrawSetStrokeLineJoin(DrawingWand *drawing_wand,
%        const LineJoin linejoin)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o linejoin: line join style
%
%
*/
WandExport void MagickDrawSetStrokeLineJoin(DrawingWand *drawing_wand,
  const LineJoin linejoin)
{
  DrawSetStrokeLineJoin(drawing_wand,linejoin);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e M i t e r L i m i t                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeMiterLimit() returns the miter limit. When two line
%  segments meet at a sharp angle and miter joins have been specified for
%  'lineJoin', it is possible for the miter to extend far beyond the
%  thickness of the line stroking the path. The miterLimit' imposes a
%  limit on the ratio of the miter length to the 'lineWidth'.
%
%  The format of the DrawGetStrokeMiterLimit method is:
%
%      unsigned long DrawGetStrokeMiterLimit(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
% */
WandExport unsigned long MagickDrawGetStrokeMiterLimit(const DrawingWand *drawing_wand)
{
  return DrawGetStrokeMiterLimit(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e M i t e r L i m i t                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeMiterLimit() specifies the miter limit. When two line
%  segments meet at a sharp angle and miter joins have been specified for
%  'lineJoin', it is possible for the miter to extend far beyond the
%  thickness of the line stroking the path. The miterLimit' imposes a
%  limit on the ratio of the miter length to the 'lineWidth'.
%
%  The format of the DrawSetStrokeMiterLimit method is:
%
%      void DrawSetStrokeMiterLimit(DrawingWand *drawing_wand,
%        const unsigned long miterlimit)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o miterlimit: miter limit
%
% */
WandExport void MagickDrawSetStrokeMiterLimit(DrawingWand *drawing_wand,
  const unsigned long miterlimit)
{
  DrawSetStrokeMiterLimit(drawing_wand,miterlimit);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e O p a c i t y                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeOpacity() returns the opacity of stroked object outlines.
%
%  The format of the DrawGetStrokeOpacity method is:
%
%      double DrawGetStrokeOpacity(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
*/
WandExport double MagickDrawGetStrokeOpacity(const DrawingWand *drawing_wand)
{
  return DrawGetStrokeOpacity(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e O p a c i t y                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeOpacity() specifies the opacity of stroked object outlines.
%
%  The format of the DrawSetStrokeOpacity method is:
%
%      void DrawSetStrokeOpacity(DrawingWand *drawing_wand,
%        const double stroke_opacity)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o stroke_opacity: stroke opacity.  The value 1.0 is opaque.
%
*/
WandExport void MagickDrawSetStrokeOpacity(DrawingWand *drawing_wand,
  const double stroke_opacity)
{
  DrawSetStrokeOpacity(drawing_wand,stroke_opacity);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t S t r o k e W i d t h                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetStrokeWidth() returns the width of the stroke used to draw object
%  outlines.
%
%  The format of the DrawGetStrokeWidth method is:
%
%      double DrawGetStrokeWidth(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport double MagickDrawGetStrokeWidth(const DrawingWand *drawing_wand)
{
  return DrawGetStrokeWidth(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t S t r o k e W i d t h                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetStrokeWidth() sets the width of the stroke used to draw object
%  outlines.
%
%  The format of the DrawSetStrokeWidth method is:
%
%      void DrawSetStrokeWidth(DrawingWand *drawing_wand,
%        const double stroke_width)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o stroke_width: stroke width
%
*/
WandExport void MagickDrawSetStrokeWidth(DrawingWand *drawing_wand,
  const double stroke_width)
{
  DrawSetStrokeWidth(drawing_wand,stroke_width);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t T e x t A n t i a l i a s                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetTextAntialias() returns the current text antialias setting, which
%  determines whether text is antialiased.  Text is antialiased by default.
%
%  The format of the DrawGetTextAntialias method is:
%
%      unsigned int DrawGetTextAntialias(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport unsigned int MagickDrawGetTextAntialias(const DrawingWand *drawing_wand)
{
  return DrawGetTextAntialias(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t T e x t A n t i a l i a s                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetTextAntialias() controls whether text is antialiased.  Text is
%  antialiased by default.
%
%  The format of the DrawSetTextAntialias method is:
%
%      void DrawSetTextAntialias(DrawingWand *drawing_wand,
%        const unsigned int text_antialias)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o text_antialias: antialias boolean. Set to false (0) to disable
%      antialiasing.
%
*/
WandExport void MagickDrawSetTextAntialias(DrawingWand *drawing_wand,
  const unsigned int text_antialias)
{
  DrawSetTextAntialias(drawing_wand,text_antialias);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t T e x t D e c o r a t i o n                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetTextDecoration() returns the decoration applied when annotating with
%  text.
%
%  The format of the DrawGetTextDecoration method is:
%
%      DecorationType DrawGetTextDecoration(DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
*/
WandExport DecorationType MagickDrawGetTextDecoration(const DrawingWand *drawing_wand)
{
  return DrawGetTextDecoration(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t T e x t D e c o r a t i o n                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetTextDecoration() specifies a decoration to be applied when
%  annotating with text.
%
%  The format of the DrawSetTextDecoration method is:
%
%      void DrawSetTextDecoration(DrawingWand *drawing_wand,
%        const DecorationType decoration)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o decoration: text decoration.  One of NoDecoration, UnderlineDecoration,
%      OverlineDecoration, or LineThroughDecoration
%
*/
WandExport void MagickDrawSetTextDecoration(DrawingWand *drawing_wand,
  const DecorationType decoration)
{
  DrawSetTextDecoration(drawing_wand,decoration);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t T e x t E n c o d i n g                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetTextEncoding() returns a null-terminated string which specifies the
%  code set used for text annotations. The string must be freed by the user
%  once it is no longer required.
%
%  The format of the DrawGetTextEncoding method is:
%
%      char *DrawGetTextEncoding(const DrawingWand *drawing_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
% */
WandExport char *MagickDrawGetTextEncoding(const DrawingWand *drawing_wand)
{
  return DrawGetTextEncoding(drawing_wand);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t T e x t E n c o d i n g                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetTextEncoding() specifies specifies the code set to use for
%  text annotations. The only character encoding which may be specified
%  at this time is "UTF-8" for representing Unicode as a sequence of
%  bytes. Specify an empty string to set text encoding to the system's
%  default. Successful text annotation using Unicode may require fonts
%  designed to support Unicode.
%
%  The format of the DrawSetTextEncoding method is:
%
%      void DrawSetTextEncoding(DrawingWand *drawing_wand,const char *encoding)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o encoding: character string specifying text encoding
%
% */
WandExport void MagickDrawSetTextEncoding(DrawingWand *drawing_wand,
  const char *encoding)
{
  DrawSetTextEncoding(drawing_wand,encoding);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w G e t T e x t U n d e r C o l o r                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawGetTextUnderColor() returns the color of a background rectangle
%  to place under text annotations.
%
%  The format of the DrawGetTextUnderColor method is:
%
%      void DrawGetTextUnderColor(const DrawingWand *drawing_wand,
%        PixelWand *under_color)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o under_color: Return the under color.
%
*/
WandExport void MagickDrawGetTextUnderColor(const DrawingWand *drawing_wand,
  PixelWand *under_color)
{
  PixelPacket
    packet;

  packet=DrawGetTextUnderColor(drawing_wand);
  PixelSetQuantumColor(under_color,&packet);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t T e x t U n d e r C o l o r                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetTextUnderColor() specifies the color of a background rectangle
%  to place under text annotations.
%
%  The format of the DrawSetTextUnderColor method is:
%
%      void DrawSetTextUnderColor(DrawingWand *drawing_wand,
%        const PixelWand *under_wand)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o under_wand.: text under wand.
%
*/
WandExport void MagickDrawSetTextUnderColor(DrawingWand *drawing_wand,
  const PixelWand *under_wand)
{
  PixelPacket
    under_color;

  assert(drawing_wand != (DrawingWand *) NULL);
  assert(under_wand != (const PixelWand *) NULL);
  PixelGetQuantumColor(under_wand,&under_color);
  DrawSetTextUnderColor(drawing_wand,&under_color);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w T r a n s l a t e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawTranslate() applies a translation to the current coordinate
%  system which moves the coordinate system origin to the specified
%  coordinate.
%
%  The format of the DrawTranslate method is:
%
%      void DrawTranslate(DrawingWand *drawing_wand,const double x,
%        const double y)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x: new x ordinate for coordinate system origin
%
%    o y: new y ordinate for coordinate system origin
%
*/
WandExport void MagickDrawTranslate(DrawingWand *drawing_wand,const double x,
  const double y)
{
  DrawTranslate(drawing_wand,x,y);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   D r a w S e t V i e w b o x                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DrawSetViewbox() sets the overall canvas size to be recorded with the
%  drawing vector data.  Usually this will be specified using the same
%  size as the canvas image.  When the vector data is saved to SVG or MVG
%  formats, the viewbox is use to specify the size of the canvas image that
%  a viewer will render the vector data on.
%
%  The format of the DrawSetViewbox method is:
%
%      void DrawSetViewbox(DrawingWand *drawing_wand,unsigned long x1,
%        unsigned long y1,unsigned long x2,unsigned long y2)
%
%  A description of each parameter follows:
%
%    o drawing_wand: The drawing wand.
%
%    o x1: left x ordinate
%
%    o y1: top y ordinate
%
%    o x2: right x ordinate
%
%    o y2: bottom y ordinate
%
*/
WandExport void MagickDrawSetViewbox(DrawingWand *drawing_wand,unsigned long x1,
  unsigned long y1,unsigned long x2,unsigned long y2)
{
  DrawSetViewbox(drawing_wand,x1,y1,x2,y2);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   N e w D r a w i n g W a n d                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  NewDrawingWand() returns a drawing wand required for all other methods in
%  the API.
%
%  The format of the NewDrawingWand method is:
%
%      DrawingWand *NewDrawingWand(void)
%
*/
/*
  Similar to magick/draw.c DrawNewContext()
*/
WandExport DrawingWand *MagickNewDrawingWand(void)
{
  DrawingWand
    *drawing_wand;

  /*
    Initialize GraphicsMagick in case it is not already initialized.
  */

  /*
    Initialize locale from environment variables (LANG, LC_CTYPE,
    LC_NUMERIC, LC_TIME, LC_COLLATE, LC_MONETARY, LC_MESSAGES,
    LC_ALL), but require that LC_NUMERIC use common conventions.  The
    LC_NUMERIC variable affects the decimal point character and
    thousands separator character for the formatted input/output
    functions and string conversion functions.
  */
  (void) setlocale(LC_ALL,"");
  (void) setlocale(LC_NUMERIC,"C");

  InitializeMagick(NULL);

  drawing_wand=DrawNewContext();

  return(drawing_wand);
}
