#include <Keyboard.h>

#include <Adafruit_Keypad.h>


const byte ROWS = 4; 
const byte COLS = 4; 

const uint8_t hexaKeys[COLS][ROWS] = {
  {0xF0, 0xF4, 0xF8, 0x46}, // {F13, F17, F21, F(YT FLSCN},
  {0xF1, 0xF5, 0xF9, 0x20}, // {F14, F18, F22, SPACE(YT PSE)},
  {0xF2, 0xF6, 0xFA, 0xD8}, // {F15, F19, F23, LFT(YT RW)},
  {0xF3, 0xF7, 0xFB, 0xD7}  // {F16, F20, F24, RT(YT FF)}
};

byte rowPins[ROWS] = {10, 16, 14, 15}; 
byte colPins[COLS] = {9, 8, 7, 6}; 

Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(hexaKeys), rowPins, colPins, COLS, ROWS); 

void setup(){
  Serial.begin(9600);
  customKeypad.begin();
}
  
void loop() {
  // put your main code here, to run repeatedly:
  customKeypad.tick();

  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    Serial.print(e.bit.KEY);
    if(e.bit.EVENT == KEY_JUST_PRESSED){
      Serial.println(" pressed");
      Keyboard.press(e.bit.KEY);
    }
    else if(e.bit.EVENT == KEY_JUST_RELEASED){
      Serial.println(" released");
      Keyboard.release(e.bit.KEY);
    }
  }
  
  delay(10);
}
