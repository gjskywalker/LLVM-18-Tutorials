#include "HI_ArrayInfo.h"

using namespace llvm;

bool HI_ArrayInfo::runOnModule(Module &M)
{
    for (auto &it : M.global_values())
    {
        if (DEBUG)
        {
            *Array_out << "Global Value: " << it.getValueName() << "\n";
            *Array_out << "Type: " << *it.getValueType() << "\n";
        }
        if (it.getValueType()->isArrayTy())
        {
            if (DEBUG)
                *Array_out << "Global Array: " << it.getValueName() << "\n";
            Target2ArrayInfo_ref[&it] = getArrayInfo(&it);
        }
    }
    bool find = false;
    for (auto &F : M)
    {
        if (F.getName().find("llvm.") != std::string::npos)
            continue;
        if (F.getName().find("HIPartitionMux") != std::string::npos)
            continue;
        LI = &getAnalysis<LoopInfoWrapperPass>(F).getLoopInfo();
        SE = &getAnalysis<ScalarEvolutionWrapperPass>(F).getSE();
        for (auto it = F.arg_begin(); it != F.arg_end(); it++)
        {
            if (it->getType()->isPointerTy())
            {
                if (DEBUG)
                    *Array_out << "Argument Array: " << it->getName() << "\n";
                Target2ArrayInfo_ref[it] = getArrayInfo(it);
            }
        }
        for (auto &B : F)
        {
            for (auto &I : B)
            {
                if (auto alloc = dyn_cast<AllocaInst>(&I))
                {
                    if (DEBUG)
                        *Array_out << "Local Array: " << I.getName() << "\n";
                    Target2ArrayInfo_ref[&I] = getArrayInfo(&I);
                }
            }
        }
    }
    // TODO: for some cases the complete array information is not available, we chose to set the following defualt values to keep correct compilation flow.
    // TODO: The default values are: num_dims = 1, dim_size[0] = 1, total_ele = 1, elementType = it.first->getType(), isArgument = true; This can affect the resource estimation but has tiny effect on latency estimation.
    for (auto &it : Target2ArrayInfo_ref)
    {
        if (it.first)
        {
            if (it.second->dim_size[0] == 0)
            {
                it.second->num_dims = 1;
                it.second->dim_size[0] = 1;
                it.second->total_ele = 1;
                // it.second->elementType = it.first->getType();
                it.second->isArgument = true;
            }
        }
        else
            assert(false && "The target should not be nullptr.");
    }
    Array_out->flush();
    return false;
}
char HI_ArrayInfo::ID =
    0; // the ID for pass should be initialized but the value does not matter, since LLVM uses the
// address of this variable as label instead of its value.

ArrayInfo *HI_ArrayInfo::getArrayInfo(Value *V)
{
    ArrayInfo *AI = new ArrayInfo();
    if (auto GV = dyn_cast<GlobalVariable>(V))
    {
        auto tmp = GV->getValueType();
        while (auto array_T = dyn_cast<ArrayType>(tmp))
        {
            AI->dim_size[AI->num_dims] = array_T->getNumElements();
            AI->total_ele *= array_T->getNumElements();
            AI->num_dims++;
            tmp = array_T->getArrayElementType();
        }
        AI->elementType = tmp;
        if (DEBUG)
        {
            *Array_out << "Array: " << V->getName() << " has " << AI->num_dims << " dimensions. " << " and " << AI->total_ele << " elements.\n";
            *Array_out << "The element type is " << *AI->elementType << "\n";
            for (int i = 0; i < AI->num_dims; i++)
            {
                *Array_out << "Dimension " << i << " has size " << AI->dim_size[i] << "\n";
            }
        }
    }
    else if (auto arg = dyn_cast<Argument>(V))
    {
        AI->isArgument = true;
        bool find = false;
        GetElementPtrInst *GEP_Inst = nullptr;
        for (User *U : arg->users())
        {
            if (auto GEP = dyn_cast<GetElementPtrInst>(U))
            {
                GEP_Inst = GEP;
                find = true;
                auto tmp = GEP->getSourceElementType();
                AI->num_dims++;
                while (auto array_T = dyn_cast<ArrayType>(tmp))
                {
                    AI->dim_size[AI->num_dims] = array_T->getNumElements();
                    AI->total_ele *= array_T->getNumElements();
                    AI->num_dims++;
                    tmp = array_T->getArrayElementType();
                }
                AI->elementType = tmp;
                if (DEBUG)
                {
                    *Array_out << "Array: " << V->getName() << " has " << AI->num_dims << " dimensions. " << " and " << AI->total_ele << " elements.\n";
                    *Array_out << "The element type is " << *AI->elementType << "\n";
                    for (int i = 0; i < AI->num_dims; i++)
                    {
                        *Array_out << "Dimension " << i << " has size " << AI->dim_size[i] << "\n";
                    }
                }
                break;
            }
        }
        if (!find)
        {
            llvm::errs() << *V << "\n";
            llvm::errs() << "Unused argument.\n";
            // assert(find && "The target should be used by GEP instruction and this pass should be run before the HI_SeparateConstOffsetFromGEP pass.");
        }

        auto idx0 = GEP_Inst->idx_begin();
        if (auto inst = dyn_cast<Instruction>(idx0))
        {
            if (inst->getOpcode() == Instruction::PHI)
            {
                auto PHI = dyn_cast<PHINode>(inst);
                auto BB = PHI->getParent();
                if (Loop *L = LI->getLoopFor(BB))
                {
                    if (DEBUG)
                    {
                        *Array_out << "Array: " << V->getName() << " is in loop with header: " << L->getHeader()->getName() << "\n";
                    }
                    if (auto tripCount = SE->getSmallConstantTripCount(L))
                    {
                        AI->dim_size[0] = tripCount;
                        AI->total_ele *= tripCount;
                        if (DEBUG)
                        {
                            *Array_out << "Array: " << V->getName() << " has " << AI->num_dims << " dimensions " << " and " << AI->total_ele << " elements.\n";
                            *Array_out << "The element type is " << *AI->elementType << "\n";
                            for (int i = 0; i < AI->num_dims; i++)
                            {
                                *Array_out << "Dimension " << i << " has size " << AI->dim_size[i] << "\n";
                            }
                            *Array_out << "Since " << V->getName() << " is declared as an argument, the innermost loop trip count is used to approximate the size of the first dimension.\n";
                            // *Array_out << "Since normally the first idx of the GEP instruction is corresponding to the loop trip count.\n";
                        }
                    }
                    else
                    {
                        assert(false && "The loop trip count is not constant.");
                    }
                }
            }
        }
    }
    else
    {
        if (auto Inst = dyn_cast<Instruction>(V))
        {
            if (auto Alloc = dyn_cast<AllocaInst>(Inst))
            {
                auto tmp = Alloc->getAllocatedType();
                while (auto array_T = dyn_cast<ArrayType>(tmp))
                {
                    AI->dim_size[AI->num_dims] = array_T->getNumElements();
                    AI->total_ele *= array_T->getNumElements();
                    AI->num_dims++;
                    tmp = array_T->getArrayElementType();
                }
                AI->elementType = tmp;
                if (DEBUG)
                {
                    *Array_out << "Array: " << V->getName() << " has " << AI->num_dims << " dimensions. " << " and " << AI->total_ele << " elements.\n";
                    *Array_out << "The element type is " << *AI->elementType << "\n";
                    for (int i = 0; i < AI->num_dims; i++)
                    {
                        *Array_out << "Dimension " << i << " has size " << AI->dim_size[i] << "\n";
                    }
                }
            }
        }
    }
    return AI;
}
void HI_ArrayInfo::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.setPreservesAll();
    AU.addRequired<LoopInfoWrapperPass>();
    AU.addRequired<ScalarEvolutionWrapperPass>();
}
