#include "project.h"

#include <iostream>

Project * load_project_config(YAML::Node & config) {
  auto * project = new Project;

  #ifdef DEBUG
    std::cout << "loading project config\n";
  #endif

  if (!config["project"]) {
    #ifdef DEBUG
      std::cout << "could not find project group in config\n";
    #endif

    return nullptr;
  }

  auto & project_config = config["project"];

  project->name = get_value(project_config, "project", true);
  project->entry = get_value(project_config, "entry", true);
  project->manager = get_value(project_config, "__test__", true);

  std::cout << project->name << std::endl;

  return project;
}

std::string get_value(
  YAML::Node & node,
  char * key,
  bool required) {
  
  if (node[key]) {
    return node[key].as<std::string>();
  }
  else if (required) {
    std::cout << "required key was not found: " << key << "\n";
  }

  return std::string();
}