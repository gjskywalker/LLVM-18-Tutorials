#include "HI_FindFunction.h"
#include "HI_print.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <ios>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace llvm;

bool HI_FindFunctions::runOnModule(
    Module &M) // The runOnModule declaration will overide the virtual one in ModulePass, which will
               // be executed for each Module.
{
    for (Module::iterator GI = M.begin(), GE = M.end(); GI != GE;
         ++GI) // Module iterator is used to iterate the functions in the module, ++GI is better
               // than GI ++, for the sake of stability
    {
        *Function_Demangle << "Found function Definition named == " << GI->getName()
                           << "\n"; // a Function class is inherited from Value class, which has a
                                    // function to get the name of the value (function).
        std::string fname(GI->getName().str());
        if (fname[0] == '_')
        {
            *Function_Demangle << "     its demangled name == "
                               << DemangleFunctionName(GI->getName().str()) << "\n";
            Function_Demangle_Map[GI->getName().str()] = DemangleFunctionName(fname);
        }
    }

    // for (Function &F : M)
    // {
    //     if (F.getName().find("llvm.") != std::string::npos) // bypass the "llvm.xxx" functions..
    //         continue;
    //     if (F.getName().find("HIPartitionMux") != std::string::npos) // bypass the "llvm.xxx" functions..
    //         continue;
    //     // SE = &getAnalysis<ScalarEvolutionWrapperPass>(F).getSE();
    //     for (BasicBlock &B : F)
    //     {
    //         for (Instruction &I : B)
    //         {
    //             if (SE->isSCEVable(I.getType()))
    //             {
    //                 // llvm::errs() << "Instruction: " << I << " is SCEVable\n";
    //                 auto tmp_S = SE->getSCEV(&I);
    //                 *Function_Demangle << "Instruction: " << I << " SCEV: " << *tmp_S << "\n";
    //             }
    //             else
    //             {
    //                 *Function_Demangle << "Instruction: " << I << " is not SCEVable\n";
    //             }
    //         }
    //     }
    // }

    *Function_Demangle
        << "===============printing the module ====================================\n";
    *Function_Demangle << M << "\n";
    Function_Demangle->flush();
    return false;
}

char HI_FindFunctions::ID =
    0; // the ID for pass should be initialized but the value does not matter, since LLVM uses the
       // address of this variable as label instead of its value.

void HI_FindFunctions::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.setPreservesAll();
    AU.addRequiredTransitive<ScalarEvolutionWrapperPass>();
}
