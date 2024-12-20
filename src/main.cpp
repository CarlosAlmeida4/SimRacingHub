#include "Arduino.h"
#include "LCD\lgfx_gc9a01.hpp"
#include "Joystick\Joystick.h"
#include "ui\ui.h"
#include <lv_demo.h>
#include <lvgl.h>
#include <string.h>

/*Change to your screen resolution*/
static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][screenWidth * 10];

static LGFX_GC9A01 gfx;
/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  if (gfx.getStartCount() == 0)
  { // Processing if not yet started
    gfx.startWrite();
  }
  gfx.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);
  lv_disp_flush_ready(disp);
}

void sd_access_sample(void)
{
  if (gfx.getStartCount() > 0)
  { // Free the bus before accessing the SD card
    gfx.endWrite();
  }

  // Something to manipulate the SD card.
  // auto file = SD.open("/file");
  // file.close();
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;

  data->state = LV_INDEV_STATE_REL;

  if (gfx.getTouch(&touchX, &touchY))
  {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

void setup()
{
  //Serial.println("Use BOOTSEL to start the Joystick demo.");
  Joystick.begin();
}

void loop()
{
    if (BOOTSEL) {
	Serial.println("Joystick buttons");
    for(uint8_t i = 1; i<=32; i++)
    {
		Joystick.button(i,true);
		delay(250);
		Joystick.button(i,false);
		delay(10); //we need a short delay here, sending packets with less than 1ms leads to packet loss!
	}
	//alternativ with manual send:
	Joystick.useManualSend(true);
	Serial.println("Joystick buttons - manual send");
    for(uint8_t i = 1; i<=32; i++)
    {
		Joystick.button(i,true);
		Joystick.send_now();
		delay(250);
		Joystick.button(i,false);
	}
	Joystick.useManualSend(false);
	
    //iterate all joystick axis
    //Note: although you can use 0-1023 here (10bit), internally 8bits are used (-127 to 127)
    Serial.println("Joystick X");
    for(uint16_t i = 0; i<1023; i++) { Joystick.X(i); delay(2); } Joystick.X(512);
    Serial.println("Joystick Y");
    for(uint16_t i = 0; i<1023; i++) { Joystick.Y(i); delay(2); } Joystick.Y(512);
    Serial.println("Joystick Z");
    for(uint16_t i = 0; i<1023; i++) { Joystick.Z(i); delay(2); } Joystick.Z(512);
    Serial.println("Joystick Zrotate");
    for(uint16_t i = 0; i<1023; i++) { Joystick.Zrotate(i); delay(2); } Joystick.Zrotate(512);
    Serial.println("Joystick sliderLeft");
    for(uint16_t i = 0; i<1023; i++) { Joystick.sliderLeft(i); delay(2); } Joystick.sliderLeft(0);
    Serial.println("Joystick sliderRight");
    for(uint16_t i = 0; i<1023; i++) { Joystick.sliderRight(i); delay(2); } Joystick.sliderRight(0);
    Serial.println("Joystick hat");
    for(uint16_t i = 0; i<360; i++) { Joystick.hat(i); delay(20); } Joystick.hat(-1);
    
    //use int8 mode for the axis.
    //Note: hat is not used differently.
    Serial.println("Now all axis in 8bit mode, -127 to 127");
    Joystick.use8bit(true);
    Serial.println("Joystick X");
    for(int16_t i = -127; i<128; i++) { Joystick.X(i); delay(2); } Joystick.X(0);
    Serial.println("Joystick Y");
    for(int16_t i = -127; i<128; i++) { Joystick.Y(i); delay(2); } Joystick.Y(0);
    Serial.println("Joystick Z");
    for(int16_t i = -127; i<128; i++) { Joystick.Z(i); delay(2); } Joystick.Z(0);
    Serial.println("Joystick Zrotate");
    for(int16_t i = -127; i<128; i++) { Joystick.Zrotate(i); delay(2); } Joystick.Zrotate(0);
    Serial.println("Joystick sliderLeft");
    for(int16_t i = -127; i<128; i++) { Joystick.sliderLeft(i); delay(2); } Joystick.sliderLeft(0);
    Serial.println("Joystick sliderRight");
    for(int16_t i = -127; i<128; i++) { Joystick.sliderRight(i); delay(2); } Joystick.sliderRight(0);
    Joystick.use8bit(false);
  }
}