# Firmware

`epd-s3-platformio/` contains the original board bring-up baseline. The product firmware is intentionally split into layers:

1. board support / pins
2. panel profile and panel-specific initialization/LUT
3. image buffer and dithering
4. connectivity (Wi-Fi/BLE)
5. local web UI / OTA
6. power manager / deep sleep

The current repository does **not** claim one universal binary for all 24-pin E-Paper panels. Exact controller initialization and waveform behavior remain panel-specific.
