# Firmware

`epd-s3-platformio/` now contains a product-oriented bring-up baseline rather than only a pin smoke test.

## Current baseline features

- ESP32-S3 SPI / I²C board-support initialization
- E-Paper RESET / BUSY primitives
- protected panel refresh boundary: no controller command/LUT is sent until an exact panel profile is linked
- default Wi-Fi SoftAP: `vibe-EPD-setup`
- local HTTP service console at the SoftAP IP
- JSON status API: uptime, EPD BUSY state, AP IP/client count and panel-profile state
- board pin-map API
- panel hardware-reset endpoint
- timed deep-sleep endpoint for low-power smoke testing

### Service endpoints

| Method | Path | Purpose |
|---|---|---|
| GET | `/` | local product service dashboard |
| GET | `/api/status` | live JSON status |
| GET | `/api/pins` | board pin map |
| POST | `/api/reset-panel` | hardware-reset the E-Paper panel |
| POST | `/api/refresh` | deliberately returns 501 until an exact panel profile is linked |
| POST | `/api/sleep?seconds=60` | enter timer deep sleep |

The setup AP password is a development default (`vibepcb-setup`) and must be changed for a deployed product.

## Next firmware layer

1. exact panel profile + initialization/LUT
2. framebuffer / dithering / image upload
3. STA provisioning and persistent network configuration
4. OTA firmware update
5. content scheduler/cache
6. measured low-power policy for the final product hardware

The repository does **not** claim one universal binary for all 24-pin E-Paper panels. Exact controller initialization and waveform behavior remain panel-specific.
