#include <LiquidCrystal.h>

const int rs = 2;
const int en = 3;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int aqi_sensor = A0;
const int green_led = 8;
const int blue_led = 9;
const int red_led = 10;
const int buzzer = 11;

int aqi_ppm = 0;

void setup() {
  pinMode(aqi_sensor, INPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);
  digitalWrite(red_led, LOW);
  digitalWrite(buzzer, LOW);

  Serial.begin(9600);
  lcd.clear();
  lcd.begin(16, 2);

  Serial.println("AQI Alert System");
  lcd.setCursor(0, 0);
  lcd.print("AQI Alert System");
  delay(1000);
}

void loop() {
  aqi_ppm = analogRead(aqi_sensor);
  Serial.print("Air Quality:");
  Serial.println(aqi_ppm);

  lcd.setCursor(0, 0);
  lcd.print("Air Quality:");
  lcd.print(aqi_ppm);

  if ((aqi_ppm >= 0) && (aqi_ppm <= 400)) {
    lcd.setCursor(0, 1);
    lcd.print("AQI Good");
    Serial.println("AQI Good");

    digitalWrite(green_led, HIGH);
    digitalWrite(blue_led, LOW);
    digitalWrite(red_led, LOW);
    noTone(buzzer);
  } else if ((aqi_ppm >= 401) && (aqi_ppm <= 700)) {
    lcd.setCursor(0, 1);
    lcd.print("AQI Moderate");
    Serial.println("AQI Moderate");
    tone(buzzer, 1000, 200);
    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, HIGH);
    digitalWrite(red_led, LOW);
  } else if ((aqi_ppm >= 701) && (aqi_ppm <= 2000)) {
    lcd.setCursor(0, 1);
    lcd.print("AQI Unhealthy");
    Serial.println("AQI Unhealthy");
    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, HIGH);
    digitalWrite(red_led, LOW);
    noTone(buzzer);
  } else if ((aqi_ppm >= 2001) && (aqi_ppm <= 5000)) {
    lcd.setCursor(0, 1);
    lcd.print("AQI V.Unhealthy");
    Serial.println("AQI V.Unhealthy");
    digitalWrite(green_led, LOW);
    tone(buzzer, 1000, 200);
    digitalWrite(blue_led, LOW);
    digitalWrite(red_led, HIGH);
  } else if (aqi_ppm > 5000) {
    lcd.setCursor(0, 1);
    lcd.print("AQI Hazardous");
    Serial.println("AQI Hazardous");

    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, LOW);
    digitalWrite(red_led, HIGH);
    tone(buzzer, 1000, 500);
  }
  delay(700);
}
