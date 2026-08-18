# vibe-EPD Product Specification

## Product intent

vibe-EPD is a low-power, network-connected E-Ink reference product built around the `EPD_S3_Universal v0.15` electronics core. The repository treats the product as a complete system: display, electronics, firmware, enclosure, manufacturing data and validation.

## Current prototype hardware

| Item | Specification |
|---|---|
| MCU | ESP32-S3-WROOM-1-N8R2 |
| PCB | 60 × 45 mm, 2-layer prototype |
| Host connectivity | 2.4 GHz Wi-Fi, BLE, native USB signals on J1 |
| Display bus | 24-pin, 0.5 mm FPC E-Paper interface |
| Screen control | SPI + BUSY / RESET / DC / CS, plus I2C lines |
| Power input | 5 V on J1; local 3.3 V regulator |
| User controls | RESET + BOOT |
| Manufacturing | Gerber + drill + BOM + CPL included |

## Reference product configuration

The enclosure model targets a **4.2-inch 400×300 panel** in the GDEY042T81 mechanical class (91 × 77 mm outline). Other 24-pin panels may be electrically supportable but require a panel-specific mechanical frame and firmware profile.

## Product-level functions

### Implemented in the reference firmware baseline

- Wi-Fi SoftAP setup/service network
- Local web service dashboard
- JSON board-status and pin-map APIs
- Panel hardware-reset service action
- Timer deep-sleep smoke-test action
- Native USB firmware download/debug path
- SPI/I²C board-support initialization

### Requires an exact panel profile or later product revision

- actual framebuffer refresh and full/partial refresh LUTs — panel/controller-specific
- image upload, dithering and content scheduling
- STA provisioning and persistent Wi-Fi configuration
- BLE commissioning
- OTA firmware update
- integrated USB-C receptacle / Li-ion charger / fuel gauge / RTC on the next product PCB revision

## Mechanical/product structure

- replaceable front-display frame concept
- 4.2-inch reference panel locating geometry
- rear shell with PCB mounting bosses
- service opening and wall-mount relief
- parametric OpenSCAD source suitable for STL export after final fit verification

## Revision status

- `EPD_S3_Universal v0.15`: prototype-candidate electronics; custom geometry validation passed, but no claim of completed physical-production validation.
- `Enclosure v0.1`: parametric fit-check model.
- `Product firmware`: local service-console baseline implemented; panel-specific LUT/initialization still required per exact display.
