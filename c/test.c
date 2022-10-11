#include <wiringPi.h>
#include <stdio.h>
#define RED_LED_PIN 18      // BCM GPIO pin for Red LED
#define GREEN_LED_PIN 12    // BCM GPIO pin for Green LED
#define PWM_ON 1024         // Value for ON state represented using PWM
#define PWM_OFF 0           // Value for OFF state represented using PWM

// Function prototypes
void resetLED(int led_pin);
void onLED(int led_pin);

// Program entrypoint
int main() {
    // Initialise user's input
    int user_input = 0;

    wiringPiSetupGpio();                // Use BCM GPIO pin numbers
    pinMode(RED_LED_PIN, PWM_OUTPUT);   // Set pin mode for gpio pin
    pinMode(GREEN_LED_PIN, PWM_OUTPUT); // Set pin mode for gpio pin

    // Digital output
    // digitalWrite(RED_LED_PIN, HIGH);
    // digitalWrite(GREEN_LED_PIN, HIGH);

    do {
        printf("Please enter an option from the following:\n(0) Turn off LEDs\n(1) Turn on LEDs\n(2) LEDs blink twice per second\n(3) Red LED blinks 8 times per second and Green LED blinks twice per second with reduced brightness\n(Any other number) Exit Program\n\nEnter your choice: ");
        scanf("%d", &user_input);
        switch(user_input) {
            case 0:
                printf("Turning off LEDs!\n\n");
                resetLED(RED_LED_PIN);      // Reset LED
                resetLED(GREEN_LED_PIN);    // Reset LED
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

    return 0;

}

// Function to turn off an LED
void resetLED(int led_pin) {
    pwmWrite(led_pin, PWM_OFF);
}
// Function to turn on an LED
void onLED(int led_pin) {
    pwmWrite(led_pin, PWM_ON);
}