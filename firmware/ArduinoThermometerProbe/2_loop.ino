void loop() {
  if (oneSecTimer.isReady()) {
    previousTemp = currentTemp;
    currentTemp = therm.getTempAverage();

    // BME280
    bme.takeForcedMeasurement();
    dispTemp = bme.readTemperature();
    dispHum = bme.readHumidity();
    dispPres = (float)bme.readPressure() * 0.00750062;

    progressIconFilled = !progressIconFilled;

    addTempToStack(currentTemp);
  }

  if (fiveSecTimer.isReady()) {
    fiveSecTemp = currentTemp;
  }

  if (tenSecTimer.isReady()) {
    tenSecTemp = currentTemp;
  }

  if (minuteTimer.isReady()) {
    minuteTemp = currentTemp;
  }

  if (withDisplay) {
    display.clearDisplay();

    // Draw white text
    display.setTextColor(DEFAULT_COLOR);

    // Sign
    display.setTextSize(1);
    // Start at top-left corner
    display.setCursor(0, 7);
    if (currentTemp >= 0) {
      display.print("+");
    }

    display.setTextSize(2);
    display.setCursor(6, 0);
    display.print(currentTemp);

    // Arrow
    display.setTextSize(1);
    // if (currentTemp > 99 || currentTemp < -99) {
    //   display.setCursor(39, 0);
    // } else {
    //   display.setCursor(31, 0);
    // }
    if ((currentTemp == previousTemp && up) || currentTemp > previousTemp) {
      up = true;
      display.write(0x18); // ↑
    } else {
      up = false;
      display.write(0x19); // ↓
    }

    // BME280
    display.setTextSize(1);
    if (abs(dispTemp) > 99) {
      display.setCursor(37, 25);
    } else {
      display.setCursor(43, 25);
    }
    if (dispTemp >= 0) {
      display.print("+");
    }
    display.print(dispTemp, 0);
    display.print("C");

    if (dispHum >= 100) {
      display.setCursor(70, 25);
    } else if (dispHum >= 10) {
      display.setCursor(76, 25);
    } else {
      display.setCursor(82, 25);
    }
    display.print(dispHum);
    display.print("%");

    if (dispPres >= 100) {
      display.setCursor(98, 25);
    } else if (dispPres >= 10) {
      display.setCursor(104, 25);
    } else {
      display.setCursor(110, 25);
    }
    display.print(dispPres);
    display.print("mm");


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

    if (progressIconFilled) {
      display.fillCircle(120, 1, 1, DEFAULT_COLOR);
    }

    drawTempChart();

    display.display();
  }

  // delay in between reads for stability
  delay(100);
}