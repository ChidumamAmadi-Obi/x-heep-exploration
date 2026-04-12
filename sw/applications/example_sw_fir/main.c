#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define NUM_SENSOR_VALUES 50
#define NUM_TAPS 8

int sensorValues(uint32_t max) {
    return (rand() % (max + 1));
}

float firFilter(float rawSensorValue) {
    float accumulator=0;
    float coefficients[NUM_TAPS]={0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1, 0.05};
    static float shiftRegister[NUM_TAPS]={0, 0, 0, 0, 0, 0, 0, 0};
    static uint8_t index=0; 
    
    for (int i=NUM_TAPS-1; i > 0; i--) { // shift all values to make room for new one
        shiftRegister[i]=shiftRegister[i-1];
    }
    shiftRegister[0]=rawSensorValue;

    for (int i = 0; i < NUM_TAPS; i++) {
        accumulator += shiftRegister[i] * coefficients[i];
    }
    return accumulator;
}

int main(int argc, char *argv[]) {
    int incomingSensorValue=0;
    float filteredSensorValue=0;

    printf("\n  NO.   RAW   FILTERED\n\n");
    for (int i=0; i < NUM_SENSOR_VALUES; i++) {
        incomingSensorValue=sensorValues(10);
        filteredSensorValue=firFilter((float)incomingSensorValue);
        
        printf("  %d  ->  %d   %f\n", i, incomingSensorValue, filteredSensorValue);
    }
    return EXIT_SUCCESS;
}