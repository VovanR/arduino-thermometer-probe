#include "timerMinim.h"
timerMinim oneSecTimer(1000);
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
byte dispHum;
int dispPres;

boolean progressIconFilled = false;

int graphLength = 84;
int tempGraph[84];