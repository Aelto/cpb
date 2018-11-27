#include "windows.h"

#include <iostream>

bool systems::execute_windows(
  Project * project,
  SystemOptions * system_options,
  SystemOptions * default_system_options,
  CpbOptions & cpb_options) {

  if (cpb_options.allow_commands) {
    auto before_commands = system_options
      ->commands.before.value_or(
        default_system_options == nullptr 
          ? std::vector<std::string>()
          : default_system_options
            ->commands.before.value_or(std::vector<std::string>())
      );

    for (auto & before_command : before_commands) {
      std::cout 
        << "running command: "
        << before_command
        << "\n";

      system(before_command.c_str());
    }
  }

  auto compiler_name = system_options
    ->compiler.value_or(
      default_system_options == nullptr 
        ? std::string()
        : default_system_options
          ->compiler.value_or("cl")
    );

  std::string command = compiler_name;
  
  auto args = system_options
    ->args.value_or(
      default_system_options == nullptr 
        ? std::vector<std::string>()
        : default_system_options
          ->args.value_or(std::vector<std::string>())
    );
  for (auto arg : args) {
    command += arg + " ";
  }

  auto files = system_options
    ->files.value_or(
      default_system_options == nullptr
        ? std::vector<std::string>()
        : default_system_options
          ->files.value_or(std::vector<std::string>())
    );
  auto directory = system_options
    ->directory.value_or(
      default_system_options == nullptr
        ? "."
        : default_system_options
          ->directory.value_or(".")
    );
  for (auto file_name : files) {
    command += directory + file_name + " ";
  }

  auto include_directories = system_options
    ->include_directories.value_or(
      default_system_options == nullptr
        ? std::vector<std::string>()
        : default_system_options
          ->include_directories.value_or(std::vector<std::string>())
    );
  for (auto directory : include_directories) {
    command += "/I " + directory + " ";
  }

  auto libs = system_options
    ->libs.value_or(
      default_system_options == nullptr
        ? std::vector<std::string>()
        : default_system_options
          ->libs.value_or(std::vector<std::string>())
    );

  auto lib_directory = system_options
    ->lib_directory.value_or(
      default_system_options == nullptr
        ? std::string()
        : default_system_options
          ->lib_directory.value_or(std::string())
    );
  if (!libs.empty()) {
    command += "/link";

    for (auto library : libs) {
      command += lib_directory + library + " ";
    }
  }

  #ifdef DEBUG
    std::cout
      << "running command "
      << command
      << "\n";
  #endif

  system(command.c_str());

  if (cpb_options.allow_commands) {
    auto after_commands = system_options
      ->commands.after.value_or(
        default_system_options == nullptr 
          ? std::vector<std::string>()
          : default_system_options
            ->commands.after.value_or(std::vector<std::string>())
      );


    for (auto & after_command : after_commands) {
      std::cout 
        << "running command: "
        << after_command
        << "\n";

      system(after_command.c_str());
    }
  }


  return true;
}