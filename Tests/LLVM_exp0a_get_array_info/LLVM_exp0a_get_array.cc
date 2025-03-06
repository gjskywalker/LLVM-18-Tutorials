#include "HI_DataInfo.h"
#include "HI_ArrayInfo.h"
#include "HI_print.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include <map>
#include <fstream>
#include <ios>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace llvm;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        errs() << "Usage: " << argv[0] << " <C/C++ file>\n";
        return 1;
    }

    // Compile the source code into IR and Parse the input LLVM IR file into a module
    SMDiagnostic Err;
    LLVMContext Context;
    std::string cmd_str = "clang -O1 -emit-llvm -S " + std::string(argv[1]) + " -o top.bc";
    print_cmd(cmd_str.c_str());
    system(cmd_str.c_str());

    std::unique_ptr<Module> Mod(parseIRFile("top.bc", Err, Context));
    if (!Mod)
    {
        Err.print(argv[0], errs());
        return 1;
    }

    // Create a pass manager and fill it with the passes we want to run.
    legacy::PassManager PM;

    std::map<Value *, ArrayInfo *> Target2ArrayInfo;
    bool DEBUG = true;
    auto loopinfo = new LoopInfoWrapperPass();
    PM.add(loopinfo);
    auto scalarevolution = new ScalarEvolutionWrapperPass();
    PM.add(scalarevolution);
    HI_ArrayInfo *hi_arrayinfo = new HI_ArrayInfo("ArrayInfo", Target2ArrayInfo, DEBUG);
    PM.add(hi_arrayinfo);
    PM.run(*Mod);

    return 0;
}
