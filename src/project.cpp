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

  if (project_config["entry"]) {
    project->entry = project_config["entry"]
      .as<std::string>();
  }
  else {
    std::cout 
      << "no project entry was provided, "
         "please add one\n";

    return nullptr;
  }

  if (project_config["directory"]) {
    project->directory = project_config["directory"]
      .as<std::string>();
  }
  else {
    const auto default_directory = std::string(".");

    std::cout 
      << "using default value for project.directory: "
      << default_directory
      << "\n";

    project->directory = default_directory;
  }

  if (project_config["manager"]) {
    project->manager = project_config["manager"]
      .as<std::string>();
  }
  else {
    const auto default_manager = std::string("vcpkg");

    std::cout
      << "using default value for project manager: "
      << default_manager
      << "\n";

    project->manager = default_manager;
  }

  if (project_config["dependencies"]) {
    auto dependencies = project_config["dependencies"];

    for (auto it = dependencies.begin(); 
         it != dependencies.end();
         ++it) {
      auto new_dependency = Dependency {
        it->first.as<std::string>(),
        it->second.as<std::string>()
      };

      #ifdef DEBUG
        std::cout 
          << "adding dependency: "
          << new_dependency.name
          << ", version: "
          << new_dependency.version
          << "\n";
      #endif

      project->dependencies.push_back(new_dependency);
    }
  }

  if (project_config["files"]) {
    auto files = project_config["files"];

    for (auto it = files.begin(); 
         it != files.end();
         ++it) {
      auto new_file = it->as<std::string>();

      #ifdef DEBUG
        std::cout 
          << "adding file: "
          << new_file
          << "\n";
      #endif

      project->files.push_back(new_file);
    }
  }

  return project;
}
