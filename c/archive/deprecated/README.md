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