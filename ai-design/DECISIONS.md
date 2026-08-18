# AI-assisted Design Decisions

This file records engineering intent so future revisions do not lose the rationale behind the layout.

## D001 — ESP32-S3 module

**Decision:** ESP32-S3-WROOM-1 family.

**Rationale:** integrated Wi-Fi/BLE, native USB capability, sufficient GPIO, and PSRAM-capable module variants give margin for image buffers and networking.

## D002 — 24-pin 0.5 mm EPD interface

**Decision:** keep the low-cost base board focused on the common 24-pin SPI panel family.

**Rationale:** avoids making every board pay for the larger and more specialized power/interface requirements of newer 50-pin color panels. Those should use an adapter or a dedicated revision.

## D003 — Reference enclosure uses a 4.2-inch panel

**Decision:** mechanical v0.1 targets a 91 × 77 mm, 4.2-inch panel class.

**Rationale:** gives the repository a concrete complete-product geometry while keeping the PCB electrically reusable for other screen sizes.

## D004 — Separate current facts from roadmap

**Decision:** documentation marks USB-C, battery charging, RTC and richer sensor expansion as future integrated-hardware features unless they actually exist in the released PCB files.

**Rationale:** visual polish must not turn roadmap items into false manufacturing claims.
