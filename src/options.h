#pragma once

struct CpbOptions {
  bool linux;
  bool windows;
  bool macos;
  bool allow_commands;
  bool init;
};

CpbOptions get_cpb_options(int argc, char * argv[]);
