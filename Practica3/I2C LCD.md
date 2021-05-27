# I2C Inter Integrated Circuit

It's a **serial communication protocol**. It can be refered as IIC, I2C or I^2C

The NPX card we are using has two I2C pins preconfigured. 

## Operation modes:

1. Run mode: This is the basic mode of operation. To conserve power in this mode,disable the module.

1. Wait mode: The module continues to operate when the core is in Wait mode and canprovide a wakeup interrupt.

1. Stop mode: The module is inactive in Stop mode for reduced power consumption,except that address matching is enabled in Stop mode. The STOP instruction doesnot affect the I2C module's register states.

## Registers:

I2C is enable by the *SIM_SCGC4* register. Check page 204 of the user manual. 

|Control/Status |Bit in register|Place it is | What it does              |
|---------------|---------------|------------|---------------------------|


Other important registers:

| Name      | What it's for             | Notes|
|-----------|---------------------------|------|
|**I2CX_F** | Set clock configuration   | This clock has it's own prescaler and clock divider. Check page 691 |
|**I2CX_C1**| Control register          | Enable operation, interrupts, master/slave and others|
|**I2CX_A1**| Hold slave address        | Only when it's set up as slave. |
|**I2CX_D** | Data register. Use in transmit mode | All the register is used for data  |
|**I2CX_S** | Transmission's status register.     | Check if busy, transfer complete, etc. |

### Usefull meanings:

* ARBL: Arbitration lost 
* TFC : Transfer complete flag
* IAAS: Addressed as slave
* RAM : Range address match. Turns on if the calling addres is the same as the one from device
* SRM : Slave read and write
* IICIF: Interrupt flag
* RXAK: Recieve acknowledge

### Process for recieving/sening data:

#### Recieving

    if START then:
        busy = 1
    until STOP:
        busy = 0

You shouldn't use the bus if its busy. Otherwise you'll get in trouble, such bus collision Arbitration Lost.

#### Sending
Before sending data you must read ARBL && BUSY
    
    if in transmission then:
        TCF = 0
    until not (IICIF):
        TCF = 1
    if not (RXAK):
        you're done
    else:
        there was an error
        try again?


**Set the Baut rate with the following formula:**
    I2C baud rate = bus speed (Hz)/(mul × SCL divider)


## Configuring LCD

The three hardware address pins A0, A1 and A2 allow eight devices to be on the same I2C-bus. You can change the address of the device according to the status of each of these pins. The default address of the device is 0X3F (with PCF8574AT)

https://www.rhydolabz.com/wiki/?p=16424