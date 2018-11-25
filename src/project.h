#pragma once

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

enum ProjectType {
  Binary, Library
};

struct Project {
  std::string name;
  ProjectType type;
};

Project * load_project_config(YAML::Node & config);