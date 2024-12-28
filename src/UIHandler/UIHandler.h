#ifndef UI_HANDLER_H
#define UI_HANDLER_H

#include "Arduino.h"
#include "LCD\lgfx_gc9a01.hpp"
#include "ui\ui.h"
#include <lv_demo.h>
#include <lvgl.h>
#include <string.h>


/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][ screenWidth * 10 ];
static LGFX_GC9A01 gfx;


void UIHandlerInit(void);
void UIHandlerCyclic(void);
static void my_disp_flush(lv_disp_drv_t*, const lv_area_t*, lv_color_t*);
static void my_touchpad_read(lv_indev_drv_t*, lv_indev_data_t*);


#endif