#include <Keypad.h>
#include <EEPROM.h>


unsigned long interval;
int vector[30];

const byte ROWS = 4;
const byte COLS = 3;

byte rowPins[ROWS] = {A3, A2, A1, A0};
byte colPins[COLS] = {13, 12, 11} ;//1-A0; 2-A1; 3-7; 4-6;...


const byte sensor =  10;
const byte difuzor = 6;
const byte modificare = 4;//enter in mode to change the timer


byte addr = 0;
byte value;
byte i;

boolean activat = 1;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);
  pinMode(modificare, INPUT);
  pinMode(difuzor, OUTPUT);
  digitalWrite(modificare, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  if ( !digitalRead(modificare) ) {
    activat = 0 ;
  }

  if (activat == 1) {
    value = EEPROM.read(addr);
    if ( value > 0 )
      interval = value;
    interval = interval * 1000;
    if (millis() > interval) {

      if (digitalRead(sensor) == HIGH) {
        Serial.println("Semnal");
        tone(difuzor, 4300);

      }
      else {
        Serial.println("        ");
        tone(difuzor, 7500000);
      }
    }
  }



  if (activat == 0) {
    char key = kpd.getKey();

    if (key) {
      if (key == 42)//* reset timp
        activat = 1;
      if (key == 35)//#
        vector[i] = 100;
      if (key == 48)//0
        vector[i] = 0;
      if (key == 49)//1
        vector[i] = 1;
      if (key == 50)//2
        vector[i] = 2;
      if (key == 51)//3
        vector[i] = 3;
      if (key == 52)//4
        vector[i] = 4;
      if (key == 53)//5
        vector[i] = 5;
      if (key == 54)//6
        vector[i] = 6;
      if (key == 55)//7
        vector[i] = 7;
      if (key == 56)//8
        vector[i] = 8;
      if (key == 57)//9
        vector[i] = 9;

      interval = interval * 10 + vector[i];
      i++;

      if (vector[i - 1] == 90) {
        interval = 0;
        for (int j = 0; j <= i; i++) {
          vector[j] = 0;
        }
      }
    }
    if ( interval <= 255)
      EEPROM.write(addr, interval);
  }

}
