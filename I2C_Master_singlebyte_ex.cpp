#include "mbed.h"

DigitalOut led(LED1);

/* Set your own pins if necessary- */
I2C i2c(I2C_SDA, I2C_SCL);

int main()
{
    printf("I2C Master - single byte example\n");
    thread_sleep_for(1000);

    /* Set i2c slave address of your slave device.
    In this case we use Slave address in context of I2C Slave example */
    /* Real address is 7bit 0x50 + one bit of dirrection (read/write) 
    and that brings us to 8bit(byte) 0xA0 for write and 0xA1 for read. See below. */
    const int slaveAddress = 0xA0;

    /* Set a message you want to send to Slave device. */
    char cmd[] = "MasterWrite";

    /* Set frequency if necessary - 100000 or 400000 or 1000000. */
    i2c.frequency(100000);

    /** Write sequence:
     * call Start
     * Write address byte with read/write bit under user controll
     * Write data byte by byte
     * call Stop
     */
    i2c.start();
    if(i2c.write_byte(slaveAddress | 0) == I2C::Result::ACK){
        for(size_t i = 0; i < sizeof(cmd); i++){
            if(i2c.write_byte(cmd[i]) != I2C::Result::ACK){
                printf("Write byte %d NACK\n", i);
            }
        }
    } else printf("Write address NACK\n");
    i2c.stop();

    thread_sleep_for(1000);

     /** Read sequence:
     * call Start
     * Write address byte with read/write bit under user controll
     * Read data byte by byte with true parameter but last byte should be Read with false parameter
     * call Stop
     */
    char buf[10]{};
    bool result = false;
    i2c.start();
    if(i2c.write_byte(slaveAddress | 1) == I2C::Result::ACK){
        result = true;
        int i;
        /* We should always know how many bytes we want to read from Slave device. 
        In this case we will read string "Slave!" from I2C Slave example = 6 bytes,
        but because we need to set false for last read, then just 5 and last read call will
        be called separetly with false */
        for(i = 0; i < 6 - 1; i++){
            buf[i] = (char)i2c.read_byte(true);
        }
        buf[i + 1] = (char)i2c.read_byte(false);    
    }
    i2c.stop();

    if(result) printf("Read - %s\n", buf);
    else printf("Read address NACK\n");
    
    printf("Endless blinky loop\n");
    while (1) {
        thread_sleep_for(1000);;
        led = !led;
    }
}