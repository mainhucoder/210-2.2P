const int ledPin = LED_BUILTIN; // Built-in LED pin
const int buttonPin = 2;       // Push button pin

const long dotDuration = 250;  // Duration of a dot in milliseconds
const long dashDuration = dotDuration * 3; // Duration of a dash

const char morseCode[][4] = {
  "..-",   // U
  "-..",   // D
  ".-",    // A
  "-.--"   // Y
};


int currentLetter = 0;
bool blinking = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // Button pressed
    if (!blinking) {
      blinking = true;
      blinkName();
    }
    else {
      blinking = false;
      digitalWrite(ledPin, LOW); // Turn off LED
    }
    delay(300); // Debounce delay
  }
}

void blinkName() {
  while (blinking) {
    char letter = morseCode[currentLetter][0];
    if (letter == '\0') {
      currentLetter = 0;
      delay(1000); // Pause between repetitions
    } else {
      for (int i = 1; morseCode[currentLetter][i] != '\0'; i++) {
        digitalWrite(ledPin, HIGH); // Turn on LED
        if (morseCode[currentLetter][i] == '.') {
          delay(dotDuration);
        } else if (morseCode[currentLetter][i] == '-') {
          delay(dashDuration);
        }
        digitalWrite(ledPin, LOW); // Turn off LED
        delay(dotDuration); // Inter-element gap
      }
      delay(dashDuration); // Inter-letter gap
      currentLetter++;
    }
  }
}
