const int ledPin = LED_BUILTIN;   // Pin for the built-in LED
const int buttonPin = 2;         // Pin for the push button

const long dotDuration = 250;    // Duration of a dot in milliseconds
const long dashDuration = dotDuration * 3; // Duration of a dash

const char morseCode[][4] = {
  "..-",   // U (U stands for "..-" in Morse code)
  "-..",   // D (D stands for "-.." in Morse code)
  ".-",    // A (A stands for ".-" in Morse code)
  "-.--"   // Y (Y stands for "-.--" in Morse code)
};

int currentLetter = 0;    // Index of the current letter being blinked
bool blinking = false;    // Flag to control blinking state

void setup() {
  pinMode(ledPin, OUTPUT);      // Set LED pin as output
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // Check if button is pressed
    if (!blinking) {
      blinking = true;       // Start blinking if not already blinking
      blinkName();
    } else {
      blinking = false;      // Stop blinking if already blinking
      digitalWrite(ledPin, LOW); // Turn off LED
    }
    delay(300); // Debounce delay to prevent rapid toggling
  }
}

void blinkName() {
  while (blinking) {
    char letter = morseCode[currentLetter][0];
    if (letter == '\0') {
      currentLetter = 0;     // Reset to the first letter after completing the name
      delay(1000);           // Pause between repetitions
    } else {
      for (int i = 1; morseCode[currentLetter][i] != '\0'; i++) {
        digitalWrite(ledPin, HIGH); // Turn on LED for dot/dash
        if (morseCode[currentLetter][i] == '.') {
          delay(dotDuration);
        } else if (morseCode[currentLetter][i] == '-') {
          delay(dashDuration);
        }
        digitalWrite(ledPin, LOW);  // Turn off LED after dot/dash
        delay(dotDuration);          // Gap between dots/dashes
      }
      delay(dashDuration);           // Gap between letters
      currentLetter++;               // Move to the next letter
    }
  }
}
