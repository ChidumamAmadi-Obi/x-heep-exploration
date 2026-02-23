`ifndef CONSTANTS // file guard
`define CONSTANTS

`define DATA_WIDTH 32 // 32 bit mcu
`define NUM_REGS 8

localparam FIR_DATA_WIDTH = `DATA_WIDTH; // 32 bit mcu
localparam Q_FORMAT = `DATA_WIDTH/2;
localparam NUM_REGS = `NUM_REGS; // 

// https://learn.verificationstudio.com/tutorials/1/systemverilog-tutorial/subcontents/10/randomization

`endif
