const { app, BrowserWindow, Menu, dialog } = require("electron")
const path = require("path")
const SC = require("./socket")
const LG = require("./logger")

const { ipcMain } = require("electron")

ipcMain.on("infection", () => {
  console.log("PIZDA")
})
let mainWindow

const createWindow = () => {
  mainWindow = new BrowserWindow({
    width: 1000,
    height: 600,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      preload: path.join(__dirname, "preload.js"),
    },
  })

  mainWindow.setTitle("16Anti Infector")
  mainWindow.loadFile("index.html")
  // mainWindow.openDevTools()
}
let timer
let dataded
function ddF(data) {
  dataded = data
}
timer = setInterval(() => {
  LG.GL(ddF)
  if (dataded) {
    mainWindow.webContents.send("new_data", dataded)
  }
}, 5000)

ipcMain.on("stopReading", () => {
  clearInterval(timer)
})

ipcMain.on("terminate", (e, mod, path) => {
  console.log("TERM!!!", "MOD " + mod, "PATH " + path)
  if (mod === "q") {
    SC.SD("QUART:::" + path)
  }
  if (mod === "d") {
    SC.SD("KILL:::" + path)
  }
})

const template = [
  {
    label: "Start new scan",
    submenu: [
      {
        label: "Choose file",
        click() {
          let cmd
          dialog
            .showOpenDialog(mainWindow, {
              properties: ["openFile"],
            })
            .then((result) => {
              if (!result.canceled) {
                cmd = result.filePaths
                SC.SD("SCAN_FILES:::" + cmd)
              }
            })
            .catch((err) => {
              console.log(err)
            })
        },
      },
      {
        label: "Choose dir",
        click() {
          let cmd
          dialog
            .showOpenDialog(mainWindow, {
              properties: ["openDirectory"],
            })
            .then((result) => {
              if (!result.canceled) {
                cmd = result.filePaths
                console.log(`SCAN_FILES:::` + cmd)
                SC.SD("SCAN_FILES:::" + cmd)
              }
            })
            .catch((err) => {
              console.log(err)
            })
        },
      },
      {
        label: "Scan all files",
        click() {
          SC.SD(`SCAN_ALL:::xxx}`)
        },
      },
      {
        label: "Scan all drives",
        click() {
          SC.SD(`SCAN_ALL:::/`)
        },
      },
      {
        label: "Scan all USB",
        click() {
          SC.SD(`SCAN_FILES:::/run/media`)
        },
      },
    ],
  },
  {
    label: "Pause/Stop",
    submenu: [
      {
        label: "Pause",
        click() {
          SC.SD("PAUSE:::")
        },
      },
      { label: "Stop", click() {} },
    ],
  },
  {
    label: "Quit",
    submenu: [{ role: "close" }],
  },
]

const menu = Menu.buildFromTemplate(template)
Menu.setApplicationMenu(menu)

app.whenReady().then(() => {
  createWindow()

  app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow()
  })
})

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") app.quit()
})

function callback() {
  return mainWindow
}
module.exports.cb = callback
