#include <Adafruit_MCP3008.h>
#include <SPI.h>

#define NUM_CHANNELS 8
#define NUM_CHIPS 3

#define WHITE 1600

const int csPins[] = {10, 36, 37};

Adafruit_MCP3008 chips[NUM_CHIPS];
Adafruit_MCP3008 mcp;

/* 

  TO-DO:
  - set detection boundaries (MAX 2047, MIN 0)
  - determine position of respective channels
    - use positions to determine where oob is  

*/

void setup() {
  Serial.begin(9600);
  SPI.begin();
  Serial.println("START");
  mcp.begin(csPins[0]);
  for (int i = 0; i < NUM_CHIPS; i++) {
    if (chips[i].begin(csPins[i])) {
      Serial.print("Chip ");
      Serial.print(i + 1);
      Serial.println(" START");
    }
  }

  
}

void loop() {
  for (int i = 0; i < NUM_CHIPS; i++) {
    Serial.println();
    Serial.print("Chip ");
    Serial.print(i + 1);
    Serial.println();
    for (int j = 0; j < NUM_CHANNELS; j++) {
      int val = chips[i].readADC(j);
      Serial.print("Channel ");
      Serial.print(j);
      Serial.print(": ");
      Serial.println(val);
    }
  }

  int value = mcp.readADC(0);
  Serial.println(value);


  delay(1000);
}