#pragma once

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

struct Dependency {
  std::string name;
  std::string version;
};

struct Project {
  std::string name;
  std::string directory;
  std::string entry;
  std::vector<std::string> files;
  std::string manager;
  std::vector<Dependency> dependencies; 
  std::vector<std::string> libraries;
  std::vector<std::string> directories;
};

struct SystemOptions {
  std::string compiler;
  std::vector<std::string> args;
};

Project * load_project_config(YAML::Node & config);

SystemOptions * load_system_options(YAML::Node & config, char * system_name);

bool execute_system_options_windows(Project * project, SystemOptions * system_options);