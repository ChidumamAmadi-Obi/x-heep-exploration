/* SHIFT REGISTER MODULE
on every positive edge, add new raw register value to the 
shift register, then paralell out all elements in shift register
*/

`include "constants.svh"

module shiftReg (
    input logic clk,
    input logic rst,
    input logic [FIR_DATA_WIDTH-1:0] sDataIn,  // serial data in
    output logic [FIR_DATA_WIDTH-1:0] pDataOut[0:NUM_REGS-1]  // parallel data out
);

  logic [FIR_DATA_WIDTH-1:0] sReg[0:NUM_REGS-1];  // shift register

  always @(posedge clk) begin  // sequential logic
    if (rst == 1) begin  // if reset, set all registers to zero
      for (integer i = 0; i < NUM_REGS; i++) begin
        sReg[i] <= 0;
      end
    end else begin  // else, shift over one to make room for sDatain
      for (integer i = NUM_REGS - 1; i > 0; i--) begin
        sReg[i] <= sReg[i-1];
      end
      sReg[0] <= sDataIn;  // insert serial data in
    end
  end

  always_comb begin  // combinational output
    for (integer i = 0; i < NUM_REGS; i++) begin
      pDataOut[i] = sReg[i];
    end
  end
endmodule
