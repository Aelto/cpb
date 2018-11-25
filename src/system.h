#pragma once

#include <yaml-cpp/yaml.h>
#include "project.h"

struct Dependency {
  std::string name;
  std::string version;
};

struct SystemOptions {
  std::string compiler;
  std::vector<std::string> args;
  
  std::string directory;

  std::string manager;
  std::vector<Dependency> dependencies; 
  
  std::vector<std::string> include_directories;
  std::vector<std::string> files;
  
  std::string lib_directory;
  std::vector<std::string> libs;
};

SystemOptions * load_system_options(YAML::Node & config, char * system_name);

bool execute_system_options_windows(Project * project, SystemOptions * system_options);