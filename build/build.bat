cl /EHsc /std:c++17 /DDEBUG^
  ../src/main.cpp^
  ../src/project.cpp^
  ../src/system.cpp^
  ../src/systems/windows.cpp^
  ../src/options.cpp^
  /I ../src^
  /I %vcpkg_static%/include^
  /link%vcpkg_static%/lib/libyaml-cppmd.lib