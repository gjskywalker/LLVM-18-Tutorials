#ifndef _HI_IRBUILDER
#define _HI_IRBUILDER
// related headers should be included.
#include "HI_print.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopAccessAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Demangle/Demangle.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/Support/GraphWriter.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/Transforms/Utils/LoopVersioning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include <array>
#include <bits/stl_map.h>
#include <cstdio>
#include <cxxabi.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

using namespace llvm;

class HI_IRBuilder : public ModulePass
{
public:
    HI_IRBuilder() : ModulePass(ID)
    {
        IRBuilder_log = new raw_fd_ostream("IRBuilder_log", ErrInfo, sys::fs::OF_None);
    } // define a pass, which can be inherited from ModulePass, LoopPass, FunctionPass and etc.
    ~HI_IRBuilder()
    {
        IRBuilder_log->flush();
        delete IRBuilder_log;
    }
    void getAnalysisUsage(AnalysisUsage &AU) const;
    bool runOnModule(llvm::Module &M);
    virtual bool doInitialization(llvm::Module &M)
    {
        print_status("Initilizing HI_IRBuilder pass.");
        return false;
    }
    static char ID;

    void insertInstructionsBefore(llvm::Instruction *targetInst);
    std::error_code ErrInfo;
    raw_ostream *IRBuilder_log;

    /// Timer

    struct timeval tv_begin;
    struct timeval tv_end;
};

#endif
