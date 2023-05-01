void drawTempChart(int chart[]) {
  int16_t i;
  int16_t val;
  int16_t height = SCREEN_HEIGHT;

  if (withBme) {
    height = 22;
  }

  int16_t left = SCREEN_WIDTH - chartLength;
  int16_t right = SCREEN_WIDTH - 1;
  int16_t top = 0;
  int16_t bottom = height - 1;

  for (i = 0; i < chartLength; i++) {
    val = map(constrain(chart[i], TEMP_MIN, TEMP_MAX), TEMP_MIN, TEMP_MAX, 0, 22);
    display.drawPixel(right - i, bottom - val, DEFAULT_COLOR);
  }

  // Chart border
  // display.drawPixel(left, top, DEFAULT_COLOR);
  display.drawPixel(left, bottom, DEFAULT_COLOR);
  display.drawPixel(right, top, DEFAULT_COLOR);
  display.drawPixel(right, bottom, DEFAULT_COLOR);
}

void drawChartState(char label[]) {
  int16_t left = SCREEN_WIDTH - chartLength;
  int16_t top = 0;

  display.setCursor(left, top);
  display.print(label);
}

void addTempToStack(int value, int chart[]) {
  for (int i = chartLength - 1; i >= 0; i--) {
    if (i == 0) {
      chart[i] = value;
    } else {
      chart[i] = chart[i - 1];
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

void drawStatTemp(int value) {
  if (abs(value) >= 100) {
  } else if (abs(value) >= 10) {
    display.print(" ");
  } else {
    display.print("  ");
  }
  if (value >= 0) {
    display.print(" ");
  }
  display.println(value);
}

void calculateStatTemp(int chart[]) {
  maxTemp = chart[0];
  minTemp = chart[0];
  for (int i = 1; i < chartLength; i++) {
    maxTemp = max(maxTemp, chart[i]);
    minTemp = min(minTemp, chart[i]);
  }
}

void initializeChart(int temp, int chart[]) {
  int16_t i;
  for (i = 0; i < chartLength; i++) {
    chart[i] = temp;
  }
}
