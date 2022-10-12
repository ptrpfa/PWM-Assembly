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
`sudo apt-get update`
`sudo apt-get install pigpio python-pigpio python3-pigpio`

#### Compile program
`gcc -Wall -pthread prog.c -lpigpio -lrt`<br>
`sudo ./a.out`<br>
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