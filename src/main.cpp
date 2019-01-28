#include <iostream>
#include <yaml-cpp/yaml.h>

#include "init.h"
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

  std::string config_path = "cpb.yaml";

  #ifdef DEBUG
    std::cout << "using default config_path: cpb.yaml\n";
  #endif

  if (cpb_options.init) {
    #ifdef DEBUG
      std::cout 
        << "creating empty project configuration file:"
        << config_path;
    #endif

    create_empty_config(config_path);

    return 0;
  }

  auto config = YAML::LoadFile(config_path);
  auto * project = load_project_config(config);

  if (project == nullptr) {
    std::cout 
      << "something was missing from the build file, exiting.\n";
    return 1;
  }

  auto * shared = load_system_options(config, "shared");

  if (cpb_options.windows) {
    std::cout 
      << "building for windows: "
      << cpb_options.windows
      << "\n";

    auto * windows = load_system_options(config, "windows");

    if (project->type == Binary) {
      auto success = systems::execute_windows(project, windows, shared, cpb_options);
    }
    else {
      // TODO: library project type
    }
  }

  if (cpb_options.linux) {
    std::cout 
      << "building for linux: "
      << cpb_options.linux
      << "\n";
  }

  if (cpb_options.macos) {
    std::cout 
      << "building for macos: "
      << cpb_options.macos
      << "\n";
  }
  
  std::cout << "done.\n";

  return 0;
}
