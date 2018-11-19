const { resolve } = require('path')
const config = require('./cuff.config.js')

module.exports = cuff => {
  const option = cuff.buildConfig(config)
  const output = cuff.compilers
    .clDefault
    .generate(option)

  cuff.commands.build(output)
  .catch(console.log)
}