/* Configuration file for Pulse-Width Modulation program */
// Macros
#define RED_LED_PIN 18          // Broadcom (BCM) GPIO pin for Red LED     (PWM Channel: 0)
#define GREEN_LED_PIN 13        // Broadcom (BCM) GPIO pin for Green LED   (PWM Channel: 1)
#define PWM_MAX 1000000         // Maximum value for PWM GPIO pin  (Range: 0 - 1000000)
#define MAX_FREQ 125000000      // Maximum value for PWM Frequency (Range: 1 - 125000000)
#define CFF_FREQ 500            // Critical Flicker Fusion Frequency (frequency at which flickering light is perceived as continuous by the human eye)

// Global variables
int BASE_RED_LED_FREQ;          // Red LED's base PWM Frequency (base frequency is usually 800 Hz)
int BASE_GREEN_LED_FREQ;        // Green LED's base PWM Frequency (base frequency is usually 800 Hz)

// Function prototypes
int getDutyCycleValue(float duty_cycle);            // Function to calculate the duty cycle value
void resetLEDs();                                   // Function to reset both LEDs to their base state
void offLED(int led_pin);                           // Function to turn off an LED
void onLED(int led_pin);                            // Function to turn on an LED
void blinkLED(int led_pin, int freq, float dc);     // Function to make LED blink at a specified rate