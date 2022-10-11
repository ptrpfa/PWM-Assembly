/* Configuration file for C program */
// Macros
#define RED_LED_PIN 18          // Broadcom (BCM) GPIO pin for Red LED     (PWM Channel: 0)
#define GREEN_LED_PIN 13        // Broadcom (BCM) GPIO pin for Green LED   (PWM Channel: 1)
#define PWM_ON 1024             // Value for LED ON state, represented using PWM (Duty Cycle: 100%)
#define PWM_OFF 0               // Value for LED OFF state, represented using PWM (Duty Cycle: 0%)
#define PWM_BASE_FREQ 19.2e6    // Base frequency of Raspberry Pi's PWM clock

// Function prototypes
void resetLED(int led_pin);             // Function to reset LED
void offLED(int led_pin);               // Function to turn off an LED
void onLED(int led_pin);                // Function to turn on an LED
void blinkLED(int led_pin, int rate);   // Function to make LED blink at a specified rate