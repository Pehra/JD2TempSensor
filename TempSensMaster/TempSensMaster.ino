#include "TempSens.h"
TempSens TempSens_0;

void setup() {
  TempSens_0.liveRead(50);

}

void loop() {
  TempSens_0.testOled();
}
