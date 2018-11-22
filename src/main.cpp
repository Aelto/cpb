#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "project.h"

struct BuildingPlatform {
  bool linux;
  bool windows;
  bool macos;
};

BuildingPlatform get_building_platform(int argc, char * argv[]);

int main(int argc, char * argv[]) {
  #ifdef DEBUG
    for (int i = 0; i < argc; i++) {
      std::cout << "arg: " << argv[i] << "\n";
    }
  #endif

  auto platforms_build = get_building_platform(argc, argv);

  std::cout 
    << "building for windows: "
    << platforms_build.windows
    << "\n";

  std::cout 
    << "building for linux: "
    << platforms_build.linux
    << "\n";

  std::cout 
    << "building for macos: "
    << platforms_build.macos
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

  if (platforms_build.windows) {
    auto * windows = load_windows_options(config);
  }
  
  std::cout << "done.\n";

  return 0;
}

BuildingPlatform get_building_platform(int argc, char * argv[]) {
  BuildingPlatform platforms { false, false, false };

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--windows") == 0) {
      platforms.windows = true;
    }

    if (strcmp(argv[i], "--linux") == 0) {
      platforms.linux = true;
    }

    if (strcmp(argv[i], "--macos") == 0) {
      platforms.macos = true;
    }
  }

  return platforms;
}