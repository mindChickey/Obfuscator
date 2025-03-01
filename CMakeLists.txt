add_library(ObfuscatorPass SHARED
  AddPass.cpp
  Obfuscation/Utils.cpp
  Obfuscation/CryptoUtils.cpp
  Obfuscation/ObfuscationOptions.cpp
  Obfuscation/BogusControlFlow.cpp
  Obfuscation/IPObfuscationContext.cpp
  Obfuscation/Flattening.cpp
  Obfuscation/StringEncryption.cpp
  Obfuscation/SplitBasicBlock.cpp
  Obfuscation/Substitution.cpp
  Obfuscation/IndirectBranch.cpp
  Obfuscation/IndirectCall.cpp
  Obfuscation/IndirectGlobalVariable.cpp
)
