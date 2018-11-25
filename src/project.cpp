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

  if (project_config["name"]) {
    project->name = project_config["name"]
      .as<std::string>();
  }
  else {
    std::cout 
      << "no project name was provided, "
         "it is suggested you provide one\n";

    return nullptr;
  }

  if (project_config["type"]) {
    auto project_type = project_config["type"]
      .as<std::string>();

    if (project_type == "bin") {
      project->type = Binary;

      std::cout 
        << "project type: binary\n";
    }
    else if (project_type == "lib") {
      project->type = Library;

      std::cout 
        << "project type: libarry\n";
    }
    else {
      std::cout
        << "unrecognized project type: "
        << project_type
        << ", use either `bin` or `lib`\n";
    }
  }
  else {
    project->type = Binary;
    
    std::cout
      << "using default type value: bin\n";
  }

  return project;
}
