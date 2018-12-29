#include "init.h"

#include <yaml-cpp/yaml.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>


bool create_empty_config(std::string & config_path) {
  using namespace YAML;

  auto * emitter = new Emitter();

  *emitter 
    << BeginMap
    << Key << "project" << Value
      << BeginMap
      << Key << "name" << Value << "hello-world"
      << Key << "bin" << Value << "bin"
      << EndMap
    
    << Key << "windows" << Value
      << BeginMap
      << Key << "compiler" << Value << "cl"
      << Key << "args" << Value 
        << BeginSeq
        << "/EHsc"
        << "/std:c++17"
        << EndSeq
      << EndMap

    << Key << "linux" << Value
      << BeginMap
      << Key << "compiler" << Value << "g++"
      << Key << "args" << Value
        << BeginSeq
        << "-Wall"
        << EndSeq
      << EndMap

    << Key << "shared"
      << Value 
      << BeginMap
        << Key << "directory" << Value << "src/"
        << Key << "files" << Value
          << BeginSeq
          << "main.cpp"
          << EndSeq
      << EndMap

    << EndMap;

  std::ofstream file;
  file.open(config_path);
  file << emitter->c_str();
  file.close();

  #ifdef DEBUG
    std::cout << emitter->c_str();
  #endif

  std::cout << "project created at" << config_path << '\n';

  return true;
}
