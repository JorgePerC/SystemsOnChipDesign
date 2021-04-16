# SystemsOnChipDesign
Para la clase de diseño de sistemas en chip

    Note: for the Freescale Kinetis OSJTAG Drivers V1.20, install them on the default settings

## Vocabulario

* **SFR:** Special Function Register. Will allow us to multiplex a pin.
* **SIM:** Configure clock gate register
* **PORTB:** ??

|  Port acronym  | Full name                    | Description                   |
| -------------- | ---------------------------- | ----------------------------  |
| **GPIO_PDOR:** | Port Data Output Register    | |
| **GPIO_PSOR:** | Port Set Output Register     | |
| **GPIO_PCOR:** | Port Clear Output Register   | |
| **GPIO_PTOR:** | Port Toggle Output Register  | |
| **GPIO_PDIR:** | Port Data Input Register     | Donde está el valor de entrada |
| **GPIO_PDDR:** | Port Data Direction Register | Make the pin Input or output              |
| **PORTx_PCRn** | PortX Pin Control            | Alternate a pin Funcion (Multiplexing), Control Drive Strength, Pull Up/Down resistor  |


* **GPIO Control Register:** 

|  BIT  | Field                      | Description                   |
| ----- | -------------------------- | ----------------------------- |
| **0** | Pull Select (PS)           | 0: Pull down ⁝ 1: Pull Up     |
| **1** | Pull Enable (PE)           | 0: Disable ⁝ 1: Enable, pull resistors|
| **2** | Slew Rate Enable (SRE)     | 0: Fast ⁝ 1: Slow, Slew Rate         |
| **4** | Passive Filter Enable (PFE)| 0: Disable ⁝ 1: Enable, input filter |
| **6** | Drive Strength Enable (DSE)| 0: Low ⁝ 1: High, drive strength|