#include <stdio.h>
#include <stdio.h>
#include <pigpio.h>

#define RED_LED_PIN 18          // Broadcom (BCM) GPIO pin for Red LED     (PWM Channel: 0)
#define GREEN_LED_PIN 13        // Broadcom (BCM) GPIO pin for Green LED   (PWM Channel: 1)
#define PWM_MAX 1000000             // Maximum value for PWM GPIO pin (Range: 0 - 1000000)
#define MAX_FREQ 125000000      // range from 1 to 125000000


// Function to calculate the duty cycle value
int setDutyCycle(float duty_cycle){
    int value = PWM_MAX  * (duty_cycle / 100); // Calculate value to set for a given duty cycle percentage
    return value;
}

int main() {
    if (gpioInitialise() < 0)
    {
    // pigpio initialisation failed.
    }
    else
    {
        printf("success!\n");
    // pigpio initialised okay.
    }

    float rfreq = 0, gfreq = 0;
    int rdc = 0, gdc = 0;
    printf("RED LED: Frequency = %d, Duty Cycle = %d\n", gpioGetPWMfrequency(RED_LED_PIN), gpioGetPWMdutycycle(RED_LED_PIN));
    printf("GREEN LED: Frequency = %d, Duty Cycle = %d\n", gpioGetPWMfrequency(GREEN_LED_PIN), gpioGetPWMdutycycle(GREEN_LED_PIN));
    // while(1){
    //     printf("Enter frequency and duty cycle percentage for red LED: ");
    //     scanf("%f %d", &rfreq, &rdc);
    //     printf("Enter frequency and duty cycle percentage for green LED: ");
    //     scanf("%f %d", &gfreq, &gdc);
    //     gpioHardwarePWM(RED_LED_PIN, rfreq, setDutyCycle(rdc));
    //     gpioHardwarePWM(GREEN_LED_PIN, gfreq, setDutyCycle(gdc));
    // }
    printf("Enter frequency and duty cycle percentage for red LED: ");
    scanf("%f %d", &rfreq, &rdc);
    printf("Enter frequency and duty cycle percentage for green LED: ");
    scanf("%f %d", &gfreq, &gdc);
    gpioHardwarePWM(RED_LED_PIN, rfreq, setDutyCycle(rdc));
    gpioHardwarePWM(GREEN_LED_PIN, gfreq, setDutyCycle(gdc));
    // gpioHardwarePWM(GREEN_LED_PIN, MAX_FREQ, setDutyCycle(100));

    gpioTerminate(); // Terminate pigpio library before end of program execution
    return 0;

}
