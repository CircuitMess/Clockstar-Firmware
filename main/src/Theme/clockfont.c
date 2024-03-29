/*******************************************************************************
 * Size: 25 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef CLOCKFONT
#define CLOCKFONT 1
#endif

#if CLOCKFONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x3f, 0xb3, 0xfc, 0xff, 0x7f, 0xff, 0xff, 0xff,
    0xfc, 0xfe, 0x3f, 0x8f, 0xe1, 0xe0, 0x78, 0x0,
    0x0, 0x1, 0xe0, 0xfe, 0x3f, 0x8f, 0xe3, 0xf8,
    0x78, 0x1e, 0x0,

    /* U+0022 "\"" */
    0x7c, 0xf, 0x3e, 0x7, 0xa3, 0x8c, 0x73, 0xc6,
    0xf9, 0xe3, 0x7f, 0xf1, 0xff, 0xf8, 0xff, 0xfc,
    0x7f, 0xfe, 0x3f, 0xbe, 0x7, 0x80,

    /* U+0023 "#" */
    0x7, 0x87, 0x0, 0xc6, 0x7e, 0x6, 0x33, 0xf0,
    0x37, 0x9f, 0x81, 0xbc, 0xfc, 0x3f, 0xe7, 0xf3,
    0xff, 0xff, 0xef, 0xff, 0xfc, 0x7f, 0xff, 0xe0,
    0xfe, 0x7e, 0x7, 0xf3, 0xf0, 0x3f, 0x9f, 0x87,
    0xff, 0xfe, 0x3f, 0xff, 0xf3, 0xff, 0xff, 0xef,
    0xf9, 0xfc, 0x7f, 0xcf, 0xe0, 0xfe, 0x7e, 0x7,
    0xf3, 0xf0, 0xf, 0xe, 0x0, 0x78, 0x70, 0x0,

    /* U+0024 "$" */
    0x0,

    /* U+0025 "%" */
    0x3c, 0x1, 0xe3, 0xc0, 0x1e, 0xc6, 0x7, 0xfd,
    0xe0, 0xff, 0xde, 0xf, 0xff, 0xe3, 0xff, 0x3c,
    0x7f, 0xe0, 0x7, 0xfc, 0x0, 0xff, 0xc0, 0x3f,
    0xf0, 0x3, 0xfe, 0x0, 0x7f, 0xe0, 0x1f, 0xf8,
    0x1, 0xff, 0x0, 0x3f, 0xf1, 0xef, 0xfe, 0x7f,
    0xff, 0x87, 0xff, 0xf8, 0x7f, 0xfe, 0x7, 0xf3,
    0xc0, 0x1e, 0x3c, 0x1, 0xe0,

    /* U+0026 "&" */
    0x0,

    /* U+0027 "'" */
    0x3c, 0x7b, 0x1e, 0xfd, 0xff, 0xff, 0xff, 0xfe,
    0x78,

    /* U+0028 "(" */
    0x3, 0xc0, 0xf, 0x0, 0xf1, 0x3f, 0x3f, 0xc3,
    0xfc, 0x3f, 0x8f, 0xe0, 0xfe, 0xf, 0xe0, 0xfe,
    0xf, 0xe0, 0xfe, 0x3, 0xf8, 0x3f, 0x83, 0xfc,
    0x1f, 0xf1, 0xff, 0xf, 0xf0, 0x3c, 0x3, 0xc0,

    /* U+0029 ")" */
    0x3c, 0xc, 0x70, 0xc7, 0xd, 0xf8, 0x3f, 0xc1,
    0xfc, 0x1f, 0xc0, 0x7f, 0x7, 0xf0, 0x7f, 0x7,
    0xf0, 0x7f, 0x7, 0xf1, 0xfc, 0x1f, 0xc3, 0xfc,
    0xff, 0x8f, 0xf8, 0xff, 0x3, 0xc0, 0x3c, 0x0,

    /* U+002A "*" */
    0x73, 0xa3, 0xf8, 0xfe, 0x7f, 0x7f, 0xbf, 0xff,
    0xff, 0xff, 0x73, 0x9c, 0xe0,

    /* U+002B "+" */
    0x1, 0xf8, 0x0, 0x11, 0xf0, 0x0, 0x8f, 0x80,
    0x4, 0xfc, 0x0, 0x27, 0xe0, 0x1, 0xff, 0x0,
    0xf, 0xf8, 0xf, 0xff, 0xfc, 0x7f, 0xff, 0xe7,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7,
    0xff, 0xfe, 0x1, 0xff, 0x0, 0xf, 0xf8, 0x0,
    0x7f, 0xc0, 0x3, 0xfe, 0x0, 0x1f, 0xf0, 0x0,
    0xff, 0x80, 0x3, 0xf0, 0x0, 0x1f, 0x80, 0x0,

    /* U+002C "," */
    0x3c, 0x7b, 0x1e, 0xfd, 0xff, 0xff, 0xff, 0xfe,
    0x78,

    /* U+002D "-" */
    0x7f, 0xff, 0x23, 0xff, 0xfb, 0xff, 0xfe, 0xff,
    0xff, 0xff, 0xff, 0xdf, 0xff, 0xc7, 0xff, 0xf0,

    /* U+002E "." */
    0x3d, 0x8f, 0x7e, 0xff, 0xe7, 0x8f, 0x0,

    /* U+002F "/" */
    0x0, 0x1, 0xe0, 0x0, 0x1e, 0x0, 0x7, 0xf0,
    0x0, 0xff, 0x0, 0xf, 0xf0, 0x3, 0xff, 0x0,
    0x7f, 0xe0, 0x7, 0xfe, 0x0, 0xff, 0xc0, 0x3f,
    0xf0, 0x3, 0xfe, 0x0, 0x7f, 0xe0, 0x1f, 0xf8,
    0x3, 0xff, 0x0, 0x3f, 0xf0, 0xf, 0xfe, 0x0,
    0xff, 0x80, 0xf, 0xf8, 0x0, 0xfe, 0x0, 0x3,
    0xc0, 0x0, 0x3c, 0x0, 0x0,

    /* U+0030 "0" */
    0x1f, 0xff, 0xc0, 0x7f, 0xff, 0x3, 0xff, 0xf9,
    0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xf8, 0x3f, 0xff, 0xc1, 0xff,
    0xfe, 0xf, 0xff, 0xf0, 0x7f, 0xff, 0x83, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xf8, 0x3f, 0xff, 0x81, 0xff, 0xfc, 0x0,

    /* U+0031 "1" */
    0x3f, 0xf3, 0x1f, 0xfc, 0x7f, 0xf3, 0xff, 0x3f,
    0xfc, 0xff, 0xf0, 0xff, 0xc3, 0xff, 0xf, 0xfc,
    0x3f, 0xf0, 0xff, 0xc3, 0xff, 0xf, 0xfc, 0x3f,
    0xf0, 0xff, 0xc3, 0xff, 0xf, 0xfc, 0x3f, 0xf0,
    0xff, 0xc1, 0xfc, 0x7, 0xf0,

    /* U+0032 "2" */
    0x3f, 0xff, 0xc8, 0xff, 0xfe, 0x8f, 0xff, 0xe9,
    0xff, 0xff, 0x3f, 0xff, 0xf3, 0xff, 0xff, 0x0,
    0x7, 0xf0, 0x0, 0x7f, 0x1f, 0xff, 0xf3, 0xff,
    0xfe, 0xff, 0xff, 0xcf, 0xff, 0xfc, 0xff, 0xc0,
    0xf, 0xff, 0xfe, 0xff, 0xff, 0xef, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3,
    0xff, 0xfe, 0x3f, 0xff, 0xe0,

    /* U+0033 "3" */
    0x1f, 0xff, 0xc0, 0x7f, 0xff, 0x3, 0xff, 0xf9,
    0x3f, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xfc,
    0x0, 0x7, 0xe3, 0xff, 0xff, 0x1f, 0xff, 0xfb,
    0xff, 0xff, 0xdf, 0xff, 0xfe, 0x3f, 0xff, 0xf0,
    0x0, 0x1f, 0xbf, 0xff, 0xfd, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xf8, 0x3f, 0xff, 0x81, 0xff, 0xfc, 0x0,

    /* U+0034 "4" */
    0x3f, 0xf, 0x6, 0x7d, 0xfc, 0x33, 0xef, 0xe1,
    0xbf, 0x7f, 0xf, 0xfb, 0xf8, 0x7f, 0xdf, 0xc3,
    0xfe, 0xfe, 0x1f, 0xf7, 0xf0, 0xff, 0xbf, 0x87,
    0xfd, 0xfc, 0x3f, 0xff, 0xf9, 0xff, 0xff, 0xcf,
    0xff, 0xff, 0x9f, 0xff, 0xfc, 0xff, 0xff, 0xe3,
    0xff, 0xfc, 0x0, 0x3f, 0x80, 0x1, 0xfc, 0x0,
    0xf, 0xe0, 0x0, 0x1e, 0x0, 0x0, 0xf0, 0x0,

    /* U+0035 "5" */
    0x3f, 0xff, 0xf4, 0x3f, 0xff, 0xe1, 0xff, 0xff,
    0x3f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xfb,
    0xff, 0x80, 0x1f, 0xff, 0xf8, 0xff, 0xff, 0xc7,
    0xff, 0xff, 0x8f, 0xff, 0xfc, 0x7f, 0xff, 0xf0,
    0x0, 0x3f, 0x80, 0x1, 0xfc, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0x7f, 0xff, 0x83, 0xff, 0xfc, 0x0,

    /* U+0036 "6" */
    0x1f, 0xff, 0xc0, 0xff, 0xfe, 0x3, 0xff, 0xf9,
    0x3f, 0xff, 0x8f, 0xfc, 0x0, 0x7f, 0xe0, 0x3,
    0xff, 0x0, 0x1f, 0xf8, 0x0, 0xff, 0xff, 0xc7,
    0xff, 0xff, 0x3f, 0xff, 0xf9, 0xff, 0xff, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xf8, 0x3f, 0xff, 0x81, 0xff, 0xfc, 0x0,

    /* U+0037 "7" */
    0x7f, 0xff, 0xe8, 0xff, 0xff, 0x8f, 0xff, 0xf9,
    0xff, 0xff, 0x7f, 0xff, 0xf7, 0xff, 0xff, 0x0,
    0x3f, 0xf0, 0x3, 0xfe, 0x0, 0x7f, 0xe0, 0x1f,
    0xf8, 0x1, 0xff, 0x80, 0x1f, 0xf0, 0x3, 0xfe,
    0x0, 0x3f, 0xe0, 0x3, 0xfe, 0x0, 0x3f, 0xe0,
    0x3, 0xfe, 0x0, 0x3f, 0xe0, 0x3, 0xfe, 0x0,
    0x1f, 0x80, 0x1, 0xf8, 0x0,

    /* U+0038 "8" */
    0x1f, 0xff, 0xc0, 0x7f, 0xff, 0x3, 0xff, 0xf9,
    0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfb,
    0xff, 0xff, 0x1f, 0xff, 0xf9, 0xff, 0xff, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xf8, 0x3f, 0xff, 0x81, 0xff, 0xfc, 0x0,

    /* U+0039 "9" */
    0x1f, 0xff, 0xc0, 0x7f, 0xff, 0x3, 0xff, 0xf9,
    0xbf, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb,
    0xff, 0xff, 0xc7, 0xff, 0xf8, 0x3f, 0xff, 0xc0,
    0x3, 0xfe, 0x0, 0x1f, 0xe0, 0x1, 0xff, 0x0,
    0x3f, 0xe0, 0x1, 0xff, 0x0, 0x1f, 0xf0, 0x3,
    0xfe, 0x0, 0x7, 0xe0, 0x0, 0x3f, 0x0, 0x0,

    /* U+003A ":" */
    0x3c, 0x7b, 0x1e, 0xfd, 0xff, 0xcf, 0x0, 0x0,
    0x0, 0x1, 0xef, 0xff, 0xff, 0xff, 0xfe, 0x78,

    /* U+003B ";" */
    0x3d, 0x8f, 0x7e, 0xff, 0xe7, 0x8f, 0x0, 0x0,
    0x0, 0xf1, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf9, 0xe0,

    /* U+003C "<" */
    0x0, 0xf0, 0x3, 0xc0, 0x1e, 0x9, 0xf1, 0xff,
    0xf, 0xf9, 0xff, 0x1f, 0xf0, 0xff, 0x87, 0xf0,
    0x3f, 0x81, 0xfc, 0xf, 0xf8, 0x3f, 0xe1, 0xff,
    0x3, 0xfe, 0x7, 0xf8, 0x3f, 0xc0, 0xfe, 0x1,
    0xe0, 0xf, 0x0,

    /* U+003D "=" */
    0x7f, 0xff, 0x1f, 0xff, 0xc8, 0xff, 0xfe, 0xff,
    0xff, 0xbf, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff,
    0xc0,

    /* U+003E ">" */
    0x3c, 0x4, 0x70, 0x23, 0x81, 0x3f, 0x3, 0xfe,
    0x1f, 0xf0, 0x7f, 0xc1, 0xff, 0xf, 0xf8, 0x1f,
    0xc0, 0xfe, 0x7, 0xf0, 0xff, 0x8f, 0xf8, 0x7f,
    0xc7, 0xfc, 0xff, 0x87, 0xfc, 0x3f, 0x80, 0x78,
    0x3, 0xc0, 0x0,

    /* U+003F "?" */
    0x3f, 0xff, 0xc8, 0xff, 0xfe, 0x8f, 0xff, 0xe9,
    0xff, 0xff, 0x3f, 0xff, 0xf3, 0xff, 0xff, 0x0,
    0x7, 0xf0, 0xf, 0xff, 0x0, 0xff, 0xf0, 0x3f,
    0xfe, 0x0, 0xff, 0xc0, 0xf, 0xfc, 0x0, 0x0,
    0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0x3f, 0x80,
    0x3, 0xf8, 0x0, 0x3f, 0x80, 0x3, 0xf8, 0x0,
    0xf, 0x0, 0x0, 0xf0, 0x0,

    /* U+0040 "@" */
    0x0,

    /* U+0041 "A" */
    0x1f, 0xff, 0x0, 0xff, 0xfe, 0x1, 0xff, 0xf1,
    0xbf, 0xff, 0xcd, 0xff, 0xfe, 0x7f, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0x83, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xf8, 0x3f, 0xff, 0xc1, 0xff, 0xfe, 0xf, 0xff,
    0xf0, 0x7e, 0x7f, 0x1, 0xc3, 0xf8, 0xe, 0x0,

    /* U+0042 "B" */
    0x3f, 0xff, 0xc4, 0x7f, 0xff, 0x23, 0xff, 0xf9,
    0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf8, 0x7f, 0xff, 0x83, 0xff, 0xfc, 0x0,

    /* U+0043 "C" */
    0x1f, 0xff, 0xe0, 0xff, 0xff, 0x1, 0xff, 0xff,
    0xbf, 0xff, 0xcf, 0xfc, 0x0, 0x7f, 0xe0, 0x3,
    0xff, 0x0, 0x1f, 0xf8, 0x0, 0xff, 0xc0, 0x7,
    0xfe, 0x0, 0x3f, 0xf0, 0x1, 0xff, 0x80, 0xf,
    0xfc, 0x0, 0x7f, 0xe0, 0x3, 0xff, 0x0, 0x1f,
    0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf,
    0xff, 0xfe, 0x3f, 0xff, 0xc1, 0xff, 0xfe, 0x0,

    /* U+0044 "D" */
    0x7f, 0xff, 0x4, 0x3f, 0xfe, 0x21, 0xff, 0xf1,
    0x3f, 0xff, 0xc9, 0xff, 0xfe, 0x7f, 0xe3, 0xff,
    0xff, 0x7, 0xff, 0xf8, 0x3f, 0xff, 0xc1, 0xff,
    0xfe, 0xf, 0xff, 0xf0, 0x7f, 0xff, 0x83, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x1f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf8, 0xff, 0xff, 0x87, 0xff, 0xfc, 0x0,

    /* U+0045 "E" */
    0x7f, 0xff, 0xe4, 0x3f, 0xff, 0xe1, 0xff, 0xff,
    0x3f, 0xff, 0xcf, 0xff, 0xfe, 0x7f, 0xf0, 0x3,
    0xff, 0x80, 0x1f, 0xff, 0xfc, 0xff, 0xff, 0xe7,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf,
    0xfe, 0x0, 0x7f, 0xf0, 0x3, 0xff, 0x80, 0x1f,
    0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xff, 0xff, 0xc7, 0xff, 0xfe, 0x0,

    /* U+0046 "F" */
    0x3f, 0xff, 0xe6, 0x3f, 0xff, 0xf1, 0xff, 0xff,
    0xbf, 0xff, 0xcd, 0xff, 0xfe, 0x7f, 0xe0, 0x3,
    0xff, 0x0, 0x1f, 0xf8, 0x0, 0xff, 0xff, 0xe7,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xcf,
    0xfc, 0x0, 0x7f, 0xe0, 0x3, 0xff, 0x0, 0x1f,
    0xf8, 0x0, 0xff, 0xc0, 0x7, 0xfe, 0x0, 0x3f,
    0xf0, 0x0, 0x7f, 0x0, 0x3, 0xf8, 0x0, 0x0,

    /* U+0047 "G" */
    0x1f, 0xff, 0xe0, 0xff, 0xff, 0x1, 0xff, 0xff,
    0x3f, 0xff, 0xcf, 0xfc, 0x0, 0x7f, 0xe0, 0x3,
    0xff, 0x0, 0x1f, 0xf8, 0x0, 0xff, 0xc7, 0xe7,
    0xfe, 0xff, 0xff, 0xf7, 0xff, 0xff, 0x8f, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xf8, 0x3f, 0xff, 0x81, 0xff, 0xfc, 0x0,

    /* U+0048 "H" */
    0x3f, 0x81, 0xec, 0x7c, 0x7f, 0xc7, 0xc7, 0xfd,
    0xfc, 0x7f, 0xdf, 0xc7, 0xff, 0xfc, 0x7f, 0xff,
    0xc7, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7,
    0xff, 0xfc, 0x7f, 0xff, 0xc7, 0xff, 0xfc, 0x7f,
    0xff, 0xc7, 0xff, 0xfc, 0x7f, 0xff, 0xc7, 0xf3,
    0xf8, 0x1e, 0x3f, 0x81, 0xe0,

    /* U+0049 "I" */
    0x3f, 0xb1, 0xfc, 0x7f, 0x7f, 0xdf, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0xfe, 0x3f, 0x80,

    /* U+004A "J" */
    0x0, 0xf, 0xe0, 0x0, 0x1e, 0x0, 0x31, 0xf0,
    0x3, 0x7f, 0x0, 0x37, 0xf0, 0x3, 0xff, 0x0,
    0x3f, 0xf0, 0x3, 0xff, 0x0, 0x3f, 0xf3, 0xc3,
    0xff, 0x3c, 0x3f, 0xff, 0xe3, 0xff, 0xfe, 0x3f,
    0xff, 0xe3, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xe3,
    0xff, 0xfe, 0x1f, 0xff, 0xc0,

    /* U+004B "K" */
    0x3f, 0x80, 0xe0, 0x3c, 0x7, 0x31, 0xf0, 0x7f,
    0xbf, 0x8f, 0xff, 0xfc, 0xff, 0xff, 0xe7, 0xff,
    0xff, 0xff, 0x9f, 0xff, 0xfc, 0xff, 0xff, 0xc7,
    0xff, 0xf8, 0x3f, 0xff, 0xf1, 0xff, 0xff, 0x8f,
    0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf9, 0xff, 0xff, 0xc7, 0xff, 0xfe, 0x3f, 0xff,
    0xf0, 0x7e, 0x7f, 0x1, 0xc3, 0xf8, 0xe, 0x0,

    /* U+004C "L" */
    0x3f, 0x80, 0x18, 0xf8, 0x3, 0x1f, 0x0, 0x6f,
    0xe0, 0xf, 0xfc, 0x1, 0xff, 0x80, 0x3f, 0xf0,
    0x7, 0xfe, 0x0, 0xff, 0xc0, 0x1f, 0xf8, 0x3,
    0xff, 0x0, 0x7f, 0xe0, 0xf, 0xfc, 0x1, 0xff,
    0x80, 0x3f, 0xf0, 0x7, 0xff, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xe3,
    0xff, 0xfc,

    /* U+004D "M" */
    0x3f, 0x80, 0xf3, 0x1f, 0x7, 0xfc, 0x7c, 0x1f,
    0xf7, 0xf0, 0x7f, 0xdf, 0xc1, 0xff, 0xff, 0x7,
    0xff, 0xfc, 0x1f, 0xff, 0xf0, 0x7f, 0xff, 0xf7,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf2, 0x7f, 0xff, 0xc1, 0xff, 0xff,
    0x7, 0xff, 0xfc, 0x1f, 0xcf, 0xe0, 0x3c, 0x3f,
    0x80, 0xf0,

    /* U+004E "N" */
    0x3f, 0x81, 0xec, 0x7c, 0x7f, 0xc7, 0xc7, 0xfd,
    0xfc, 0x7f, 0xdf, 0xc7, 0xff, 0xfc, 0x7f, 0xff,
    0xc7, 0xff, 0xff, 0x7f, 0xff, 0xf7, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfd, 0xff, 0xff, 0xdf, 0xff, 0xfc, 0x7f,
    0xff, 0xc7, 0xff, 0xfc, 0x7f, 0xff, 0xc7, 0xf3,
    0xf8, 0x1e, 0x3f, 0x81, 0xe0,

    /* U+004F "O" */
    0x1f, 0xff, 0xc0, 0x7f, 0xff, 0x3, 0xff, 0xf9,
    0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xf8, 0x3f, 0xff, 0xc1, 0xff,
    0xfe, 0xf, 0xff, 0xf0, 0x7f, 0xff, 0x83, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xf8, 0x3f, 0xff, 0x81, 0xff, 0xfc, 0x0,

    /* U+0050 "P" */
    0x3f, 0xff, 0xcc, 0xff, 0xfe, 0xcf, 0xff, 0xed,
    0xff, 0xff, 0xdf, 0xff, 0xff, 0xfc, 0x7f, 0xff,
    0xc7, 0xff, 0xfc, 0x7f, 0xff, 0xc7, 0xff, 0xfc,
    0x7f, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xef, 0xff, 0xfc, 0xff, 0xff, 0xcf, 0xfc, 0x0,
    0xff, 0xc0, 0xf, 0xfc, 0x0, 0xff, 0xc0, 0x3,
    0xf8, 0x0, 0x3f, 0x80, 0x0,

    /* U+0051 "Q" */
    0x1f, 0xff, 0xc0, 0x7f, 0xff, 0x3, 0xff, 0xf9,
    0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xf8, 0x3f, 0xff, 0xc1, 0xff,
    0xfe, 0xf, 0xff, 0xf0, 0x7f, 0xff, 0x83, 0xff,
    0xfc, 0x1f, 0xff, 0xe0, 0xff, 0xff, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xf8, 0x3f, 0xff, 0x81, 0xff, 0xfc, 0x0,
    0x1f, 0xe0, 0x0, 0xff, 0x0, 0x1, 0xf8,

    /* U+0052 "R" */
    0x3f, 0xff, 0xc6, 0x7f, 0xff, 0x33, 0xff, 0xf9,
    0xbf, 0xff, 0xfd, 0xfc, 0x1f, 0xff, 0xe0, 0xff,
    0xff, 0x7, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x3f, 0xff, 0xf1, 0xff, 0xff, 0x8f,
    0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf9, 0xff, 0xff, 0xc7, 0xff, 0xfe, 0x3f, 0xff,
    0xf0, 0x7e, 0x7f, 0x1, 0xc3, 0xf8, 0xe, 0x0,

    /* U+0053 "S" */
    0x1f, 0xff, 0xe0, 0x3f, 0xff, 0xc1, 0xff, 0xff,
    0x3f, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xf3,
    0xff, 0x80, 0x1f, 0xff, 0xfc, 0xff, 0xff, 0xe7,
    0xff, 0xff, 0xcf, 0xff, 0xfe, 0x7f, 0xff, 0xf0,
    0x0, 0x3f, 0x80, 0x1, 0xfc, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf8, 0x7f, 0xff, 0x83, 0xff, 0xfc, 0x0,

    /* U+0054 "T" */
    0x7f, 0xff, 0xe4, 0x3f, 0xff, 0xe1, 0xff, 0xff,
    0x3f, 0xff, 0xf7, 0xff, 0xfe, 0x3f, 0xff, 0xf0,
    0xf, 0xf8, 0x0, 0x7f, 0xc0, 0x3, 0xfe, 0x0,
    0x1f, 0xf0, 0x0, 0xff, 0x80, 0x7, 0xfc, 0x0,
    0x3f, 0xe0, 0x1, 0xff, 0x0, 0xf, 0xf8, 0x0,
    0x7f, 0xc0, 0x3, 0xfe, 0x0, 0x1f, 0xf0, 0x0,
    0xff, 0x80, 0x7, 0xfc, 0x0, 0x1f, 0x80, 0x0,

    /* U+0055 "U" */
    0x3f, 0x81, 0xe0, 0xf8, 0x1e, 0xcf, 0xc7, 0xfd,
    0xfc, 0x7f, 0xff, 0xc7, 0xff, 0xfc, 0x7f, 0xff,
    0xc7, 0xff, 0xfc, 0x7f, 0xff, 0xc7, 0xff, 0xfc,
    0x7f, 0xff, 0xc7, 0xff, 0xfc, 0x7f, 0xff, 0xc7,
    0xff, 0xfc, 0x7f, 0xff, 0xc7, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xe1,
    0xff, 0xfc, 0x1f, 0xff, 0xc0,

    /* U+0056 "V" */
    0x3f, 0x81, 0xe0, 0xf8, 0x1e, 0xcf, 0xc3, 0xfd,
    0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xfc, 0x3f, 0xff,
    0xc3, 0xff, 0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xfc,
    0x3f, 0xff, 0xcf, 0xff, 0xfc, 0xff, 0xff, 0xff,
    0xef, 0xff, 0xfe, 0xff, 0xff, 0xcf, 0xff, 0xf0,
    0xff, 0xff, 0xf, 0xff, 0xe0, 0x3f, 0xfc, 0x1,
    0xff, 0x0, 0x1f, 0xf0, 0x0,

    /* U+0057 "W" */
    0x3f, 0x80, 0xf3, 0x1f, 0x7, 0xfc, 0x7c, 0x1f,
    0xf7, 0xf0, 0x7f, 0xdf, 0xc1, 0xff, 0xff, 0x7,
    0xff, 0xfc, 0x1f, 0xff, 0xf0, 0x7f, 0xff, 0xc1,
    0xff, 0xff, 0x27, 0xff, 0xfc, 0x9f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff,
    0xdf, 0xff, 0xfc, 0x1f, 0xcf, 0xe0, 0x3c, 0x3f,
    0x80, 0xf0,

    /* U+0058 "X" */
    0x3c, 0x1, 0xe0, 0x60, 0xf, 0x23, 0x80, 0xff,
    0x3f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0xff, 0xff, 0x87, 0xff, 0xfc, 0x1f, 0xff, 0xc0,
    0x7f, 0xf8, 0x3, 0xff, 0xc0, 0x1f, 0xfe, 0x1,
    0xff, 0xfc, 0xf, 0xff, 0xe0, 0xff, 0xff, 0x9f,
    0xff, 0xff, 0xff, 0x8f, 0xff, 0xfc, 0x7f, 0xff,
    0x80, 0xfe, 0x78, 0x3, 0xc3, 0xc0, 0x1e, 0x0,

    /* U+0059 "Y" */
    0x7e, 0x7, 0xe0, 0x70, 0x3f, 0x23, 0xe3, 0xff,
    0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
    0xff, 0xff, 0x83, 0xff, 0xf8, 0x1f, 0xff, 0xc0,
    0x7f, 0xf8, 0x3, 0xff, 0xc0, 0x7, 0xfc, 0x0,
    0x3f, 0xe0, 0x1, 0xff, 0x0, 0xf, 0xf8, 0x0,
    0x7f, 0xc0, 0x3, 0xfe, 0x0, 0x1f, 0xf0, 0x0,
    0xff, 0x80, 0x7, 0xfc, 0x0, 0x1f, 0x80, 0x0,

    /* U+005A "Z" */
    0x7f, 0xff, 0xe4, 0x3f, 0xff, 0xe1, 0xff, 0xff,
    0x3f, 0xff, 0xf7, 0xff, 0xff, 0xbf, 0xff, 0xfc,
    0x1, 0xff, 0x80, 0xf, 0xfc, 0x0, 0xff, 0xc0,
    0x1f, 0xf8, 0x0, 0xff, 0xc0, 0xf, 0xfc, 0x1,
    0xff, 0x80, 0xf, 0xfc, 0x1, 0xff, 0xff, 0x9f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xff, 0xff, 0xc7, 0xff, 0xfe, 0x0,

    /* U+005B "[" */
    0x1f, 0x83, 0xf0, 0xfe, 0x7f, 0xff, 0xbf, 0xef,
    0xe3, 0xf8, 0xfe, 0x3f, 0x8f, 0xe3, 0xf8, 0xfe,
    0x3f, 0x8f, 0xe3, 0xfe, 0xff, 0xff, 0xf7, 0xfc,
    0x7e, 0x1f, 0x80,

    /* U+005C "\\" */
    0x3c, 0x0, 0x0, 0xc0, 0x0, 0x8e, 0x0, 0x9,
    0xf8, 0x0, 0x9f, 0x80, 0xf, 0xfc, 0x0, 0x3f,
    0xf0, 0x3, 0xff, 0x0, 0x1f, 0xf8, 0x0, 0xff,
    0xc0, 0xf, 0xff, 0x0, 0x3f, 0xf0, 0x0, 0xff,
    0xc0, 0x7, 0xfc, 0x0, 0x7f, 0xe0, 0x3, 0xff,
    0x0, 0xf, 0xf0, 0x0, 0xff, 0x0, 0x7, 0xf0,
    0x0, 0x1e, 0x0, 0x1, 0xe0,

    /* U+005D "]" */
    0x7e, 0x23, 0xe8, 0xfa, 0x7f, 0x7f, 0xdf, 0xf1,
    0xfc, 0x7f, 0x1f, 0xc7, 0xf1, 0xfc, 0x7f, 0x1f,
    0xc7, 0xf1, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xf9,
    0xf8, 0x7e, 0x0,

    /* U+005E "^" */
    0x7f, 0xc8, 0xff, 0x9f, 0xf9, 0xff, 0xff, 0xf7,
    0xfc, 0x7f, 0xc0,

    /* U+005F "_" */
    0x7f, 0xff, 0xe4, 0x3f, 0xff, 0xe7, 0xff, 0xff,
    0x3f, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xf1,
    0xff, 0xff, 0x80,

    /* U+0060 "`" */
    0x7f, 0xc8, 0xff, 0x9f, 0xf9, 0xff, 0xff, 0xf7,
    0xfc, 0x7f, 0xc0,

    /* U+0061 "a" */
    0x1f, 0xfe, 0xf, 0xff, 0x3, 0xff, 0xd3, 0xff,
    0xff, 0xf8, 0x7f, 0xfc, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff,
    0xf0, 0xff, 0xf8, 0x7f, 0xfc, 0x3f, 0xfe, 0x1f,
    0xff, 0xf, 0x7e, 0x1, 0x3f, 0x0, 0x80,

    /* U+0062 "b" */
    0x3f, 0xfe, 0x23, 0xff, 0xc8, 0xff, 0xf2, 0x7f,
    0xff, 0xff, 0x87, 0xff, 0xe1, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xf8,
    0x7f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x3f, 0xfe, 0xf, 0xff,
    0x80,

    /* U+0063 "c" */
    0x1f, 0xff, 0x7, 0xff, 0xf0, 0x7f, 0xff, 0x7f,
    0xfc, 0xff, 0x80, 0x3f, 0xe0, 0xf, 0xf8, 0x3,
    0xfe, 0x0, 0xff, 0x80, 0x3f, 0xe0, 0xf, 0xf8,
    0x3, 0xfe, 0x0, 0xff, 0xff, 0x3f, 0xff, 0xff,
    0xff, 0xfc, 0xff, 0xff, 0x1f, 0xff, 0x7, 0xff,
    0xc0,

    /* U+0064 "d" */
    0x7f, 0xf8, 0x43, 0xff, 0x21, 0xff, 0x93, 0xff,
    0xe9, 0xff, 0xf7, 0xfc, 0x7f, 0xfe, 0x1f, 0xff,
    0xf, 0xff, 0x87, 0xff, 0xc3, 0xff, 0xe1, 0xff,
    0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0x7f, 0xfe, 0x3f, 0xff, 0x0,

    /* U+0065 "e" */
    0x7f, 0xff, 0x21, 0xff, 0xf9, 0xff, 0xfe, 0x7f,
    0xfc, 0xff, 0x80, 0x3f, 0xff, 0xcf, 0xff, 0xf3,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf8,
    0x3, 0xfe, 0x0, 0xff, 0xff, 0x3f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x1f, 0xff,
    0xc0,

    /* U+0066 "f" */
    0x7f, 0xff, 0x21, 0xff, 0xf8, 0x7f, 0xfe, 0x7f,
    0xfc, 0xff, 0xff, 0x3f, 0xe0, 0xf, 0xff, 0xf3,
    0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf8,
    0x3, 0xfe, 0x0, 0xff, 0x80, 0x3f, 0xe0, 0xf,
    0xf8, 0x3, 0xfe, 0x0, 0x7e, 0x0, 0x1f, 0x80,
    0x0,

    /* U+0067 "g" */
    0x1f, 0xff, 0x7, 0xff, 0xf0, 0x7f, 0xfe, 0x7f,
    0xfc, 0xff, 0x80, 0x3f, 0xe0, 0xf, 0xf8, 0xf3,
    0xfe, 0x3c, 0xff, 0xbf, 0xff, 0xe3, 0xff, 0xf8,
    0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfd, 0xff, 0xfc, 0x1f, 0xfe, 0x7, 0xff,
    0x80,

    /* U+0068 "h" */
    0x7e, 0x7, 0x23, 0xe3, 0xf8, 0xf8, 0xfe, 0x7e,
    0x3f, 0xff, 0x8f, 0xff, 0xe3, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
    0xff, 0xfe, 0x3f, 0xff, 0x8f, 0xff, 0xe3, 0xff,
    0xf8, 0xff, 0xfe, 0x3f, 0x7e, 0x7, 0x1f, 0x81,
    0xc0,

    /* U+0069 "i" */
    0x7e, 0x47, 0xe7, 0xf3, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x7e, 0x3f, 0x0,

    /* U+006A "j" */
    0x0, 0x3f, 0x0, 0x1, 0xc0, 0x4, 0x7c, 0x1,
    0x3f, 0x0, 0x7f, 0xc0, 0x1f, 0xf0, 0x7, 0xfd,
    0xc1, 0xff, 0x70, 0x7f, 0xff, 0x1f, 0xff, 0xc7,
    0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfd, 0xff, 0xfc, 0x1f, 0xfe, 0x7, 0xff,
    0x80,

    /* U+006B "k" */
    0x7e, 0x7, 0x23, 0xe3, 0xf8, 0xf8, 0xfe, 0x7e,
    0xff, 0xff, 0xff, 0x3f, 0xff, 0xcf, 0xff, 0xe3,
    0xff, 0xe0, 0xff, 0xf8, 0x3f, 0xff, 0x8f, 0xff,
    0xf3, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xef, 0xff,
    0xfb, 0xff, 0xfe, 0x3f, 0x7e, 0x7, 0x1f, 0x81,
    0xc0,

    /* U+006C "l" */
    0x7e, 0x0, 0x8f, 0x80, 0x8f, 0x80, 0x9f, 0x80,
    0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80,
    0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80,
    0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x7f, 0xfc, 0x7f, 0xfc,

    /* U+006D "m" */
    0x7e, 0x1, 0xd1, 0xf0, 0xfe, 0x7e, 0x1f, 0xcf,
    0xc3, 0xff, 0xfc, 0xff, 0xff, 0x9f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfe, 0xdf, 0xff, 0xdb, 0xff, 0xf8, 0x7f, 0xff,
    0xf, 0xff, 0xe1, 0xff, 0xfc, 0x3f, 0x7e, 0x1,
    0xcf, 0xc0, 0x38,

    /* U+006E "n" */
    0x7e, 0x7, 0x23, 0xe3, 0xf8, 0xf8, 0xfe, 0x7e,
    0x3f, 0x9f, 0x8f, 0xff, 0xfb, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xf8,
    0xff, 0xfe, 0x3f, 0xff, 0x8f, 0xff, 0xe3, 0xff,
    0xf8, 0xff, 0xfe, 0x3f, 0x7e, 0x7, 0x1f, 0x81,
    0xc0,

    /* U+006F "o" */
    0x1f, 0xfe, 0x7, 0xff, 0x83, 0xff, 0xd3, 0xff,
    0xff, 0xf8, 0x7f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff,
    0xf, 0xff, 0x87, 0xff, 0xc3, 0xff, 0xe1, 0xff,
    0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xfe, 0x1f, 0xfe, 0xf, 0xff, 0x0,

    /* U+0070 "p" */
    0x7f, 0xfc, 0x23, 0xff, 0xc8, 0xff, 0xf2, 0x7f,
    0xff, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xf8, 0xff,
    0xfe, 0x3f, 0xff, 0x8f, 0xff, 0xff, 0xcf, 0xff,
    0xc3, 0xff, 0xf0, 0xff, 0x80, 0x3f, 0xe0, 0xf,
    0xf8, 0x3, 0xfe, 0x0, 0x7e, 0x0, 0x1f, 0x80,
    0x0,

    /* U+0071 "q" */
    0x1f, 0xfe, 0x7, 0xff, 0x83, 0xff, 0xd3, 0xff,
    0xff, 0xf8, 0x7f, 0xfc, 0x3f, 0xfe, 0x1f, 0xff,
    0xf, 0xff, 0x87, 0xff, 0xc3, 0xff, 0xe1, 0xff,
    0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xfe, 0x1f, 0xfe, 0xf, 0xff, 0x0, 0x1f,
    0x80, 0xf, 0xc0, 0x3, 0xe0,

    /* U+0072 "r" */
    0x7f, 0xfc, 0x1f, 0xff, 0x8, 0xff, 0xf2, 0x7f,
    0xff, 0xff, 0x87, 0xff, 0xe1, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0xff, 0xff, 0x3f, 0xff, 0xf, 0xff,
    0xc3, 0xff, 0xfc, 0xff, 0xbf, 0xff, 0xe3, 0xff,
    0xf8, 0xff, 0xfe, 0x1f, 0x7e, 0x3, 0x1f, 0x80,
    0xc0,

    /* U+0073 "s" */
    0x1f, 0xff, 0x7, 0xff, 0xf0, 0x7f, 0xfe, 0x7f,
    0xfc, 0xff, 0x80, 0x3f, 0xe0, 0xf, 0xff, 0xf0,
    0xff, 0xfc, 0x3f, 0xff, 0xc0, 0x3, 0xf0, 0x0,
    0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xf, 0xff,
    0x80,

    /* U+0074 "t" */
    0x7f, 0xff, 0x23, 0xff, 0xfb, 0xff, 0xfe, 0xff,
    0xff, 0x7f, 0xff, 0x1f, 0xff, 0xc0, 0xff, 0x80,
    0x3f, 0xe0, 0xf, 0xf8, 0x3, 0xfe, 0x0, 0xff,
    0x80, 0x3f, 0xe0, 0xf, 0xf8, 0x3, 0xfe, 0x0,
    0xff, 0x80, 0x3f, 0xe0, 0x3, 0xf0, 0x0, 0xfc,
    0x0,

    /* U+0075 "u" */
    0x7e, 0x7, 0x3, 0x81, 0xc8, 0xf8, 0xfe, 0x7e,
    0x3f, 0xff, 0x8f, 0xff, 0xe3, 0xff, 0xf8, 0xff,
    0xfe, 0x3f, 0xff, 0x8f, 0xff, 0xe3, 0xff, 0xf8,
    0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfd, 0xff, 0xfc, 0x1f, 0xfe, 0x7, 0xff,
    0x80,

    /* U+0076 "v" */
    0x7e, 0x7, 0x3, 0x81, 0xc8, 0xf8, 0xfe, 0x7e,
    0x3f, 0xff, 0x8f, 0xff, 0xe3, 0xff, 0xf8, 0xff,
    0xfe, 0x3f, 0xff, 0x8f, 0xff, 0xef, 0xff, 0xff,
    0xff, 0xff, 0xfc, 0xff, 0xfe, 0x3f, 0xfe, 0xf,
    0xff, 0x81, 0xff, 0x80, 0x1f, 0xc0, 0x7, 0xf0,
    0x0,

    /* U+0077 "w" */
    0x7e, 0x1, 0xd1, 0xf0, 0xfe, 0x7e, 0x1f, 0xcf,
    0xc3, 0xff, 0xf8, 0x7f, 0xff, 0xf, 0xff, 0xe1,
    0xff, 0xfc, 0xbf, 0xff, 0x97, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xdf, 0xff, 0xfb, 0xff, 0xfc, 0x3f, 0x7e, 0x1,
    0xcf, 0xc0, 0x38,

    /* U+0078 "x" */
    0x38, 0xf, 0x0, 0x3, 0xc8, 0x43, 0xfe, 0x79,
    0xff, 0x9e, 0x7f, 0xff, 0xff, 0xc3, 0xff, 0xe0,
    0xff, 0xf8, 0x1f, 0xf8, 0x1, 0xff, 0x81, 0xff,
    0xf0, 0x7f, 0xfc, 0x3f, 0xff, 0xff, 0xef, 0xff,
    0xfb, 0xff, 0xf8, 0x3f, 0x3c, 0x7, 0xf, 0x1,
    0xc0,

    /* U+0079 "y" */
    0x3c, 0xf, 0x23, 0x87, 0xf8, 0xe1, 0xfe, 0x7f,
    0xff, 0x3f, 0xff, 0xf, 0xff, 0xc1, 0xff, 0xe0,
    0x3f, 0xe0, 0xf, 0xf8, 0x0, 0xfe, 0x0, 0x3f,
    0x80, 0xf, 0xe0, 0x3, 0xf8, 0x0, 0xfe, 0x0,
    0x3f, 0x80, 0xf, 0xe0, 0x0, 0xf0, 0x0, 0x3c,
    0x0,

    /* U+007A "z" */
    0x7f, 0xff, 0x3f, 0xff, 0xf8, 0x7f, 0xfe, 0x7f,
    0xff, 0xff, 0xff, 0xdf, 0xff, 0xc0, 0xf, 0xe0,
    0x3, 0xf8, 0x3, 0xf8, 0x1, 0xfc, 0x0, 0x7f,
    0x0, 0x7f, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x1f, 0xff,
    0xc0,

    /* U+007B "{" */
    0x3, 0xf0, 0xf, 0xc0, 0x7e, 0x27, 0xf1, 0xff,
    0xf, 0xf8, 0x7f, 0xf, 0xf8, 0x7f, 0xc7, 0xfe,
    0x3f, 0xf1, 0xff, 0x87, 0xfc, 0xf, 0xe0, 0x7f,
    0x3, 0xfe, 0x1f, 0xf8, 0xff, 0xc3, 0xfe, 0x7,
    0xe0, 0x3f, 0x0,

    /* U+007C "|" */
    0x3f, 0xb1, 0xfc, 0x7f, 0x7f, 0xdf, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0xfe, 0x3f, 0x80,

    /* U+007D "}" */
    0x7e, 0x4, 0x7c, 0x23, 0xe1, 0x3f, 0x87, 0xfc,
    0x3f, 0xe0, 0x7f, 0x3, 0xfe, 0x1f, 0xf0, 0xff,
    0xc7, 0xfe, 0x3f, 0xf1, 0xff, 0xf, 0xe0, 0x7f,
    0xf, 0xf8, 0xff, 0xc7, 0xfe, 0x3f, 0xe0, 0xfc,
    0x7, 0xe0, 0x0,

    /* U+007E "~" */
    0x7f, 0xc8, 0xff, 0x9f, 0xf9, 0xff, 0xff, 0xf7,
    0xfc, 0x7f, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 329, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 212, .box_w = 10, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 329, .box_w = 17, .box_h = 10, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 50, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 329, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 329, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 165, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 170, .adv_w = 235, .box_w = 12, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 235, .box_w = 12, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 212, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 247, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 165, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 312, .adv_w = 329, .box_w = 18, .box_h = 7, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 328, .adv_w = 165, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 335, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 259, .box_w = 14, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 923, .adv_w = 165, .box_w = 7, .box_h = 18, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 939, .adv_w = 165, .box_w = 7, .box_h = 20, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 957, .adv_w = 259, .box_w = 13, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 992, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1033, .adv_w = 259, .box_w = 13, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1068, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1121, .adv_w = 329, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1122, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1178, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1234, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1290, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1346, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1402, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1458, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1514, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1567, .adv_w = 212, .box_w = 10, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1594, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1647, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1703, .adv_w = 353, .box_w = 19, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1753, .adv_w = 400, .box_w = 22, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1811, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1864, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1920, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1973, .adv_w = 376, .box_w = 21, .box_h = 24, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2036, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2092, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2148, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2204, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2257, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2310, .adv_w = 400, .box_w = 22, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2368, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2424, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2480, .adv_w = 376, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2536, .adv_w = 212, .box_w = 10, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2563, .adv_w = 376, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2616, .adv_w = 212, .box_w = 10, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2643, .adv_w = 235, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 2654, .adv_w = 376, .box_w = 21, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2673, .adv_w = 235, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 2684, .adv_w = 329, .box_w = 17, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2723, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2764, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2805, .adv_w = 329, .box_w = 17, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2844, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2885, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2926, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2967, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3008, .adv_w = 188, .box_w = 9, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3029, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3070, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3111, .adv_w = 306, .box_w = 16, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3147, .adv_w = 353, .box_w = 19, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3190, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3231, .adv_w = 329, .box_w = 17, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3270, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3311, .adv_w = 329, .box_w = 17, .box_h = 21, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3356, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3397, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3438, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3479, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3520, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3561, .adv_w = 353, .box_w = 19, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3604, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3645, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3686, .adv_w = 329, .box_w = 18, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3727, .adv_w = 259, .box_w = 13, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3762, .adv_w = 212, .box_w = 10, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3789, .adv_w = 259, .box_w = 13, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3824, .adv_w = 235, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 12}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t clockfont = {
#else
lv_font_t clockfont = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 25,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if CLOCKFONT*/

