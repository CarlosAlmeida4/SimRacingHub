#ifndef USB_COMM_H
#define USB_COMM_H

#include "Arduino.h"
#include <Adafruit_TinyUSB.h>
#include <string.h>


// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_GAMEPAD()
};


class USBComm
{
    private:

    public:
        void Init(void);
        void Cyclic(void);
    private:
        // HID report descriptor using TinyUSB's template
        // Single Report (no ID) descriptor
        
        // USB HID object
        Adafruit_USBD_HID usb_hid;
        // Report payload defined in src/class/hid/hid.h
        // - For Gamepad Button Bit Mask see  hid_gamepad_button_bm_t
        // - For Gamepad Hat    Bit Mask see  hid_gamepad_hat_t
        hid_gamepad_report_t gp;
    public:

};


#endif