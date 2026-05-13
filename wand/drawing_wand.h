/* Copyright (C) 2003-2026 GraphicsMagick Group */
/*
  GraphicsMagick Drawing Wand API.

  Originates from code written by Bob Friesenhahn in 2002.
*/
#ifndef _MAGICK_DRAWING_WAND_H
#define _MAGICK_DRAWING_WAND_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include "wand/wand_symbols.h"
#include "wand/pixel_wand.h"

  /*
    ImageMagick decided to move my magick/draw.h and magick/draw.c simplified
    drawing API functions to wand so they are no longer in the core
    library. But GraphicsMagick did not remove magick/draw.h or magick/draw.c
    from its core library.  Due to this, macros are used to rename API
    function names to have a "magick" prefix for Wand so that they do not
    collide with those from magick/draw.h.

    This means that magick/draw.h should not be included after this header!
  */
#if !defined(MAGICK_EXCLUDE_DRAWING_WAND_MACROS)
#undef CloneDrawingWand
#define CloneDrawingWand MagickCloneDrawingWand
#undef DestroyDrawingWand
#define DestroyDrawingWand MagickDestroyDrawingWand
#undef DrawAffine
#define DrawAffine MagickDrawAffine
#undef DrawAllocateWand
#define DrawAllocateWand MagickDrawAllocateWand
#undef DrawAnnotation
#define DrawAnnotation MagickDrawAnnotation
#undef DrawArc
#define DrawArc MagickDrawArc
#undef DrawBezier
#define DrawBezier MagickDrawBezier
#undef DrawClearException
#define DrawClearException MagickDrawClearException
#undef DrawCircle
#define DrawCircle MagickDrawCircle
#undef DrawColor
#define DrawColor MagickDrawColor
#undef DrawComment
#define DrawComment MagickDrawComment
#undef DrawComposite
#define DrawComposite MagickDrawComposite
#undef DrawEllipse
#define DrawEllipse MagickDrawEllipse
#undef DrawGetClipPath
#define DrawGetClipPath MagickDrawGetClipPath
#undef DrawGetClipRule
#define DrawGetClipRule MagickDrawGetClipRule
#undef DrawGetClipUnits
#define DrawGetClipUnits MagickDrawGetClipUnits
#undef DrawGetException
#define DrawGetException MagickDrawGetException
#undef DrawGetFillColor
#define DrawGetFillColor MagickDrawGetFillColor
#undef DrawGetFillOpacity
#define DrawGetFillOpacity MagickDrawGetFillOpacity
#undef DrawGetFillRule
#define DrawGetFillRule MagickDrawGetFillRule
#undef DrawGetFont
#define DrawGetFont MagickDrawGetFont
#undef DrawGetFontFamily
#define DrawGetFontFamily MagickDrawGetFontFamily
#undef DrawGetFontSize
#define DrawGetFontSize MagickDrawGetFontSize
#undef DrawGetFontStretch
#define DrawGetFontStretch MagickDrawGetFontStretch
#undef DrawGetFontStyle
#define DrawGetFontStyle MagickDrawGetFontStyle
#undef DrawGetFontWeight
#define DrawGetFontWeight MagickDrawGetFontWeight
#undef DrawGetGravity
#define DrawGetGravity MagickDrawGetGravity
#undef DrawGetStrokeAntialias
#define DrawGetStrokeAntialias MagickDrawGetStrokeAntialias
#undef DrawGetStrokeColor
#define DrawGetStrokeColor MagickDrawGetStrokeColor
#undef DrawGetStrokeDashArray
#define DrawGetStrokeDashArray MagickDrawGetStrokeDashArray
#undef DrawGetStrokeDashOffset
#define DrawGetStrokeDashOffset MagickDrawGetStrokeDashOffset
#undef DrawGetStrokeLineCap
#define DrawGetStrokeLineCap MagickDrawGetStrokeLineCap
#undef DrawGetStrokeLineJoin
#define DrawGetStrokeLineJoin MagickDrawGetStrokeLineJoin
#undef DrawGetStrokeMiterLimit
#define DrawGetStrokeMiterLimit MagickDrawGetStrokeMiterLimit
#undef DrawGetStrokeOpacity
#define DrawGetStrokeOpacity MagickDrawGetStrokeOpacity
#undef DrawGetStrokeWidth
#define DrawGetStrokeWidth MagickDrawGetStrokeWidth
#undef DrawGetTextAntialias
#define DrawGetTextAntialias MagickDrawGetTextAntialias
#undef DrawGetTextDecoration
#define DrawGetTextDecoration MagickDrawGetTextDecoration
#undef DrawGetTextEncoding
#define DrawGetTextEncoding MagickDrawGetTextEncoding
#undef DrawGetTextUnderColor
#define DrawGetTextUnderColor MagickDrawGetTextUnderColor
#undef DrawLine
#define DrawLine MagickDrawLine
#undef DrawMatte
#define DrawMatte MagickDrawMatte
#undef DrawPathClose
#define DrawPathClose MagickDrawPathClose
#undef DrawPathCurveToAbsolute
#define DrawPathCurveToAbsolute MagickDrawPathCurveToAbsolute
#undef DrawPathCurveToQuadraticBezierAbsolute
#define DrawPathCurveToQuadraticBezierAbsolute MagickDrawPathCurveToQuadraticBezierAbsolute
#undef DrawPathCurveToQuadraticBezierRelative
#define DrawPathCurveToQuadraticBezierRelative MagickDrawPathCurveToQuadraticBezierRelative
#undef DrawPathCurveToQuadraticBezierSmoothAbsolute
#define DrawPathCurveToQuadraticBezierSmoothAbsolute MagickDrawPathCurveToQuadraticBezierSmoothAbsolute
#undef DrawPathCurveToQuadraticBezierSmoothRelative
#define DrawPathCurveToQuadraticBezierSmoothRelative MagickDrawPathCurveToQuadraticBezierSmoothRelative
#undef DrawPathCurveToRelative
#define DrawPathCurveToRelative MagickDrawPathCurveToRelative
#undef DrawPathCurveToSmoothAbsolute
#define DrawPathCurveToSmoothAbsolute MagickDrawPathCurveToSmoothAbsolute
#undef DrawPathCurveToSmoothRelative
#define DrawPathCurveToSmoothRelative MagickDrawPathCurveToSmoothRelative
#undef DrawPathEllipticArcAbsolute
#define DrawPathEllipticArcAbsolute MagickDrawPathEllipticArcAbsolute
#undef DrawPathEllipticArcRelative
#define DrawPathEllipticArcRelative MagickDrawPathEllipticArcRelative
#undef DrawPathFinish
#define DrawPathFinish MagickDrawPathFinish
#undef DrawPathLineToAbsolute
#define DrawPathLineToAbsolute MagickDrawPathLineToAbsolute
#undef DrawPathLineToHorizontalAbsolute
#define DrawPathLineToHorizontalAbsolute MagickDrawPathLineToHorizontalAbsolute
#undef DrawPathLineToHorizontalRelative
#define DrawPathLineToHorizontalRelative MagickDrawPathLineToHorizontalRelative
#undef DrawPathLineToRelative
#define DrawPathLineToRelative MagickDrawPathLineToRelative
#undef DrawPathLineToVerticalAbsolute
#define DrawPathLineToVerticalAbsolute MagickDrawPathLineToVerticalAbsolute
#undef DrawPathLineToVerticalRelative
#define DrawPathLineToVerticalRelative MagickDrawPathLineToVerticalRelative
#undef DrawPathMoveToAbsolute
#define DrawPathMoveToAbsolute MagickDrawPathMoveToAbsolute
#undef DrawPathMoveToRelative
#define DrawPathMoveToRelative MagickDrawPathMoveToRelative
#undef DrawPathStart
#define DrawPathStart MagickDrawPathStart
#undef DrawPeekGraphicContext
#define DrawPeekGraphicContext MagickDrawPeekGraphicContext
#undef DrawPoint
#define DrawPoint MagickDrawPoint
#undef DrawPolygon
#define DrawPolygon MagickDrawPolygon
#undef DrawPolyline
#define DrawPolyline MagickDrawPolyline
#undef DrawPopClipPath
#define DrawPopClipPath MagickDrawPopClipPath
#undef DrawPopDefs
#define DrawPopDefs MagickDrawPopDefs
#undef DrawPopGraphicContext
#define DrawPopGraphicContext MagickDrawPopGraphicContext
#undef DrawPopPattern
#define DrawPopPattern MagickDrawPopPattern
#undef DrawPushClipPath
#define DrawPushClipPath MagickDrawPushClipPath
#undef DrawPushDefs
#define DrawPushDefs MagickDrawPushDefs
#undef DrawPushGraphicContext
#define DrawPushGraphicContext MagickDrawPushGraphicContext
#undef DrawPushPattern
#define DrawPushPattern MagickDrawPushPattern
#undef DrawRectangle
#define DrawRectangle MagickDrawRectangle
#undef DrawRender
#define DrawRender MagickDrawRender
#undef DrawRotate
#define DrawRotate MagickDrawRotate
#undef DrawRoundRectangle
#define DrawRoundRectangle MagickDrawRoundRectangle
#undef DrawScale
#define DrawScale MagickDrawScale
#undef DrawSetClipPath
#define DrawSetClipPath MagickDrawSetClipPath
#undef DrawSetClipRule
#define DrawSetClipRule MagickDrawSetClipRule
#undef DrawSetClipUnits
#define DrawSetClipUnits MagickDrawSetClipUnits
#undef DrawSetFillColor
#define DrawSetFillColor MagickDrawSetFillColor
#undef DrawSetFillOpacity
#define DrawSetFillOpacity MagickDrawSetFillOpacity
#undef DrawSetFillPatternURL
#define DrawSetFillPatternURL MagickDrawSetFillPatternURL
#undef DrawSetFillRule
#define DrawSetFillRule MagickDrawSetFillRule
#undef DrawSetFont
#define DrawSetFont MagickDrawSetFont
#undef DrawSetFontFamily
#define DrawSetFontFamily MagickDrawSetFontFamily
#undef DrawSetFontSize
#define DrawSetFontSize MagickDrawSetFontSize
#undef DrawSetFontStretch
#define DrawSetFontStretch MagickDrawSetFontStretch
#undef DrawSetFontStyle
#define DrawSetFontStyle MagickDrawSetFontStyle
#undef DrawSetFontWeight
#define DrawSetFontWeight MagickDrawSetFontWeight
#undef DrawSetGravity
#define DrawSetGravity MagickDrawSetGravity
#undef DrawSetStrokeAntialias
#define DrawSetStrokeAntialias MagickDrawSetStrokeAntialias
#undef DrawSetStrokeColor
#define DrawSetStrokeColor MagickDrawSetStrokeColor
#undef DrawSetStrokeDashArray
#define DrawSetStrokeDashArray MagickDrawSetStrokeDashArray
#undef DrawSetStrokeDashOffset
#define DrawSetStrokeDashOffset MagickDrawSetStrokeDashOffset
#undef DrawSetStrokeLineCap
#define DrawSetStrokeLineCap MagickDrawSetStrokeLineCap
#undef DrawSetStrokeLineJoin
#define DrawSetStrokeLineJoin MagickDrawSetStrokeLineJoin
#undef DrawSetStrokeMiterLimit
#define DrawSetStrokeMiterLimit MagickDrawSetStrokeMiterLimit
#undef DrawSetStrokeOpacity
#define DrawSetStrokeOpacity MagickDrawSetStrokeOpacity
#undef DrawSetStrokePatternURL
#define DrawSetStrokePatternURL MagickDrawSetStrokePatternURL
#undef DrawSetStrokeWidth
#define DrawSetStrokeWidth MagickDrawSetStrokeWidth
#undef DrawSetTextAntialias
#define DrawSetTextAntialias MagickDrawSetTextAntialias
#undef DrawSetTextDecoration
#define DrawSetTextDecoration MagickDrawSetTextDecoration
#undef DrawSetTextEncoding
#define DrawSetTextEncoding MagickDrawSetTextEncoding
#undef DrawSetTextUnderColor
#define DrawSetTextUnderColor MagickDrawSetTextUnderColor
#undef DrawSetViewbox
#define DrawSetViewbox MagickDrawSetViewbox
#undef DrawSkewX
#define DrawSkewX MagickDrawSkewX
#undef DrawSkewY
#define DrawSkewY MagickDrawSkewY
#undef DrawTranslate
#define DrawTranslate MagickDrawTranslate
#undef NewDrawingWand
#define NewDrawingWand MagickNewDrawingWand

#endif /* if !defined(MAGICK_EXCLUDE_DRAWING_WAND_MACROS) */

typedef struct _DrawContext
  DrawingWand;

extern WandExport char
  *MagickDrawGetClipPath(const DrawingWand *),
  *MagickDrawGetException(const DrawingWand *,ExceptionType *),
  *MagickDrawGetFont(const DrawingWand *),
  *MagickDrawGetFontFamily(const DrawingWand *),
  *MagickDrawGetTextEncoding(const DrawingWand *);

extern WandExport ClipPathUnits
  MagickDrawGetClipUnits(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport DecorationType
  MagickDrawGetTextDecoration(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport double
  MagickDrawGetFillOpacity(const DrawingWand *) MAGICK_FUNC_PURE,
  MagickDrawGetFontSize(const DrawingWand *) MAGICK_FUNC_PURE,
  *MagickDrawGetStrokeDashArray(const DrawingWand *,unsigned long *),
  MagickDrawGetStrokeDashOffset(const DrawingWand *) MAGICK_FUNC_PURE,
  MagickDrawGetStrokeOpacity(const DrawingWand *) MAGICK_FUNC_PURE,
  MagickDrawGetStrokeWidth(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport DrawInfo
  *MagickDrawPeekGraphicContext(const DrawingWand *);

extern WandExport DrawingWand
  *MagickCloneDrawingWand(const DrawingWand *drawing_wand),
  *MagickDrawAllocateWand(const DrawInfo *,Image *) MAGICK_ATTRIBUTE ((deprecated)),
  *MagickNewDrawingWand(void);

extern WandExport FillRule
  MagickDrawGetClipRule(const DrawingWand *) MAGICK_FUNC_PURE,
  MagickDrawGetFillRule(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport GravityType
  MagickDrawGetGravity(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport LineCap
  MagickDrawGetStrokeLineCap(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport LineJoin
  MagickDrawGetStrokeLineJoin(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport StretchType
  MagickDrawGetFontStretch(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport StyleType
  MagickDrawGetFontStyle(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport unsigned int
  MagickDrawClearException(DrawingWand *),
  MagickDrawGetStrokeAntialias(const DrawingWand *) MAGICK_FUNC_PURE,
  MagickDrawGetTextAntialias(const DrawingWand *) MAGICK_FUNC_PURE,
  MagickDrawRender(const DrawingWand *) MAGICK_ATTRIBUTE ((deprecated)); /* Use MagickDrawImage() instead */

extern WandExport unsigned long
  MagickDrawGetFontWeight(const DrawingWand *) MAGICK_FUNC_PURE,
  MagickDrawGetStrokeMiterLimit(const DrawingWand *) MAGICK_FUNC_PURE;

extern WandExport void
  MagickDrawAffine(DrawingWand *,const AffineMatrix *),
  MagickDrawAnnotation(DrawingWand *,const double,const double,const unsigned char *),
  MagickDrawArc(DrawingWand *,const double,const double,const double,const double,
    const double,const double),
  MagickDrawBezier(DrawingWand *,const unsigned long,const PointInfo *),
  MagickDrawCircle(DrawingWand *,const double,const double,const double,const double),
  MagickDrawColor(DrawingWand *,const double,const double,const PaintMethod),
  MagickDrawComment(DrawingWand *,const char *),
  MagickDestroyDrawingWand(DrawingWand *),
  MagickDrawEllipse(DrawingWand *,const double,const double,const double,const double,
    const double,const double),
  MagickDrawComposite(DrawingWand *,const CompositeOperator,const double,const double,
    const double,const double,const Image *),
  MagickDrawGetFillColor(const DrawingWand *,PixelWand *),
  MagickDrawGetStrokeColor(const DrawingWand *,PixelWand *),
  MagickDrawGetTextUnderColor(const DrawingWand *,PixelWand *),
  MagickDrawLine(DrawingWand *,const double, const double,const double,const double),
  MagickDrawMatte(DrawingWand *,const double,const double,const PaintMethod),
  MagickDrawPathClose(DrawingWand *),
  MagickDrawPathCurveToAbsolute(DrawingWand *,const double,const double,const double,
    const double,const double,const double),
  MagickDrawPathCurveToRelative(DrawingWand *,const double,const double,const double,
    const double,const double, const double),
  MagickDrawPathCurveToQuadraticBezierAbsolute(DrawingWand *,const double,
    const double,const double,const double),
  MagickDrawPathCurveToQuadraticBezierRelative(DrawingWand *,const double,
    const double,const double,const double),
  MagickDrawPathCurveToQuadraticBezierSmoothAbsolute(DrawingWand *,const double,
    const double),
  MagickDrawPathCurveToQuadraticBezierSmoothRelative(DrawingWand *,const double,
    const double),
  MagickDrawPathCurveToSmoothAbsolute(DrawingWand *,const double,const double,
    const double,const double),
  MagickDrawPathCurveToSmoothRelative(DrawingWand *,const double,const double,
    const double,const double),
  MagickDrawPathEllipticArcAbsolute(DrawingWand *,const double,const double,
    const double,unsigned int,unsigned int,const double,const double),
  MagickDrawPathEllipticArcRelative(DrawingWand *,const double,const double,
    const double,unsigned int,unsigned int,const double,const double),
  MagickDrawPathFinish(DrawingWand *),
  MagickDrawPathLineToAbsolute(DrawingWand *,const double,const double),
  MagickDrawPathLineToRelative(DrawingWand *,const double,const double),
  MagickDrawPathLineToHorizontalAbsolute(DrawingWand *,const double),
  MagickDrawPathLineToHorizontalRelative(DrawingWand *,const double),
  MagickDrawPathLineToVerticalAbsolute(DrawingWand *,const double),
  MagickDrawPathLineToVerticalRelative(DrawingWand *,const double),
  MagickDrawPathMoveToAbsolute(DrawingWand *,const double,const double),
  MagickDrawPathMoveToRelative(DrawingWand *,const double,const double),
  MagickDrawPathStart(DrawingWand *),
  MagickDrawPoint(DrawingWand *,const double,const double),
  MagickDrawPolygon(DrawingWand *,const unsigned long,const PointInfo *),
  MagickDrawPolyline(DrawingWand *,const unsigned long,const PointInfo *),
  MagickDrawPopClipPath(DrawingWand *),
  MagickDrawPopDefs(DrawingWand *),
  MagickDrawPopGraphicContext(DrawingWand *),
  MagickDrawPopPattern(DrawingWand *),
  MagickDrawPushClipPath(DrawingWand *,const char *),
  MagickDrawPushDefs(DrawingWand *),
  MagickDrawPushGraphicContext(DrawingWand *),
  MagickDrawPushPattern(DrawingWand *,const char *,const double,const double,
    const double,const double),
  MagickDrawRectangle(DrawingWand *,const double,const double,const double,
    const double),
  MagickDrawRotate(DrawingWand *,const double),
  MagickDrawRoundRectangle(DrawingWand *,double,double,double,double,double,double),
  MagickDrawScale(DrawingWand *,const double,const double),
  MagickDrawSetClipPath(DrawingWand *,const char *),
  MagickDrawSetClipRule(DrawingWand *,const FillRule),
  MagickDrawSetClipUnits(DrawingWand *,const ClipPathUnits),
  MagickDrawSetFillColor(DrawingWand *,const PixelWand *),
  MagickDrawSetFillOpacity(DrawingWand *,const double),
  MagickDrawSetFillRule(DrawingWand *,const FillRule),
  MagickDrawSetFillPatternURL(DrawingWand *,const char *),
  MagickDrawSetFont(DrawingWand *,const char *),
  MagickDrawSetFontFamily(DrawingWand *,const char *),
  MagickDrawSetFontSize(DrawingWand *,const double),
  MagickDrawSetFontStretch(DrawingWand *,const StretchType),
  MagickDrawSetFontStyle(DrawingWand *,const StyleType),
  MagickDrawSetFontWeight(DrawingWand *,const unsigned long),
  MagickDrawSetGravity(DrawingWand *,const GravityType),
  MagickDrawSkewX(DrawingWand *,const double),
  MagickDrawSkewY(DrawingWand *,const double),
  MagickDrawSetStrokeAntialias(DrawingWand *,const unsigned int),
  MagickDrawSetStrokeColor(DrawingWand *,const PixelWand *),
  MagickDrawSetStrokeDashArray(DrawingWand *,const unsigned long,const double *),
  MagickDrawSetStrokeDashOffset(DrawingWand *,const double dashoffset),
  MagickDrawSetStrokeLineCap(DrawingWand *,const LineCap),
  MagickDrawSetStrokeLineJoin(DrawingWand *,const LineJoin),
  MagickDrawSetStrokeMiterLimit(DrawingWand *,const unsigned long),
  MagickDrawSetStrokeOpacity(DrawingWand *, const double),
  MagickDrawSetStrokePatternURL(DrawingWand *,const char *),
  MagickDrawSetStrokeWidth(DrawingWand *,const double),
  MagickDrawSetTextAntialias(DrawingWand *,const unsigned int),
  MagickDrawSetTextDecoration(DrawingWand *,const DecorationType),
  MagickDrawSetTextEncoding(DrawingWand *,const char *),
  MagickDrawSetTextUnderColor(DrawingWand *,const PixelWand *),
  MagickDrawSetViewbox(DrawingWand *,unsigned long,unsigned long,unsigned long,
    unsigned long),
  MagickDrawTranslate(DrawingWand *,const double,const double);

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
