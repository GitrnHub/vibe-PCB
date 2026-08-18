#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <esp_sleep.h>
#include "board_pins.h"

#ifndef VIBE_AP_SSID
#define VIBE_AP_SSID "vibe-EPD-setup"
#endif

#ifndef VIBE_AP_PASSWORD
#define VIBE_AP_PASSWORD "vibepcb-setup"
#endif

SPIClass epdSPI(FSPI);
WebServer server(80);

static void epdWriteCommand(uint8_t c) {
  digitalWrite(PIN_EPD_DC, LOW);
  digitalWrite(PIN_EPD_CS, LOW);
  epdSPI.transfer(c);
  digitalWrite(PIN_EPD_CS, HIGH);
}

static void epdWriteData(uint8_t d) {
  digitalWrite(PIN_EPD_DC, HIGH);
  digitalWrite(PIN_EPD_CS, LOW);
  epdSPI.transfer(d);
  digitalWrite(PIN_EPD_CS, HIGH);
}

static bool epdWaitReady(uint32_t timeout_ms = 30000) {
  const uint32_t start = millis();
  while (digitalRead(PIN_EPD_BUSY) == LOW) {
    if (millis() - start > timeout_ms) return false;
    delay(5);
  }
  return true;
}

static void epdHardwareReset() {
  digitalWrite(PIN_EPD_RST, LOW);
  delay(10);
  digitalWrite(PIN_EPD_RST, HIGH);
  delay(10);
}

static String jsonStatus() {
  String out = "{";
  out += "\"product\":\"vibe-EPD\",";
  out += "\"hardware\":\"EPD_S3_Universal_v0.15\",";
  out += "\"uptime_ms\":" + String(millis()) + ",";
  out += "\"epd_busy\":" + String(digitalRead(PIN_EPD_BUSY) == HIGH ? "false" : "true") + ",";
  out += "\"ap_ip\":\"" + WiFi.softAPIP().toString() + "\",";
  out += "\"ap_clients\":" + String(WiFi.softAPgetStationNum()) + ",";
  out += "\"panel_profile\":\"not-linked\"";
  out += "}";
  return out;
}

static String dashboardHtml() {
  return R"HTML(
<!doctype html><html><head><meta name="viewport" content="width=device-width,initial-scale=1">
<title>vibe-EPD</title><style>
:root{color-scheme:dark}body{font-family:system-ui;margin:0;background:#0b0e12;color:#e9edf1}.w{max-width:760px;margin:auto;padding:28px}.card{border:1px solid #2c3540;background:#121820;border-radius:16px;padding:18px;margin:14px 0}.muted{color:#9aa6b2}.grid{display:grid;grid-template-columns:repeat(2,1fr);gap:10px}button{border:0;border-radius:10px;padding:11px 14px;font-weight:700;background:#d7bc58;color:#17140b}code{color:#b9e2cf}@media(max-width:560px){.grid{grid-template-columns:1fr}}
</style></head><body><main class="w"><h1>vibe-EPD</h1><p class="muted">Local service console · EPD_S3_Universal v0.15</p>
<div class="card"><h2>Live status</h2><pre id="s">loading…</pre></div>
<div class="grid"><div class="card"><h3>Panel service</h3><p class="muted">Hardware reset is safe; refresh remains panel-profile specific.</p><button id="r">Reset panel</button></div><div class="card"><h3>Low power</h3><p class="muted">Timer deep-sleep smoke test.</p><button id="z">Sleep 60 s</button></div></div>
<div class="card"><h3>EPD pin map</h3><code>SCLK 21 · MOSI 47 · CS 14 · DC 13 · RST 12 · BUSY 11 · I²C 9/10</code></div>
<div class="card"><h3>Refresh API</h3><p class="muted"><code>POST /api/refresh</code> intentionally returns 501 until a controller/LUT profile for the exact panel is linked.</p></div>
</main><script>
async function status(){const r=await fetch('/api/status');document.querySelector('#s').textContent=JSON.stringify(await r.json(),null,2)}
document.querySelector('#r').onclick=async()=>{await fetch('/api/reset-panel',{method:'POST'});status()};
document.querySelector('#z').onclick=async()=>{await fetch('/api/sleep?seconds=60',{method:'POST'});};
status();setInterval(status,2000);
</script></body></html>)HTML";
}

static void startWebConsole() {
  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(VIBE_AP_SSID, VIBE_AP_PASSWORD)) {
    Serial.println("SoftAP start failed.");
    return;
  }

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html; charset=utf-8", dashboardHtml());
  });

  server.on("/api/status", HTTP_GET, []() {
    server.send(200, "application/json", jsonStatus());
  });

  server.on("/api/pins", HTTP_GET, []() {
    server.send(200, "application/json",
      "{\"sclk\":21,\"mosi\":47,\"cs\":14,\"dc\":13,\"rst\":12,\"busy\":11,\"i2c_scl\":9,\"i2c_sda\":10}");
  });

  server.on("/api/reset-panel", HTTP_POST, []() {
    epdHardwareReset();
    server.send(200, "application/json", "{\"ok\":true}");
  });

  server.on("/api/refresh", HTTP_POST, []() {
    server.send(501, "application/json",
      "{\"ok\":false,\"error\":\"panel profile not linked; select exact controller/LUT first\"}");
  });

  server.on("/api/sleep", HTTP_POST, []() {
    uint32_t seconds = 60;
    if (server.hasArg("seconds")) {
      const long requested = server.arg("seconds").toInt();
      if (requested >= 5 && requested <= 86400) seconds = static_cast<uint32_t>(requested);
    }
    server.send(200, "application/json", "{\"ok\":true,\"sleep_seconds\":" + String(seconds) + "}");
    delay(100);
    esp_sleep_enable_timer_wakeup(static_cast<uint64_t>(seconds) * 1000000ULL);
    esp_deep_sleep_start();
  });

  server.onNotFound([]() {
    server.send(404, "application/json", "{\"error\":\"not found\"}");
  });

  server.begin();
  Serial.printf("SoftAP: %s\n", VIBE_AP_SSID);
  Serial.printf("Service UI: http://%s/\n", WiFi.softAPIP().toString().c_str());
}

void setup() {
  Serial.begin(115200);
  delay(250);

  pinMode(PIN_EPD_CS, OUTPUT);
  pinMode(PIN_EPD_DC, OUTPUT);
  pinMode(PIN_EPD_RST, OUTPUT);
  pinMode(PIN_EPD_BUSY, INPUT);
  digitalWrite(PIN_EPD_CS, HIGH);

  epdSPI.begin(PIN_EPD_SCLK, -1, PIN_EPD_MOSI, PIN_EPD_CS);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  epdHardwareReset();

  Serial.println("EPD-S3-Universal product bring-up.");
  Serial.println("Exact panel controller init/LUT remains profile-specific.");
  startWebConsole();

  (void)epdWriteCommand;
  (void)epdWriteData;
  (void)epdWaitReady;
}

void loop() {
  server.handleClient();
  delay(2);
}
