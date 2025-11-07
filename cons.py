from mcons import batch, ConsModule, cons_object, task
from cons_config import Config
from .Obfuscation.cons import cons_Obfuscation_a

cm = ConsModule(__file__)

def cons_AddPass_o(config: Config):
  return cons_object(cm, "AddPass.o", "AddPass.cpp", config.compile_templ)

def cons_Obfuscator_so(config: Config):
  deps = batch([cons_AddPass_o, cons_Obfuscation_a], config)
  cmd = f"{config.cxx} -fuse-ld={config.ld} -fPIC -shared {config.link_flags} {{_deps}} -o {{_target}}"
  return task(cm, "libObfuscatorPass.so", deps, cmd)
