//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are at these valies: 0, 100, 255, 410, 640,
 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 110)  return btnUP; 
 if (adc_key_in < 260)  return btnDOWN; 
 if (adc_key_in < 420)  return btnLEFT; 
 if (adc_key_in < 650)  return btnSELECT;  



 return btnNONE;  // when all others fail, return this...
}

void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Select Start Pos"); // print a simple message

 Serial.begin(9600);
 Serial.print(lcd_key);
 
}
 
void loop()
{
 lcd.setCursor(14,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up


 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("Right       ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("Left        ");
     break;
     }
   case btnUP:
     {
     lcd.print("Middle      ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("None       ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("Next        ");
     break;
     }
     case btnNONE:
     {
     lcd.print("None Chosen ");
     break;
     }
 }

}
