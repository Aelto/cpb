#include "options.h"

#include <string>

CpbOptions get_cpb_options(int argc, char * argv[]) {
  CpbOptions options { false, false, false, false };

  for (int i = 0; i < argc; i++) {
    auto & current_arg = argv[i];
    
    if (strcmp(current_arg, "--windows") == 0 || strcmp(current_arg, "-w") == 0) {
      options.windows = true;
    }

    if (strcmp(current_arg, "--linux") == 0 || strcmp(current_arg, "-l") == 0) {
      options.linux = true;
    }

    if (strcmp(current_arg, "--macos") == 0 || strcmp(current_arg, "-m") == 0) {
      options.macos = true;
    }

    if (strcmp(current_arg, "--allow-command") == 0 || strcmp(current_arg, "-ac") == 0) {
      options.allow_commands = true;
    }
  }

  return options;
}