const path = require('path')

const SRC_DIR = `../src`

const config = {
  entry: `${SRC_DIR}/main.cpp`,
  includeDirectories: [SRC_DIR],
  args: ['/MD', '/EHsc']
}

module.exports = cuff => {
  cuff.commands
    .watch(config, option => {
      const output = cff.compilers
        .clDefault
        .generate(option)
    
      cuff.commands.build(output)
      .catch(console.log)
    })
}