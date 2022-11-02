## Pulse-Width Modulation Program
---
### Usage
---
1. Download source code and and ensure that pigpio has been [installed](#pigpio-c-library) into the Raspberry Pi.
2. Ensure that the Raspberry Pi and its required components have been [set up](#raspberry-pi-setup) correctly.
3. Compile the Pulse-Width Modulation program.<br>
    ` gcc -Wall -pthread -o pwm pwm.c -l pigpio -lrt`<br><br>
    *Flags:<br>
    -Wall : Enable all compiler warning messages<br>
    -pthread : Add support for multithreading with the pthreads library. This option sets the flags for both the preprocessor and linker. <br>
    -o : Used to specify the output file name<br>
    -l <library> : Link to specified library <br>
    -lrt : Link in real time <br>*
4. Run/execute the Pulse-Width Modulation program (root privileges are required to run the program!)<br>
    `sudo ./pwm ` <br>

#### Sample program execution previews
---
Turning both LEDs on and off
![Code preview for turning both LEDs on & off](docs/on-and-off.png)<br>
Making both LEDs blink twice per second
![Code preview for making both LEDs blink twice per second](docs/blink-twice.png)<br>
Making the Red LED blink 8 times per second and the Green LED blink twice per second, at reduced brightness
![Code preview for making LEDs blink at different rates](docs/blink.png)

### Raspberry Pi Setup
---
#### Components Required
- 1 x Raspberry Pi Model 3B
- 1 x Breadboard
- 1 x Red LED and 1 x Green LED
- 2 x 10K Ω Resistors

#### Setup
- Place both LEDs onto the breadboard and connect the Red LED's anode (longer, positive end) to BCM GPIO pin 18, which is the Raspberry Pi's PWM pin (Channel 0). Connect the Green LED's anode (longer, positive end) to BCM GPIO pin 13, which is the Raspberry Pi's PWM pin (Channel 1).
    - The two PWM GPIO pins to be connected are highlighted below:
    ![PWM Pins](docs/pins.png)
- Connect a resistor to each LED's cathode (shorter, negative end), and connect the other end of each resistor to any ground pin on the Raspberry Pi. Both LEDs are connected to a resistor in order to limit the current that passes through each LED (to prevent excess current that can burn out the LEDs).
- The Fritzing Diagram of the setup is as follows:
    ![Fritzing Diagram](docs/fritzing.png)
- The physical setup of the Raspberry Pi and its components should look something like this:
    ![Physical Setup](docs/physical-setup-labelled.png)

### pigpio C library
---
*Please note that we are using pigpio, and not pigpiod_if2, which is another separate version of the library!*
#### Installation
Preferred Method (using apt package installer):
1. `sudo apt-get update`<br>
2. `sudo apt-get install pigpio python-pigpio python3-pigpio`<br><br>
Alternative Method (download library from Github):
1. `wget https://github.com/joan2937/pigpio/archive/master.zip`<br>
2. `unzip master.zip`<br>
3. `cd pigpio-master`<br>
4. `make`<br>
5. `sudo make install`<br>