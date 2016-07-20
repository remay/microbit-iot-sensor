
/*
The MIT License (MIT)

Copyright (c) 2016 Robert May.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "MicroBit.h"

MicroBit uBit;

const char * const radio_waves ="\
    000,000,000,000,000,  000,000,000,000,000,  000,000,255,255,255\n\
    000,000,000,000,000,  000,000,000,000,000,  000,255,000,000,000\n\
    000,000,000,000,000,  000,000,000,255,255,  255,000,000,255,255\n\
    000,000,000,000,000,  000,000,255,000,000,  255,000,255,000,000\n\
    000,000,000,000,255,  000,000,255,000,255,  255,000,255,000,255\n";

MicroBitImage radio(radio_waves);

int main() {
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.radio.enable();

    // Sets the group to an arbitrary number (69 in this case) to avoid interference
    uBit.radio.setGroup(69);

    // Use the highest output put level on the radio, to increase range and reliability.
    uBit.radio.setTransmitPower(7);

    // Run a short animaiton at power up.
    uBit.display.animate(radio, 500, 5, 0, 0);
    uBit.sleep(1000);

    // Get a short unique id for this micro:bit - used to filter received
    // messages
    ManagedString id = uBit.getName();

    // Get into powersaving sleep mode, whilst still processing events?  XXX Wouldn't release_fiber() be better?
    while(1) {
        int t = uBit.thermometer.getTemperature();
        uBit.display.scrollAsync(t);
        uBit.radio.datagram.send(id + ":t=" + t);
        uBit.sleep(10000);
    }

    // NOT REACHED
}
