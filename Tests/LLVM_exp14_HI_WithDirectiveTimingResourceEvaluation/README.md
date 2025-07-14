# HI_WithDirectiveTimingResourceEvaluation

HI_WithDirectiveTimingResourceEvaluation pass is used to evaluate the timing and resource of the application, considering the effect of HLS directives.

Here, I mainly consider array partitioning, loop pipelining and loop unrolling.
When adding pragmas, please add the requirement pragma in `config.txt` file, the loop label will be automatically added
during the compilation. The nameing rule for loop label is `Loop_funcname_id`. Users can find them in `tmp.cc` file.

Examples for pragma writing:

`

1. array_partition variable=A scope=Loop\_\_2mm_1 dim=1 factor=2 cyclic=1
2. loop_unroll label=Loop\_\_2mm_1 factor=2
3. loop_pipeling label=Loop\_\_2mm_1 factor=2

`

Basic implementation idea:

0. Mapping some information between IR and source code, so we can determine the outermost size of the array in the parameters of function and set the directives of loops.

1. Array partitioning: Using SCEV, the pass can get the pattern of array accesses. In the analysis of array partitioning, we emulate the loop, and find which partitons the access will tough during the entire process of loop. Based on the access pattern, the map from accesses to partitions can be determined. According to the map and the port limitation of BRAMs, we can schedule the array accesses. Please note that we do not split arrays in IR but just record the accesses and their corresponding partitions for scheduling. We suppose that the array partitioning should be done at back-end (CodeGen)

2. Loop unrolling: we mimic the procedure of loop unrolling passes from LLVM and we transform the IR before we do the timing/resource evaluation. By doing so, we can exactly check which component among the unrolled iterations can be reused, e.g. address calculation. Moreover, there are some BRAM access optimization can be done to remove the redundant accesses to BRAM. Finally, after IR transformation, we can exactly check access patterns. All these situations cannot be analyzed by using mathematic models like the one proposed by COMBA.

3. Loop pipelining: since we cannot implement pipeline in the IR level, we use loop label to mark which loop should be pipelined. During the evaluation, the loop requested to be pipelined will be checked and the proper initial interval will be found.

4. Muxes will be inserted for array partitions.

Moreover, many other optimizations are involved for this test:
a) Mul2Shl
b) MulOrderOpt
c) RemoveRedundantAccess
d) SwitchLower
