# LLVM_exp6_GEP_Transformation


Since in HLS, the GEP instruction is actually done by multiplication and additions, which are used to get the 1-D offset of an element in a multiple-dimensional array.
As I found, the SeparateConstOffsetFromGEP pass, with the LowerGEP flag set true, can actually achieve such function. 
However, the major problem is that the pass handle the memeory space by byte but in FPGA the memory space is much more flexible.
Therefore, we need to improve the pass to adpapt to the HLS design.

Note that:

`addRequiredTransitive` means that one pass relies on another pass for its entire lifetime. It is a very strict constraint and should be used carefully.

> The difference between `addRequired` and `addRequiredTransitive` is as follows:

* `AddRerequired`
  * This method is used to declare that the current pass requires another pass to be executed before it.
  * The required pass will be run before the current pass, but only if it has not already been run.
  * It ensures that the required pass is available for the current pass.
* `AddRequiredTransitive`
  * This method is similar to addRequired, but it also ensures that any passes required by the required pass are also run.
  * It creates a transitive dependency, meaning that not only the required pass but also all of its dependencies will be executed before the current pass.
  * This is useful when the required pass itself has dependencies that need to be satisfied.

The test can be run with the following command:

      ./LLVM_expXXXXX  <C/C++ FILE> <top_function_name>