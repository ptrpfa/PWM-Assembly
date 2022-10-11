/* Configuration file for C program */
// Macros
#define RED_LED_PIN 18      // BCM GPIO pin for Red LED     (PWM Channel: 0)
#define GREEN_LED_PIN 13    // BCM GPIO pin for Green LED   (PWM Channel: 1)
#define PWM_ON 1023         // Value for LED ON state, represented using PWM
#define PWM_OFF 0           // Value for LED OFF state, represented using PWM

// Function prototypes
void offLED(int led_pin); // Function to turn off an LED
void onLED(int led_pin);    // Function to turn on an LED