#include "LiquidCrystal.h"

LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

int buttonPins[] = {8, 9, 10, 11};

int previousResult {-1};

__attribute__((unused)) void setup()
{
    for (const int pin: buttonPins) pinMode(pin, INPUT); // Set button pins to INPUT mode.
    lcd.setCursor(0, 0);
}

__attribute__((unused)) void loop()
{
    int i {0}, result {0};
    for (const int pin: buttonPins)
    {
        bool buttonPressed = digitalRead(pin); // Check if button is pressed.

        if (buttonPressed) result += (int) pow(2, i); // Convert binary to decimal.
        if (i >= 2 && buttonPressed) result += 1; // Fixes issue when more than 2 bits are used.

        i++;
    }

    if (result != previousResult) // Only update lcd if the answer is updated.
    {
        lcd.clear();
        lcd.print(result);
    }
    previousResult = result;
    delay(50); // Prevent program from eating all available memory.
}
