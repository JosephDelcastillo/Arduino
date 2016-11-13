#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);  

int keypad_pin = A0;
int keypad_value = 0;
int keypad_value_old = 0;

char btn_push;

byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 4;

byte SecondMenuPage = 1;
byte SecondMenuPageOld = 1;
byte SecondMenuTotal = 4;

void setup()
{
    lcd.begin(16,2);  //Initialize a 2x16 type LCD
    
    MainMenuDisplay();
    delay(1000);
}
void loop()
{
    btn_push = ReadKeypad();
    
    MainMenuBtn();
    
    if(btn_push == 'S')//enter selected menu
    {
        WaitBtnRelease();
        switch (mainMenuPage)
        {
            case 1:
              None1();
              break;
            case 2:
              Left1();
              break;
            case 3:
              Middle1();
              break;
            case 4:
              Right1();
              break;
        }

          MainMenuDisplay();
          WaitBtnRelease();

        WaitBtnRelease();
        switch (SecondMenuPage)
        {
            case 1:
              None2();
              break;
            case 2:
              Left2();
              break;
            case 3:
              Middle2();
              break;
            case 4:
              Right2();
              break;
        }  
        SecondMenuDisplay();
        WaitBtnRelease();
    }
    


    delay(10);
  
}//--------------- End of loop() loop ---------------------
void None1()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Start At None");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for None here
       delay(2500);
       SecondMenuDisplay();
    }
}

void None2()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finish At None");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for None here
       delay(1000);
       
    }
}

void Left1()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Start At Left");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Left here
       delay(2500);
       SecondMenuDisplay();
    }
}

void Left2()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finish At Left");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Left here
       delay(1000);
       
    }
}

void Middle1()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Start At Middle");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Middle here
       delay(2500);
       SecondMenuDisplay();
    }
}

void Middle2()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finish At Middle");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Middle here
       delay(1000);
       
    }
}

void Right1()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Start At Right");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Right here
       delay(2500);
       SecondMenuDisplay();
    }
}

void Right2()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finish At Right");
    
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Right here
       delay(1000);
       
    }
}


void MainMenuDisplay()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select Start Pos");
    lcd.setCursor(0,1);
    switch (mainMenuPage)
    {
        case 1:
          lcd.print("None");
          break;
        case 2:
          lcd.print("Left");
          break;
        case 3:
          lcd.print("Middle");
          break;
        case 4:
          lcd.print("Right");
          break;
    }
}

void SecondMenuDisplay()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select Fin Pos");
    lcd.setCursor(0,1);
    switch (SecondMenuPage)
    {
        case 1:
          lcd.print("None");
          break;
        case 2:
          lcd.print("Left");
          break;
        case 3:
          lcd.print("Middle");
          break;
        case 4:
          lcd.print("Right");
          break;
    }
}

void MainMenuBtn()
{
    WaitBtnRelease();
    if(btn_push == 'U')
    {
        mainMenuPage++;
        if(mainMenuPage > mainMenuTotal)
          mainMenuPage = 1;
    }
    else if(btn_push == 'D')
    {
        mainMenuPage--;
        if(mainMenuPage == 0)
          mainMenuPage = mainMenuTotal;    
    }
    
    if(mainMenuPage != mainMenuPageOld) //only update display when page change
    {
        MainMenuDisplay();
        mainMenuPageOld = mainMenuPage;
    }
    
}

void SecondMenuBtn()
{
    WaitBtnRelease();
    if(btn_push == 'U')
    {
        SecondMenuPage++;
        if(SecondMenuPage > SecondMenuTotal)
          SecondMenuPage = 1;
    }
    else if(btn_push == 'D')
    {
        SecondMenuPage--;
        if(SecondMenuPage == 0)
          SecondMenuPage = SecondMenuTotal;    
    }
    
    if(SecondMenuPage != SecondMenuPageOld) //only update display when page change
    {
        SecondMenuDisplay();
        SecondMenuPageOld = SecondMenuPage;
    }
    
}

char ReadKeypad()
{
  /* Keypad button analog Value
  no button pressed 1023
  select  741
  left    503
  down    326
  up      142
  right   0 
  */
  keypad_value = analogRead(keypad_pin);
  
  if(keypad_value < 100)
    return 'R';
  else if(keypad_value < 200)
    return 'U';
  else if(keypad_value < 400)
    return 'D';
  else if(keypad_value < 600)
    return 'L';
  else if(keypad_value < 800)
    return 'S';
  else 
    return 'N';

}

void WaitBtnRelease()
{
    while( analogRead(keypad_pin) < 800){} 
}
