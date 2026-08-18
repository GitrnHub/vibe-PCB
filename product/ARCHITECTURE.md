# Product Architecture

```text
Cloud / LAN content
        │ Wi-Fi / BLE
        ▼
┌───────────────────────────┐
│ ESP32-S3 application      │
│ scheduler / cache / OTA   │
└────────────┬──────────────┘
             │ SPI + control + I2C
             ▼
┌───────────────────────────┐
│ EPD interface + HV rails  │
│ on EPD_S3_Universal PCB   │
└────────────┬──────────────┘
             │ 24-pin FPC
             ▼
┌───────────────────────────┐
│ E-Ink panel               │
└───────────────────────────┘

Power: 5 V input → 3.3 V logic + panel high-voltage support rails
Mechanical: front bezel + panel + PCB standoffs + rear shell
```

The current product separates **validated-as-generated prototype data** from **future product targets**. USB-C, battery charging and RTC are not silently claimed as already present on v0.15; they belong to a future integrated hardware revision unless implemented with accessories.
