# HI_FindFunctions

The HI_FindFunction pass is mainlyed tested by LLVM_exp0_find_functions

HI_FindFunction Pass is just a HelloWorld-level pass, showing the template of the construction of Pass in LLVM. Detailed explanation can be found in the source code's comments.


The following line is used to demangle a mangled function name in IR: e.g.   _ZN6ap_intILi271EEC2Ei ==> ap_int<271>::ap_int(int)

(abi::__cxa_demangle(functioname.c_str(), NULL, &size, &status));