#include "windows.h"

#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <chrono>

namespace fs = std::experimental::filesystem;

bool systems::execute_windows(
  Project * project,
  SystemOptions * system_options,
  SystemOptions * default_system_options,
  CpbOptions & cpb_options) {

  bool full_rebuild = false;
  auto dotfile_path = fs::current_path() / fs::path(".cpb"); 
  auto ymlfile_path = fs::current_path() / fs::path("cpb.yaml");
  
  if (fs::exists(dotfile_path)) {
    auto dotfile_wtime = fs::last_write_time(dotfile_path);
    auto ymlfile_wtime = fs::last_write_time(ymlfile_path);

    if (ymlfile_wtime > dotfile_wtime) {
      full_rebuild = true;
    }
    
    fs::last_write_time(dotfile_path, std::chrono::system_clock::now());
  }
  else {
    full_rebuild = true;

    std::ofstream(dotfile_path.c_str());
  }

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
    auto file = fs::path(directory) / file_name;
    if (!fs::exists(file)) {
      std::cout
        << "could not find file: "
        << file_name
        << "\n";

      continue;
    }

    auto file_wtime = fs::last_write_time(file);
    auto obj_file = fs::current_path() / fs::path(file_name).filename().replace_extension(".obj");

    if (fs::exists(obj_file) && !full_rebuild) {
      auto obj_wtime = fs::last_write_time(obj_file);

      #ifdef DEBUG
        std::cout
          << "found obj file: "
          << obj_file.filename()
          << "\n";
      #endif

      if (obj_wtime > file_wtime) {
        // file_wtime older than obj_wtime
        command += obj_file.filename().string() + " ";

        continue;
      }
    }

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