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

****Hardware Pin Configuration**

| Module / Device           | LPC2148 Pins Used               |
| ------------------------- | ------------------------------- |
| LCD Control Pins          | P0.4 (RS), P0.5 (RW), P0.6 (EN) |
| 16x2 LCD Data Pins        | P0.8 – P0.15                    |
| 4x4 Matrix Keypad Rows    | P1.16 – P1.19                   |
| 4x4 Matrix Keypad Columns | P1.20 – P1.23                   |
| LM35 Temperature Sensor   | AD0.1 (P0.28)                   |
| External Interrupt Switch | EINT0 (P0.1)                    |
| Device 1 Output LED       | P1.24                           |
| Device 2 Output LED       | P1.25                           |

****Flow Chart**

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
**# Working Principle
1. System initializes RTC, LCD, ADC, and keypad modules.
2. RTC continuously updates current time, date, and day.
3. LM35 sensor monitors surrounding temperature.
4. Current status is displayed on 16x2 LCD.
5. Devices are automatically controlled based on RTC schedules.
6. If temperature exceeds threshold:
   - Devices are turned OFF
   - Interrupt access is disabled
   - System enters protection mode
7. User can edit settings only after:
   - External interrupt generation
   - Successful password authentication

**# Applications**

- Smart Home Automation
- Industrial Timer Control
- Temperature Safety Systems
- Laboratory Equipment Automation
- Scheduled Power Management
