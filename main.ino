#include <IRremote.hpp>
#include "FastLED.h"

#define NUM_LEDS 3
#define DATA_PIN 5  
#define RECV_PIN 2

const int max_delay_speed = 2000;   // max delay speed is 2s
const int max_color_menu = 4;       // current menu range is 4
const int software_debounce = 500;  // software debounce of 0.5s

CRGB leds[NUM_LEDS];
byte  r, g, b;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned int IR_result;
int current_menu_index = 0;   // by default is MIX TROPICAL
int POWER_INDEX = 1;          // by default the power is on
int delaySpeed = 200;         // by default the delay speed is 0.2s

/*
 * IR_result 
 * Power    :     47409
 * Speed    :     15494
 * Up       :     9947
 * Left     :     57515
 * Down     :     7622
 * Right    :     19382
 */

 /*
  * Since this is a simple program, Up and Right will be using as the same function, Down Left will be the same function
  * Power will be used to turn the lights on and off
  * Speed will be used to adjust the light switching speed
  */

int LED_Array[3][3] = {{0,0,0},{0,0,0},{0,0,0}};          // the array is created JUST IN CASE in the future I wanna use it LOL
int COLOR_MENU[max_color_menu] = {1,2,3,4};   // menu list 

/*
 * 1 => MIX TROPICAL
 * 2 => RED
 * 3 => GREEN
 * 4 => BLUE
 */

void saveArray(int row, int red, int green, int blue){
  LED_Array[row][0] = red;
  LED_Array[row][1] = green;
  LED_Array[row][2] = blue;
};

void randomLED(){
  for (int cur = 0; cur < NUM_LEDS; cur++) {
    // chose random value for the r/g/b
    r = random(0, 255);
    g = random(0, 255);
    b = random(0, 255);

    // set the value to the led
    leds[cur] = CRGB (r, g, b);

    // save array 
    saveArray(cur,r,g,b);
    
    // set the colors set into the phisical LED
    FastLED.show();

    // delay 0.2s
    FastLED.delay(delaySpeed);
  }
};

void redTHEME(){
  int colourPalette[8][3] = {
    {102,0,0},
    {153,0,0},
    {204,0,0},
    {255,0,0},
    {255,51,51},
    {255,102,102},
    {255,153,153},
    {255,204,204}
  };

  for (int cur = 0; cur < NUM_LEDS; cur++) {
    int temp = random(8); // choose random colour palette
    r = colourPalette[temp][2];
    g = colourPalette[temp][0];
    b = colourPalette[temp][1];

    // set the value to the led
    leds[cur] = CRGB (r, g, b);

    // save array 
    saveArray(cur,r,g,b);
    
    // set the colors set into the phisical LED
    FastLED.show();

    // delay 0.2s
    FastLED.delay(delaySpeed);
  }
};

void greenTHEME(){
  int colourPalette[8][3] = {
    {102,0,0},
    {153,0,0},
    {204,0,0},
    {255,0,0},
    {255,51,51},
    {255,102,102},
    {255,153,153},
    {255,204,204}
  };

  for (int cur = 0; cur < NUM_LEDS; cur++) {
    int temp = random(8); // choose random colour palette
    r = colourPalette[temp][0];
    g = colourPalette[temp][1];
    b = colourPalette[temp][2];

    // set the value to the led
    leds[cur] = CRGB (r, g, b);

    // save array 
    saveArray(cur,r,g,b);
    
    // set the colors set into the phisical LED
    FastLED.show();

    // delay 0.2s
    FastLED.delay(delaySpeed);
  }
};

void blueTHEME(){
  int colourPalette[8][3] = {
    {102,0,0},
    {153,0,0},
    {204,0,0},
    {255,0,0},
    {255,51,51},
    {255,102,102},
    {255,153,153},
    {255,204,204}
  };

  for (int cur = 0; cur < NUM_LEDS; cur++) {
    int temp = random(8); // choose random colour palette
    r = colourPalette[temp][1];
    g = colourPalette[temp][2];
    b = colourPalette[temp][0];

    // set the value to the led
    leds[cur] = CRGB (r, g, b);

    // save array 
    saveArray(cur,r,g,b);
    
    // set the colors set into the phisical LED
    FastLED.show();

    // delay 0.2s
    FastLED.delay(delaySpeed);
  }
};

void offLED(){
  for (int cur = 0; cur < NUM_LEDS; cur++) {
    leds[cur] = CRGB (0, 0, 0);
    FastLED.show();
  }
}

int manualDecode(unsigned int in){
  if(in == 47409) return 0;         //"Power"
  else if(in == 15494) return 1;    //"Speed"
  else if(in == 9947) return 2;     //"Up"
  else if(in == 57515) return 3;    //"Left"
  else if(in == 7622) return 4;     //"Down"
  else if(in == 19382) return 5;    //"Right"
  else return 6;
};

void debug(){
  Serial.println(" ");
  Serial.print("IR receive: ");
  Serial.print(IR_result);

  Serial.print("| Power Index: ");
  Serial.print(POWER_INDEX);

  Serial.print("| Current Menu Index: ");
  Serial.print(current_menu_index);

  Serial.print("| Delay Speed: ");
  Serial.print(delaySpeed);
}

void setup() { 
     Serial.begin(115200);
  
     FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
     randomSeed(analogRead(0));

    irrecv.enableIRIn();
    irrecv.blink13(true);

    randomLED();
};

void loop() {
  if (irrecv.decode(&results)){
        IR_result = results.value;
        Serial.println(IR_result);
        irrecv.resume();
  }

  else IR_result = 0;

  delay(software_debounce);
  
  switch(manualDecode(IR_result)){
    case 0:
      POWER_INDEX ^= 1; // toggle the value 
      break;

    case 1:
      delaySpeed += 200; 
      if(delaySpeed == max_delay_speed+200) delaySpeed = 200; // wrap around 
      break;

    case 2:
      current_menu_index += 1;
      if(current_menu_index == max_color_menu) current_menu_index = 0; // wrap around 
      break;
      
    case 3:
      current_menu_index += 1;
      if(current_menu_index == max_color_menu) current_menu_index = 0; // wrap around 
      break;

    case 4:
      current_menu_index -= 1;
      if(current_menu_index == -1) current_menu_index = max_color_menu-1; // wrap around 
      break;

    case 5:
      current_menu_index -= 1;
      if(current_menu_index == -1) current_menu_index = max_color_menu-1; // wrap around 
      break;
      
    case 6:
      break;
     
    default:
      break;
  };

  if (POWER_INDEX){
    // if power is on
    
    int currentTheme = COLOR_MENU[current_menu_index];
    
    switch(currentTheme){
      case(1):
        randomLED();
        break;

      case(2):
        redTHEME();
        break;

      case(3):
        greenTHEME();
        break;

      case(4):
        blueTHEME();
        break;
      
      default:
        for (int cur = 0; cur < NUM_LEDS; cur++) {
          leds[cur] = CRGB (255, 255, 255); // white
          saveArray(cur,255,255,255);
          FastLED.show();
          FastLED.delay(delaySpeed);
        }
        break;
    }
  }

  else offLED();
  
  debug();
};
