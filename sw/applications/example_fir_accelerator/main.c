/* FIR ACCELERATOR EXAMPLE PROGRAM
*/

#include <stdlib.h>
#include <stdint.h>

#include "core_v_mini_mcu.h"
#include "fir_accelerator_driver.h" 

#define NUM_SENSOR_VALUES 20 // number of values to be filtered by fir accelerator (needs to be > 8)

#define COLOR_YELLOW printf("\x1b[33m"); // terminal colors
#define COLOR_BOLD_YELLOW printf("\x1b[1;33m");
#define COLOR_RESET printf("\x1b[0m");

FIRAcceleratorStatus errorCode;

float sensorValues(uint32_t max){ // emulate incoming sensor values by generating random numbers
    return (float)(rand() % (max + 1)); // gen random values between max and 0
}

int main(int argc, char *argv[]){

    float coefficients[8] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1, 0.05};
    float incomingSensorValue=0;
    float filteredSensorValue=0;

    COLOR_BOLD_YELLOW // change color output so i can see
    printf("\n\n    --FIR ACCELERATOR EXAMPLE PROGRAM-- \n");
    printf("    FIR_ACC_PERIPH BASE: 0x%08x\n", (unsigned int)FIR_ACC_PERIPH); // check to see if accelerator is present
    printf("    STATUS REGISTER: 0x%08lx\n", FIR_ACC_PERIPH->STATUS);
    COLOR_RESET

    // **********************************************************************

    COLOR_YELLOW
    //errorCode=NONE; // initialize accelerator and get error code
    errorCode=firInit(); // initialize accelerator and get error code
    if (errorCode != NONE) {
        printf("ERROR, FAILED TO INITIALIZE ACCELERATOR");
        return -1;
    }

    firLoadCoefficientBatch(coefficients);
    for (int i=0; i<NUM_SENSOR_VALUES; i++) {
        incomingSensorValue=sensorValues(10);
        firSendData(incomingSensorValue);
        errorCode=firReadResult(&filteredSensorValue); // get result and store in filteredSensorValue

        if (errorCode != NONE) {
            printf("ERROR, NULL POINTER");
            return -1;
        }

        printf("    Value In: %d Value Out: %f\n", incomingSensorValue, filteredSensorValue);
    }
    COLOR_RESET
    return EXIT_SUCCESS;
}