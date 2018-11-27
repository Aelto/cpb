#include <iostream>
#include <yaml-cpp/yaml.h>

#include "project.h"
#include "system.h"
#include "systems/windows.h"
#include "options.h"

int main(int argc, char * argv[]) {
  #ifdef DEBUG
    for (int i = 0; i < argc; i++) {
      std::cout << "arg: " << argv[i] << "\n";
    }
  #endif

  auto cpb_options = get_cpb_options(argc, argv);

  std::cout 
    << "building for windows: "
    << cpb_options.windows
    << "\n";

  std::cout 
    << "building for linux: "
    << cpb_options.linux
    << "\n";

  std::cout 
    << "building for macos: "
    << cpb_options.macos
    << "\n";

  std::string config_path = "cpb.yaml";

  #ifdef DEBUG
    std::cout << "using default config_path: cpb.yaml\n";
  #endif

  auto config = YAML::LoadFile(config_path);
  auto * project = load_project_config(config);

  if (project == nullptr) {
    std::cout 
      << "something was missing from the build file, exiting.\n";
    return 1;
  }

  auto * shared = load_system_options(config, "shared");

  if (cpb_options.windows) {
    auto * windows = load_system_options(config, "windows");

    if (project->type == Binary) {
      auto success = systems::execute_windows(project, windows, shared, cpb_options);
    }
    else {
      // TODO: library project type
    }
  }
  
  std::cout << "done.\n";

  return 0;
}
