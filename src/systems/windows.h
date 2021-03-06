#pragma once

#include <yaml-cpp/yaml.h>
#include "../project.h"
#include "../system.h"
#include "../options.h"

namespace systems {

  bool execute_windows(
    Project * project,
    SystemOptions * system_options,
    SystemOptions * default_system_options,
    CpbOptions & cpb_options);

}