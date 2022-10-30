/* Main C program for controlling PWM of the Red and Green LEDs. This program operates with the assumption that the Raspberry Pi and its components have been set up correctly. */
#include <pigpio.h>     // Include pigpio library, which is used to interact with the GPIO pins (Note: Using pigpio, not pigpiod_if2!)
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
        // Save LED base states (frequency)
        BASE_RED_LED_FREQ = gpioGetPWMfrequency(RED_LED_PIN);         // Save Red LED's PWM Frequency
        BASE_GREEN_LED_FREQ = gpioGetPWMfrequency(GREEN_LED_PIN);     // Save Green LED's PWM Frequency
    }
    
    // Program execution message
    printf("CSC1104 Pulse-Width Modulation Program\n"
           "This program enables you to control the PWM of a Red and Green LED, until you have chosen to end to program.\n\n");

    // Do-While loop to obtain user input
    do {    
        // Get user's input
        printf("Please select and enter an option from the following:\n"
               "(0) Turn off both LEDs\n"
               "(1) Turn on both LEDs\n"
               "(2) Make both LEDs blink twice per second\n"
               "(3) Make Red LED blink 8 times per second and Green LED blink twice per second at reduced brightness\n"
               "(Any other number) End Program\n\n"
               "Enter your choice: ");
        scanf("%d", &user_input);

        // Check user's input option
        switch(user_input) {
            case 0:
                // Option for turning off both LEDs
                printf("\nTurning off LEDs..\n");
                offLED(RED_LED_PIN);      // Turn off Red LED
                offLED(GREEN_LED_PIN);    // Turn off Green LED
                printf("Both LEDs turned off!\n\n");
                break;
            case 1:
                // Option for turning on both LEDs
                printf("\nTurning on both LEDs..\n");
                onLED(RED_LED_PIN);       // Turn on Red LED
                onLED(GREEN_LED_PIN);     // Turn on Green LED
                printf("Both LEDs turned on!\n\n");
                break;
            case 2:
                // Option for making both LEDs blink twice per second
                printf("\nMaking both LEDs blink twice per second (50%% duty cycle)..\n");
                blinkLED(RED_LED_PIN, 2, 50);       // Set Red LED's Duty Cycle to 50% for it to be turned on half the time (square wave signal), and set Frequency to 2 for it to blink twice per second
                blinkLED(GREEN_LED_PIN, 2, 50);     // Set Green LED's Duty Cycle to 50% for it to be turned on half the time (square wave signal), and set Frequency to 2 for it to blink twice per second
                printf("Both LEDs blinking twice per second!\n\n");
                break;
            case 3:
                // Option for making Red LED blink 8 times per second & Green LED blink twice per second at reduced brightness
                printf("\nMaking Red LED blink 8 times per second (50%% duty cycle), and Green LED blink twice per second at reduced brightness (12.5%% duty cycle)..\n");
                blinkLED(RED_LED_PIN, 8, 50);       // Set Red LED's Duty Cycle to 50% for it to be turned on half the time (square wave signal), and set Frequency to 8 for it to blink 8 times per second
                blinkLED(GREEN_LED_PIN, 2, 12.5);   // Set Green LED's Duty Cycle to 12.5% for it to be turned on with reduced brightness by 4 times, and set Frequency to 2 for it to blink twice per second
                printf("Red LED is blinking 8 times per second and Green LED is blinking twice per second at reduced brightness!\n\n");
                break;
            default:
                // Default option for any other user input values
                // Program termination procedure
                printf("\nProceeding to end this program..\n");
                resetLEDs();        // Reset both LEDs
                gpioTerminate();    // Terminate pigpio library before end of program execution
                printf("GPIO terminated and both LEDs have been reset!\nEnd of Program!\n");
                break;
        }

    } while (user_input >= 0 && user_input <= 3); // Loop continues until user chooses to end the program

    // Signal successful program execution
    return 0;

}

// Function to calculate the duty cycle value
int getDutyCycleValue(float duty_cycle){
    int value = PWM_MAX  * (duty_cycle / 100); // Calculate value to set for a given duty cycle percentage
    return value;
}

// Function to reset both LEDs to their base state
void resetLEDs(){
    // Reset both LEDs to their base frequencies, but set duty cycle to 0% (turn off both LEDs)
    gpioHardwarePWM(RED_LED_PIN, BASE_RED_LED_FREQ, getDutyCycleValue(0));
    gpioHardwarePWM(GREEN_LED_PIN, BASE_GREEN_LED_FREQ, getDutyCycleValue(0));
}

// Function to turn off an LED
void offLED(int led_pin) {
    // To turn off an LED set it's Duty Cycle to 0% (Frequency is set to the defined Critical Flicker Fusion Frequency)
    gpioHardwarePWM(led_pin, CFF_FREQ, getDutyCycleValue(0));
}

// Function to turn on an LED
void onLED(int led_pin) {
    // To turn on an LED set it's Duty Cycle to 100% (Frequency is set to the defined Critical Flicker Fusion Frequency)
    gpioHardwarePWM(led_pin, CFF_FREQ, getDutyCycleValue(100));
}

// Function to make LED blink at a specified rate
void blinkLED(int led_pin, int freq, float dc){
    // Set LED's frequency and duty cycle to the provided values to make it blink
    gpioHardwarePWM(led_pin, freq, getDutyCycleValue(dc));
}
