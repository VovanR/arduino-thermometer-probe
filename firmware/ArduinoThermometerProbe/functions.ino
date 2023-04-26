int16_t chartX = 64;
int16_t chartY = 32;

void drawTempChart() {
  int16_t i;
  int16_t val;

  for (i = 0; i < graphLength; i++) {
    val = map(tempGraph[i], -10, 100, 0, 32);
    // Right-to-left
    display.drawPixel(128 - i, 32 - val, SSD1306_WHITE);
    // Left-to-right
    // display.drawPixel(64 + i, 32 - val, SSD1306_WHITE);
  }

  display.drawPixel(64, 0, SSD1306_WHITE);
  display.drawPixel(64, 32 - 1, SSD1306_WHITE);

  display.drawPixel(128 - 1, 0, SSD1306_WHITE);
  display.drawPixel(128 - 1, 32 - 1, SSD1306_WHITE);
}
