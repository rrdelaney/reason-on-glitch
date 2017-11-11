/*

Hello! This is an example of using ReasonML on Glitch!

This file is mostly a wrapper around running the server found in `src/server.re`.
The index file here will run `bsb` for you on changes to `.js` and `.json` files
so there's no need to dip down to the console to run BuckleScript!

*/

const fs = require('fs')
const path = require('path')
const {promisify} = require('util')
const bsb = require('bsb-js')
const browserify = require('browserify')

const writeFile = promisify(fs.writeFile)

;(async () => {
  try {
    // Try to run `bsb` before booting the server
    await bsb.runBuild()

    // Run browserify to bundle our client-side code
    const b = browserify(path.join(__dirname, 'src', 'client.bs.js'))
    const bundle = promisify(b.bundle.bind(b))
    const jsFile = await bundle()
    await writeFile('bundle.js', jsFile.toString())

    // Require our ReasonML server :)
    require('./src/server.bs')
  } catch (e) {
    // Capture any errors that might happen, replace ANSI colors from the output
    const bsbError = typeof e === 'string'
      ? e.replace(/[\u001b\u009b][[()#;?]*(?:[0-9]{1,4}(?:;[0-9]{0,4})*)?[0-9A-ORZcf-nqry=><]/g, '')
      : e.stack

    // Also log the error
    console.error(bsbError)

    // If there was an error start a server to display it
    require('express')()
      .get('/', (req, res) => {
        res.status(500).send(`<html><pre style="color:red">${bsbError}</pre></html>`)
      })
      .listen(process.env.PORT, () => {
        console.log('Booted with errors o_o')
      })
  }
})()
