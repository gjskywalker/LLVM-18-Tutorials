# LLVM Exp8 VarWidthReduce

LLVM_exp8_VarWidthReduce is used to test the pass HI_VarWidthReduce

The HI_VarWidthReduce pass is used to shrink the bitwidth of the varaibles which have predictale range. This can reduce the hardware cost in HLS.

T T now you can see that implement a HLS pass is not that easy like you thought before... it could be... a lot of dirty work.

0. Using IRBuilder, you can genenrate and insert IR instruction much easier:
    IRBuilder<> Builder(XXXX);  // tell LLVM insert instruction before XXXX
    XXXXInst * tmp_XXXXInst = Builder.createXXXInst(.....)

1. When Handling bitwidth in LLVM, you need to be very very very very very careful to ensure those operands have the bit-width, otherwise you may get strange error, during compilation or running.

2. When you try to remove an instruction from BasicBlock by using ->eraseFromParent in for (instruction &I : B), you need to be careful, because sometime when you are removing an instruction, you are actually destroy the list of instructions for a block. That could lead to segmentation fault.


The test can be run with the following command:

      ./LLVM_expXXXXX  <C/C++ FILE> <top_function_name>   