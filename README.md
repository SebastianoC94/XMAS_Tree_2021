# XMAS_Tree_2021
The XMAS Tree 2021 project circuit board has an STM8L101F2P3 and 7 LEDs.
The LEDs are used to simulate a small Christmas tree. 

# Why these components?
The main constraint of the design is to minimize the power consumption of the entire circuit.
This choice stems from the fact that the device is powered by commercial batteries and needs to be able to operate for as long as possible. 
More detailed power consumption analysis will be conducted in the future. 

It was therefore chosen to use a microcontroller classified suitable for low power applications: STM8L. 

# How it works?
The electronic board is normally in the lowest power consumption state. In that condition, all LEDs are off, the microcontroller waits in the halt state, and interrupts are active.

When the user presses the button, an interrupt is generated that wakes up the microcontroller, bringing it out of the halt state.
The STM8L clock is brought to the used peripherals and a visual LED on/off sequence is performed.
Through the use of timers it is possible to generate 7 different and independent software PWMs, one for each LED. It is therefore possible to dim the light intensity of the various LEDs. Exploiting this technique allows you to have more interesting optical effects and simultaneously reduce power consumption.
At the expiration of a preset timer, the microcontroller returns to the low power state. 
