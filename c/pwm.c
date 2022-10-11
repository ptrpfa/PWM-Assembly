/* Main C program for controlling PWM of the red and green LEDs. This program operates with the assumption that the Raspberry Pi and components have been set up correctly. */
#include <wiringPi.h>   // Include wiringPi library, which is used to interact with the GPIO pins
#include <stdio.h>      // Include stdio library, which is used for input/output functions
#include <stdlib.h>     // Include stdlib library, which is used for general purpose functions
#include "config.h"     // Include configuration file

// Program entrypoint
int main() {
    // Initialise user's input
    int user_input = 0;

    // Use Broadcom (BCM) GPIO pin numbers
    if(wiringPiSetupGpio() != 0) {
        printf("Initialisation of GPIO failed!\n");
        exit(1); // Terminate program with exit failure if setup failed
    }
    else {
        pinMode(RED_LED_PIN, PWM_OUTPUT);   // Set pin mode for GPIO pin
        pinMode(GREEN_LED_PIN, PWM_OUTPUT); // Set pin mode for GPIO pin
        pwmSetMode(PWM_MODE_MS);            // Set PWM mode to Mark-Space mode, which is the traditional PWM mode. By default, the PWM mode is PWM_MODE_BAL, which is Balanced mode. In Balanced mode, the frequency varies with duty cycle. This was implemented by Broadcom to make the on and off PWM pulses as evenly distributed as possible.
    }
    
    // Do-While loop to obtain user input
    do {    
        // Get user's input
        printf("Please enter an option from the following:\n(0) Turn off LEDs\n(1) Turn on LEDs\n(2) LEDs blink twice per second\n(3) Red LED blinks 8 times per second and Green LED blinks twice per second with reduced brightness\n(Any other number) Exit Program\n\nEnter your choice: ");
        scanf("%d", &user_input);

        // Check user's input option
        switch(user_input) {
            case 0:
                printf("Turning off LEDs!\n\n");
                offLED(RED_LED_PIN);      // Reset LED
                offLED(GREEN_LED_PIN);    // Reset LED
                break;
            case 1:
                printf("Turning on both LEDs!\n\n");
                onLED(RED_LED_PIN);         // Turn on LED
                onLED(GREEN_LED_PIN);       // Turn on LED
                break;
            case 2:
                pwmToneWrite(RED_LED_PIN, 2);
                delay(1);
                pwmWrite(RED_LED_PIN, PWM_ON);
                // both LEDs blink at the pattern of 2 times per second (Square wave signal with frequency of 2Hz (50% duty cycle))
                break;
            case 3:
                // Red LED to blink at the pattern of 8 times per second
                // Green LED to blink at 2 times per second, but with reduced brightness by 4 times. Duty cycle of GPIO pin reduced from 50% to 12.5%
                break;
            default:
                printf("Program Ended!\n");
                break;
        }
    } while (user_input >= 0 && user_input <= 3);

    // Reset PWM

    return 0; // Signal successful program execution

}

// Function to reset LED
void resetLED(int led_pin){
    pwmToneWrite(led_pin, PWM_BASE_FREQ); // Reset frequency of PWM clock
    delay(1);
}

// Function to turn off an LED
void offLED(int led_pin) {
    // resetLED(led_pin);
    pwmWrite(led_pin, PWM_OFF);
    // delay(1); // Delay required if both LEDs are on the same PWM channel
}
// Function to turn on an LED
void onLED(int led_pin) {
    // resetLED(led_pin);
    pwmWrite(led_pin, PWM_ON);
    // delay(1); // Delay required if both LEDs are on the same PWM channel
}

// Function to make LED blink at a specified rate
void blinkLED(int led_pin, int rate){
    // pwmSetClock(rate);
    // pwmWrite(led_pin, PWM_ON);
}