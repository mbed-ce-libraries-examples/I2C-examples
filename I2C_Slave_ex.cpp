#include <mbed.h>

/* Set your own pins if necessary. */
I2CSlave slave(I2C_SDA, I2C_SCL);   

int main()
{
    printf("I2C Slave example\n");
    thread_sleep_for(1000);

    /* just a read buffer */
    char buf[15]{};

    /* Set reply string. */
    char msg[] = "Slave!";          

    /* Set frequency if necessary - 100000 or 400000 or 1000000. */
    slave.frequency(100000);

    /* Set a slave i2c address of this device if necessary. 
    This device will listen only under this address.*/
    slave.address(0xA0);            

    while (1) {
        int i = slave.receive();
        switch (i) {
            case I2CSlave::ReadAddressed:
                slave.write(msg, strlen(msg) + 1);
                break;
            case I2CSlave::WriteGeneral:   
                /* This case is not supported for every target. */         
                slave.read(buf, sizeof(buf));
                printf("Read G: %s\n", buf);
                break;
            case I2CSlave::WriteAddressed:
                slave.read(buf, sizeof(buf));
                printf("Read A: %s\n", buf);
                break;
        }
        for (int i = 0; i < sizeof(buf); i++) {
            buf[i] = 0;    // Clear buffer
        }
    }
}