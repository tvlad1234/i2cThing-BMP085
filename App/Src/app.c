#include "main.h"
#include "bmp085.h"

float tempMax, tempMin;
int presMax, presMin;

int main(void)
{
    thingInit();

    if (!bmpBegin(BMP085_STANDARD, thingPort()))
    {
        printf("BMP085 error!\n");
        flushDisplay();
        Error_Handler();
    }
    else
    {
        printf("BMP085 OK!\n");
        flushDisplay();
        tempMin = tempMax = readTemperature();
        presMin = presMax = readPressure() / 100;
        HAL_Delay(1000);
    }

    while (1)
    {
        clearDisplay();
        setCursor(0, 0);

        float temp = readTemperature();
        int pres = readPressure() / 100;

        if (temp > tempMax)
            tempMax = temp;
        if (temp < tempMin)
            tempMin = temp;

        if (pres > presMax)
            presMax = pres;
        if (pres < presMin)
            presMin = pres;

        printf("%.1fC Mx:%.1f Mn:%.1f\n%dhPa Mx:%d\nMn:%d\n", temp, tempMax, tempMin, pres, presMax, presMin);

        if (readButton()) // reset min and max values
        {
            tempMax = temp;
            tempMin = temp;
            presMax = pres;
            presMin = pres;
        }

        flushDisplay();
        HAL_Delay(100);
    }
}