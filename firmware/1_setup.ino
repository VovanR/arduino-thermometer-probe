void setup() {
  Serial.begin(9600);

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

  // Screen
  if (withDisplay) {
    // Set display contrast
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(SCREEN_CONTRAST);
    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(500);
  
    // Clear the buffer
    display.clearDisplay();
  }
  
  
  // BME280
  display.print(F("BME280... "));
  // Serial.print(F("BME280... "));
  if (bme.begin(BME280_ADDRESS, &Wire) || bme.begin(BME280_ADDRESS_ALTERNATE, &Wire)) {
    display.println(F("OK"));
    // Serial.println(F("OK"));
  } else {
    display.println(F("ERROR"));
    // Serial.println(F("ERROR"));
  }

  
  // TODO: What is it?
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);
  
  Serial.print(F("Start... "));
}