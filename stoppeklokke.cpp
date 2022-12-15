// In general code should be self explanatory and complex statements that might be hard to understand should be explained with a comment.
// Even tho it is bad practice I will write comments more frequently here to display that I understand what the code I write does in detail so the reviewer can assess me.
// If there is code that repeat something that is explained previously it will not be commented again.

// Include library with methods to use the lcd display.
#include "LiquidCrystal.h"

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates instance of LiquidCrystal object with the used pin numbers on the Arduino.

// Declares three variables with the integer data type.
const int startStopButtonPin{9}, resetButton{10}; // Create two constant variables with the type of integer, the const keyword prevents anyone form overwriting them.
int recordedMinutes; // First and second variable is referencing the pin number of the button components used to start / stop and reset the display.
float recordedTimeInSeconds = 0; // Declare variable with the floating point value data type.

bool startStopButtonHasBeenPressed = false; // Declare variable with the boolean data type.

// The setup function is the first function that will be executed after booting the arduino.
__attribute__((unused)) void setup() { // Applying the unused attribute to decorate the function declaration so my code highlighter don't complain about it being unused.
    for (int i = 9; i <= 10; i++) pinMode(i, INPUT); // Set button pins 9 and 10 to INPUT mode with a for loop.
    lcd.setCursor(5, 0); // Uses the setCursor method from the LiquidCrystal object to set the cursor 5 spaces forward.
    lcd.print("0:0.00"); // Uses the print method from the LiquidCrystal object to print the string value passed to the lcd screen.
}

// The loop function will run after the setup function has been executed and will loop until the arduinos power is cut.
__attribute__((unused)) void loop() {
    lcd.setCursor(5, 0);
    if (digitalRead(resetButton)) // Reads the status of the resetButton pin and then resets the timer if it detects that the reset button is pressed.
    {
        recordedTimeInSeconds = 0, recordedMinutes = 0; // Resetting the values storing the currently counted secondes and minutes.
        lcd.clear(); // Uses the clear method from the LiquidCrystal object removing any value currently written on the screen.
        lcd.setCursor(5, 0);
        lcd.print((String) recordedMinutes + ":" + (String) recordedTimeInSeconds); // Updates LCD with: 0:0.0
        delay(500); // The delay function blocks the thread for x amount of milliseconds making the entire program pause for x amount of time.
    }

    if (digitalRead(startStopButtonPin)) // Detect if the 'start / stop' button has been pressed.
    {
        startStopButtonHasBeenPressed = true;
        delay(500);
    }
    while (startStopButtonHasBeenPressed) { // Makes the stop watch keep running until the stop button is pressed.
        if (startStopButtonHasBeenPressed) // Start or stop stopwatch when button is pressed.
        {
            if (recordedTimeInSeconds >= 59.8) // Convert seconds to minutes, it is inaccurate by 20 ms beacuse the display is not responding fast enough.
            {
                tone(1, 2000); // Make a tone to warn the user that a minute has passed by.
                recordedTimeInSeconds = 0; // Sets the second counter back to 0.
                recordedMinutes++; // Adds a minute to the minute counter.
                delay(100); // Make the tone ring for 200 ms adding the delay after the if statement.
            }
            delay(100);
            if (recordedTimeInSeconds == 0) noTone(1);

            recordedTimeInSeconds += 0.1; // Adding 100 ms to recorded time.
            lcd.clear();
            lcd.setCursor(5, 0);

            lcd.print((String) recordedMinutes + ":" + (String) recordedTimeInSeconds); // Type casting recordedMinutes and recordedTimeInSeconds to the type of string to print the values to the lcd screen.

            if (digitalRead(startStopButtonPin)) { // Detect if user is pressing button to stop.
                startStopButtonHasBeenPressed = false;
                delay(500);
            }
        }
    }
    delay(50); // Prevent program from eating all available memory when the arduino idling.
}
