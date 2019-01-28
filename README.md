# cpb
cpp build system utility, not yet for production use. Go to the [dev branch](https://github.com/Aelto/cpb/tree/dev) to see how the development phase is going

## building cpb

### using msvc (`cl.exe`)
> i'm using `msvc` myself, hence why it is the only compiler documented **at the moment**
> maybe later i will add a more common build system like cmake to make this simpler.

### using a precompiled binary
run the command `cpb --windows`, it will output a new binary you can use

### command-line
the source code is so small it is easy to compile it by hand,
this is the command i use to compile it in `DEBUG` mode:
```
cl /EHsc /DDEBUG C:\files\github\cpb\src\main.cpp^
  C:\files\github\cpb\src\project.cpp^
  /I C:\files\github\cpb\src^
  /I C:\files\cpp\vcpkg\installed\x86-windows-static\include^
  /linkC:\files\cpp\vcpkg\installed\x86-windows-static\lib\libyaml-cppmd.lib
```
