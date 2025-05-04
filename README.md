# MbedCE-I2C-examples

This repository contains 3 examples of I2C and I2C Slave driver that describe how to use it and also some tips.
* I2C Master - I2C_Master_ex.cpp
* I2C Master single byte version - I2C_Master_singlebyte_ex.cpp
* I2C Slave - I2C_Slave_ex.cpp
  
> [!NOTE]
> All examples contain information about how to use I2C but they are in context of two boards connected over I2C together, one acts like I2C master and second as I2C slave.


## How to set up this project:

1. Clone it to your machine.  Don't forget to use `--recursive` to clone the submodules: `git clone --recursive https://github.com/mbed-ce-libraries-examples/MbedCE-I2C-examples.git`
2. You may want to update the mbed-os submodule to the latest version, with `cd MbedCE-I2C-examples/mbed-os && git fetch origin && git reset --hard origin/master`
3. If you don't have set up environment already, then visit https://github.com/mbed-ce/mbed-os/wiki#environmenttoolchain-setup
4. The build tool will build all binaries, so you have to choose which one you want use - Master, Master (single byte) or Slave.
5. Make physical connection between two mbed targets / dev boards (may not be the same) and deploy.

## Mbed I2C basics:
> [!IMPORTANT]
> Remember that you need a pull-up resistors (R1 & R2) on SDA and SCL. All drivers on the I2C bus are required to be open collector, and so it is necessary to use pull-up resistors on the two signals. A typical value for the pull-up resistors is around 2.2k ohms, connected between the pin and 3v3.

![image](https://github.com/user-attachments/assets/0519dc5d-878c-4c7c-b766-b500f2d51a9e)

> [!WARNING]
> The Mbed I2C API uses 8 bit addresses, so make sure to left-shift 7 bit addresses by 1 bit before passing them.

## I2C troubleshooting:
When we have a problem to estabilish connection over I2C then there are few basic points what we should check
* wires are not damaged, correctly connected and not twisted
* pull-up ressistors are pressent and have correct values
* we are sure we have correct I2C address of our Slave device. To avoid any mistake in user application we use simple code, based on Linux i2cdetect function, to scan I2C bus for correctly connected slaves. You can switch to I2C_Scanner program or simply copy&paste the code and use it directly in your program.
