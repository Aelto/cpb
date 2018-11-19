const { resolve } = require('path')

const SRC_DIR = resolve(__dirname, '../src')
const VCPKG_X86_STATIC = `/files/cpp/vcpkg/installed/x86-windows-static`
const VCPKG_X86 = `/files/cpp/vcpkg/installed/x86-windows`
const VCPKG_INCLUDE = resolve(VCPKG_X86_STATIC, 'include')
const VCPKG_LIB = resolve(VCPKG_X86_STATIC, 'lib')

const config = {
  entry: resolve(SRC_DIR, 'main.cpp'),
  includeDirectories: [
    SRC_DIR,
    VCPKG_INCLUDE
  ],
  staticLibraries: [
    resolve(VCPKG_LIB, 'libyaml-cppmd.lib')
  ],
  args: ['/EHsc'],
  macros: ['DEBUG']
}

module.exports = config