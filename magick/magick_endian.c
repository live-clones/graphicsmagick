/*
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include "magick/studio.h"
#include "magick/magick_endian.h"

MagickExport void
MagickSwabUInt16(magick_uint16_t* wp)
{
  register unsigned char* cp = (unsigned char*) wp;
  unsigned char t;

  t = cp[1]; cp[1] = cp[0]; cp[0] = t;
}

MagickExport void
MagickSwabUInt32(magick_uint32_t* lp)
{
  register unsigned char* cp = (unsigned char*) lp;
  unsigned char t;

  t = cp[3]; cp[3] = cp[0]; cp[0] = t;
  t = cp[2]; cp[2] = cp[1]; cp[1] = t;
}

MagickExport void
MagickSwabArrayOfUInt16(magick_uint16_t* wp, register size_t n)
{
  register unsigned char* cp;
  register unsigned char t;

  while (n-- > 0) {
    cp = (unsigned char*) wp;
    t = cp[1]; cp[1] = cp[0]; cp[0] = t;
    wp++;
  }
}

MagickExport void
MagickSwabArrayOfUInt32(register magick_uint32_t* lp, register size_t n)
{
  register unsigned char *cp;
  register unsigned char t;

  while (n-- > 0) {
    cp = (unsigned char *)lp;
    t = cp[3]; cp[3] = cp[0]; cp[0] = t;
    t = cp[2]; cp[2] = cp[1]; cp[1] = t;
    lp++;
  }
}

MagickExport void
MagickSwabFloat(float *fp)
{
  MagickSwabUInt32((magick_uint32_t *) fp);
}

MagickExport void
MagickSwabArrayOfFloat(float *fp, size_t n)
{
  MagickSwabArrayOfUInt32((magick_uint32_t *) fp, n);
}

MagickExport void
MagickSwabDouble(double *dp)
{
  register magick_uint32_t* lp = (magick_uint32_t*) dp;
  magick_uint32_t t;

  MagickSwabArrayOfUInt32(lp, 2);
  t = lp[0]; lp[0] = lp[1]; lp[1] = t;
}

MagickExport void
MagickSwabArrayOfDouble(double* dp, register size_t n)
{
  register magick_uint32_t* lp = (magick_uint32_t*) dp;
  register magick_uint32_t t;

  MagickSwabArrayOfUInt32(lp, n + n);
  while (n-- > 0) {
    t = lp[0]; lp[0] = lp[1]; lp[1] = t;
    lp += 2;
  }
}

/*
  FIXME: Nothing in GraphicsMagick is using MagickReverseBits() or
  MagickGetBitRevTable() so they should be entirely removed.
*/
MagickExport const unsigned char*
MagickGetBitRevTable(int reversed)
{
  (void) reversed;
  return (const unsigned char*) NULL;
}

MagickExport void
MagickReverseBits(register unsigned char* cp, register size_t n)
{
  (void) cp;
  (void) n;
}
