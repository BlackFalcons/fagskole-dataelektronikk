// Fotgjenger
int r_1 = 2;
int y_1 = 3;
int g_1 = 4;

// Bilister
int r_2 = 8;
int y_2 = 9;
int g_2 = 10;

void setup ()
{
// Fotgjenger
    for (int i = 0; i < 4; i++)
    {
        pinMode (i, OUTPUT);
    }

// Bilister
    for (int i = 8; i < 11; i++)
    {
        pinMode (i, OUTPUT);
    }
}

void loop ()
{
//Bilister er rød, fotgjenger er grønn
    digitalWrite(r_1, HIGH);
    digitalWrite(g_2, HIGH);

    digitalWrite(y_1, LOW);
    digitalWrite(y_2, LOW);
    delay(3000);

//Endring mot bilister blir rød, fotgjenger blir grønn
    digitalWrite(y_1, HIGH);
    digitalWrite(y_2, HIGH);
    digitalWrite(g_2, LOW);
    delay(3000);

//bilister er grønn, fotgjenger er rød
    digitalWrite(g_1, HIGH);
    digitalWrite(y_1, LOW);
    digitalWrite(r_1, LOW);
    digitalWrite(y_2, LOW);
    digitalWrite(r_2, HIGH);
    delay(3000);

    digitalWrite(y_2, HIGH);
    digitalWrite(g_1, LOW);
    digitalWrite(y_1, HIGH);

    delay(3000);

    digitalWrite(r_2, LOW); //slå av rød, for loop starter
    digitalWrite(y_2, LOW); //slå av gul før loop starter
    digitalWrite(g_2, HIGH);
    delay(3000);
}
