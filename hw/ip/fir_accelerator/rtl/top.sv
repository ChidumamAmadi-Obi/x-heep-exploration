/* TOP MODULE OF FIR ACCELERATOR FOR THE PULP CV32E40X

*/

`include "constants.svh"

module top (
    input logic clk,
    input logic rstN,  // active low reset
    input logic clrC,  // clear coeffs in register file
    input logic accelerateEn,  // to enable accelerator
    input logic coeffWriteEn,  // write enable sig for coeffs
    input logic [2:0] coeffAddress,  // 3 bit address for coeffs
    input logic [FIR_DATA_WIDTH-1:0] rawSensorVal,
    input logic [FIR_DATA_WIDTH-1:0] coeffIn,  // coefficient
    output logic [FIR_DATA_WIDTH-1:0] macResult,  // result
    output logic resultIsValid,
    output logic busy
);

  // internal signals and registers
  logic [FIR_DATA_WIDTH-1:0] pDataIntoMac[0:NUM_REGS-1];
  logic [FIR_DATA_WIDTH-1:0] coefficientRegs[0:NUM_REGS-1];  // coeff register file
  logic [FIR_DATA_WIDTH-1:0] macResultWire;
  logic [1:0] accelerateEnSync;  // 2 stage sync reg
  logic accelerateEnSyncClean;  // synced and clean signal 

  always_ff @(posedge clk or negedge rstN) begin  // 2-stage synchronizer with asynch reset
    if (!rstN) begin
      accelerateEnSync <= 2'b00;
    end else begin  // shift reg: stage0 gets async input, stage1 gets stage0
      accelerateEnSync[0] <= accelerateEn;
      accelerateEnSync[1] <= accelerateEnSync[0];
    end
  end
  assign accelerateEnSyncClean = accelerateEnSync[1];

  always_ff @(posedge clk or negedge rstN) begin  // loads coeffin value into coeff reg file
    if (clrC) begin  // clear coeffs
      for (integer i = 0; i < NUM_REGS; i++) begin
        coefficientRegs[i] <= '0;  // initialize all coefs to 0
      end
    end else if (coeffWriteEn) begin  // if enebled write vals to coeff regs
      coefficientRegs[coeffAddress] <= coeffIn;
    end
  end

  shiftReg shiftRegInstance (
      .clk(clk),
      .rst(!rstN),  // convert reset sig to active high
      .sDataIn(rawSensorVal),
      .pDataOut(pDataIntoMac)
  );
  mac macInstance (
      .pDataIn(pDataIntoMac),
      .coefs(coefficientRegs),
      .macResult(macResultWire)
  );

  always_ff @(posedge clk or negedge rstN) begin  // output result to register with enable
    if (!rstN || clrC) begin
      macResult <= '0;
      resultIsValid <= 1'b0;
    end else if (accelerateEnSyncClean) begin
      macResult <= macResultWire;
      resultIsValid <= 1'b1;  // sig valid result
    end else begin
      resultIsValid <= 1'b0;
    end
  end

  assign busy = accelerateEnSyncClean;  // accelerator is busy wehen its enabled and computing
endmodule
