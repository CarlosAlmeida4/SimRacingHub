#include "USBComm\USBComm.h"
#include "Arduino.h"
#include <Adafruit_TinyUSB.h>
#include <string.h>

#if CFG_TUD_HID < 2
  #error "Requires two HID instances support. See https://github.com/adafruit/Adafruit_TinyUSB_Arduino/commit/b75604f794acdf88daad310dd75d3a0724129056"
#endif 

#define MAX_PACKET_SIZE 5 //The packet is always 64 bytes

// Report ID
enum
{
  RID_GAMEPAD = 0,
  RID_GENERIC,
};

hid_gamepad_report_t gp;
// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report_gamepad[] = {
  TUD_HID_REPORT_DESC_GAMEPAD()
};
uint8_t const desc_hid_report_inout[] = {
  TUD_HID_REPORT_DESC_GENERIC_INOUT(MAX_PACKET_SIZE)
};

// USB HID object
Adafruit_USBD_HID usb_hid_gamepad(desc_hid_report_gamepad, sizeof(desc_hid_report_gamepad), HID_ITF_PROTOCOL_NONE, 2, true);
Adafruit_USBD_HID usb_hid_inout(desc_hid_report_inout, sizeof(desc_hid_report_inout), HID_ITF_PROTOCOL_NONE, 2, true);

// Buffer to receive a packet
uint8_t ReceivedPacket[MAX_PACKET_SIZE];

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
  //Serial.print("Called Set Report Callback: ");
  //Serial.println(report_id);
  if(bufsize <= MAX_PACKET_SIZE)
  {
    memcpy(ReceivedPacket,buffer,MAX_PACKET_SIZE);
  }
  // echo back anything we received from host
  usb_hid_inout.sendReport(0, buffer, bufsize);
}

void USBCommInit()
{
    // Manual begin() is required on core without built-in support e.g. mbed rp2040
    if (!TinyUSBDevice.isInitialized()) {
      TinyUSBDevice.begin(0);
    }   
    // Setup HID
    usb_hid_inout.enableOutEndpoint(true);
    usb_hid_inout.setPollInterval(10);
    usb_hid_inout.setReportDescriptor(desc_hid_report_inout, sizeof(desc_hid_report_inout));
    usb_hid_inout.setReportCallback(USBCommGet_report_callback,USBCommSet_report_callback);
    usb_hid_inout.begin(); 

    usb_hid_gamepad.setPollInterval(2);
    usb_hid_gamepad.setReportDescriptor(desc_hid_report_gamepad, sizeof(desc_hid_report_gamepad));   
    usb_hid_gamepad.begin(); 
    // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
    if (TinyUSBDevice.mounted()) {
      TinyUSBDevice.detach();
      delay(10);
      TinyUSBDevice.attach();
    }

}

void USBCommCyclic(SharedData_t *SharedData)
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

    if (!usb_hid_gamepad.ready() || !usb_hid_inout.ready()) return;

    USBCommHandleReceivedPacket(SharedData);
}

void USBCommHandleReceivedPacket(SharedData_t *SharedData)
{
  //Serial.print("message to handle: ");
  //Serial.println(ReceivedPacket[0]);
  switch (ReceivedPacket[0])
  {
  case 1:
    //Serial.print("The curent gear is: ");
    //Serial.println(ReceivedPacket[1]);
    SharedData->CurrentGear = ReceivedPacket[1];
    break;
  
  default:
    break;
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
    usb_hid_gamepad.sendReport(0, &gp, sizeof(gp));
}

void USBCommSetButtonReport(uint32_t button)
{
    gp.buttons = (1U << button);
    usb_hid_gamepad.sendReport(0, &gp, sizeof(gp));
}

void USBCommResetButtonReport(uint32_t button)
{
    gp.buttons = (0U << button);
    usb_hid_gamepad.sendReport(0, &gp, sizeof(gp));
}