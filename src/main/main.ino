#include <Adafruit_MCP3008.h>
#include <SPI.h>

#define NUM_CHANNELS 8
#define NUM_CHIPS 2

#define WHITE_THRESHOLD 450

const int csPins[] = {10, 36};

Adafruit_MCP3008 chips[NUM_CHIPS];
Adafruit_MCP3008 mcp;

typedef struct {
  int index;
  int value;
} ColourSensor;

float channels[NUM_CHANNELS * NUM_CHIPS];


/* 

  TO-DO:
  - set detection boundaries (MAX 2047, MIN 0)
  - determine position of respective channels
    - use positions to determine where oob is  

*/

// RIGHT: 5, 4, 3, 2
// 


void print_arr(float* arr, int arr_len) {
  for (int i = 0; i < arr_len; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(arr[i]);
    Serial.print(' ');
  }
  Serial.println();
}

void print_arr_for_emulation(float* arr, int arr_len){
  Serial.print("[ ");
  for (int i = 0; i < arr_len; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.print("]");
  Serial.println(); 
}

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

  for (int i = 0; i < NUM_CHIPS * NUM_CHANNELS; i++) {
    channels[i] = 0;
  }
}

void loop() {
  for (int i = 0; i < NUM_CHIPS; i++) {
    for (int j = 0; j < NUM_CHANNELS; j++) {
      float val = chips[i].readADC(j);
      channels[NUM_CHANNELS * i + j] = map(val, 0, 1023, 0, 1);
    }
  }

  print_arr_for_emulation(channels, NUM_CHANNELS * NUM_CHIPS);


  delay(50);
}