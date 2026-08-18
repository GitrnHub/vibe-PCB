# Prototype Test Plan

## Electrical

- 5 V input short check before population
- 3.3 V rail regulation and ripple
- ESP32-S3 USB download mode
- RESET / BOOT behavior
- SPI signal integrity at the selected panel clock
- BUSY / RST / DC / CS logic levels
- EPD high-voltage rail sanity checks before panel attachment

## Firmware

- Cold boot
- USB flash/logging
- Wi-Fi association/reconnect
- Deep sleep/wake cycle
- Full refresh, fast refresh and partial refresh where supported by the selected panel
- 100-cycle refresh endurance smoke test

## Mechanical

- Panel fit without glass stress
- FPC bend radius and latch access
- PCB standoff alignment
- Cable/service opening clearance
- Rear shell closure
- Wall-mount and desk-use stability

## Manufacturing

- Gerber viewer layer review
- Drill file review
- BOM/CPL designator match
- First article: 5 boards recommended before any volume build
