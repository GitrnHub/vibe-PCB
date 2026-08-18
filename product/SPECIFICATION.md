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

- Wi-Fi image/content delivery
- BLE commissioning path (firmware roadmap)
- Native USB firmware download/debug
- Full/partial refresh profiles per panel controller
- OTA firmware update (firmware roadmap)
- Local web status/configuration UI (firmware roadmap)
- Deep-sleep oriented operation
- Replaceable display frame concept
- Parametric 3D-printable enclosure source and wall-mount relief

## Revision status

- `EPD_S3_Universal v0.15`: prototype-candidate electronics; custom geometry validation passed, but no claim of completed physical-production validation.
- `Enclosure v0.1`: parametric fit-check model.
- `Product firmware`: bring-up baseline plus architecture/roadmap; panel-specific LUT/initialization still required per exact display.
