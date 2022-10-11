/* Main C program for controlling PWM of the red and green LEDs. This program operates with the assumption that the Raspberry Pi and components have been set up correctly. */
#include <wiringPi.h>   // Include wiringPi library, which is used to interact with the GPIO pins
#include <stdio.h>      // Include stdio library, which is used for input/output functions
#include "config.h"     // Include configuration file

// Program entrypoint
int main() {
    // Initialise user's input
    int user_input = 0;

    wiringPiSetupGpio();                // Use BCM GPIO pin numbers
    pinMode(RED_LED_PIN, PWM_OUTPUT);   // Set pin mode for GPIO pin
    pinMode(GREEN_LED_PIN, PWM_OUTPUT); // Set pin mode for GPIO pin

    do {
        printf("Please enter an option from the following:\n(0) Turn off LEDs\n(1) Turn on LEDs\n(2) LEDs blink twice per second\n(3) Red LED blinks 8 times per second and Green LED blinks twice per second with reduced brightness\n(Any other number) Exit Program\n\nEnter your choice: ");
        scanf("%d", &user_input);
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
                break;
            case 3:
                break;
            default:
                printf("Program Ended!\n");
                break;
        }
    } while (user_input >= 0 && user_input <= 3);

    return 0; // Signal successful program execution

}

// Function to turn off an LED
void offLED(int led_pin) {
    pwmWrite(led_pin, PWM_OFF);
    // delay(1); // Delay required if both LEDs are on the same PWM channel
}
// Function to turn on an LED
void onLED(int led_pin) {
    pwmWrite(led_pin, PWM_ON);
    // delay(1); // Delay required if both LEDs are on the same PWM channel
}