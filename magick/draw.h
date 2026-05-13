/*
  Copyright (C) 2003-2026 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Drawing API.

  Usage synopsis:

  DrawContext context;
  context = DrawAllocateContext((DrawInfo*)NULL, image);
    [ any number of drawing commands ]
    DrawSetStrokeColorString(context,"black");
    DrawSetFillColorString(context,"#ff00ff");
    DrawSetStrokeWidth(context,4);
    DrawRectangle(context,72,72,144,144);
  DrawRender(context);
  DrawDestroyContext(context);

*/
#ifndef _MAGICK_DRAW_H
#define _MAGICK_DRAW_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include "magick/render.h"


typedef struct _DrawContext *DrawContext;

typedef enum
{
  DefaultPathMode,
  AbsolutePathMode,
  RelativePathMode
} DrawPathMode;

extern MagickExport ClipPathUnits
  DrawGetClipUnits(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport DrawInfo
  *DrawPeekGraphicContext(const struct _DrawContext * context);

extern MagickExport DecorationType
  DrawGetTextDecoration(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport struct _DrawContext
  *DrawNewContext(void),
  *DrawAllocateContext(const DrawInfo *draw_info, Image *image),
  *DrawCloneContext(const struct _DrawContext *context);

extern MagickExport MagickBool
  DrawClearException(struct _DrawContext * context);

extern MagickExport FillRule
  DrawGetClipRule(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetFillRule(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport GravityType
  DrawGetGravity(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport LineCap
  DrawGetStrokeLineCap(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport LineJoin
  DrawGetStrokeLineJoin(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport PixelPacket
  DrawGetFillColor(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetStrokeColor(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetTextUnderColor(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport StretchType
  DrawGetFontStretch(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport StyleType
  DrawGetFontStyle(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport char
  *DrawGetClipPath(const struct _DrawContext * context),
  *DrawGetFont(const struct _DrawContext * context),
  *DrawGetFontFamily(const struct _DrawContext * context),
  *DrawGetTextEncoding(const struct _DrawContext * context),
  *DrawGetException(const struct _DrawContext * context,ExceptionType *severity);

extern MagickExport int
  DrawRender(const struct _DrawContext * context);

extern MagickExport unsigned int
  DrawGetStrokeAntialias(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetTextAntialias(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport unsigned long
  DrawGetFontWeight(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetStrokeMiterLimit(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport double
  DrawGetFillOpacity(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetFontSize(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  *DrawGetStrokeDashArray(const struct _DrawContext * context, unsigned long *num_elems),
  DrawGetStrokeDashOffset(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetStrokeOpacity(const struct _DrawContext * context) MAGICK_FUNC_PURE,
  DrawGetStrokeWidth(const struct _DrawContext * context) MAGICK_FUNC_PURE;

extern MagickExport void
  DrawAffine(struct _DrawContext * context, const AffineMatrix *affine),
  DrawAnnotation(struct _DrawContext * context,
    const double x, const double y,
    const unsigned char *text),
  DrawArc(struct _DrawContext * context,
          const double sx, const double sy,
          const double ex, const double ey,
          const double sd, const double ed),
  DrawBezier(struct _DrawContext * context,
             const unsigned long num_coords, const PointInfo * coordinates),
  DrawCircle(struct _DrawContext * context,
             const double ox, const double oy,
             const double px, const double py),
  DrawColor(struct _DrawContext * context,
            const double x, const double y,
            const PaintMethod paintMethod),
  DrawComment(struct _DrawContext * context,const char* comment),
  DrawDestroyContext(struct _DrawContext * context),
  DrawEllipse(struct _DrawContext * context,
              const double ox, const double oy,
              const double rx, const double ry,
              const double start, const double end),
  DrawComposite(struct _DrawContext * context,
                const CompositeOperator composite_operator,
                const double x, const double y,
                const double width, const double height,
                const Image * image ),
  DrawLine(struct _DrawContext * context,
           const double sx, const double sy,
           const double ex, const double ey),
  DrawMatte(struct _DrawContext * context,
            const double x, const double y,
            const PaintMethod paint_method),
  DrawPathClose(struct _DrawContext * context),
  DrawPathCurveToAbsolute(struct _DrawContext * context,
                          const double x1, const double y1,
                          const double x2, const double y2,
                          const double x, const double y),
  DrawPathCurveToRelative(struct _DrawContext * context,
                          const double x1, const double y1,
                          const double x2, const double y2,
                          const double x, const double y),
  DrawPathCurveToQuadraticBezierAbsolute(struct _DrawContext * context,
                                         const double x1, const double y1,
                                         const double x, const double y),
  DrawPathCurveToQuadraticBezierRelative(struct _DrawContext * context,
                                         const double x1, const double y1,
                                         const double x, const double y),
  DrawPathCurveToQuadraticBezierSmoothAbsolute(struct _DrawContext * context,
                                               const double x, const double y),
  DrawPathCurveToQuadraticBezierSmoothRelative(struct _DrawContext * context,
                                               const double x, const double y),
  DrawPathCurveToSmoothAbsolute(struct _DrawContext * context,
                                const double x2, const double y2,
                                const double x, const double y),
  DrawPathCurveToSmoothRelative(struct _DrawContext * context,
                                const double x2, const double y2,
                                const double x, const double y),
  DrawPathEllipticArcAbsolute(struct _DrawContext * context,
                              const double rx, const double ry,
                              const double x_axis_rotation,
                              unsigned int large_arc_flag,
                              unsigned int sweep_flag,
                              const double x, const double y),
  DrawPathEllipticArcRelative(struct _DrawContext * context,
                              const double rx, const double ry,
                              const double x_axis_rotation,
                              unsigned int large_arc_flag,
                              unsigned int sweep_flag,
                              const double x, const double y),
  DrawPathFinish(struct _DrawContext * context),
  DrawPathLineToAbsolute(struct _DrawContext * context,
                         const double x, const double y),
  DrawPathLineToRelative(struct _DrawContext * context,
                         const double x, const double y),
  DrawPathLineToHorizontalAbsolute(struct _DrawContext * context, const double x),
  DrawPathLineToHorizontalRelative(struct _DrawContext * context, const double x),
  DrawPathLineToVerticalAbsolute(struct _DrawContext * context, const double y),
  DrawPathLineToVerticalRelative(struct _DrawContext * context, const double y),
  DrawPathMoveToAbsolute(struct _DrawContext * context,
                         const double x, const double y),
  DrawPathMoveToRelative(struct _DrawContext * context,
                         const double x, const double y),
  DrawPathStart(struct _DrawContext * context),
  DrawPoint(struct _DrawContext * context, const double x, const double y),
  DrawPolygon(struct _DrawContext * context,
              const unsigned long num_coords, const PointInfo * coordinates),
  DrawPolyline(struct _DrawContext * context,
               const unsigned long num_coords, const PointInfo * coordinates),
  DrawPopClipPath(struct _DrawContext * context),
  DrawPopDefs(struct _DrawContext * context),
  DrawPopGraphicContext(struct _DrawContext * context),
  DrawPopPattern(struct _DrawContext * context),
  DrawPushClipPath(struct _DrawContext * context, const char *clip_path_id),
  DrawPushDefs(struct _DrawContext * context),
  DrawPushGraphicContext(struct _DrawContext * context),
  DrawPushPattern(struct _DrawContext * context,
                  const char *pattern_id,
                  const double x, const double y,
                  const double width, const double height),
  DrawRectangle(struct _DrawContext * context,
                const double x1, const double y1,
                const double x2, const double y2),
  DrawRoundRectangle(struct _DrawContext * context,
                     double x1, double y1,
                     double x2, double y2,
                     double rx, double ry),
  DrawScale(struct _DrawContext * context, const double x, const double y),
  DrawSetClipPath(struct _DrawContext * context, const char *clip_path),
  DrawSetClipRule(struct _DrawContext * context, const FillRule fill_rule),
  DrawSetClipUnits(struct _DrawContext * context, const ClipPathUnits clip_units),
  DrawSetFillColor(struct _DrawContext * context, const PixelPacket *fill_color),
  DrawSetFillColorString(struct _DrawContext * context, const char *fill_color),
  DrawSetFillOpacity(struct _DrawContext * context, const double fill_opacity),
  DrawSetFillRule(struct _DrawContext * context, const FillRule fill_rule),
  DrawSetFillPatternURL(struct _DrawContext * context, const char *fill_url),
  DrawSetFont(struct _DrawContext * context, const char *font_name),
  DrawSetFontFamily(struct _DrawContext * context, const char *font_family),
  DrawSetFontSize(struct _DrawContext * context, const double font_pointsize),
  DrawSetFontStretch(struct _DrawContext * context, const StretchType font_stretch),
  DrawSetFontStyle(struct _DrawContext * context, const StyleType font_style),
  DrawSetFontWeight(struct _DrawContext * context, const unsigned long font_weight),
  DrawSetGravity(struct _DrawContext * context, const GravityType gravity),
  DrawRotate(struct _DrawContext * context, const double degrees),
  DrawSkewX(struct _DrawContext * context, const double degrees),
  DrawSkewY(struct _DrawContext * context, const double degrees),
  /*
   DrawSetStopColor(struct _DrawContext * context, const PixelPacket * color,
                    const double offset),
  */
  DrawSetStrokeAntialias(struct _DrawContext * context, const unsigned int true_false),
  DrawSetStrokeColor(struct _DrawContext * context, const PixelPacket *stroke_color),
  DrawSetStrokeColorString(struct _DrawContext * context, const char *stroke_color),
  DrawSetStrokeDashArray(struct _DrawContext * context, const unsigned long num_elems,
                         const double *dasharray),
  DrawSetStrokeDashOffset(struct _DrawContext * context,const double dashoffset),
  DrawSetStrokeLineCap(struct _DrawContext * context, const LineCap linecap),
  DrawSetStrokeLineJoin(struct _DrawContext * context, const LineJoin linejoin),
  DrawSetStrokeMiterLimit(struct _DrawContext * context,const unsigned long miterlimit),
  DrawSetStrokeOpacity(struct _DrawContext * context, const double opacity),
  DrawSetStrokePatternURL(struct _DrawContext * context, const char* stroke_url),
  DrawSetStrokeWidth(struct _DrawContext * context, const double width),
  DrawSetTextAntialias(struct _DrawContext * context, const unsigned int true_false),
  DrawSetTextDecoration(struct _DrawContext * context, const DecorationType decoration),
  DrawSetTextEncoding(struct _DrawContext * context, const char *encoding),
  DrawSetTextUnderColor(struct _DrawContext * context, const PixelPacket *color),
  DrawSetTextUnderColorString(struct _DrawContext * context, const char *under_color),
  DrawSetViewbox(struct _DrawContext * context,
                 unsigned long x1, unsigned long y1,
                 unsigned long x2, unsigned long y2),
  DrawTranslate(struct _DrawContext * context, const double x, const double y);


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
