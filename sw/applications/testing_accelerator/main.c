#include <stdio.h>
#include <stdlib.h>

#include "core_v_mini_mcu.h"
#include "fir_accelerator_driver.h" 

#define COLOR_RESET printf("\x1b[0m");

FIRAcceleratorStatus errorCode;

float sensorValues(uint32_t max){ // emulate incoming sensor values by generating random numbers
    return (float)(rand() % (max + 1)); // gen random values between max and 0
}

int main(int argc, char *argv[]) {
    /* write something to stdout */
    printf("\x1b[1;32mTESTING FIR ACCELREATOR\n");
    printf("FIR_ACC_PERIPH BASE: 0x%08x\n", (unsigned int)FIR_ACC_PERIPH); // check to see if accelerator is present
    printf("STATUS REGISTER: 0x%08lx\n", FIR_ACC_PERIPH->STATUS);


// *****************************************************************************************************************************

    errorCode=firInit(); 
    printf("ACCELERATOR INITIALIZED SUCCESSFULLY... %d\n",errorCode);

    float coefficients[8] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1, 0.05};
    errorCode=firLoadCoefficientBatch(coefficients); 
    printf("COEFFICIENT BATCH LOADED SUCCESSFULLY... %d\n",errorCode);

    float incomingSensorValue=0;
    float filteredSensorValue=0;

    for (int i=0; i<50; i++) {
        incomingSensorValue=sensorValues(10);
        firSendData(incomingSensorValue);
        printf("DATA %f SENT SUCCESSFULLY...\n",incomingSensorValue);

        errorCode=firReadResult(&filteredSensorValue);
        printf("FILTERED %f... %d\n",filteredSensorValue, errorCode);        
    }

    COLOR_RESET
    return EXIT_SUCCESS;
}