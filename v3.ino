#include <SPI.h>

#include <LiquidCrystal.h>
#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

LiquidCrystal lcd(8,9,4,5,6,7);

const int keypad_pin = A0;

byte current_menu = 0;    // index of the active menu
byte current_option = 0;  // index of the active item within the menu
int selections[2] = {};   // holds "locked in" (selected) menu options

// contains the prompt title and the affirmation title of each menu
const char* titles[][2] = {
    { "Start Pos", "Start at " },
    { "Fin Post", "Finish at " }
};
// contains the options for each menu
const char* menus[][4] = {
    { "None", "Left", "Middle", "Right" }, // first menu
    { "None", "Left", "Middle", "Right" }  // second menu
};

// flag to indicate when we've exhausted all the menus; when true, the
// main loop will stop computing.
boolean finished = false;

void setup() {
  // initialize a 2x16 LCD screen
  lcd.begin(16, 2);
}

void loop() {
  if (!finished) {
    // read the button that was pressed
    char button_pressed = ReadKeyPad();
    Serial.println("Button pressed: " + button_pressed);
    
    // update the model (current option, current menu, etc.), then render
    switch(button_pressed) {
      case 'U':
        current_option = Wrap(current_option + 1, NELEMS(menus[current_menu]));
        Render(titles[current_menu][0], menus[current_menu][current_option]);
        break;
      case 'D':
        current_option = Wrap(current_option - 1, NELEMS(menus[current_menu]));
        Render(titles[current_menu][0], menus[current_menu][current_option]);
        break;
      case 'S':
        selections[current_menu] = current_option; // store the selection
        
        // There's no easy way to combine string constants in C. One solution
        // solution is to allocate a new string (char array), copy the first
        // string onto it, and then cat (concatenate) all the other strings.
        char title[20]; // allocate an array that can hold up to 20 characters
        strcpy(title, titles[current_menu][1]);
        strcat(title, menus[current_menu][current_option]);
        
        // Show our recently-created affirmation message
        RenderSingle(title);
        delay(1000);
        
        current_menu++;
        current_option = 0;
        if (current_menu > NELEMS(menus)) {
          // We've gone through all the menus. Because there's no way to
          // end the loop, we instead update the "finished" flag to stop
          // the loop from performing anything else. We also exit the
          // function early to skip the rendering that happens later.
          // TODO: do something with the results
          Serial.println("Finished");
          finished = true;
          return;
        }
    }
    
    delay(10);
  }
}

char ReadKeyPad() {
  // keypad button analog value
  // 1023   No button
  // 741    Select
  // 503    Left
  // 326    Down
  // 142    Up
  // 0      Right
  int keypad_value = analogRead(keypad_pin);
  
  // wait for the button to be released
  while(analogRead(keypad_pin) < 800){}
  
  // map the analog value to the matching key
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

// Returns 0 if the number has exceeded the maximum and returns
// the maximum if the number is below 0.
int Wrap(int number, int maximum) {
  if (current_option > maximum) {
    return 0;
  } else if (current_option < maximum) {
    return maximum;
  } else {
    return number; // in range, no need to wrap
  }
}

// Clears the LCD and prints one line
void RenderSingle(const char* line) {
  Render(line, "");
}

// Clears the LCD and prints two lines
void Render(const char* line1, const char* line2) {
  lcd.clear();
  
  // print the top line
  lcd.setCursor(0,0);
  lcd.print(line1);
  
  // print the bottom line
  lcd.setCursor(0,1);
  lcd.print(line2);
}
