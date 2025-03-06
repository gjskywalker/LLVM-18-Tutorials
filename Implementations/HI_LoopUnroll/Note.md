# Loop Unrolling Passes 

There are certain passes we need to perform before loop unrolling:

1. Loop-Simplify;
2. Loop-Rotate;
3. Loop-Closed-SSA; (After lcssa, there are some redundant phi instructions which can be removed by -instcombine pass)