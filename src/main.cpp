#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "project.h"

int main(int argc, char * argv[]) {
  #ifdef DEBUG
    for (int i = 0; i < argc; i++) {
      std::cout << "arg: " << argv[i] << "\n";
    }
  #endif

  std::string config_path;
  if (argc < 2) {
    config_path = "cpb.yaml";

    #ifdef DEBUG
      std::cout << "using default config_path: cpb.yaml\n";
    #endif
  }
  else {
    config_path = argv[1];

    #ifdef DEBUG
      std::cout 
        << "using supplied config_path: " 
        << config_path 
        << "\n";
    #endif
  }

  auto config = YAML::LoadFile(config_path);
  auto * project = load_project_config(config);

  return 0;
}