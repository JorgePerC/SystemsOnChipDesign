# Timers 

## Timers in computers

* Are made out of flip flops.
* Can be called *counters*, since they count to a number.
    * Counts from up to down or down to up
* Have a frequency
    * The freqyency can be divided
Here's a [video](https://www.youtube.com/watch?v=aLCUDv_fgoU) explaining them.

## System Tick Timer

    A.K.A _SysTick_ (STCTRL)

Has a single register for control and status.

|Control/Status |Bit in register|Place it is | What it does              |
|---------------|---------------|------------|---------------------------|
|Status         |Count flag     | 16 | 1 is count has reached 0 (ended)  |
|Control        |Clock source   | 2  | 1 is system clock. 0 is SysClk/16 |
|Control        |Tick interrupt | 1  | Sends interruptions, only when CtrlFlag is also 1 |
|Control        |Timer enable   | 0  | Enables source signal from clock  |

Other important registers:

| Name              | What it's for         | Notes|
|-------------------|-----------------------|------|
|**SysTick_LOAD** (STRELOAD)  |Value to count down.   | Not all digits are used in saving the number. |
|**SysTick_VAL** (STCURRENT) |Current timer value.   | Same as before. Can set it to "interrupt" a countdown. **Should be set to 0** upon inicialization. |
|**SysTick_CALIB**  |??          | Read only. 

*SysTick_LOAD sould be set to: `Desired - 1`

## Delay Generation

    Frequency is how many times a cycle is completed in a certain amount of time. 
    Period is the duration of one cycle. 
    1 Hz is a unit for frequency (Reps/Seconds)

So... if we want a delay of n time we would do:

**TODO**: ADD FORMULA

There are several timer modules on ARM boards, these are called `TPM0, TPM1, TPM2`. These modules have their own memory addresses 

### TMP# registers:

TPMSRC bits and the PLLFLLSEL bit of SIM_SOPT2 register in System Integration Module.

| Name              | What it's for         | Notes|
|-------------------|-----------------------|------|
| TPMSRC            | Select Clock source   | You can choose between MCGFLLCLK, MCGPLLCLK/2, OSCERCLK and MCGIRCLK, each clock has a different freq|
| PLLFLLSEL         | Selects the PLL/FLL clock for peripheral clocking options.| 0 - **FLL** clock. 1 - **PLL** clock with fixed divide by two.|
| Count (TPMx_CNT)  | Value the count is at.| It's like *CURRENT* |
| Modulo (TPMx_MOD) | Value that is compared to count| It's like *LOAD* |
| Stat Ctrl (TPMx_SC)| Enable Counter | Must be disable upon initialization.

### Status Control (SC) registers:
| Name              | What it's for         | Notes|
|-------------------|-----------------------|------|
| MCG               | Multiple Clock Generation
| TOF               | Timer Over Flow flag
| PS                | Prescaler
| TOIE              | Timer Overflow Interrupt Enable
| DMA               |
| CPWMS             |

This must be done in addition to allowing clock to the TPMx module using the SIM_SCGC6 register and selecting the clock source for timer counter using SIM_SOPT2 register.

## Output Compare

Each Timer has several Output compare channes, This allows you to raise an interrupt on different stages in the clock cycle without resetting _count_.

### Polling vs Interruptions:

Polling is a practice where you have to go to the register and read it each time to see if the timer has compleated it's count. 

Later on we'll see how to do it with interruptions.

## Applications

* Counting events
* Making delays (parallell delays, that don't block the main CPU).
* Measure time 
    * Schedule tasks

On our project timers will be key to produce PWM signals, wich will control some of our peripherals. 

## Prescaler or Clock Divider

A [prescaler](https://www.youtube.com/watch?v=wOeRTo55BCE) allows yout to get a rising edge every $`2^n`$ from the original input signal, essentially making lower frequency clocks.

Incluya algunas investigaciones sobre posibles aplicaciones y temporizadores en una aplicación (especialmente en su proyecto final).

TODO: Edge Time Capturing