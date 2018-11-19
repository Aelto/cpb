#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

int main() {
  auto config = YAML::LoadFile("config.yaml");

  if (config["project"] && config["project"]["name"]) {
    std::cout 
      << config["project"]["name"].as<std::string>() 
      << "\n";
  }

  return 0;
}