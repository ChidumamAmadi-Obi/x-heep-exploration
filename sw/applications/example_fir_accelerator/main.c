/* FIR ACCELERATOR EXAMPLE PROGRAM
*/

#include <stdlib.h>
#include <stdint.h>

#include "core_v_mini_mcu.h"
#include "fir_accelerator_driver.h" 

#define NUM_SENSOR_VALUES 50 // number of values to be filtered by fir accelerator (needs to be > 8)

FIRAcceleratorStatus errorCode;

int sensorValues(uint32_t max){ // emulate incoming sensor values by generating random numbers
    return (rand() % (max + 1)); // return gen random values between max and 0
}

int main(int argc, char *argv[]){
    int incomingSensorValue=0;
    float coefficients[8] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1, 0.05};
    float filteredSensorValue=0;

    printf("\e[0;36m===================================\e[0m\n"); // use ansi escape codes to print in color so i can see
    printf("  \e[1;37mFIR ACCELERATOR EXAMPLE PROGRAM\e[0m\n");
    printf("\e[0;36m===================================\e[0m\n"); 
    printf("  FIR_ACC_PERIPH BASE: \e[1;37m0x%08x\e[0m\n", (unsigned int)FIR_ACC_PERIPH); // check to see if accelerator is present
    printf("\e[0;36m===================================\e[0m\n"); 

    // **********************************************************************

    errorCode=firInit(); // initialize accelerator and get error code
    if (errorCode != NONE) {
        printf("\n\e[0;31m ERROR, FAILED TO INITIALIZE ACCELERATOR \e[0m\n");
        return -1;
    }

    firLoadCoefficientBatch(coefficients);

    printf("  NO.   RAW   FILTERED\n\n");
    for (int i=0; i<=NUM_SENSOR_VALUES; i++) {
        incomingSensorValue=sensorValues(10);
        firSendData((float)incomingSensorValue);
        wait(WAIT_CYCLES);
        errorCode=firReadResult(&filteredSensorValue); // get result and store in filteredSensorValue
        wait(WAIT_CYCLES);

        if (errorCode != NONE) {
            printf("\n\e[0;31m ERROR, NULL POINTER \e[0m\n");
            return -1;
        }
        if (i < 8) printf("  %d  ->  %d   %f\n", i, incomingSensorValue, filteredSensorValue); // visualize how the first 8 results should be discarded
        else printf("  %d  ->  \e[0;36m%d\e[0m   \e[1;36m%f\e[0m\n", i, incomingSensorValue, filteredSensorValue);
    }
    printf("\e[0;36m===================================\e[0m\n"); 

    return EXIT_SUCCESS;
}