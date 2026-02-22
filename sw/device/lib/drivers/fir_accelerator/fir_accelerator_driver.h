#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "core_v_mini_mcu.h"
#include "fir_accelerator.h"

// PERIPHERAL STRUCTS **************************************************************************************
typedef uint32_t ufp32_t; // fixed point
typedef struct{ // saccess all registers in accelerator from peripheral struct
    volatile uint32_t CTRL;
    /* control register bits:
    bit 0 = accelerate enable
    bit 1 = coeff write enable
    bit 2 = clear coeffs
    bit 3 = busy
    */    

    volatile uint32_t CADDR; // input coefficient address to write to 
    volatile uint32_t CDATA; // input coefficient
    volatile uint32_t DATAI; // input unfiltered data

    // read only...
    volatile const uint32_t DATAO; // filteredd data out
    volatile const uint32_t STATUS;  // bit 0 = result valid
}FIRAcceleratorPeriph;

// ENUMS **************************************************************************************************
typedef enum{ // keep track of accelerator error codes
    NONE,           // no errors occured
    TIME_OUT,
    OUT_OF_BOUNDS,  // user is trying to access something that does not exist/ outof bounds
    INVALID         // invalid 
} FIRAcceleratorStatus;
typedef enum{ // error codes when reading registers
    INVALID_READ = 0xDEADBEEF
} ReadErrors;
typedef enum{ // valid coeff addresses
    C_0,
    C_1,
    C_2,
    C_3,
    C_4,
    C_5,
    C_6,
    C_7
} CoefficientAddresses;

// MACROS **************************************************************************************************
/* fixed point conversions 
the accelerator does fixed point arithmetic, 
convertions need to be made before reading & writing to the peripheral
*/

#define Q_FORMAT FIR_ACCELERATOR_PARAM_REG_WIDTH/2 // 16 decimal places (Q16.16)
#define SCALE (1 << Q_FORMAT)
#define FL2FP(value) (ufp32_t)(value * SCALE + (value >= 0 ? 0.5 : -0.5)) // floating point to fixed point conversion
#define I2FP(value) (((ufp32_t)(value)) << Q_FORMAT) // 32 bit int to fixed point conversion
#define FP2FL(value) ((float)value/SCALE) // fixed point to floating point conversion

// init peripheral struct into memory address (defined in core_v_mini_mcu.h)
#define FIR_ACC_PERIPH ((FIRAcceleratorPeriph*) FIR_ACCELERATOR_START_ADDRESS)
#define NUM_COEFF_REGS 8

// configure delay macros ( will be replaced with proper timer implimentation later)
#define SLEEP_ASM asm volatile("nop");
#define WAIT_CYCLES 255
#define TIMEOUT_COUNT 100

// DECLARATIONS ********************************************************************************************
void wait(uint8_t cycles); 

void firEnable(bool en);
void firCWEnable(bool en); // coefficient write enable
void firCClear(); // clear coefficient register file
void firRClear(); // clear writeable registers
void firRst();
void firSendData(float dataIn); // send data to be filtered

FIRAcceleratorStatus firInit();
FIRAcceleratorStatus firLoadCoefficient(uint8_t coeffAddr, float coeffIn); 
FIRAcceleratorStatus firLoadCoefficientBatch(float coeffsIn[NUM_COEFF_REGS]);
FIRAcceleratorStatus firReadResult(float*dataOut);
