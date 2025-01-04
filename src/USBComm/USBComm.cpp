#include "USBComm\USBComm.h"
#include "Arduino.h"
#include <Adafruit_TinyUSB.h>
#include <string.h>


void USBComm::Init()
{
    // Manual begin() is required on core without built-in support e.g. mbed rp2040
    if (!TinyUSBDevice.isInitialized()) {
      TinyUSBDevice.begin(0);
    }   
    // Setup HID
    usb_hid.setPollInterval(2);
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.begin();    
    // If already enumerated, additional class driverr begin() e.g msc, hid, midi won't take effect until re-enumeration
    if (TinyUSBDevice.mounted()) {
      TinyUSBDevice.detach();
      delay(10);
      TinyUSBDevice.attach();
    }

}

void USBComm::Cyclic()
{
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
    usb_hid.sendReport(0, &gp, sizeof(gp));
    aux++;
    if(aux>32) aux=0;
    /*for (int i = 0; i < 32; ++i) {
      Serial.print("Pressing button ");
      Serial.println(i);
      gp.buttons = (1U << i);
      usb_hid.sendReport(0, &gp, sizeof(gp));
    }*/
}


void USBComm::ResetButtons(void)
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
    usb_hid.sendReport(0, &gp, sizeof(gp));
}