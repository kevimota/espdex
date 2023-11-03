/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef UI_ARONE16
#define UI_ARONE16 1
#endif

#if UI_ARONE16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x55, 0x55, 0x3c,

    /* U+0022 "\"" */
    0x99, 0x90,

    /* U+0023 "#" */
    0x9, 0x82, 0x40, 0x91, 0xff, 0x11, 0x4, 0xc1,
    0x23, 0xff, 0x32, 0x8, 0x82, 0x60,

    /* U+0024 "$" */
    0x10, 0xff, 0xc, 0x8, 0xc, 0xe, 0x6, 0x6,
    0x6, 0x1f, 0xe1, 0x2, 0x0,

    /* U+0025 "%" */
    0x70, 0x91, 0x12, 0x24, 0x45, 0x87, 0x20, 0xc,
    0x1, 0x30, 0x49, 0x19, 0x22, 0x24, 0xc3, 0x0,

    /* U+0026 "&" */
    0x3c, 0x21, 0x10, 0x88, 0xc2, 0x43, 0x83, 0x23,
    0x9, 0x82, 0xc1, 0x5f, 0xc0,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x2d, 0x69, 0x24, 0x92, 0x24, 0x40,

    /* U+0029 ")" */
    0x99, 0x22, 0x49, 0x25, 0xa5, 0x0,

    /* U+002A "*" */
    0x21, 0x3e, 0xe5, 0x80,

    /* U+002B "+" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x20, 0x84, 0x10, 0xc2, 0x8, 0x41, 0xc,
    0x0,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x19, 0xb3, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+0031 "1" */
    0x33, 0xc9, 0x4, 0x10, 0x41, 0x4, 0x10, 0x4f,
    0xc0,

    /* U+0032 "2" */
    0xf2, 0x30, 0x41, 0x4, 0x21, 0x8c, 0x63, 0xf,
    0xc0,

    /* U+0033 "3" */
    0x7f, 0x3, 0x6, 0xc, 0x18, 0x1e, 0x3, 0x1,
    0x1, 0xc3, 0x7c,

    /* U+0034 "4" */
    0x10, 0x8, 0xc, 0x4, 0x6, 0x23, 0x11, 0x9,
    0xff, 0x2, 0x1, 0x0, 0x80,

    /* U+0035 "5" */
    0x7c, 0x81, 0x6, 0xf, 0x80, 0x80, 0x81, 0x3,
    0xb, 0xe0,

    /* U+0036 "6" */
    0x18, 0x60, 0x82, 0xf, 0x98, 0xa0, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+0037 "7" */
    0xff, 0x86, 0x86, 0x4, 0xc, 0x8, 0x18, 0x10,
    0x30, 0x20, 0x60,

    /* U+0038 "8" */
    0x3c, 0x42, 0x42, 0x42, 0x24, 0x3c, 0xc2, 0x81,
    0x81, 0xc3, 0x7e,

    /* U+0039 "9" */
    0x38, 0x8a, 0xc, 0x18, 0x38, 0xcf, 0x82, 0x8,
    0x30, 0xc0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0x60,

    /* U+003C "<" */
    0x3, 0x1e, 0xe0, 0xe0, 0x3e, 0x3,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0xc0, 0x78, 0xf, 0x7, 0x78, 0xc0,

    /* U+003F "?" */
    0xfa, 0x30, 0x41, 0x8, 0x42, 0x8, 0x1, 0x86,
    0x0,

    /* U+0040 "@" */
    0x1f, 0x6, 0x19, 0x1, 0x47, 0x99, 0x13, 0x22,
    0x64, 0x4c, 0x76, 0x40, 0x4, 0x0, 0x7c, 0x0,

    /* U+0041 "A" */
    0xc, 0x3, 0x1, 0xe0, 0x48, 0x12, 0xc, 0xc2,
    0x11, 0xfe, 0x40, 0x90, 0x2c, 0xc,

    /* U+0042 "B" */
    0xfc, 0x86, 0x82, 0x82, 0x86, 0xfc, 0x82, 0x81,
    0x81, 0x83, 0xfe,

    /* U+0043 "C" */
    0x1f, 0x61, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x40, 0x61, 0x3f,

    /* U+0044 "D" */
    0xfc, 0x41, 0xa0, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x81, 0x41, 0xbf, 0x0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0x83, 0xf8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0x83, 0xf8, 0x20, 0x82, 0x8,
    0x0,

    /* U+0047 "G" */
    0x1f, 0x30, 0x50, 0x10, 0x8, 0x4, 0x3e, 0x3,
    0x1, 0x40, 0xb0, 0x47, 0xe0,

    /* U+0048 "H" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xf, 0xfe, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x20,

    /* U+0049 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x21, 0x3e,

    /* U+004A "J" */
    0x78, 0x42, 0x10, 0x84, 0x21, 0x8, 0xfc,

    /* U+004B "K" */
    0x86, 0x84, 0x8c, 0x98, 0xb0, 0xf0, 0x90, 0x98,
    0x8c, 0x86, 0x82,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+004D "M" */
    0xc0, 0x7c, 0x1e, 0x82, 0xd0, 0x5b, 0x1b, 0x22,
    0x66, 0xcc, 0xd9, 0x8a, 0x31, 0xc6, 0x10, 0x80,

    /* U+004E "N" */
    0xc0, 0xe0, 0x78, 0x36, 0x19, 0x8c, 0x46, 0x33,
    0xd, 0x83, 0xc0, 0xe0, 0x60,

    /* U+004F "O" */
    0x1e, 0x18, 0x64, 0xa, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x40, 0x98, 0x61, 0xe0,

    /* U+0050 "P" */
    0xf9, 0xa, 0xc, 0x18, 0x30, 0xbe, 0x40, 0x81,
    0x2, 0x0,

    /* U+0051 "Q" */
    0x1e, 0x18, 0x64, 0xa, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x40, 0x98, 0x61, 0xe0, 0x18, 0x3,
    0x0,

    /* U+0052 "R" */
    0xf8, 0x84, 0x82, 0x82, 0x82, 0x84, 0xf8, 0x98,
    0x8c, 0x84, 0x82,

    /* U+0053 "S" */
    0x7d, 0x82, 0x4, 0x6, 0x7, 0x3, 0x81, 0x3,
    0xf, 0xf0,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40,

    /* U+0055 "U" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xa0, 0x8f, 0x80,

    /* U+0056 "V" */
    0x40, 0xd0, 0x26, 0x8, 0x86, 0x21, 0xc, 0x41,
    0x30, 0x48, 0xa, 0x3, 0x0, 0xc0,

    /* U+0057 "W" */
    0xc3, 0x5, 0xc, 0x34, 0x38, 0xd1, 0xa2, 0x64,
    0x88, 0x92, 0x62, 0x4d, 0x8b, 0x14, 0x38, 0x50,
    0x61, 0x41, 0x82, 0x0,

    /* U+0058 "X" */
    0x41, 0xb0, 0x88, 0xc6, 0xc1, 0x40, 0x60, 0x50,
    0x64, 0x23, 0x30, 0xb0, 0x60,

    /* U+0059 "Y" */
    0x41, 0x31, 0x88, 0x86, 0xc1, 0x40, 0xa0, 0x20,
    0x10, 0x8, 0x4, 0x2, 0x0,

    /* U+005A "Z" */
    0xff, 0x3, 0x6, 0xc, 0xc, 0x18, 0x30, 0x30,
    0x60, 0xc0, 0xff,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0xc0,

    /* U+005C "\\" */
    0xc1, 0x6, 0x8, 0x20, 0xc1, 0x6, 0x8, 0x20,
    0xc0,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x93, 0xc0,

    /* U+005E "^" */
    0x30, 0xc5, 0x92, 0xcc,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xc9, 0x80,

    /* U+0061 "a" */
    0x7c, 0xc, 0xb, 0xfc, 0x30, 0x61, 0xbd,

    /* U+0062 "b" */
    0x81, 0x2, 0x5, 0xcc, 0x50, 0x60, 0xc1, 0x83,
    0x8a, 0xe0,

    /* U+0063 "c" */
    0x3d, 0x8, 0x20, 0x82, 0x4, 0xf,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xd4, 0x70, 0x60, 0xc1, 0x82,
    0x84, 0xf8,

    /* U+0065 "e" */
    0x3c, 0x8e, 0xf, 0xf8, 0x10, 0x10, 0x9f,

    /* U+0066 "f" */
    0x3a, 0x11, 0xf4, 0x21, 0x8, 0x42, 0x10,

    /* U+0067 "g" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x50, 0x9f, 0x2,
    0xd, 0xe0,

    /* U+0068 "h" */
    0x81, 0x2, 0x5, 0xec, 0x70, 0x60, 0xc1, 0x83,
    0x6, 0x8,

    /* U+0069 "i" */
    0x6c, 0x72, 0x49, 0x24, 0x80,

    /* U+006A "j" */
    0x33, 0xf, 0x11, 0x11, 0x11, 0x11, 0x1e,

    /* U+006B "k" */
    0x81, 0x2, 0x4, 0x68, 0x92, 0x3c, 0x48, 0x99,
    0x1a, 0x18,

    /* U+006C "l" */
    0x92, 0x49, 0x24, 0x93, 0x80,

    /* U+006D "m" */
    0xb9, 0xd8, 0xc6, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xc, 0x21,

    /* U+006E "n" */
    0xbd, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xc1,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xb9, 0x8a, 0xc, 0x18, 0x30, 0x71, 0x5c, 0x81,
    0x2, 0x0,

    /* U+0071 "q" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x50, 0x9f, 0x2,
    0x4, 0x8,

    /* U+0072 "r" */
    0xbe, 0x21, 0x8, 0x42, 0x10,

    /* U+0073 "s" */
    0x7e, 0x18, 0x1c, 0x1c, 0x18, 0x7e,

    /* U+0074 "t" */
    0x42, 0x3e, 0x84, 0x21, 0x8, 0x41, 0xc0,

    /* U+0075 "u" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x61, 0xbd,

    /* U+0076 "v" */
    0x43, 0x42, 0x62, 0x26, 0x24, 0x34, 0x1c, 0x18,

    /* U+0077 "w" */
    0x46, 0x14, 0x73, 0x65, 0x36, 0x52, 0x29, 0xa2,
    0x8e, 0x38, 0xc1, 0x8c,

    /* U+0078 "x" */
    0x42, 0x26, 0x34, 0x18, 0x18, 0x34, 0x66, 0x43,

    /* U+0079 "y" */
    0xc3, 0x42, 0x46, 0x64, 0x24, 0x3c, 0x18, 0x18,
    0x10, 0x10, 0x60,

    /* U+007A "z" */
    0xfc, 0x31, 0x84, 0x21, 0x8c, 0x3f,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x11, 0x98, 0x21, 0x8, 0x42,
    0xc,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0xc3, 0x21, 0x8, 0x42,
    0x60,

    /* U+007E "~" */
    0xe6, 0x70,

    /* U+00C0 "À" */
    0x18, 0x2, 0x0, 0x40, 0x30, 0xc, 0x7, 0x81,
    0x20, 0x48, 0x33, 0x8, 0x47, 0xf9, 0x2, 0x40,
    0xb0, 0x30,

    /* U+00C1 "Á" */
    0x6, 0x3, 0x0, 0x80, 0x30, 0xc, 0x7, 0x81,
    0x20, 0x48, 0x33, 0x8, 0x47, 0xf9, 0x2, 0x40,
    0xb0, 0x30,

    /* U+00C2 "Â" */
    0xe, 0x2, 0x81, 0x10, 0x10, 0xa, 0x2, 0x81,
    0xa0, 0x4c, 0x31, 0x8, 0x43, 0xf9, 0x82, 0x40,
    0xb0, 0x30,

    /* U+00C3 "Ã" */
    0x39, 0x9, 0xc0, 0x0, 0x30, 0xc, 0x7, 0x81,
    0x20, 0x48, 0x33, 0x8, 0x47, 0xf9, 0x2, 0x40,
    0xb0, 0x30,

    /* U+00C4 "Ä" */
    0x12, 0x0, 0x0, 0xc0, 0x78, 0x1e, 0x4, 0x83,
    0x30, 0xc4, 0x21, 0x1f, 0xe4, 0x9, 0x2, 0xc0,
    0xc0,

    /* U+00C5 "Å" */
    0x1c, 0x5, 0x1, 0x40, 0x70, 0x1c, 0x5, 0x1,
    0x60, 0xc8, 0x23, 0x8, 0xc7, 0xf1, 0x6, 0x40,
    0xb0, 0x30,

    /* U+00C6 "Æ" */
    0x3, 0xf8, 0x18, 0x1, 0x40, 0x1a, 0x0, 0x90,
    0x8, 0xf8, 0xc4, 0x7, 0xe0, 0x61, 0x2, 0x8,
    0x30, 0x7e,

    /* U+00C7 "Ç" */
    0x1f, 0x61, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x40, 0x61, 0x3f, 0xc, 0x2, 0x1e,

    /* U+00C8 "È" */
    0x30, 0x30, 0x27, 0xf8, 0x10, 0x20, 0x40, 0xfd,
    0x2, 0x4, 0x8, 0x1f, 0xc0,

    /* U+00C9 "É" */
    0x18, 0xc2, 0x3f, 0x82, 0x8, 0x20, 0xfe, 0x8,
    0x20, 0x83, 0xf0,

    /* U+00CA "Ê" */
    0x30, 0xd0, 0x17, 0xf8, 0x10, 0x20, 0x40, 0xfd,
    0x2, 0x4, 0x8, 0x1f, 0xc0,

    /* U+00CB "Ë" */
    0x48, 0xf, 0xe0, 0x82, 0x8, 0x3e, 0x82, 0x8,
    0x20, 0xfc,

    /* U+00CC "Ì" */
    0x46, 0x3f, 0x44, 0x44, 0x44, 0x44, 0x4f,

    /* U+00CD "Í" */
    0x31, 0x19, 0xf2, 0x10, 0x84, 0x21, 0x8, 0x42,
    0x7c,

    /* U+00CE "Î" */
    0x72, 0xa3, 0xf2, 0x10, 0x84, 0x21, 0x8, 0x42,
    0x7c,

    /* U+00CF "Ï" */
    0x88, 0x3e, 0x42, 0x10, 0x84, 0x21, 0x8, 0x4f,
    0x80,

    /* U+00D2 "Ò" */
    0xc, 0x1, 0x80, 0x0, 0x78, 0x61, 0x90, 0x28,
    0x6, 0x1, 0x80, 0x60, 0x18, 0x5, 0x2, 0x61,
    0x87, 0x80,

    /* U+00D3 "Ó" */
    0x6, 0x3, 0x0, 0x0, 0x78, 0x61, 0x90, 0x28,
    0x6, 0x1, 0x80, 0x60, 0x18, 0x5, 0x2, 0x61,
    0x87, 0x80,

    /* U+00D4 "Ô" */
    0xe, 0x6, 0xc0, 0x0, 0x78, 0x61, 0x90, 0x28,
    0x6, 0x1, 0x80, 0x60, 0x18, 0x5, 0x2, 0x61,
    0x87, 0x80,

    /* U+00D5 "Õ" */
    0x39, 0x9, 0xc0, 0x0, 0x78, 0x61, 0x90, 0x28,
    0x6, 0x1, 0x80, 0x60, 0x18, 0x5, 0x2, 0x61,
    0x87, 0x80,

    /* U+00D6 "Ö" */
    0x12, 0x0, 0x1, 0xe1, 0x86, 0x40, 0xa0, 0x18,
    0x6, 0x1, 0x80, 0x60, 0x14, 0x9, 0x86, 0x1e,
    0x0,

    /* U+00D7 "×" */
    0x1, 0x89, 0xa1, 0x83, 0x88, 0x80, 0x0,

    /* U+00D8 "Ø" */
    0x1e, 0x58, 0x64, 0x1a, 0x9, 0x84, 0x61, 0x18,
    0x86, 0x41, 0x60, 0x98, 0x69, 0xe0,

    /* U+00D9 "Ù" */
    0x18, 0x6, 0x0, 0x10, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x11, 0xf0,

    /* U+00DA "Ú" */
    0xc, 0xc, 0x0, 0x10, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x11, 0xf0,

    /* U+00DB "Û" */
    0x1c, 0x1b, 0x0, 0x10, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x11, 0xf0,

    /* U+00DC "Ü" */
    0x22, 0x0, 0x20, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x28, 0x23, 0xe0,

    /* U+00E0 "à" */
    0x38, 0x10, 0x3, 0xe0, 0x60, 0x5f, 0xe1, 0x83,
    0xd, 0xe8,

    /* U+00E1 "á" */
    0x18, 0x20, 0x3, 0xe0, 0x60, 0x5f, 0xe1, 0x83,
    0xd, 0xe8,

    /* U+00E2 "â" */
    0x38, 0xc8, 0x3, 0xe0, 0x60, 0x5f, 0xe1, 0x83,
    0xd, 0xe8,

    /* U+00E3 "ã" */
    0x72, 0x9c, 0x3, 0xe0, 0x60, 0x5f, 0xe1, 0x83,
    0xd, 0xe8,

    /* U+00E4 "ä" */
    0x24, 0x0, 0x3, 0xe0, 0x20, 0x5f, 0xe1, 0xc3,
    0x8d, 0xe8,

    /* U+00E5 "å" */
    0x38, 0x50, 0xe0, 0x7, 0xc0, 0xc0, 0xbf, 0xc3,
    0x6, 0x1b, 0xd0,

    /* U+00E6 "æ" */
    0x79, 0xe0, 0x71, 0x2, 0x17, 0xff, 0x82, 0x8,
    0x20, 0x85, 0x17, 0x8f,

    /* U+00E7 "ç" */
    0x3d, 0x8, 0x20, 0x82, 0x4, 0xf, 0x38, 0x23,
    0x80,

    /* U+00E8 "è" */
    0x30, 0x20, 0x1, 0xe4, 0x70, 0x7f, 0xc0, 0x80,
    0x84, 0xf8,

    /* U+00E9 "é" */
    0xc, 0x30, 0x1, 0xe4, 0x70, 0x7f, 0xc0, 0x80,
    0x84, 0xf8,

    /* U+00EA "ê" */
    0x38, 0xd8, 0x1, 0xe4, 0x70, 0x7f, 0xc0, 0x80,
    0x80, 0xf0,

    /* U+00EB "ë" */
    0x24, 0x0, 0x1, 0xe6, 0x38, 0x7f, 0xe0, 0xc0,
    0xc0, 0xf8,

    /* U+00EC "ì" */
    0x44, 0x72, 0x49, 0x24, 0x80,

    /* U+00ED "í" */
    0x31, 0x1, 0xc2, 0x10, 0x84, 0x21, 0x8,

    /* U+00EE "î" */
    0x36, 0x40, 0xe1, 0x8, 0x42, 0x10, 0x84,

    /* U+00EF "ï" */
    0x88, 0x1, 0xc2, 0x10, 0x84, 0x21, 0x8,

    /* U+00F2 "ò" */
    0x20, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F3 "ó" */
    0x8, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F4 "ô" */
    0x38, 0xd8, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F5 "õ" */
    0x74, 0xb8, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F6 "ö" */
    0x24, 0x0, 0x1, 0xc6, 0x58, 0x70, 0xe1, 0xc2,
    0xc8, 0xe0,

    /* U+00F7 "÷" */
    0x18, 0x0, 0x7, 0xf0, 0x0, 0x6, 0x0,

    /* U+00F8 "ø" */
    0x2, 0x79, 0x34, 0x59, 0x32, 0x68, 0xb2, 0x79,
    0x0,

    /* U+00F9 "ù" */
    0x60, 0x20, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0xd, 0xe8,

    /* U+00FA "ú" */
    0xc, 0x20, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0xd, 0xe8,

    /* U+00FB "û" */
    0x38, 0xd8, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0xd, 0xe8,

    /* U+00FC "ü" */
    0x44, 0x0, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0xd, 0xe8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 67, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 66, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 94, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 144, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 211, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 185, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 53, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 63, .adv_w = 72, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 72, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 75, .adv_w = 114, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 79, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 86, .adv_w = 67, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 87, .adv_w = 97, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 88, .adv_w = 66, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 97, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 154, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 154, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 66, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 67, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 207, .adv_w = 144, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 213, .adv_w = 143, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 217, .adv_w = 144, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 223, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 203, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 248, .adv_w = 165, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 166, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 186, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 145, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 133, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 187, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 195, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 111, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 129, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 146, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 235, .box_w = 11, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 197, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 197, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 153, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 197, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 445, .adv_w = 169, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 148, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 189, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 166, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 230, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 144, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 78, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 566, .adv_w = 97, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 78, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 581, .adv_w = 120, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 585, .adv_w = 116, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 586, .adv_w = 57, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 588, .adv_w = 140, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 153, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 151, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 98, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 645, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 86, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 94, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 667, .adv_w = 142, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 78, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 227, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 152, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 150, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 153, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 717, .adv_w = 151, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 727, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 103, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 150, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 752, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 204, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 772, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 791, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 797, .adv_w = 95, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 806, .adv_w = 122, .box_w = 1, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 808, .adv_w = 98, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 817, .adv_w = 103, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 819, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 855, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 165, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 244, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 944, .adv_w = 155, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 958, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 971, .adv_w = 145, .box_w = 6, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 982, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 995, .adv_w = 145, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1005, .adv_w = 111, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1012, .adv_w = 111, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1021, .adv_w = 111, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1030, .adv_w = 111, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1039, .adv_w = 197, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 197, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1075, .adv_w = 197, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1093, .adv_w = 197, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 197, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1128, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1135, .adv_w = 200, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1149, .adv_w = 189, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1165, .adv_w = 189, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1181, .adv_w = 189, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1197, .adv_w = 189, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1212, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1222, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1232, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1242, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1252, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1262, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1273, .adv_w = 219, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1285, .adv_w = 129, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1294, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1304, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1314, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1324, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1334, .adv_w = 86, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1339, .adv_w = 86, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1346, .adv_w = 86, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1353, .adv_w = 86, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1360, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1370, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1380, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1390, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1400, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1410, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1417, .adv_w = 150, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1426, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1436, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1446, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1456, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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
    },
    {
        .range_start = 192, .range_length = 16, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 210, .range_length = 11, .glyph_id_start = 112,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 224, .range_length = 16, .glyph_id_start = 123,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 242, .range_length = 11, .glyph_id_start = 139,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    2, 2,
    2, 10,
    2, 14,
    2, 15,
    2, 27,
    2, 32,
    2, 62,
    3, 4,
    3, 6,
    3, 7,
    3, 9,
    3, 10,
    3, 11,
    3, 12,
    3, 13,
    3, 14,
    3, 15,
    3, 16,
    3, 27,
    3, 28,
    3, 30,
    3, 32,
    3, 33,
    3, 61,
    3, 62,
    3, 64,
    3, 92,
    3, 95,
    4, 9,
    4, 13,
    4, 15,
    4, 16,
    5, 9,
    5, 12,
    5, 13,
    5, 14,
    5, 15,
    5, 27,
    5, 28,
    5, 30,
    5, 64,
    6, 3,
    6, 8,
    6, 10,
    6, 11,
    6, 14,
    6, 16,
    6, 27,
    6, 28,
    6, 32,
    7, 3,
    7, 8,
    7, 10,
    7, 14,
    8, 4,
    8, 7,
    8, 9,
    8, 10,
    8, 11,
    8, 12,
    8, 13,
    8, 14,
    8, 15,
    8, 16,
    8, 27,
    8, 28,
    8, 30,
    8, 32,
    8, 33,
    8, 61,
    8, 62,
    8, 64,
    8, 92,
    8, 95,
    9, 2,
    9, 3,
    9, 4,
    9, 5,
    9, 7,
    9, 8,
    9, 9,
    9, 10,
    9, 12,
    9, 14,
    9, 15,
    9, 16,
    9, 27,
    9, 29,
    9, 30,
    9, 31,
    9, 32,
    9, 33,
    9, 61,
    9, 62,
    9, 63,
    9, 95,
    9, 117,
    9, 144,
    10, 2,
    10, 3,
    10, 8,
    10, 9,
    10, 10,
    10, 11,
    10, 14,
    10, 16,
    10, 28,
    10, 29,
    10, 30,
    10, 31,
    10, 32,
    10, 62,
    10, 63,
    10, 92,
    11, 8,
    11, 13,
    11, 14,
    11, 15,
    11, 16,
    11, 27,
    11, 28,
    12, 3,
    12, 5,
    12, 8,
    12, 10,
    12, 11,
    12, 12,
    12, 13,
    12, 15,
    12, 16,
    12, 27,
    12, 28,
    12, 30,
    12, 32,
    12, 62,
    12, 94,
    13, 3,
    13, 8,
    13, 11,
    13, 14,
    14, 3,
    14, 8,
    14, 9,
    14, 10,
    14, 11,
    14, 13,
    14, 14,
    14, 15,
    14, 16,
    14, 27,
    14, 28,
    14, 92,
    15, 2,
    15, 3,
    15, 8,
    15, 10,
    15, 11,
    15, 14,
    15, 15,
    15, 16,
    15, 27,
    15, 32,
    15, 62,
    15, 94,
    16, 3,
    16, 4,
    16, 8,
    16, 9,
    16, 10,
    16, 11,
    16, 12,
    16, 13,
    16, 14,
    16, 15,
    16, 16,
    16, 27,
    16, 30,
    16, 31,
    16, 32,
    16, 61,
    16, 62,
    16, 63,
    16, 64,
    27, 3,
    27, 8,
    27, 10,
    27, 11,
    27, 62,
    28, 3,
    28, 8,
    28, 11,
    28, 14,
    29, 9,
    29, 14,
    29, 29,
    30, 3,
    30, 5,
    30, 8,
    30, 9,
    30, 10,
    30, 12,
    30, 13,
    30, 14,
    30, 15,
    30, 30,
    31, 9,
    31, 10,
    31, 14,
    31, 31,
    32, 2,
    32, 3,
    32, 8,
    32, 9,
    32, 10,
    32, 11,
    32, 13,
    32, 14,
    32, 15,
    32, 16,
    32, 32,
    32, 62,
    33, 3,
    33, 8,
    33, 10,
    33, 14,
    33, 64,
    60, 2,
    60, 3,
    60, 4,
    60, 8,
    60, 9,
    60, 10,
    60, 12,
    60, 15,
    60, 16,
    60, 27,
    60, 30,
    60, 32,
    60, 62,
    60, 63,
    60, 94,
    61, 3,
    61, 8,
    61, 11,
    61, 62,
    63, 9,
    63, 10,
    63, 11,
    63, 13,
    63, 15,
    63, 16,
    63, 28,
    63, 62,
    64, 3,
    64, 8,
    64, 9,
    64, 10,
    64, 11,
    64, 15,
    64, 27,
    64, 28,
    64, 62,
    64, 64,
    92, 12,
    92, 15,
    92, 32,
    92, 62,
    92, 63,
    92, 94,
    94, 3,
    94, 8,
    94, 9,
    94, 10,
    94, 12,
    94, 13,
    94, 14,
    94, 15,
    94, 92,
    94, 94,
    95, 2,
    95, 3,
    95, 9,
    95, 10,
    95, 13,
    95, 14,
    95, 15,
    95, 16,
    95, 27,
    95, 28,
    95, 32,
    117, 10,
    144, 10
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    2, 5, 4, -2, -2, 4, 2, -9,
    3, -11, 1, 4, -1, -15, -34, -13,
    -33, -19, -9, -10, -7, 7, -12, 9,
    1, -47, -12, -15, 7, -12, -16, -8,
    5, -14, -4, 6, -5, -10, -8, -6,
    -24, -17, -17, -5, -18, 8, 2, -5,
    -4, -4, -18, -18, -9, 7, -9, -11,
    1, 4, -1, -15, -27, -13, -27, -19,
    -9, -10, -7, 7, -12, 9, 1, -27,
    -12, -15, 5, 4, -6, -1, -3, 4,
    3, 10, -13, -3, -2, 3, -5, -11,
    -9, -5, 11, -3, 10, 11, -8, -10,
    -9, -14, 6, 1, 1, 17, 3, 1,
    15, 6, 2, 2, 3, 3, 8, 4,
    1, 16, -2, -34, -6, -33, -18, -7,
    -7, -15, -13, -15, -13, -10, -5, -34,
    -33, -14, -11, -12, -9, -16, -11, -16,
    -34, -27, -34, -8, -13, -13, 15, -3,
    -6, -8, -5, -8, 3, -1, -2, 15,
    -2, -33, -27, -2, -33, -8, -8, 4,
    -2, -7, -3, -5, 9, -8, 9, 1,
    10, 4, -14, -24, -6, -24, -21, -11,
    -7, -3, 10, 12, 6, -6, -39, -9,
    -9, -5, -6, -4, -10, -10, -7, -2,
    3, 8, -7, -7, -4, -7, 3, -9,
    -9, -18, 8, -18, 1, 2, -11, 6,
    -7, 4, 8, 8, 8, 4, 7, -22,
    -2, -23, -14, 7, 2, -9, -9, -5,
    12, -29, 2, 1, -3, 1, 4, 11,
    -11, -3, 4, -4, -8, 6, 14, -8,
    8, -19, -19, -18, 4, 1, -9, -2,
    -34, -33, -17, -7, -8, -47, -27, -9,
    6, -57, -6, -11, -3, 6, 13, -15,
    -4, 7, 10, -9, 7, -8, -8, 10,
    -3, -3, -10, 12, -10, 13, -7, -1,
    -8, 8, -9, -34, 9, -33, -12, -6,
    -7, -15, -9, -14
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 292,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 5,
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
const lv_font_t ui_arone16 = {
#else
lv_font_t ui_arone16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_ARONE16*/

