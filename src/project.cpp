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

  if (project_config["libraries"]) {
    auto libraries = project_config["libraries"];

    for (auto it = libraries.begin();
         it !=  libraries.end();
         ++it) {
      auto new_library = it->as<std::string>();
      
      #ifdef DEBUG
        std::cout 
          << "adding library: "
          << new_library
          << "\n";
      #endif

      project->libraries.push_back(new_library);
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

  if (project_config["directories"]) {
    auto directories = project_config["directories"];

    for (auto it = directories.begin(); 
         it != directories.end();
         ++it) {
      auto new_directory = it->as<std::string>();

      #ifdef DEBUG
        std::cout 
          << "adding include directory: "
          << new_directory
          << "\n";
      #endif

      project->directories.push_back(new_directory);
    }
  }


  return project;
}

SystemOptions * load_system_options(YAML::Node & config, char * system_name) {
  auto * new_system_options = new SystemOptions; 

  #ifdef DEBUG
    std::cout 
      << "loading " 
      << system_name
      << " options\n";
  #endif

  if (!config[system_name]) {
    #ifdef DEBUG
      std::cout << "could not find windows group in config\n";
    #endif

    return nullptr;
  }

  auto & system_config = config[system_name];

  if (system_config["compiler"]) {
    new_system_options->compiler = system_config["compiler"]
      .as<std::string>();

    #ifdef DEBUG
      std::cout
        << "found windows compiler: "
        << new_system_options->compiler
        << "\n";
    #endif
  }
  else {
    std::cout << "using default windows compiler: cl\n";

    new_system_options->compiler = "cl";
  }

  if (system_config["args"]) {
    auto args = system_config["args"];

    for (auto it = args.begin(); 
         it != args.end();
         ++it) {
      auto new_file = it->as<std::string>();

      #ifdef DEBUG
        std::cout 
          << "adding arg: "
          << new_file
          << "\n";
      #endif

      new_system_options->args.push_back(new_file);
    }
  }

  return new_system_options;
}

bool execute_system_options_windows(Project * project, SystemOptions * system_options) {
  std::string command = "cl ";

  for (auto arg : system_options->args) {
    command += arg + " ";
  }

  command += project->directory + project->entry + " ";

  for (auto file_name : project->files) {
    command += project->directory + file_name + " ";
  }

  for (auto directory : project->directories) {
    command += "/I " + directory + " ";
  }

  if (project->libraries.size() > 0) {
    command += "/link";

    for (auto library : project->libraries) {
      command += library + " ";
    }
  }

  #ifdef DEBUG
    std::cout
      << "running command "
      << command
      << "\n";
  #endif

  system(command.c_str());

  return true;
}