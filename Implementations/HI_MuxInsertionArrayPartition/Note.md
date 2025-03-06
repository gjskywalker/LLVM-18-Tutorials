# Important Notice

Be careful!!!
There could be "llvm.xxxx" functions called in the llvm IR, which should be filtered, otherwise, some passes (like ScalarEvolutionWrapperPass) will go wrong!!!

In the LLVM 18.0.0 IR, array variables have different declaration methods.

1. Array variables as function arguments:
   1. In this case, array is degenerated into pointers;
2. Array variables declared within function:
   1. In this case, IR generates "allocate" instructions;
3. Array varaibles declared as global variable:
   1. In this case, IR generate @A [N [N * i32]] as array type;

For both methods, we can get array info by tracking getelement inst.
