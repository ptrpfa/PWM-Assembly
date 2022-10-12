/* Main C program for controlling PWM of the red and green LEDs. This program operates with the assumption that the Raspberry Pi and components have been set up correctly. */
#include <pigpio.h>     // Include pigpio library, which is used to interact with the GPIO pins (Note: wiringPi not used due to its lack of support for setting separate PWM frequencies for each of the PWM channel on the Raspberry Pi)
#include <stdio.h>      // Include stdio library, which is used for input/output functions
#include <stdlib.h>     // Include stdlib library, which is used for general purpose functions
#include "config.h"     // Include configuration file

// Program entrypoint
int main() {
    // Initialise user's input
    int user_input = 0;

    // Check if there are any issues initialising the GPIO pins
    if(gpioInitialise() < 0) {
        printf("Initialisation of GPIO failed!\n");
        exit(1); // Terminate program with exit failure if setup failed
    }
    else {
        // Save LED base states (frequency and duty cycle)
        BASE_RED_LED_FREQ = gpioGetPWMfrequency(RED_LED_PIN);         // Save Red LED's PWM Frequency
        BASE_RED_LED_DC = gpioGetPWMdutycycle(RED_LED_PIN);           // Save Red LED's PWM Duty Cycle
        BASE_GREEN_LED_FREQ = gpioGetPWMfrequency(GREEN_LED_PIN);     // Save Green LED's PWM Frequency
        BASE_GREEN_LED_DC = gpioGetPWMdutycycle(GREEN_LED_PIN);       // Save Green LED's PWM Duty Cycle
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
            default:
                printf("Program Ended!\n");
                break;
        }
    } while (user_input >= 0 && user_input <= 3);

    // Program termination procedure
    resetLEDs();        // Reset both LEDs
    gpioTerminate();    // Terminate pigpio library before end of program execution
    return 0;           // Signal successful program execution

}

// Function to calculate the duty cycle value
int getDutyCycle(float duty_cycle){
    int value = PWM_MAX  * (duty_cycle / 100); // Calculate value to set for a given duty cycle percentage
    return value;
}

// Function to reset both LEDs to their base state
void resetLEDs(){
    // Reset both LEDs to their base frequencies, but set duty cycle to 0% (turn off both LEDs)
    gpioHardwarePWM(RED_LED_PIN, BASE_RED_LED_FREQ, getDutyCycle(0));
    gpioHardwarePWM(GREEN_LED_PIN, BASE_GREEN_LED_FREQ, getDutyCycle(0));
}

// Function to turn off an LED
void offLED(int led_pin) {
    // To turn off an LED set it's Duty Cycle to 0% (Frequency is set to the defined Critical Flicker Fusion Frequency)
    gpioHardwarePWM(led_pin, CFF_FREQ, getDutyCycle(0));
}

// Function to turn on an LED
void onLED(int led_pin) {
    // To turn on an LED set it's Duty Cycle to 100% (Frequency is set to the defined Critical Flicker Fusion Frequency)
    gpioHardwarePWM(led_pin, CFF_FREQ, getDutyCycle(100));
}

// Function to make LED blink at a specified rate
void blinkLED(int led_pin, int rate){
    // pwmSetClock(rate);
    // pwmWrite(led_pin, 1024);
}