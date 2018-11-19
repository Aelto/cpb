const { resolve } = require('path')

const SRC_DIR = resolve(__dirname, '../src')
const VCPKG_X86_STATIC = `/files/cpp/vcpkg/installed/x86-windows-static`
const VCPKG_X86 = `/files/cpp/vcpkg/installed/x86-windows`
const VCPKG_INCLUDE = resolve(VCPKG_X86, 'include')
const VCPKG_LIB = resolve(VCPKG_X86, 'lib')

const config = {
  entry: resolve(SRC_DIR, 'main.cpp'),
  includeDirectories: [
    SRC_DIR,
    VCPKG_INCLUDE
  ],
  args: ['/EHsc'],
  macros: ['DEBUG']
}

module.exports = config