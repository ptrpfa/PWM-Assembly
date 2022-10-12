## Pulse-Width Modulation Program
---
### Usage
1. Download source code and ensure that pigpio has been [installed](#pigpio).
2. Ensure Raspberry Pi and the required components have been [setup](#raspberry-pi-setup).
3. Compile program<br>
    ` gcc -Wall -pthread -o pwm pwm.c -l pigpio -lrt`<br>
4. Run program (root privileges required for PWM)<br>
    `sudo ./pwm ` <br>

#### Sample program execution previews
---
Turning both LEDs on and off
![Code preview for turning both LEDs on & off](docs/on-and-off.png)
Making both LEDs blink twice per second
![Code preview for making both LEDs blink twice per second](docs/blink-twice.png)
Making Red LED blink 8 times per second and Green LED blink twice per second, at reduced brightness
![Code preview for making LEDs blink at different rates](docs/blink.png)

### Raspberry Pi Setup
#### Components Required
- 1 x Raspberry Pi Model 3B
- 1 x Breadboard
- 1 x Red LED and 1 x Green LED
- 2 x 10K Ω Resistors

#### Setup
- Place both LEDs on the breadboard and connect the Red LED's anode (longer, positive end) to BCM GPIO pin 18, which is the Raspberry Pi's PWM pin (Channel 0). Connect the Green LED's anode (longer, positive end) to BCM GPIO pin 13, which is the Raspberry Pi's PWM pin (Channel 1).
    - The two PWM GPIO pins to be connected are highlighted below:
    ![PWM Pins](docs/pins.png)
- Connect a resistor to each LED's cathode (shorter, negative end), and connect the other end of each resistor to any ground pin on the Raspberry Pi.

- The Fritzing Diagram of the setup is as follows:
    ![Fritzing Diagram](docs/fritzing.png)
- The physical setup of the Raspberry Pi and components should look something like this:
    ![Physical Setup](docs/physical-setup.png)
### pigpio
---
*Using pigpio, not pigpiod_if2!*
#### Installation
`wget https://github.com/joan2937/pigpio/archive/master.zip`<br>
`unzip master.zip`<br>
`cd pigpio-master`<br>
`make`<br>
`sudo make install`<br>
OR<br>
`sudo apt-get update`<br>
`sudo apt-get install pigpio python-pigpio python3-pigpio`

#### Compile program
`gcc -Wall -pthread prog.c -lpigpio -lrt`<br>
`sudo ./a.out`<br><br>
Flags:<br>
-Wall enables all compiler's warning messages<br>
-l <library> link to library <br>
-lrt link in real time <br>
-pthread Adds support for multithreading with the pthreads library. This option sets flags for both the preprocessor and linker. <br>

### wiringPi
---
*No longer used due to lack of support for setting separate PWM frequencies for the two PWM channels on the Raspberry Pi, as well as due to difficulty in setting PWM frequencies and duty cycle*
#### Installation
`sudo apt-get install wiringpi`

#### Pin numbers
`wiringPiSetup(); // Initializes wiringPi using wiringPi's simlified number system.`<br>
`wiringPiSetupGpio(); // Initializes wiringPi using the Broadcom GPIO pin numbers`

#### Compile program
`gcc program.c -l wiringPi // need to include -l option to link to wiringPi library`