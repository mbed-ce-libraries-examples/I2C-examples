#include "mbed.h"

DigitalOut led(LED1);

/* Set your own pins if necessary. */
I2C i2c(I2C_SDA, I2C_SCL);

void ScanI2C(I2C *i2c){
    printf("I2C scanner\n   ");
    for (int i = 0; i < 16; i++) printf(" %02X", i);
    printf("\n");

    for (int y = 0x0; y < 0x80; y += 0x10)
    {
        printf("%02X: ", y);
        for (int x = 0; x < 16; x++)
        {
            int addr = y + x;
            if(addr < 3) printf("   ");
            else if (addr > 0x77)
            {
                printf("\n");
                break;
            }
            else if(i2c->write(addr<<1, nullptr, 0) == I2C::ACK) printf("%02X ", addr);
            else  printf("-- ");
        }
        printf("\n");
    }
}


/** The result in a serial terminal will be something like below
 * 
 * I2C scanner
 *     00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
 * 00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * 10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * 20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * 30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * 40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * 50: 50 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * 60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
 * 70: -- -- -- -- -- -- -- -- 
 * 
 * How we can see the function gets possitive answer (ACK) at 
 * address 0x50h (7bit) what is corresponding to 0xA0h (0x50 << 1).
 */

int main()
{
    /* Set frequency if necessary - 100000 or 400000 or 1000000. */
    i2c.frequency(100000);

    /* Call bus scanner */
    ScanI2C(&i2c);

    printf("Endless blinky loop\n");
    while (1) {
        thread_sleep_for(1000);
        led = !led;
    }
}
