/*
  Copyright (C) 2003-2026 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Private Color Utility Methods.
*/

/*
  Macros for testing a pixel to see if it is grayscale, bilevel,
  black, or white
*/
#define IsGray(color)  \
  (((color).red == (color).green) && ((color).red == (color).blue))
#define IsMonochrome(color) \
  (((0 == (color).red) || (MaxRGB == (color).red)) && IsGray(color))

#define IsBlackPixel(color) \
  (((color).red == 0U) && IsGray(color))

#define IsWhitePixel(color) \
  (((color).red == MaxRGB) && IsGray(color))

/*
  Compare two colors
*/
#define ColorMatch(p,q)                                         \
  (((p)->red == (q)->red) &&                                    \
   ((p)->green == (q)->green) &&                                \
   ((p)->blue == (q)->blue))

#define NotColorMatch(p,q)                                      \
  (((p)->red != (q)->red) ||                                    \
   ((p)->green != (q)->green) ||                                \
   ((p)->blue != (q)->blue))

#define QauntumDifference(p,q,element) \
  ((double)p->element-(double) q->element)
#define QuantumElementDistance(p,q,element) \
  (QauntumDifference(p,q,element)*QauntumDifference(p,q,element))
#define QuantumColorDistance(p,q) (QuantumElementDistance(p,q,red)+ \
                                   QuantumElementDistance(p,q,green) + \
                                   QuantumElementDistance(p,q,blue))

extern MagickExport unsigned int
  FuzzyColorMatch(const PixelPacket *p,const PixelPacket *q,const double fuzz) MAGICK_FUNC_PURE MAGICK_FUNC_DEPRECATED;

#if defined(MagickEpsilon)
static inline MagickBool FuzzyColorMatchInlined(const PixelPacket *p,
  const PixelPacket *q,const double fuzz) MAGICK_FUNC_PURE;
static inline MagickBool FuzzyColorMatchInlined(const PixelPacket *p,
  const PixelPacket *q,const double fuzz)
{
  return (fuzz <= MagickEpsilon ? ColorMatch(q,p) :
          (QuantumColorDistance(p,q) > fuzz*fuzz ? MagickFalse : MagickTrue));
}
#endif /* if defined(MagickEpsilon) */

/*
  Compare two pixels (including opacity)
*/
#define PixelMatch(p,q,matte)                                   \
  (ColorMatch(p,q) &&                                           \
   (!matte || ((p)->opacity == (q)->opacity)))

#define NotPixelMatch(p,q,matte)                                \
  (NotColorMatch(p,q) ||                                        \
   (matte && ((p)->opacity != (q)->opacity)))

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
