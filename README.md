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