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
    printf("I2C Master - transfer example\n");
    thread_sleep_for(1000);

    /* Set frequency if necessary - 100000 or 400000 or 1000000. */
    i2c.frequency(100000);

    
    /* Buffers for transaction with Slave device */
    char msgW[] = "TransW";
    char bufW[10]{};

    /* The transfer_and_wait function write a buffer to slave and also read one back with timeout. */
    i2c.transfer_and_wait(addr, msgW, strlen(msgW), bufW, 6, 1s);
    printf("Transfer_and_wait read: %s\n", bufW);

    thread_sleep_for(1000);

    /* Buffers for transaction with Slave device */
    char msgA[] = "TransA";
    char bufA[10]{};

    /* I2C transaction complete flag*/
    static volatile bool trCompleteFlag = false;

    /* Lambda Expression for I2C transfer event callback */
    auto I2cTransferEventCallback = [](int){
        printf("I2C event transfer complete \n");
        trCompleteFlag = true;
    };
    
    /* The transfer is asynch function that write a buffer to slave and also read one 
    back with callback after transaction complete. */
    /* We should always know how many bytes we want to read from Slave device. 
    In this case we will read string "Slave!" from I2C Slave example = 6 bytes */
    i2c.transfer(addr, msgA, strlen(msgA), bufA, 6, I2cTransferEventCallback, I2C_EVENT_TRANSFER_COMPLETE);

    printf("Endless blinky loop\n");
    while (1) {
        if(trCompleteFlag){
            printf("Asynch transfer Read: %s\n", bufA);
            trCompleteFlag = false;
        }
        thread_sleep_for(500);
        led = !led;
    }
}