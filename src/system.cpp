#include "system.h"
#include <iostream>

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

  if (system_config["directory"]) {
    new_system_options->directory = system_config["directory"]
      .as<std::string>();
  }
  else {
    const auto default_directory = std::string(".");

    std::cout 
      << "using default value for system options directory: "
      << default_directory
      << "\n";

    new_system_options->directory = default_directory;
  }

  if (system_config["include_directories"]) {
    auto include_directories = system_config["include_directories"];

    for (auto it = include_directories.begin(); 
         it != include_directories.end();
         ++it) {
      auto new_directory = it->as<std::string>();

      #ifdef DEBUG
        std::cout 
          << "adding include directory: "
          << new_directory
          << "\n";
      #endif

      new_system_options->include_directories.push_back(new_directory);
    }
  }

  if (system_config["files"]) {
    auto files = system_config["files"];

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

      new_system_options->files.push_back(new_file);
    }
  }

  if (system_config["libraries"]) {
    auto libraries = system_config["libraries"];

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

      new_system_options->libs.push_back(new_library);
    }
  }

  if (system_config["lib_directory"]) {
    new_system_options->lib_directory = system_config["lib_directory"].as<std::string>();

    #if DEBUG
      std::cout 
        << "setting lib directory: "
        << new_system_options->lib_directory
        << "\n";
    #endif
  }

  if (system_config["dependencies"]) {
    auto dependencies = system_config["dependencies"];

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

      new_system_options->dependencies.push_back(new_dependency);
    }
  }

  if (system_config["manager"]) {
    new_system_options->manager = system_config["manager"]
      .as<std::string>();

    #ifdef DEBUG
      std::cout 
        << "adding manager: "
        << new_system_options->manager
        << "\n";
    #endif
  }
  else {
    const auto default_manager = std::string("vcpkg");

    std::cout
      << "using default value for project manager: "
      << default_manager
      << "\n";

    new_system_options->manager = default_manager;
  }

  return new_system_options;
}

bool execute_system_options_windows(Project * project, SystemOptions * system_options) {
  std::string command = "cl ";

  for (auto arg : system_options->args) {
    command += arg + " ";
  }

  for (auto file_name : system_options->files) {
    command += system_options->directory + file_name + " ";
  }

  for (auto directory : system_options->include_directories) {
    command += "/I " + directory + " ";
  }

  if (system_options->libs.size() > 0) {
    command += "/link";

    for (auto library : system_options->libs) {
      command += system_options->lib_directory + library + " ";
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