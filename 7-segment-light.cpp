class SegmentDisplayHandler {
public:
    static void clearDisplay(const int displayPins[8])
    {
        for (unsigned int i = 0; i < 8; i++) digitalWrite(displayPins[i], LOW);
    };

    static void displayHex(const int displayPins[8], int num)
    {
        const byte hexValue[16]
        {
            B00111111, // 0
            B00000110, // 1
            B01011011, // 2
            B01001111, // 3
            B01100110, // 4
            B01101101, // 5
            B01111101, // 6
            B00000111, // 7
            B01111111, // 8
            B01100111, // 9
            B01110111, // A
            B01111100, // B
            B00111001, // C
            B01011110, // D
            B01111001, // E
            B01110001, // F
        };
        SegmentDisplayHandler::clearDisplay(displayPins);
        for (int i = 0; i < 8; i++) if (bitRead(hexValue[num], i)) digitalWrite(displayPins[i], HIGH); // Write hexadecimal to segmented display.
    }

};

int buttonPins[] = {10, 11, 12, 13};
int segmentedDisplayPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int previousResult {-1};

__attribute__((unused)) void setup()
{
    for (const int pin: buttonPins) pinMode(pin, INPUT); // Set button pins to INPUT mode.
    for (const int pin: segmentedDisplayPins) pinMode(pin, OUTPUT);
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

    if (result != previousResult) SegmentDisplayHandler::displayHex(segmentedDisplayPins, result); // Only update lcd if the answer is updated.
    previousResult = result;
    delay(50); // Prevent program from eating all available memory.
}
