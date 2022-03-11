#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif
#ifndef LV_ATTRIBUTE_IMG_PROJECT_LINK
#define LV_ATTRIBUTE_IMG_PROJECT_LINK
#endif
const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_PROJECT_LINK uint8_t project_link_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x7f, 0xff, 0x0c, 0x01, 0x80, 0x00, 0xff, 0xfe, 
  0x7f, 0xff, 0x0c, 0x01, 0x80, 0x00, 0xff, 0xfe, 
  0x60, 0x03, 0x3f, 0x00, 0x01, 0x8c, 0xc0, 0x06, 
  0x60, 0x03, 0x3f, 0x00, 0x01, 0x8c, 0xc0, 0x06, 
  0x67, 0xe3, 0x33, 0xf1, 0x80, 0x0c, 0xcf, 0xc6, 
  0x67, 0xe3, 0x33, 0xf1, 0x80, 0x0c, 0xcf, 0xc6, 
  0x67, 0xe3, 0x30, 0x7e, 0x1e, 0x00, 0xcf, 0xc6, 
  0x67, 0xe3, 0x30, 0x7e, 0x1e, 0x00, 0xcf, 0xc6, 
  0x67, 0xe3, 0x30, 0x7e, 0x1e, 0x00, 0xcf, 0xc6, 
  0x67, 0xe3, 0x0f, 0xf1, 0x98, 0x3c, 0xcf, 0xc6, 
  0x67, 0xe3, 0x0f, 0xf1, 0x98, 0x3c, 0xcf, 0xc6, 
  0x60, 0x03, 0x03, 0x1e, 0x18, 0x0c, 0xc0, 0x06, 
  0x60, 0x03, 0x03, 0x1e, 0x18, 0x0c, 0xc0, 0x06, 
  0x7f, 0xff, 0x33, 0x11, 0x99, 0x8c, 0xff, 0xfe, 
  0x7f, 0xff, 0x33, 0x11, 0x99, 0x8c, 0xff, 0xfe, 
  0x00, 0x00, 0x3f, 0x01, 0xf8, 0x3c, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0x01, 0xf8, 0x3c, 0x00, 0x00, 
  0x60, 0x03, 0x3f, 0xff, 0x9e, 0x23, 0xc3, 0xf0, 
  0x60, 0x03, 0x3f, 0xff, 0x9e, 0x23, 0xc3, 0xf0, 
  0x07, 0xe0, 0xf3, 0xc7, 0x87, 0xe3, 0x3c, 0x70, 
  0x07, 0xe0, 0xf3, 0xc7, 0x87, 0xe3, 0x3c, 0x70, 
  0x78, 0x0f, 0x00, 0x00, 0x79, 0x8c, 0x0c, 0x00, 
  0x78, 0x0f, 0x00, 0x00, 0x79, 0x8c, 0x0c, 0x00, 
  0x78, 0x0f, 0x00, 0x00, 0x79, 0x8c, 0x0c, 0x00, 
  0x67, 0x8c, 0x3f, 0xc0, 0x01, 0x8f, 0x03, 0x00, 
  0x67, 0x8c, 0x3f, 0xc0, 0x01, 0x8f, 0x03, 0x00, 
  0x78, 0x03, 0x30, 0x00, 0x18, 0x0c, 0xf0, 0x06, 
  0x78, 0x03, 0x30, 0x00, 0x18, 0x0c, 0xf0, 0x06, 
  0x78, 0x3c, 0x3f, 0xf0, 0x78, 0x3c, 0xfc, 0x1e, 
  0x78, 0x3c, 0x3f, 0xf0, 0x78, 0x3c, 0xfc, 0x1e, 
  0x7e, 0x3f, 0x3c, 0x11, 0xf8, 0x0f, 0x0f, 0xc0, 
  0x7e, 0x3f, 0x3c, 0x11, 0xf8, 0x0f, 0x0f, 0xc0, 
  0x01, 0xe0, 0xf3, 0xf0, 0x00, 0x20, 0x3c, 0x46, 
  0x01, 0xe0, 0xf3, 0xf0, 0x00, 0x20, 0x3c, 0x46, 
  0x60, 0x23, 0x33, 0x10, 0x66, 0x23, 0x33, 0xc0, 
  0x60, 0x23, 0x33, 0x10, 0x66, 0x23, 0x33, 0xc0, 
  0x78, 0x20, 0xf3, 0x06, 0x79, 0xe0, 0xfc, 0x7e, 
  0x78, 0x20, 0xf3, 0x06, 0x79, 0xe0, 0xfc, 0x7e, 
  0x7f, 0xe3, 0x3f, 0x00, 0x67, 0xe0, 0x0f, 0x06, 
  0x7f, 0xe3, 0x3f, 0x00, 0x67, 0xe0, 0x0f, 0x06, 
  0x7f, 0xe3, 0x3f, 0x00, 0x67, 0xe0, 0x0f, 0x06, 
  0x67, 0xe0, 0xcc, 0x06, 0x78, 0x0c, 0xc0, 0x00, 
  0x67, 0xe0, 0xcc, 0x06, 0x78, 0x0c, 0xc0, 0x00, 
  0x60, 0x03, 0x0c, 0x11, 0xff, 0xff, 0xfc, 0x7e, 
  0x60, 0x03, 0x0c, 0x11, 0xff, 0xff, 0xfc, 0x7e, 
  0x00, 0x00, 0x33, 0xc1, 0xe7, 0x8c, 0x0f, 0x00, 
  0x00, 0x00, 0x33, 0xc1, 0xe7, 0x8c, 0x0f, 0x00, 
  0x7f, 0xff, 0x00, 0x70, 0x7e, 0x3c, 0xcf, 0xc0, 
  0x7f, 0xff, 0x00, 0x70, 0x7e, 0x3c, 0xcf, 0xc0, 
  0x60, 0x03, 0x03, 0xf1, 0x80, 0x3c, 0x0c, 0x00, 
  0x60, 0x03, 0x03, 0xf1, 0x80, 0x3c, 0x0c, 0x00, 
  0x67, 0xe3, 0x00, 0x47, 0x98, 0x3f, 0xff, 0x10, 
  0x67, 0xe3, 0x00, 0x47, 0x98, 0x3f, 0xff, 0x10, 
  0x67, 0xe3, 0x00, 0x41, 0xf8, 0x3f, 0x03, 0xc6, 
  0x67, 0xe3, 0x00, 0x41, 0xf8, 0x3f, 0x03, 0xc6, 
  0x67, 0xe3, 0x00, 0x41, 0xf8, 0x3f, 0x03, 0xc6, 
  0x67, 0xe3, 0x03, 0x07, 0xfe, 0x3f, 0xff, 0xf0, 
  0x67, 0xe3, 0x03, 0x07, 0xfe, 0x3f, 0xff, 0xf0, 
  0x60, 0x03, 0x0f, 0xc0, 0x00, 0x00, 0xf3, 0xc6, 
  0x60, 0x03, 0x0f, 0xc0, 0x00, 0x00, 0xf3, 0xc6, 
  0x7f, 0xff, 0x33, 0xc0, 0x66, 0x20, 0xfc, 0x40, 
  0x7f, 0xff, 0x33, 0xc0, 0x66, 0x20, 0xfc, 0x40, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t project_link = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 64,
  .header.h = 64,
  .data_size = 521,
  .data = project_link_map,
};