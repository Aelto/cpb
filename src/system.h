#pragma once

#include <optional>
#include <yaml-cpp/yaml.h>
#include "project.h"

struct Dependency {
  std::string name;
  std::string version;
};

struct Commands {
  std::optional<std::vector<std::string>> before;
  std::optional<std::vector<std::string>> after;
};


struct SystemOptions {
  std::optional<std::string> compiler;
  std::optional<std::vector<std::string>> args;
  
  std::optional<std::string> directory;

  std::optional<std::string> manager;
  std::optional<std::vector<Dependency>> dependencies;
  
  std::optional<std::vector<std::string>> include_directories;
  std::optional<std::vector<std::string>> files;
  
  std::optional<std::string> lib_directory;
  std::optional<std::vector<std::string>> libs;

  Commands commands;
};

SystemOptions * load_system_options(YAML::Node & config, char * system_name);