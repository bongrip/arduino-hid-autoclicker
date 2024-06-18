# arduino-hid-autoclicker
An autoclicker created for Arduino + USB Host Shield.

# Requirements

- Arduino `(For this I used An KEYESTUDIO ARDUINO LEONARDO R3)` [AMAZON USA](https://www.amazon.com/KEYESTUDIO-Leonardo-Development-Board-Arduino/dp/B0786LJQ8K)
- USB Host Shield `(For this I used An HILETGO USB Host Shield)` [AMAZON USA](https://www.amazon.com/HiLetgo-Shield-Arduino-Support-Android/dp/B01MTU9OLM/)

# Usage

Open the Arduino IDE and upload the Sketch file.<br>
The Default binding for this autoclicker is double pressing the MOUSE_4 within quick succession<br>
Then you will be able to hold your mouse click, and it will simulate clicks!

# How can I spoof this as a REAL mouse?

To make this look like a real mouse, you can upload a custom boards.txt<br>

Example `(Logitech Lightspeed Reciever)`

Path to add this board `(<arduino-ide-install-path>\packages\arduino\hardware\avr\*\boards.txt)`

```
custom.name=Lightspeed Receiver
custom.vid.0=0x046D
custom.pid.0=0xC539
custom.vid.1=0x046D
custom.pid.1=0xC539
custom.vid.2=0x046D
custom.pid.2=0xC539
custom.vid.3=0x046D
custom.pid.3=0xC539
custom.upload_port.0.vid=0x046D
custom.upload_port.0.pid=0xC539
custom.upload_port.1.vid=0x046D
custom.upload_port.1.pid=0xC539
custom.upload_port.2.vid=0x046D
custom.upload_port.2.pid=0xC539
custom.upload_port.3.vid=0x046D
custom.upload_port.3.pid=0xC539
custom.upload_port.4.board=leonardo

custom.upload.tool=avrdude
custom.upload.tool.default=avrdude
custom.upload.tool.network=arduino_ota
custom.upload.protocol=avr109
custom.upload.maximum_size=28672
custom.upload.maximum_data_size=2560
custom.upload.speed=57600
custom.upload.disable_flushing=true
custom.upload.use_1200bps_touch=true
custom.upload.wait_for_upload_port=true

custom.bootloader.tool=avrdude
custom.bootloader.tool.default=avrdude
custom.bootloader.low_fuses=0xff
custom.bootloader.high_fuses=0xd8
custom.bootloader.extended_fuses=0xcb
custom.bootloader.file=caterina/Caterina-Leonardo.hex
custom.bootloader.unlock_bits=0x3F
custom.bootloader.lock_bits=0x2F

custom.build.mcu=atmega32u4
custom.build.f_cpu=16000000L
custom.build.vid=0x046D
custom.build.pid=0xC539
custom.build.usb_product="Lightspeed Receiver"
custom.build.board=AVR_LEONARDO
custom.build.core=arduino
custom.build.variant=leonardo
custom.build.extra_flags={build.usb_flags} -DCDC_DISABLED # Remove -DCDC_DISABLED to re-enable the COM port on your board!
```

# I've uploaded a custom board, but lost my COM port!

To re-enable your COM port, please follow the steps below:

- Select a new board WITHOUT `-DCDC_DISABLED`
- Press COMPILE, wait for it to finish but **AS** you compile, **HOLD** the reset on your Arduino Board
- Once compile has **FINISHED** successfully, **RELEASE** the reset.
- The arduino will now flash/upload the new board without `-DCDC_DISABLED`
