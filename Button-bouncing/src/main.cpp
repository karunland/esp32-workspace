#include <Arduino.h>
#include <ezButton.h>

/// constants won't change
const int BUTTON_PIN = 14; // the number of the pushbutton pin
const int LED_PIN    = 2; // the number of the LED pin

ezButton button(BUTTON_PIN);  // create ezButton object that attach to pin 7;

// variables will change:
int ledState = LOW;   // the current state of LED

void setup() {
  Serial.begin(9600);         // initialize serial
  pinMode(LED_PIN, OUTPUT);   // set arduino pin to output mode
  button.setDebounceTime(650); // set debounce time to 50 milliseconds
}

void loop() {
  button.loop(); // MUST call the loop() function first

  if(button.isPressed()) {
    Serial.println("The button is pressed");

    // toggle state of LED
    ledState = !ledState;

    // control LED arccoding to the toggleed sate
    digitalWrite(LED_PIN, ledState); 
  }
}




// const int BUTTON_PIN = 14; // Arduino pin connected to button's pin
// const int LED_PIN    = LED_BUILTIN; // Arduino pin connected to LED's pin

// // variables will change:
// int ledState = LOW;     // the current state of LED
// int lastButtonState;    // the previous state of button
// int currentButtonState; // the current state of button

// void setup() {
//   Serial.begin(115200);                // initialize serial
//   pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
//   pinMode(LED_PIN, OUTPUT);          // set arduino pin to output mode

//   currentButtonState = digitalRead(BUTTON_PIN);
// }

// void loop() {
//   lastButtonState    = currentButtonState;      // save the last state
//   currentButtonState = digitalRead(BUTTON_PIN); // read new state

//   if(lastButtonState == HIGH && currentButtonState == LOW) {
//     Serial.println("The button is pressed");

//     // toggle state of LED
//     ledState = !ledState;

//     // control LED arccoding to the toggled state
//     digitalWrite(LED_PIN, ledState); 
//   }
// }




/*
#define BUTTON_PIN 
#define LED_PIN LED_BUILTIN
void setup(void) {

   pinMode(BUTTON_PIN, INPUT_PULLUP);
   pinMode(LED_PIN,OUTPUT);

   Serial.begin(250000);
}

#define STATE_WAIT_KEY  0
#define STATE_CHECK_KEY 1
#define STATE_WAIT_KEY_RELEASE 2

void loop(void) {
static byte state = STATE_WAIT_KEY;
static uint32_t startKeyPress,stopKeyPress;

   byte b = !digitalRead(BUTTON_PIN);          // Pulled up so zero = hit.

   if (state == STATE_WAIT_KEY && b==1) {
      startKeyPress = millis();
      state = STATE_CHECK_KEY;
   }

   // After n milliseconds, is the key still pressed?
   if (state == STATE_CHECK_KEY && ( millis()-startKeyPress) > 30) {
       if (b==1) {
          Serial.print("Key pressed ");   Serial.println(millis());
          state = STATE_WAIT_KEY_RELEASE;
       } else state = STATE_WAIT_KEY;
   }

   if (state == STATE_WAIT_KEY_RELEASE && b==0) state = STATE_WAIT_KEY;
}
*/