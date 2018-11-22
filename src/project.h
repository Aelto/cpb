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
};

struct WindowsOptions {
  std::string compiler;
  std::vector<std::string> args;
};

struct LinuxOptions {
  std::string compiler;
  std::vector<std::string> args;
};

Project * load_project_config(YAML::Node & config);
WindowsOptions * load_windows_options(YAML::Node & config);