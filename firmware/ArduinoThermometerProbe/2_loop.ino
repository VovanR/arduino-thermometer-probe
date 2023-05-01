void loop() {
  // Fill first gramph value immediate
  if (isFirstLoop) {
    readSensors();
    initializeChart(currentTemp, tempChart);
    initializeChart(currentTemp, fiveSecTempChart);
    initializeChart(currentTemp, tenSecTempChart);
    initializeChart(currentTemp, minuteTempChart);
  }

  if (oneSecTimer.isReady()) {
    readSensors();
    addTempToStack(currentTemp, tempChart);

    progressIconFilled = !progressIconFilled;
  }

  if (fiveSecTimer.isReady()) {
    addTempToStack(currentTemp, fiveSecTempChart);
  }

  if (tenSecTimer.isReady()) {
    addTempToStack(currentTemp, tenSecTempChart);
  }

  if (minuteTimer.isReady()) {
    addTempToStack(currentTemp, minuteTempChart);
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

    switch (chartState) {
      case 0:
        drawChartState("1.5m");
        drawTempChart(tempChart);
        calculateStatTemp(tempChart);
        break;
      case 1:
        drawChartState("7m");
        drawTempChart(fiveSecTempChart);
        calculateStatTemp(fiveSecTempChart);
        break;
      case 2:
        drawChartState("14m");
        drawTempChart(tenSecTempChart);
        calculateStatTemp(tenSecTempChart);
        break;
      case 3:
      default:
        drawChartState("1.5h");
        drawTempChart(minuteTempChart);
        calculateStatTemp(minuteTempChart);
        break;
    }

    display.setTextSize(1);
    display.setCursor(0, 16);
    drawStatTemp(maxTemp);
    drawStatTemp(minTemp);

    display.display();
  }

  // Button
  if (btn1.click()) {
    chartState++;
    if (chartState > 3) {
      chartState = 0;
    }
  }

  // delay in between reads for stability
  delay(100);
  isFirstLoop = false;
}