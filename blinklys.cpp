class TrafficLightController {
public:
    void switchLight(int id, int delayTime = 0) // Switches state of LED to HIGH or LOW depending on current state.
    {
        digitalRead(id) == HIGH ? digitalWrite(id, LOW) : digitalWrite(id, HIGH);
        delay(delayTime);
    }

    void blinkLight(int id, int cycles, int delayTime = 0, int blinkDelayTime = 400) // Makes LED blink (n) amount of times.
    {
        for (int i = 0; i < cycles * 2; i++) {
            this->switchLight(id);
            delay(blinkDelayTime);
        }
        delay(delayTime);
    }
};

TrafficLightController TLC;

int redVehicleLight{6}, yellowVehicleLight{5}, greenVehicleLight{4}, redPedestrianLight{3}, greenPedestrianLight{2};

void setup()
{
    for (int i = 1; i <= 6; i++) // Set range of pins to output state.
    {
        pinMode(i, OUTPUT);
    }
    TLC.switchLight(redPedestrianLight);
    TLC.switchLight(greenVehicleLight, 1000);
}


void loop()
{
    for (int i = 4; i <= 6; i++) // Turn vehicle light red.
    {
        TLC.switchLight(i, 1000);
        if (i == yellowVehicleLight) TLC.switchLight(i, 1000);
    }
    delay(1000);

    // Turn Pedestrian light green START
    TLC.switchLight(redPedestrianLight);
    TLC.switchLight(greenPedestrianLight, 7000);
    TLC.blinkLight(greenPedestrianLight, 4, 1000);
    // Turn Pedestrian light green END

    // Turn Pedestrian light red START
    TLC.switchLight(greenPedestrianLight);
    TLC.switchLight(redPedestrianLight, 1500);
    // Turn Pedestrian light red END

    // Turn vehicle light green START
    TLC.switchLight(yellowVehicleLight, 1500);
    TLC.switchLight(redVehicleLight);
    TLC.switchLight(yellowVehicleLight);
    TLC.switchLight(greenVehicleLight, 12000);
    // Turn vehicle light green END
}
