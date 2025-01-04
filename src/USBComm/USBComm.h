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
        void ResetButtons(void);
        static uint16_t get_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
        static void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize); 
    public:
        void Init(void);
        void Cyclic(void);
    private:
        // HID report descriptor using TinyUSB's template
        // Single Report (no ID) descriptor
        

        // Report payload defined in src/class/hid/hid.h
        // - For Gamepad Button Bit Mask see  hid_gamepad_button_bm_t
        // - For Gamepad Hat    Bit Mask see  hid_gamepad_hat_t
        hid_gamepad_report_t gp;
    public:

};


#endif