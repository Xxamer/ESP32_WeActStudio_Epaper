#include <Arduino.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#define EPD_BUSY  4
#define EPD_RST   16
#define EPD_DC    17
#define EPD_CS    5
#define EPD_SCK   18
#define EPD_MOSI  23

GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> epd(
  GxEPD2_154_D67(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)
);

String texto =
"According to all known laws of aviation, there is no way a bee should be able to fly. Its wings are too small to get its fat little body off the ground. The bee, of course, flies anyway because bees don't care what humans think is impossible. Yellow, black. Yellow, black. Yellow, black. Yellow, black. Ooh, black and yellow! Let's shake it up a little. Barry! Breakfast is ready! Coming! Hang on a second. Hello?";

// CONFIG
const int LINE_HEIGHT = 18;
const int MAX_CHARS = 19;
const int SCREEN_H = 190;

// -------- SPLIT SIMPLE --------
std::vector<String> dividirLineas(String txt) {
  std::vector<String> lineas;
  String linea = "";
  for (int i = 0; i < txt.length(); i++) {
    linea += txt[i];
    if (linea.length() >= MAX_CHARS && txt[i] == ' ') {
      lineas.push_back(linea);
      linea = "";
    }
  }

  if (linea.length() > 0) lineas.push_back(linea);
  return lineas;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  epd.init();
  epd.setRotation(0);
  epd.setTextColor(GxEPD_BLACK);
  epd.setFont(&FreeMonoBold9pt7b);
  // We divide the text between lines
  auto lineas = dividirLineas(texto);
  // Max lines in screen 
  int maxLineas = SCREEN_H / LINE_HEIGHT;

  int totalPaginas = (lineas.size() + maxLineas - 1) / maxLineas;

  for (int p = 0; p < totalPaginas; p++) {
    // Clean between iterations
    epd.setFullWindow();
    epd.firstPage();
    do {
      epd.fillScreen(GxEPD_WHITE);
      int y = 20;
      int start = p * maxLineas;
      for (int i = 0; i < maxLineas; i++) {
        int idx = start + i;
        if (idx >= lineas.size()) break;
        epd.setCursor(0, y);
        epd.print(lineas[idx]);
        y += LINE_HEIGHT;
      }

    } while (epd.nextPage());
    //Time between pages
    delay(4000);
  }

  // -------- WRITE "FIN" WHEN PAGES ARE FINISHED --------
  epd.setFullWindow();
  epd.firstPage();
  do {
    epd.fillScreen(GxEPD_WHITE);
    epd.setTextSize(2);
    epd.print("THE END");
  } while (epd.nextPage());
  epd.hibernate();
}

void loop() {}