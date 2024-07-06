# 'T' light controller

Some Arduino code to run a set of 'T' lights for trams, just like those found on the streets of Melbourne, Australia.

<a href="https://railgallery.wongm.com/melbourne-tram-sidings/F163_7372.jpg.html"><img width="500" src="https://railgallery.wongm.com/cache/melbourne-tram-sidings/F163_7372_595.jpg?cached=1708075113" alt="'T' light at the exit from the Dudley Street siding" /></a>

## Operation

On startup, the red 'T' is illuminated.
When push button is pushed, white 'T' will be illuminated for 8 seconds.
Yellow 'T' will then be illuminated for 4 seconds.
Red 'T' will then be held for 4 seconds, after which button can be pushed to trigger the cycles again.

## Hardware

I'm running my code on a ESP-12F 5V/7-30V/220V 4 Channel Relay Board. These boards can be purchased from AliExpress for $12 AUD. More on this board here:

https://templates.blakadder.com/ESP12F_Relay_X4.html

GPIO pin 4 is being used for the trigger cycle push button. This input is debounced using the Bounce2 library, so that electrical noise being picked up along a ~2 metre long cable to the push button doesn't result in false triggers.

I'm using GPIO pins 14, 12 and 13 to run the red, yellow and white aspects respectively via the relays.

Wiring to the relays:

- Red to NC2
- Yellow to NO3
- White to NO4

Note red is wired to the normally closed contacts, so that relay 2 does not need to be energised at all times.
Relay 1 is not used, as it is connected to GPIO pin 16 which always turns ON when the board is powered up.

DANGER: I'm powering everything from 240 V AC, as this is what the LED modules inside my traffic light run from.

So I've enclosed the relay board inside a 3D printed case to ensure nothing comes in contact with bare PCB traces. STL file for it can be found here:

https://thangs.com/designer/ayatec/3d-model/ESP12F_RELAY_X4%204-CHANNEL%20RELAY%20CASE%20ESP8266%2087X93-863688

I've also terminated the 240 V wires with crimp ferrules where they are secured into the screw terminal blocks on the board, and used Wago connectors to form the active and neutral buses.