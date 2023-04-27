void setup() {
  // Serial.begin(9600);

  // Screen
  // Serial.print(F("Screen SSD1306... "));
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, true, true)) {
    withDisplay = true;
    // Serial.println(F("OK"));
  } else {
    // Serial.println(F("ERROR: Allocation failed"));
    withDisplay = false;
  }

  if (!withDisplay) {
    for(;;); // Don't proceed, loop forever
  }

  // Screen
  // Set display contrast
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(SCREEN_CONTRAST);
  display.setRotation(displayRotation);
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  display.drawBitmap(0, 0, epd_bitmap_allArray[0], 38, 28, DEFAULT_COLOR);
  display.display();
  delay(500);

  // Clear the buffer
  // display.clearDisplay();

  display.setTextSize(1); // Normal 1:1 pixel scale
  display.setTextColor(DEFAULT_COLOR); // Draw white text
  display.setCursor(0, 1); // Start at top-left corner

  display.println(F("       SSD1306....OK"));
  display.display();


  // NTC
  display.print(F("       NTC....."));
  int tempSample = therm.getTempAverage();
  if (tempSample == -71) {
    display.println(F("ERROR"));
  } else {
    display.println(F("...OK"));
  }
  
  
  // BME280
  display.print(F("       BME280.."));
  // Serial.print(F("BME280... "));
  if (bme.begin(BME280_ADDRESS, &Wire) || bme.begin(BME280_ADDRESS_ALTERNATE, &Wire)) {
    display.println(F("...OK"));
    // Serial.println(F("OK"));
  } else {
    display.println(F("ERROR"));
    // Serial.println(F("ERROR"));
  }
  display.display();

  
  // TODO: What is it?
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);
  

  int16_t i;
  for (i = 0; i < graphLength; i++) {
    tempGraph[i] = TEMP_MIN;
  }

  delay(500);

  // Serial.print(F("Start... "));
}