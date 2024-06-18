#include <Mouse.h>
#include <hiduniversal.h>
#include "hidmouserptparser.h"

// USB and HID objects
USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseReportParser Mou(nullptr);

// Constants for click intervals
const unsigned long BASE_CLICK_INTERVAL = 1000 / 12;  // Base interval for ~12 clicks per second
const unsigned long CLICK_INTERVAL_VARIABILITY = 50;  // Variability in click intervals in milliseconds
const unsigned long DOUBLE_CLICK_INTERVAL = 300;      // Interval for detecting double-clicks in milliseconds

// Configuration
const uint16_t DOUBLE_CLICK_BUTTON = MOUSE_BUTTON4;   // Button to double-click to toggle autoclicker

// Variables to manage click intervals and button states
unsigned long lastClickTime = 0;
unsigned long nextClickInterval = 0;
bool isLeftButtonHeld = false;
bool isAutoclickerActive = false;
unsigned long lastForwardButtonTime = 0;

void setup() {
    // Initialize USB and HID
    Mouse.begin();
    Usb.Init();
    delay(200);

    // Set HID report parser for mouse
    if (!Hid.SetReportParser(0, &Mou))
        ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);

    // Initialize random seed
    randomSeed(analogRead(0));
}

void loop() {
    // Process USB tasks
    Usb.Task();

    // Auto-clicker logic
    if (isAutoclickerActive && isLeftButtonHeld) {
        unsigned long currentTime = millis();
        if (currentTime - lastClickTime >= nextClickInterval) {
            Mouse.click(MOUSE_LEFT);
            lastClickTime = currentTime;
            nextClickInterval = generateRandomInterval(BASE_CLICK_INTERVAL, CLICK_INTERVAL_VARIABILITY);
        }
    }
}

// Handle button down events
void onButtonDown(uint16_t buttonId) {
    unsigned long currentTime = millis();

    switch (buttonId) {
        case MOUSE_LEFT:
            if (!isAutoclickerActive) {
                Mouse.press(MOUSE_LEFT);
            }
            isLeftButtonHeld = true;
            lastClickTime = currentTime;
            nextClickInterval = generateRandomInterval(BASE_CLICK_INTERVAL, CLICK_INTERVAL_VARIABILITY);
            break;
        case DOUBLE_CLICK_BUTTON:
            if (currentTime - lastForwardButtonTime <= DOUBLE_CLICK_INTERVAL) {
                isAutoclickerActive = !isAutoclickerActive;
            }
            lastForwardButtonTime = currentTime;
            break;
        default:
            Mouse.press(buttonId);
            break;
    }
}

// Handle button up events
void onButtonUp(uint16_t buttonId) {
    switch (buttonId) {
        case MOUSE_LEFT:
            if (!isAutoclickerActive) {
                Mouse.release(MOUSE_LEFT);
            }
            isLeftButtonHeld = false;
            break;
        default:
            Mouse.release(buttonId);
            break;
    }
}

// Handle tilt press events
void onTiltPress(int8_t tiltValue) {
    // Not implemented
}

// Handle mouse movement events
void onMouseMove(int8_t xMovement, int8_t yMovement, int8_t scrollValue) {
    Mouse.move(xMovement, yMovement, scrollValue);
}

// Generate a random interval around a base value
unsigned long generateRandomInterval(unsigned long baseInterval, unsigned long variability) {
    return baseInterval + random(-variability, variability + 1);
}
