// Libraries
#include <SPI.h>
#include <Wire.h>

// Display SSD1306
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display width and height, in pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_CONTRAST 10 // From 0 to 255 (sets contrast e.g. brightness)

#define OLED_RESET_PIN 4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

boolean withDisplay = false;

// Thermistor
#define SENS_PIN A0
#define T_RESIST 10000 // Resistance on 25°C
#define R_RESIST 10000 // Resister value
#define B_COEF 4300 // B-coefficient
// gray 4300
// wired 3950

// BME280
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

#include "thermistorMinim.h"
// (пин, R термистора, B термистора, базовая температура, R резистора)
thermistor therm(SENS_PIN, T_RESIST, B_COEF, 25, R_RESIST);

#include "timerMinim.h"
timerMinim sensorTimer(1000);
timerMinim fiveSecTimer(5000);
timerMinim tenSecTimer(10000);
timerMinim minuteTimer(60000);

boolean up = true;
int currentTemp = 0;
int previousTemp = currentTemp;
int fiveSecTemp = currentTemp;
int tenSecTemp = currentTemp;
int minuteTemp = currentTemp;


// BME280
float dispTemp;
// byte dispHum;
// int dispPres;

boolean progressIconFilled = false;