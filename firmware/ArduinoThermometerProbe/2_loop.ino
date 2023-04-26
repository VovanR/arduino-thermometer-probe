void loop() {
  if (sensorTimer.isReady()) {
    previousTemp = currentTemp;
    currentTemp = therm.getTempAverage();

    // BME280
    bme.takeForcedMeasurement();
    dispTemp = bme.readTemperature();
    // dispHum = bme.readHumidity();
    // dispPres = (float)bme.readPressure() * 0.00750062;

    progressIconFilled = !progressIconFilled;
  }

  if (fiveSecTimer.isReady()) {
    fiveSecTemp = currentTemp;
  }

  if (tenSecTimer.isReady()) {
    tenSecTemp = currentTemp;
  }

  if (minuteTimer.isReady()) {
    minuteTemp = currentTemp;

    for (int i = 63; i >= 0; i--) {
      if (i == 0) {
        tempGraph[i] = currentTemp;
      } else {
        tempGraph[i] = tempGraph[i - 1];
      }
    }
  }

  if (withDisplay) {
    display.clearDisplay();
    // Normal 1:1 pixel scale
    display.setTextSize(1);
    display.setCursor(0, 7);
    display.print("NTC");


    display.setTextSize(2);
    // Draw white text
    display.setTextColor(SSD1306_WHITE);
    // Start at top-left corner
    display.setCursor(20, 0);

    // display.write("T:");
    display.print(currentTemp);

    display.setTextSize(1);
    if ((currentTemp == previousTemp && up) || currentTemp > previousTemp) {
      up = true;
      display.write(0x18);  // ↑
    } else {
      up = false;
      display.write(0x19);  // ↓
    }
    // display.println(currentTemp);

    // BME280
    display.setCursor(0, 23);
    display.print("\BME");
    display.setTextSize(2);
    display.setCursor(20, 16);
    display.print(dispTemp, 0);

    // display.setTextSize(1);
    // display.print("H:");
    // display.print(bme.readHumidity(), 0);
    // display.println(" %");

    // display.print("P:");
    // display.print(bme.readPressure() * 0.00750062, 0);
    // display.println(" mm");


    // display.setTextSize(1);
    // display.setCursor(58, 16);
    // display.println(" 1  5 10 60");
    // display.setCursor(58, 24);
    // display.print(previousTemp);
    // display.write(" ");
    // display.print(fiveSecTemp);
    // display.write(" ");
    // display.print(tenSecTemp);
    // display.write(" ");
    // display.print(minuteTemp);

    display.setTextSize(1);
    display.setCursor(122, 0);
    if (progressIconFilled) {
      // display.write(0x09);
    } else {
      display.fillCircle(120, 1, 1, SSD1306_WHITE);
      // display.write(0x07);
    }

    drawTempChart();

    display.display();
  }

  // delay in between reads for stability
  delay(100);
}