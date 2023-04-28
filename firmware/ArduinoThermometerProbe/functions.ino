void drawTempChart() {
  int16_t i;
  int16_t val;
  int16_t height = SCREEN_HEIGHT;

  if (withBme) {
    height = 22;
  }

  int16_t left = SCREEN_WIDTH - graphLength;
  int16_t right = SCREEN_WIDTH - 1;
  int16_t top = 0;
  int16_t bottom = height - 1;

  for (i = 0; i < graphLength; i++) {
    val = map(constrain(tempGraph[i], TEMP_MIN, TEMP_MAX), TEMP_MIN, TEMP_MAX, 0, 22);
    display.drawPixel(right - i, bottom - val, DEFAULT_COLOR);
  }

  // Chart border
  display.drawPixel(left, top, DEFAULT_COLOR);
  display.drawPixel(left, bottom, DEFAULT_COLOR);
  display.drawPixel(right, top, DEFAULT_COLOR);
  display.drawPixel(right, bottom, DEFAULT_COLOR);
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

void writeDot(int count) {
  for (int i = 0; i < count; i++) {
    display.write(0x20);
  }
}

void readSensors() {
  previousTemp = currentTemp;
  currentTemp = therm.getTempAverage();

  // BME280
  if (withBme) {
    bme.takeForcedMeasurement();
    dispTemp = bme.readTemperature();
    dispHum = bme.readHumidity();
    dispPres = (float)bme.readPressure() * 0.00750062;
  }
}
