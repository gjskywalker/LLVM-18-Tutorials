Here, the template of the information of instruction is explained.

Take the instruction "mul" as example:

34 58 48 7 9 328 82 4 5.6 1 MulnS

These parameters are:
the bitwidth of input operandA (-1 means unrelated to bitwidth, e.g. double-floating point)
the bitwidth of input operandB 
the bitwidth of output operandC 
the period of clock
the DSP cost of the instruction at the specific clock  
the FF cost of the instruction at the specific clock   
the LUT cost of the instruction at the specific clock   
the latency (X cycles) of the instruction at the specific clock
the extra delay (Y ns) of the instruction at the specific clock (The total timing cost of the instruction = X cycles * clock_period + Y ns)
the number of initial interval cycles
the ip core used for the instruction

This line is not accurate, I add this to meet the testing requirements. The whole HLS_Data_Lib is not completed, we need to write some scripts to rebuild it.  
3 3 3 10 0 0 13 0 2.34 1 Mul