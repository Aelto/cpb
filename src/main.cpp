#include <iostream>
#include <string>
#include <toml/toml.h>

toml::Value * get_config(char * config_path);
std::string get_string(toml::Value * config, char * key);

int main() {
  auto config = get_config("config.toml");

  if (config == nullptr) {
    return 1;
  }

  std::cout << get_string(config, "project.name") << std::endl;

  return 0;
}

std::string get_string(toml::Value * config, char * key) {
  #ifdef DEBUG
    std::cout << "looking for key: " << key << "\n";
  #endif

  const auto * value = config->find(key);

  if (!value || !value->is<std::string>()) {
    #ifdef DEBUG
      std::cout << "value not found for key: " << key << " | " << value << "\n";
    #endif

    return std::string();
  }

  return value->as<std::string>();
}

toml::Value * get_config(char * config_path) {
  auto ifs = std::ifstream(config_path);
  auto config = toml::parse(ifs);

  if (!config.valid()) {
    std::cout << "error when parsing config, " << config.errorReason << "\n";

    return nullptr;
  }

  return &config.value;
}