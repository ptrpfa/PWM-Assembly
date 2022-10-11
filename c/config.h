/* Configuration file for C program */
// Macros
#define RED_LED_PIN 18          // Broadcom (BCM) GPIO pin for Red LED     (PWM Channel: 0)
#define GREEN_LED_PIN 13        // Broadcom (BCM) GPIO pin for Green LED   (PWM Channel: 1)
#define PWM_MAX 1024            // Maximum value for PWM GPIO pin (Range: 0 - 1024)
#define PWM_BASE_FREQ 19.2e6    // Base frequency of Raspberry Pi's PWM clock

// Function prototypes
void resetLED(int led_pin);                         // Function to reset LED
void setDutyCycle(int led_pin, float duty_cycle);   // Function to set the duty cycle for an LED
void offLED(int led_pin);                           // Function to turn off an LED
void onLED(int led_pin);                            // Function to turn on an LED
void blinkLED(int led_pin, int rate);               // Function to make LED blink at a specified rate