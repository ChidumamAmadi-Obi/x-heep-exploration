# HOW TO USE

make -C util/docker docker-pull TAG=latest
make -C util/docker docker-run TAG=latest

STEP 3 HELLO WORLD
init_gcc
make mcu-gen CPU=cv32e40x 

 build with fpu
make verilator-build PROJECT=example_fir_accelerator FUSESOC_PARAM="--FPU=1 --COREV_PULP=1" ARCH=rv32imfc_zicsr_zifencei
make verilator-run-app PROJECT=example_fir_accelerator FUSESOC_PARAM="--FPU=1 --COREV_PULP=1" ARCH=rv32imfc_zicsr_zifencei

# WHAT I LEARNED
## CHALLENGES
 * learning how to generate registers and header files with regtool
 * learning how to use waivers
 * configuring cpu
 * increasing memory banks as the example app was too big
 * increase the size of ram/rom "Out of bound memory access 0x00010018"
 * build with fpu to use floating point values
 * floating point valuess are not being printed  when example program is run..., to fix this i needed to add "target_link_options(${MAINFILE}.elf PRIVATE "-Wl,-u,_printf_float")" to CMakeLists.txt
 * "0 Out of bound memory access 0xffffff7c %Error: ../../../hw/core-v-mini-mcu/system_bus.sv:223: Verilog $stop"
 * 
 * 
 *  
 *  