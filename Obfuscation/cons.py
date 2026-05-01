from mcons import cons_object_list, pack_ar, ConsModule, pack_ar
from cons_config import Config

cm = ConsModule(__file__)

sources = [
  "Utils.cpp",
  "CryptoUtils.cpp",
  "ObfuscationOptions.cpp",
  "BogusControlFlow.cpp",
  "IPObfuscationContext.cpp",
  "Flattening.cpp",
  "StringEncryption.cpp",
  "SplitBasicBlock.cpp",
  "Substitution.cpp",
  "IndirectBranch.cpp",
  "IndirectCall.cpp",
]

def cons_Obfuscation_a(config: Config):
  objects = cons_object_list(cm, ".o", sources, config.compile_templ)
  return pack_ar(cm, "libObfuscation.a", objects)
