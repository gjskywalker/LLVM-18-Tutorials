## HI_DependenceList Pass

The HI_DependenceList pass is mainlyed tested by LLVM_exp1_dependence_list

HI_DependenceList pass extracts the dependence between Instructions. Detailed explanation can be found in the source code's comments.

To implement this pass, different iterators are used in to iterate functions, blocks and instrucions (and their successors(users))

Please note that the pass is implemented with doInitialization() and doFinalization() functions, since sometimes somehow, a pass could be called more than one times, which makes doInitialization and finalization important.

e.g.


for (User *U : (I)->users())

for (auto Succ_it : successors(B))

for (Instruction &I: B) 

for (BasicBlock &B : F) 