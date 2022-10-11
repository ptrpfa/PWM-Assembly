### wiringPi
---
#### Installation
`sudo apt-get install wiringpi`

#### Pin numbers
`wiringPiSetup(); // Initializes wiringPi using wiringPi's simlified number system.`
`wiringPiSetupGpio(); // Initializes wiringPi using the Broadcom GPIO pin numbers`

#### Compile program
`gcc program.c -l wiringPi // need to include -l option to link to wiringPi library`