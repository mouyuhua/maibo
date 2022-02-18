/*******************************************************************************
 * Size: 18 px
 * Bpp: 4
 * Opts: --no-compress --format lvgl --font C:\Users\yuhuahua\Desktop\iconfont.ttf -o C:\Users\yuhuahua\Desktop\iconfont_18.c --bpp 4 --size 18 -r 0xe628,0xe89b
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef ICONFONT_18
#define ICONFONT_18 1
#endif

#if ICONFONT_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E628 "" */
    0x0, 0x0, 0x69, 0x50, 0x0, 0x0, 0x0, 0xa,
    0xd8, 0xd8, 0x9, 0xfa, 0x0, 0x2f, 0x0, 0x2f,
    0x0, 0x10, 0x0, 0x4d, 0x0, 0xf, 0x18, 0xd9,
    0x0, 0x4d, 0x0, 0xf, 0x11, 0x21, 0x0, 0x17,
    0x0, 0x8, 0x8, 0xc8, 0x0, 0x44, 0x0, 0x7,
    0x2, 0x42, 0x6, 0xe4, 0x0, 0xb, 0xd0, 0x0,
    0x3f, 0x30, 0x0, 0x0, 0xaa, 0x0, 0x99, 0xa,
    0x10, 0x38, 0x1f, 0x10, 0xc5, 0x9, 0x10, 0x38,
    0xd, 0x30, 0xc5, 0x0, 0x51, 0x40, 0xd, 0x30,
    0x99, 0x1, 0xef, 0x80, 0x1f, 0x10, 0x2f, 0x30,
    0x1, 0x0, 0xb9, 0x0, 0x6, 0xe6, 0x10, 0x3b,
    0xd0, 0x0, 0x0, 0x4c, 0xff, 0xe8, 0x0, 0x0,
    0x0, 0x0, 0x1, 0x0, 0x0, 0x0,

    /* U+E89B "" */
    0x0, 0x1, 0xac, 0x80, 0x0, 0x0, 0x0, 0xda,
    0x5b, 0xa0, 0x0, 0x0, 0x3e, 0x0, 0x1f, 0x0,
    0x0, 0x4, 0xd0, 0x0, 0xf1, 0x0, 0x0, 0x4d,
    0x0, 0xf, 0x10, 0x0, 0x2, 0x80, 0x0, 0x90,
    0x0, 0x0, 0x44, 0x0, 0x7, 0x0, 0x0, 0x6e,
    0x40, 0x0, 0xbd, 0x0, 0x3f, 0x30, 0x0, 0x0,
    0xaa, 0x9, 0x90, 0xa1, 0x3, 0x81, 0xf1, 0xc5,
    0x9, 0x10, 0x38, 0xd, 0x3c, 0x50, 0x5, 0x14,
    0x0, 0xd3, 0x99, 0x1, 0xef, 0x80, 0x1f, 0x12,
    0xf3, 0x0, 0x10, 0xb, 0x90, 0x6, 0xe6, 0x10,
    0x3b, 0xd0, 0x0, 0x4, 0xcf, 0xfe, 0x80, 0x0,
    0x0, 0x0, 0x1, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 288, .box_w = 12, .box_h = 17, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 102, .adv_w = 288, .box_w = 11, .box_h = 17, .ofs_x = 3, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static uint16_t unicode_list_0[] = {
    0x0, 0x273
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58920, .range_length = 628, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    .bpp = 4,
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
const lv_font_t iconfont_18 = {
#else
lv_font_t iconfont_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ICONFONT_18*/

