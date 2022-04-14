const Net = require("net")

const port = 3425
const host = "localhost"

const client = new Net.Socket()

client.connect(port, host, function () {
  console.log("Connected")
  // client.write("Hello From Client " + client.address().address)
})
client.on("data", function (data) {
  console.log("Server Says : " + data)
  dataMake(data.toString())
})
client.on("close", function () {
  console.log("Connection closed")
})

const SocketApiSend = (msg) => {
  // console.log("FOT CMDD      ", msg)
  console.log("SEND : " + msg)
  client.write(msg)
  // SocketApiGet()
  return 0
}
const SocketApiGet = (callback) => {
  console.log("GET")
  // dataMake(callback.toString())

  return 0
}
module.exports.SD = SocketApiSend
module.exports.GT = SocketApiGet

const cb = require("./main.js")

function dataMake(str) {
  let CMD = str.substring(0, str.search(":::"))
  let data = str.substring(str.search(":::") + 3, str.length).split(":")
  let mw = cb.cb()
  console.log("DARE ", str)
  if (CMD === "INFECTED") {
    mw.webContents.send("infection", data)
  }
  if (CMD === "NO_INFECTIONS") {
    console.log("NOINF  " + str)
    mw.webContents.send("noInfection", data)
  }
  console.log(CMD)
  console.log(data)
}

// client.connect({
//   port: port,
//   host: host,
//   function() {
//     console.log("Connected")
//   },
// })
// client.on("data", (chunk) => {
//   console.log(`Data received from the server:\n ${chunk.toString()}\n`)
//   SocketApiGet(chunk)
//   client.end()
// })
