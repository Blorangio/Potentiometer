/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/admin/Documents/CTD_2023/Personal_Projects/Potentiometer/src/Potentiometer.ino"
void initialize(pin_t PIN);
void on();
void off();
void vTog(bool iVal);
void initialize(pin_t PIN);
void update();
void initialize(pin_t PIN);
void update();
void update();
void setup();
void loop();
#line 1 "/Users/admin/Documents/CTD_2023/Personal_Projects/Potentiometer/src/Potentiometer.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
#include <functional>
#include <vector>
typedef std::function<void()> VoidFunc;
typedef std::vector<VoidFunc> FuncVector;
FuncVector updates;
class LED
{
public:
  bool val = false;
  pin_t pin;
  void initialize(pin_t PIN)
  {
    pin = PIN;
    pinMode(pin, OUTPUT);
  }
  void on()
  {
    val = true;
    digitalWrite(pin, HIGH);
  }
  void off()
  {
    val = false;
    digitalWrite(pin, LOW);
  }
  void vTog(bool iVal)
  {
    val = iVal;
    if (val)
    {
      digitalWrite(pin, HIGH);
    }
    else
    {
      digitalWrite(pin, LOW);
    }
  }
};
class Button
{
public:
  bool bDown = false;
  bool val = false;
  bool clicked = false;
  pin_t pin;
  void initialize(pin_t PIN)
  {
    updates.push_back(std::bind(&Button::update, this));
    pin = PIN;
    pinMode(pin, INPUT);
  }
  bool once = true;
  void update()
  {
    clicked = false;
    pinMode(pin, INPUT);
    if (digitalRead(pin) == HIGH && !bDown)
    {
      bDown = true;
      if (once)
      {
        clicked = true;
        once = false;
      }
      val = !val;
    }
    if (digitalRead(pin) == LOW)
    {
      bDown = false;
      once = true;
    }
  }
};
class Potentiometer
{
public:
  pin_t pin;
  void initialize(pin_t PIN)
  {
    pin = PIN;
    pinMode(pin, INPUT);
    updates.push_back(std::bind(&Potentiometer::update, this));
  }
  int val = analogRead(pin);
  void update()
  {
    val = analogRead(pin);
  }
};

LED lights[5];
pin_t pins[5] = {D0, D1, D2, D3, D4};
Potentiometer p1;

void update()
{
  for (uint i = 0; i < updates.size(); i++)
  {
    updates[i]();
  }
}

void setup()
{
  for (int i = 0; i < 5; i++)
  {
    lights[i].initialize(pins[i]);
  }
  p1.initialize(A4);
  Serial.begin(9600);
}
void loop()
{
  update();
  float leds = p1.val*6 /4095;
  for (int i = 0; i < 5; i++)
  {
    lights[i].off();
  }
  for (int i = 0; i < leds; i++)
  {
    lights[i].on();
  }
}