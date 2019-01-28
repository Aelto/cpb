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
      std::cout
      << "could not find "
      << system_name
      << " group in config\n";
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
        << new_system_options->compiler.value()
        << "\n";
    #endif
  }

  if (system_config["args"]) {
    auto args = system_config["args"];
    
    new_system_options->args = std::vector<std::string>();
    // new_system_options->args
    //   .value()
    //   .resize(args.size());

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

      new_system_options->args
        .value()
        .push_back(new_file);
    }
  }

  if (system_config["directory"]) {
    new_system_options->directory = system_config["directory"]
      .as<std::string>();
  }

  if (system_config["include_directories"]) {
    auto include_directories = system_config["include_directories"];

    new_system_options->include_directories = std::vector<std::string>();
    // new_system_options->include_directories
    //   .value()
    //   .resize(include_directories.size());

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

      new_system_options->include_directories
        .value()
        .push_back(new_directory);
    }
  }

  if (system_config["files"]) {
    auto files = system_config["files"];

    new_system_options->files = std::vector<std::string>();
    // new_system_options->files
    //   .value()
    //   .resize(files.size());

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

      new_system_options->files
        .value()
        .push_back(new_file);
    }
  }

  if (system_config["libraries"]) {
    auto libraries = system_config["libraries"];

    new_system_options->libs = std::vector<std::string>();
    // new_system_options->libs
    //   .value()
    //   .resize(libraries.size());

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

      new_system_options->libs
        .value()
        .push_back(new_library);
    }
  }

  if (system_config["lib_directory"]) {
    new_system_options->lib_directory = system_config["lib_directory"].as<std::string>();

    #if DEBUG
      std::cout 
        << "setting lib directory: "
        << new_system_options->lib_directory.value()
        << "\n";
    #endif
  }

  if (system_config["dependencies"]) {
    auto & dependencies = system_config["dependencies"];

    new_system_options->dependencies = std::vector<Dependency>();
    // new_system_options->dependencies
    //   .value()
    //   .resize(dependencies.size());

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

      new_system_options->dependencies
        .value()
        .push_back(new_dependency);
    }
  }

  if (system_config["manager"]) {
    new_system_options->manager = system_config["manager"]
      .as<std::string>();

    #ifdef DEBUG
      std::cout 
        << "adding manager: "
        << new_system_options->manager.value()
        << "\n";
    #endif
  }

  if (system_config["commands"]) {
    auto & commands = system_config["commands"];

    if (commands["before"]) {
      auto & before_commands = commands["before"];

      new_system_options->commands.before = std::vector<std::string>();

      for (auto it = before_commands.begin(); 
         it != before_commands.end();
         ++it) {
        auto new_before_command = it->as<std::string>();

        #ifdef DEBUG
          std::cout 
            << "adding before command: "
            << before_commands
            << "\n";
        #endif

        new_system_options->commands.before
          .value()
          .push_back(new_before_command);
      }
    }

    if (commands["after"]) {
      auto & after_commands = commands["after"];

      new_system_options->commands.after = std::vector<std::string>();

      for (auto it = after_commands.begin(); 
         it != after_commands.end();
         ++it) {
        auto new_before_command = it->as<std::string>();

        #ifdef DEBUG
          std::cout 
            << "adding after command: "
            << after_commands
            << "\n";
        #endif

        new_system_options->commands.after
          .value()
          .push_back(new_before_command);
      }
    }
  }

  return new_system_options;
}