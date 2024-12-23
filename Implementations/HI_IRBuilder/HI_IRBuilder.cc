#include "HI_IRBuilder.h"

using namespace llvm;

void HI_IRBuilder::insertInstructionsBefore(llvm::Instruction *targetInst)
{
    llvm::LLVMContext &context = targetInst->getContext();
    *(this->IRBuilder_log) << "Inserting instructions before: " << *targetInst << "\n";
    *(this->IRBuilder_log) << "The context about this instruction is" << &context << "\n";
    llvm::IRBuilder<> builder(context);

    // Set the insertion point to the target instruction
    builder.SetInsertPoint(targetInst);

    // Example: Create a new floating-point addition instruction before the target instruction
    llvm::Value *lhs = llvm::ConstantFP::get(llvm::Type::getFloatTy(context), 1.0);
    llvm::Value *rhs = llvm::ConstantFP::get(llvm::Type::getFloatTy(context), 2.0);
    llvm::Value *sum = builder.CreateFAdd(lhs, rhs, "sum");

    // Create a variable (alloca instruction) to store the result
    llvm::Function *parentFunction = targetInst->getFunction();
    llvm::IRBuilder<> entryBuilder(&parentFunction->getEntryBlock(), parentFunction->getEntryBlock().begin());
    llvm::AllocaInst *variable = entryBuilder.CreateAlloca(llvm::Type::getFloatTy(context), nullptr, "variable");

    // Store the result in the variable
    builder.CreateStore(sum, variable);
}

bool HI_IRBuilder::runOnModule(
    Module &M) // The runOnModule declaration will overide the virtual one in ModulePass, which will
               // be executed for each Module.
{
    for (auto &F : M)
    {
        for (auto &BB : F)
        {
            for (auto &I : BB)
            {
                if (auto *inst = dyn_cast<Instruction>(&I))
                {
                    insertInstructionsBefore(inst);
                }
            }
        }
    }
    return true;
}

char HI_IRBuilder::ID =
    0; // the ID for pass should be initialized but the value does not matter, since LLVM uses the
       // address of this variable as label instead of its value.

void HI_IRBuilder::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.setPreservesAll();
}
