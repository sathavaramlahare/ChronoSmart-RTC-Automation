**ChronoSmart-RTC-Automation**
ChronoSmart is an LPC2148-based embedded automation system designed for real-time device control using RTC scheduling, secure password authentication, LCD monitoring, keypad-driven configuration, temperature sensing through ADC, and automatic ON/OFF management for multiple devices.

**Overview**

ChronoSmart RTC Automation is an LPC2148-based embedded system project designed for intelligent device automation using Real-Time Clock (RTC) scheduling, temperature monitoring, and interrupt-driven control.

The system allows users to:
- Set automatic ON/OFF timings for devices
- Monitor temperature using the LM35 sensor
- Configure system parameters through keypad interface
- Display real-time information on 16x2 LCD
- Protect settings using password authentication
- Edit parameters only when an external interrupt is generated
- Automatically disable device operation when temperature exceeds the threshold value for safety protection

**Hardware Components**

- LPC2148 Microcontroller
- 16x2 LCD Display
- 4x4 Matrix Keypad
- LM35 Temperature Sensor
- LED'S
- Switch
- USB-UART Converter


**Software Used**

- Embedded C
- Keil uVision
- Flash Magic

****Flow Chart**
                           ## Flow Chart

```text
                   ┌─────────────────┐
                   │      START      │
                   └────────┬────────┘
                            │
                            ▼
         ┌────────────────────────────────┐
         │ Initialize System Modules      │
         │ • RTC                          │
         │ • LCD                          │
         │ • ADC                          │
         │ • Keypad                       │
         └───────────────┬────────────────┘
                         │
                         ▼
         ┌────────────────────────────────┐
         │ Continuously Read RTC          │
         │ • Time                         │
         │ • Date                         │
         │ • Day                          │
         └───────────────┬────────────────┘
                         │
                         ▼
         ┌────────────────────────────────┐
         │ Read Temperature from LM35     │
         └───────────────┬────────────────┘
                         │
                         ▼
         ┌────────────────────────────────┐
         │ Display on 16x2 LCD            │
         │ • Time                         │
         │ • Date                         │
         │ • Temperature                  │
         └───────────────┬────────────────┘
                         │
                         ▼
         ┌────────────────────────────────┐
         │ Is Temperature > Threshold ?   │
         └───────────┬───────────┬────────┘
                     │ YES       │ NO
                     ▼           ▼
     ┌────────────────────────┐  ┌────────────────────────────┐
     │ Disable Devices        │  │ Compare RTC Time with      │
     │ for Safety Protection  │  │ Stored ON/OFF Schedules    │
     └────────────┬───────────┘  └─────────────┬──────────────┘
                  │                            │
                  └────────────┬───────────────┘
                               │
                               ▼
             ┌────────────────────────────────┐
             │ Automatically Control Devices  │
             │ • Device ON                    │
             │ • Device OFF                   │
             └───────────────┬────────────────┘
                             │
                             ▼
             ┌────────────────────────────────┐
             │ Is External Interrupt Generated│
             │        by User Switch ?        │
             └───────────┬───────────┬────────┘
                         │ YES       │ NO
                         ▼           ▼
         ┌────────────────────────┐  ┌────────────────────────┐
         │ Ask for Password       │  │ Continue Monitoring    │
         │ Authentication         │  │ RTC and Temperature    │
         └────────────┬───────────┘  └────────────┬───────────┘
                      │                           │
                      ▼                           │
         ┌────────────────────────┐               │
         │ Open Settings Menu     │               │
         │ • Edit RTC Time        │               │
         │ • Edit Date/Day        │               │
         │ • Set Device Timings   │               │
         │ • Set Temperature      │               │
         └────────────┬───────────┘               │
                      │                           │
                      └────────────┬──────────────┘
                                   │
                                   ▼
                       ┌──────────────────┐
                       │      REPEAT      │
                       └──────────────────┘
```
