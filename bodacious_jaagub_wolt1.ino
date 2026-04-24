#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD & Servo
LiquidCrystal_I2C lcd(0x27,16,2);
Servo sprinkler;

// Pin
int pumpPin = 9;
int potPin = A0;

// Servo
int angle = 20;
int direction = 1;

void setup() {
  pinMode(pumpPin, OUTPUT);

  sprinkler.attach(10);

  lcd.init();
  lcd.backlight();
}

void loop() {

  // ===== POTENSIOMETER =====
  int pot = analogRead(potPin);
  int pwm = map(pot, 0, 1023, 0, 255);

  // Motor
  analogWrite(pumpPin, pwm);

  // ===== SERVO SWEEP =====
  angle += direction;

  if(angle >= 120) direction = -1;
  if(angle <= 20) direction = 1;

  sprinkler.write(angle);

  // ===== LCD =====
  lcd.setCursor(0,0);
  lcd.print("Penyiram Auto");

  lcd.setCursor(0,1);
  lcd.print("Pump: ");
  lcd.print(map(pwm,0,255,0,100));
  lcd.print("%   ");

  delay(30);
}