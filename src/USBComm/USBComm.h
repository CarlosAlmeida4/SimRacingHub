#ifndef USB_COMM_H
#define USB_COMM_H

#include "Arduino.h"
#include <Adafruit_TinyUSB.h>
#include <string.h>

// USB HID object
extern hid_gamepad_report_t gp;


uint16_t USBCommGet_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
void USBCommSet_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize); 

void USBCommInit(void);
void USBCommCyclic(void);
void USBCommResetButtons(void);
void USBCommSetButtonReport(uint32_t button);
void USBCommResetButtonReport(uint32_t button);

#endif