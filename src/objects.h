void led_blink1(int j)
{
    analogWrite(led[0], 200);
    for (int increment = 0; increment < 255; increment += +5)
    {
        analogWrite(led[j], increment);
        delay(10);
        if (second_count())
            oled_print();
    }
    for (int increment = 255; increment > 0; increment += -5)
    {
        analogWrite(led[j], increment);
        delay(10);
        if (second_count())
            oled_print();
    }
    analogWrite(led[j], 0);
}

void led_blink2()
{
    analogWrite(led[0], 200);
    for (int f = 1; f < 4; f++)
        for (int j = 1; j < 4; j++)
        {
            for (int i = 0; i < 255; i = i + 5)
            {
                analogWrite(led[j], i);
                analogWrite(led[f], i);
                delay(10);
            }
            for (int i = 255; i > 0; i = i - 5)
            {
                analogWrite(led[j], i);
                analogWrite(led[f], i);
                delay(10);
            }
        }
    for (int j = 0; j < 4; j++)
        analogWrite(led[j], 0);
}