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

Project * load_project_config(YAML::Node & config);

std::string get_value(
  YAML::Node & node,
  char * key,
  bool required = false);