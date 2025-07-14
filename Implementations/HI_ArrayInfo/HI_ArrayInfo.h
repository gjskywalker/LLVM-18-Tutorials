#ifndef _HI_ARRAYINFO
#define _HI_ARRAYINFO
// related headers should be included.
#include "HI_DataInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopAccessAnalysis.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
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
#include <bits/stl_map.h>
#include <ios>
#include <map>
#include <set>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <vector>

using namespace llvm;

class HI_ArrayInfo : public ModulePass
{
public:
    HI_ArrayInfo(const char *Array_out_file, std::map<Value *, ArrayInfo *> &Target2ArrayInfo, bool debug) : ModulePass(ID), Target2ArrayInfo_ref(Target2ArrayInfo), DEBUG(debug)
    {
        Array_out = new raw_fd_ostream(Array_out_file, ErrInfo, sys::fs::OF_None);
    } // define a pass, which can be inherited from ModulePass, LoopPass, FunctionPass and etc.

    ~HI_ArrayInfo()
    {
        // Array_out->flush();
        delete Array_out;
    }

    virtual bool doInitialization(Module &M) override
    {
        // print_status("Initilizing HI_ArrayInfo pass.");
        return false;
    }

    virtual bool doFinalization(Module &M) override
    {
        // print_status("Finalizing HI_ArrayInfo pass.");
        return false;
    }

    void getAnalysisUsage(AnalysisUsage &AU) const;
    virtual bool runOnModule(Module &M) override;
    ArrayInfo *getArrayInfo(Value *V);
    static char ID;

    std::error_code ErrInfo;
    raw_ostream *Array_out;
    std::map<Value *, ArrayInfo *> &Target2ArrayInfo_ref;
    LoopInfo *LI;
    ScalarEvolution *SE;
    bool DEBUG;
    /// Timer

    struct timeval tv_begin;
    struct timeval tv_end;
};

#endif
