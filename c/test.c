#include <stdio.h>
#include <wiringPi.h>
// Macros
#define RED_LED_PIN 18          // Broadcom (BCM) GPIO pin for Red LED     (PWM Channel: 0)
#define GREEN_LED_PIN 13        // Broadcom (BCM) GPIO pin for Green LED   (PWM Channel: 1)
#define PWM_ON 1024             // Value for LED ON state, represented using PWM
#define PWM_OFF 0               // Value for LED OFF state, represented using PWM
#define PWM_BASE_FREQ 19.2e6    // Base frequency of Raspberry Pi's PWM clock

int main() {

    float dc = 0;
    int value = 0;

    wiringPiSetupGpio();
    pinMode(RED_LED_PIN, PWM_OUTPUT);   // Set pin mode for GPIO pin
    pinMode(GREEN_LED_PIN, PWM_OUTPUT); // Set pin mode for GPIO pin
    pwmSetMode(PWM_MODE_MS);       

    while(1){
        printf("Enter duty cycle: ");
        scanf("%f", &dc);
        value = (dc / 100) * 1024;
        pwmWrite(RED_LED_PIN, value);
        pwmWrite(GREEN_LED_PIN, value);
    }

    return 0;

}