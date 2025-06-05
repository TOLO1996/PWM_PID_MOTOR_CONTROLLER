
#include "icp.h"
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated
// constants won't change:
const long interval = 100;  // interval at which to blink (milliseconds)
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ICP_INIT();
  Serial.print("Wait for upload")
  delay(2000)
}
void loop() {
  ICP_ON();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    //Print values once for 100ms
    previousMillis = currentMillis;
    Serial.print(T);
    Serial.print("    ");
    Serial.print(edge);
    Serial.print("    ");
    Serial.println(T1OVF_Counter);
  }
}