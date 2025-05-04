#include "mbed.h"

DigitalOut led(LED1);

/* Set your own pins if necessary. */
I2C i2c(I2C_SDA, I2C_SCL);

/* Set i2c slave address of your slave device.
In this case we use Slave address in context of I2C Slave example */
/* Real address is 7bit 0x50 + one bit of dirrection (read/write) 
and that brings us to 0xA0 for write and 0xA1 for read. However this
is not like single byte version and direction bit is controlled by I2C driver */
const int addr = 0xA0; // already bitshifted address


int main()
{
    printf("I2C Master example\n");
    thread_sleep_for(1000);

    /* Set frequency if necessary - 100000 or 400000 or 1000000. */
    i2c.frequency(100000);

    /* Write a buffer to a Slave device */
    char msg[] = "Master!";
    if(i2c.write(addr, msg, strlen(msg)) == I2C::ACK){
        printf("Write ACK\n");
    } else {
        printf("Write NACK\n");
    }

    thread_sleep_for(1000);

    /* Read a buffer from a Slave device */
    /* We should always know how many bytes we want to read from Slave device. 
    In this case we will read string "Slave!" from I2C Slave example = 6 bytes */
    char buf[10]{};
    if(i2c.read(addr, buf, 6) == I2C::ACK){
        printf("Read: %s\n", buf);
    } else {
        printf("Read: NACK\n");
    }

    printf("Endless blinky loop\n");
    while (1) {
        thread_sleep_for(1000);
        led = !led;
    }
}