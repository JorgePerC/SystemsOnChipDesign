# SystemsOnChipDesign
Para la clase de diseño de sistemas en chip

    Note: for the Freescale Kinetis OSJTAG Drivers V1.20, install them on the default settings

## Vocabulario

* **SFR:** Special Function Register. Will allow us to multiplex a pin.
* **SIM:** System Integration Module. 
    * System clocking configuration
        * System clock divide values
        * Architectural clock gating control
        * ERCLK32K clock selection
        * USB clock selection
        * UART0 and TPM clock selection
    * Flash and System RAM size configuration
    * USB regulator configuration
    * TPM external clock and input capture selection
    * UART receive/transmit source selection/configuration
* **PORT{L} L = A, B, C, D:** Groupings of GPIO pins.

|  Port acronym  | Full name                    | Description                   | Operations allowed |
| -------------- | ---------------------------- | ----------------------------  | ------------------ |
| **GPIO_PDOR:** | Port Data Output Register    | Write output data             | Read/Write       |
| **GPIO_PSOR:** | Port Set Output Register     | Set pin value to 1. You give it the pin you want to set          | Write (if read, 0) |
| **GPIO_PCOR:** | Port Clear Output Register   | Set pin value to 0. You give it the pin you want to set          | Write (if read, 0) |
| **GPIO_PTOR:** | Port Toggle Output Register  | To change the bit value. You give it the pin you want to toggle. | Write (if read, 0) |
| **GPIO_PDIR:** | Port Data Input Register     | Where input data actually is.  | Read               |
| **GPIO_PDDR:** | Port Data Direction Register | Make the pin input or output.  | R/W                |
| **PORTx_PCRn** | PortX Pin Control            | Alternate a pin Funcion (Multiplexing), Control Drive Strength, Pull Up/Down resistor  |


* **GPIO Control Register:** 

|  BIT  | Field                      | Description                   |
| ----- | -------------------------- | ----------------------------- |
| **0** | Pull Select (PS)           | 0: Pull down ⁝ 1: Pull Up     |
| **1** | Pull Enable (PE)           | 0: Disable ⁝ 1: Enable, pull resistors|
| **2** | Slew Rate Enable (SRE)     | 0: Fast ⁝ 1: Slow, Slew Rate         |
| **4** | Passive Filter Enable (PFE)| 0: Disable ⁝ 1: Enable, input filter |
| **6** | Drive Strength Enable (DSE)| 0: Low ⁝ 1: High, drive strength|


## Basic Steps:

1. Enable clock to the port *SIM_SCGC#* your pin is at.
    * Check the registers if you want to implement an special pin (this will may require the use of extra registers)
1. Configure and control based on the ports showned before.
    1. `PORTD->PCR[0] = 0x100` sets pin as GPIO.
    1. Verify you are setting the right letter, in this case `D`, for the port
    
Note that on C, there is no need to indicate namespace

People use unsigned char to pass addresses because it has the size of a byte

Instead of using simply structs, we define as typedef struct {something} myVariable;
    With that implementation, there are no such thing as methods for structures. What you need to do is create a normal function, and pass as an argument your structure, and inside it make whatever you want/need
    myVariable_setSomething(myVariable * mv, something s){}

myVariable *arrayLike = malloc(10*sizeof(myVariable));

https://www.allaboutcircuits.com/technical-articles/understanding-embedded-C-what-are-structures/
https://www.youtube.com/watch?v=cNv4SA87y5c



