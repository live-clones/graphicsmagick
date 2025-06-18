/*
  Copyright (C) 2003-2025 GraphicsMagick Group

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick types typedefs.

  GraphicsMagick is expected to compile with any C '99 ANSI C compiler
  supporting at least 16-bit 'short', 32-bit 'int', and 32-bit 'long'.
  It is also expected to take advantage of 64-bit LP64 and Windows
  WIN64 LLP64.  We use C '99 style types but declare our own types so
  as to not directly depend on C '99 header files, and take care to
  depend only on C standard library functions, POSIX, or well-known
  extensions.
*/

#ifndef _MAGICK_TYPES_H
#define _MAGICK_TYPES_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include <inttypes.h> /* Format constants, integer types */
#include <stdint.h> /* C'99 typedefs and formatters */
#include <stddef.h> /* ptrdiff_t, size_t */

/*
  Assign ANSI C'99 stdint.h-like typedefs based on standard definitions.
  magick_int8_t   --                       -128 to 127
  magick_uint8_t  --                          0 to 255
  magick_int16_t  --                    -32,768 to 32,767
  magick_uint16_t --                          0 to 65,535
  magick_int32_t  --             -2,147,483,648 to 2,147,483,647
  magick_uint32_t --                          0 to 4,294,967,295
  magick_int64_t  -- -9,223,372,036,854,775,807 to 9,223,372,036,854,775,807
  magick_uint64_t --                          0 to 18,446,744,073,709,551,615

  magick_uintmax_t -- largest native unsigned integer type ("%ju")
                                              0 to UINTMAX_MAX
                      UINTMAX_C(value) declares constant value
  magick_uintptr_t -- unsigned type for storing a pointer value ("%tu")
                                              0 to UINTPTR_MAX

  ANSI C '89 stddef.h-like types
  size_t           -- unsigned type representing sizes of objects ("%zu")
                                              0 to SIZE_MAX
  ptrdiff_t -- signed type for subtracting two pointers ("%td")
                                    PTRDIFF_MIN to PTRDIFF_MAX

  IEEE Std 1003.1 (1990), 2004 types.  Not part of ANSI C!
  ssize_t          -- signed type for a count of bytes or an error indication ("%zd")
                                              ? to SSIZE_MAX
 Useful inttypes.h "printf" formatters:

  magick_int8_t PRId8
  magick_uint8_t PRIu8
  magick_int16_t PRId16
  magick_uint16_t PRIu16
  magick_int32_t PRId32
  magick_uint32_t PRIu32
  magick_int64_t PRId64
  magick_uint64_t PRIu64
  magick_uintmax_t ju
  magick_uintptr_t tu
  size_t zu
  ptrdiff_t td
  ssize_t zd?

*/

  /* Provide magick prefixed typedefs for standard typedefs */
  typedef int8_t   magick_int8_t;     /* int8_t */
  typedef uint8_t  magick_uint8_t;    /* uint8_t */

  typedef int16_t  magick_int16_t;    /* int16_t */
  typedef uint16_t magick_uint16_t;   /* uint16_t */

  typedef int32_t  magick_int32_t;    /* int32_t */
  typedef uint32_t magick_uint32_t;   /* uint32_t */

  typedef int64_t  magick_int64_t;    /* int64_t */
  typedef uint64_t magick_uint64_t;   /* uint64_t */

#  if defined(MAGICK_IMPLEMENTATION)

#if 0
#  define MAGICK_INT32_F  ""          /* %d (or %PRId32) */
#  define MAGICK_UINT32_F ""          /* %d (or %PRIu32) */
#  define MAGICK_INT64_F  PRId64      /* %PRId64 */
#  define MAGICK_UINT64_F PRIu64      /* %PRIu64 */
#endif

#  define MAGICK_INTMAX_F "j"         /* Formatter for intmax_t type */
#  define MAGICK_UINTMAX_F "j"        /* Formatter for uintmax_t type */

  /*
    C99 special size specifiers:

    hh - signed char / unsigned char
    h  - short / unsigned short
    ll - long long / unsigned long long
    j  - intmax_t / uintmax_t
    z  - signed size_t / size_t
    t  - ptrdiff_t / unsigned ptrdiff_t
  */

  typedef intmax_t magick_intmax_t; /* intmax_t */
#  define MAGICK_INTMAX_F "j"  /* %jd */

  typedef uintmax_t magick_uintmax_t; /* uintmax_t */
#  define MAGICK_UINTMAX_F "j"  /* %ju */

  typedef uintptr_t magick_uintptr_t; /* uintptr_t */
#  define MAGICK_UINTPTR_F "t"  /* %tu */

  typedef ptrdiff_t magick_ptrdiff_t; /* ptrdiff_t */
#  define MAGICK_PTRDIFF_F "t"  /* %td */

#  define MAGICK_SIZE_T_F "z" /* %zu */
#  define MAGICK_SIZE_T size_t     /* size_t */

#  define MAGICK_SSIZE_T_F "z" /* %zd */
#  define MAGICK_SSIZE_T ssize_t     /* ssize_t */

#endif /* defined(MAGICK_IMPLEMENTATION) */

  /* 64-bit file and blob offset type */
  typedef magick_int64_t magick_off_t;

#if defined(MAGICK_IMPLEMENTATION)
#  define MAGICK_OFF_F MAGICK_INTMAX_F
#endif /* defined(MAGICK_IMPLEMENTATION) */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* defined(__cplusplus) || defined(c_plusplus) */

#endif /* _MAGICK_TYPES_H */
