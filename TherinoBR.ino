#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>
#include "Ultrasonic.h"

const PROGMEM uint8_t tick[16 * 16 / 8] = 
{0x00,0x80,0xC0,0xE0,0xC0,0x80,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0x78,0x30,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x1F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00};
                                                                                                                             
const PROGMEM uint8_t cross[16 * 16 / 8] = 
{0x00,0x0C,0x1C,0x3C,0x78,0xF0,0xE0,0xC0,0xE0,0xF0,0x78,0x3C,0x1C,0x0C,0x00,0x00,0x00,0x30,0x38,0x3C,0x1E,0x0F,0x07,0x03,0x07,0x0F,0x1E,0x3C,0x38,0x30,0x00,0x00};
 

LCD_SSD1306 lcd; 


const int pino_trigger = 12;
const int pino_echo = 13;

Ultrasonic sensor_ultrassonico(pino_trigger, pino_echo);


int distancia_cm;

void setup() {


    lcd.setFontSize(FONT_SIZE_SMALL);
    lcd.println("NightDev");

    
    lcd.setFontSize(FONT_SIZE_LARGE);
    lcd.println("Therino");
    delay(1000); 
    lcd.setCursor(40, 6); 
    lcd.draw(tick, 16, 16); 
    
    lcd.setCursor(72, 6); 
    lcd.draw(cross, 16, 16); 
    delay(4000); 
    lcd.clear();
    lcd.setFontSize(FONT_SIZE_MEDIUM);
    lcd.println("Iniciando...");
    lcd.setFontSize(FONT_SIZE_SMALL);
    lcd.println("Feito por Nightt");
    lcd.println("tDev");
    delay(2000); 
}

void loop() {
  medir_distancia();
  lcd.clear();
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.setCursor(0, 0);
  lcd.print("cent >  ");
  lcd.print(distancia_cm);
  lcd.println("cm");  
  lcd.print("mili >  ");
  lcd.print(distancia_cm * 10);  
  lcd.println("mm");

  delay(100);

}

void medir_distancia() {
  digitalWrite(pino_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pino_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pino_trigger, LOW);

  distancia_cm = sensor_ultrassonico.Ranging(CM);
  int distancia_mm = distancia_cm * 10;

}
