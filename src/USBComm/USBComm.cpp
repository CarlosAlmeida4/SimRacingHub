#include "USBComm\USBComm.h"
#include "Arduino.h"
#include <Adafruit_TinyUSB.h>
#include <string.h>

// Report ID
enum
{
  RID_GAMEPAD = 1,
  RID_GENERIC,
};

hid_gamepad_report_t gp;
// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_GAMEPAD(HID_REPORT_ID(RID_GAMEPAD)),
  TUD_HID_REPORT_DESC_GENERIC_INOUT(64,HID_REPORT_ID(RID_GENERIC))  
};
// USB HID object
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, true);


// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t USBCommGet_report_callback (uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // not used in this example
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;
  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void USBCommSet_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  // This example doesn't use multiple report and report ID
  (void) report_id;
  (void) report_type;
  Serial.print("Called Set Report Callback: ");
  Serial.println(report_id);
  // echo back anything we received from host
  usb_hid.sendReport(RID_GENERIC, buffer, bufsize);
}

void USBCommInit()
{
    // Manual begin() is required on core without built-in support e.g. mbed rp2040
    if (!TinyUSBDevice.isInitialized()) {
      TinyUSBDevice.begin(0);
    }   
    // Setup HID
    usb_hid.setPollInterval(2);
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.setReportCallback(USBCommGet_report_callback,USBCommSet_report_callback);
    usb_hid.begin();    
    // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
    if (TinyUSBDevice.mounted()) {
      TinyUSBDevice.detach();
      delay(10);
      TinyUSBDevice.attach();
    }

}

void USBCommCyclic()
{
    int incomingByte = 0; // for incoming serial data

    #ifdef TINYUSB_NEED_POLLING_TASK
    // Manual call tud_task since it isn't called by Core's background
    TinyUSBDevice.task();
    #endif
    
    // not enumerated()/mounted() yet: nothing to do
    if (!TinyUSBDevice.mounted()) {
      return;
    }

    // Remote wakeup
//    if ( TinyUSBDevice.suspended() && btn )
//    {
      // Wake up host if we are in suspend mode
      // and REMOTE_WAKEUP feature is enabled by host
//      TinyUSBDevice.remoteWakeup();
//    }

    if (!usb_hid.ready()) return;

    //ResetButtons(); //TODO check if need to reset the buttons
    // Test buttons (up to 32 buttons)
    static int aux = 0;
    //Serial.print("Pressing button ");
    //Serial.println(aux);
    gp.buttons = (1U << aux);
    usb_hid.sendReport(RID_GAMEPAD, &gp, sizeof(gp));
    aux++;
    if(aux>32) aux=0;
    /*for (int i = 0; i < 32; ++i) {
      Serial.print("Pressing button ");
      Serial.println(i);
      gp.buttons = (1U << i);
      usb_hid.sendReport(0, &gp, sizeof(gp));
    }*/
    // send data only when you receive data:
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
    }
}


void USBCommResetButtons(void)
{ 
  // Reset buttons
    //Serial.println("No pressing buttons");
    gp.x = 0;
    gp.y = 0;
    gp.z = 0;
    gp.rz = 0;
    gp.rx = 0;
    gp.ry = 0;
    gp.hat = 0;
    gp.buttons = 0;
    usb_hid.sendReport(RID_GAMEPAD, &gp, sizeof(gp));
}