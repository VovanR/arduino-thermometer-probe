void loop() {
  if (isFirstLoop) {
    readSensors();
    addTempToStack(currentTemp);
  }

  if (oneSecTimer.isReady()) {
    readSensors();

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

    addTempToStack(currentTemp);
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

    // Min/Max
    // display.setTextSize(1);
    // // Start at top-left corner
    // display.setCursor(0, 17);
    // display.println(max(tempGraph));
    // display.println(min(tempGraph));

    // BME280
    if (withBme) {
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
    }

    if (progressIconFilled) {
      display.fillCircle(120, 1, 1, DEFAULT_COLOR);
    }

    drawTempChart();

    display.display();
  }

  // delay in between reads for stability
  delay(100);
  isFirstLoop = false;
}