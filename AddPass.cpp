
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Pass.h"

#include "Obfuscation/BogusControlFlow.h"
#include "Obfuscation/Flattening.h" 
#include "Obfuscation/SplitBasicBlock.h"
#include "Obfuscation/Substitution.h"
#include "Obfuscation/StringEncryption.h"
#include "Obfuscation/IndirectGlobalVariable.h"
#include "Obfuscation/IndirectBranch.h"
#include "Obfuscation/IndirectCall.h"

using namespace llvm;

static cl::opt<bool> s_obf_split("split", cl::init(false), cl::desc("SplitBasicBlock: split_num=3(init)"));
static cl::opt<bool> s_obf_sobf("sobf", cl::init(false), cl::desc("String Obfuscation"));
static cl::opt<bool> s_obf_fla("fla", cl::init(false), cl::desc("Flattening"));
static cl::opt<bool> s_obf_sub("sub", cl::init(false), cl::desc("Substitution: sub_loop"));
static cl::opt<bool> s_obf_bcf("bcf", cl::init(false), cl::desc("BogusControlFlow: application number -bcf_loop=x must be x > 0"));
static cl::opt<bool> s_obf_ibr("ibr", cl::init(false), cl::desc("Indirect Branch"));
static cl::opt<bool> s_obf_igv("igv", cl::init(false), cl::desc("Indirect Global Variable"));
static cl::opt<bool> s_obf_icall("icall", cl::init(false), cl::desc("Indirect Call"));

// opt --load-pass-plugin=./libObfuscatorPass.so -O0 -split  main.ll -S

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "Hello", "v0.1",
    [](llvm::PassBuilder &PB) {
      PB.registerPipelineStartEPCallback(
          [](llvm::ModulePassManager &MPM,
             llvm::OptimizationLevel Level) {
            outs() << "[Soule] run.PipelineStartEPCallback\n";
            MPM.addPass(StringEncryptionPass(s_obf_sobf));
            llvm::FunctionPassManager FPM;
            FPM.addPass(IndirectCallPass(s_obf_icall));
            FPM.addPass(SplitBasicBlockPass(s_obf_split));
            FPM.addPass(FlatteningPass(s_obf_fla));
            FPM.addPass(SubstitutionPass(s_obf_sub));
            FPM.addPass(BogusControlFlowPass(s_obf_bcf));
            MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));
            MPM.addPass(IndirectBranchPass(s_obf_ibr));
            MPM.addPass(IndirectGlobalVariablePass(s_obf_igv));
          }
      );
    }
  };
}
