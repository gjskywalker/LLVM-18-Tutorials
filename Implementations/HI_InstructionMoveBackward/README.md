# HI_InstructionMoveBackward

The HI_InstructionMoveBackward pass is used to move the instructions from the original block to the dominator block if possible, so in HLS, the parallelism can be improved.

This pass is based on the DominatorTreeWrapperPass in LLVM. As for the problem, what is dominator tree, please refer to https://en.wikipedia.org/wiki/Dominator_(graph_theory).


the rought implementation idea is shown below:

1. loop to find the lowest node in Dominator Tree, which should not be preocessed previously, to process
2. mark the block processed
3. obtain the instruction independent with those PHI nodes
4. move those specific instructions to dominator block