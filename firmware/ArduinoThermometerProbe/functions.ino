void drawTempChart() {
  int16_t i;
  int16_t val;

  for (i = 0; i < graphLength; i++) {
    val = map(constrain(tempGraph[i], TEMP_MIN, TEMP_MAX), TEMP_MIN, TEMP_MAX, 0, 22);
    display.drawPixel((128 - 1) - i, (22 - 1) - val, DEFAULT_COLOR);
  }

  // Chart border
  display.drawPixel(44, 0, DEFAULT_COLOR);
  display.drawPixel(44, 22 - 1, DEFAULT_COLOR);
  display.drawPixel(128 - 1, 0, DEFAULT_COLOR);
  display.drawPixel(128 - 1, 22 - 1, DEFAULT_COLOR);
}

void addTempToStack(int value) {
  for (int i = graphLength - 1; i >= 0; i--) {
    if (i == 0) {
      tempGraph[i] = value;
    } else {
      tempGraph[i] = tempGraph[i - 1];
    }
  }
}
