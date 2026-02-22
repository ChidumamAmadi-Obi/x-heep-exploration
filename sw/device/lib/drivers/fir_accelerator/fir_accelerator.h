// Generated register defines for fir_accelerator

#ifndef _FIR_ACCELERATOR_REG_DEFS_
#define _FIR_ACCELERATOR_REG_DEFS_

#ifdef __cplusplus
extern "C" {
#endif
// Register width
#define FIR_ACCELERATOR_PARAM_REG_WIDTH 32

// Control register
#define FIR_ACCELERATOR_CONTROL_REG_OFFSET 0x0
#define FIR_ACCELERATOR_CONTROL_ACCELERATE_EN_BIT 0
#define FIR_ACCELERATOR_CONTROL_COEFF_WRITE_EN_BIT 1
#define FIR_ACCELERATOR_CONTROL_CLR_C_BIT 2
#define FIR_ACCELERATOR_CONTROL_BUSY_BIT 3

// address of coefficient
#define FIR_ACCELERATOR_COEFF_ADDR_REG_OFFSET 0x4
#define FIR_ACCELERATOR_COEFF_ADDR_ADDR_MASK 0x7
#define FIR_ACCELERATOR_COEFF_ADDR_ADDR_OFFSET 0
#define FIR_ACCELERATOR_COEFF_ADDR_ADDR_FIELD \
  ((bitfield_field32_t) { .mask = FIR_ACCELERATOR_COEFF_ADDR_ADDR_MASK, .index = FIR_ACCELERATOR_COEFF_ADDR_ADDR_OFFSET })

// coefficients in
#define FIR_ACCELERATOR_COEFF_DATA_REG_OFFSET 0x8

// Put your sensor reading here
#define FIR_ACCELERATOR_SENSOR_DATA_REG_OFFSET 0xc


#define FIR_ACCELERATOR_RESULT_REG_OFFSET 0x10


#define FIR_ACCELERATOR_STATUS_REG_OFFSET 0x14
#define FIR_ACCELERATOR_STATUS_RESULT_VALID_BIT 0

#ifdef __cplusplus
}  // extern "C"
#endif
#endif  // _FIR_ACCELERATOR_REG_DEFS_
// End generated register defines for fir_accelerator