const { app, BrowserWindow, Menu, dialog } = require("electron")
const path = require("path")
const { exec } = require("child_process")

// exec(
//   "systemctl status AVService| grep 'dead' | awk '{print $3}'",
//   (error, stdout, stderr) => {
//     if (stdout.trim() == "(dead)") {
//       exec("systemctl start AVService", (error, stdout, stderr) => {
//         console.log(stdout)
//       })
//     }
//   }
// )

const SC = require("./socket")k
// const LG = require("./logger")

const { ipcMain } = require("electron")

// if (system("systemctl status AVService | grep 'dead'") == 0) {
//   system("systemctl start AVService")
// }

ipcMain.on("infection", () => {})
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
// let timer
// let dataded
// function ddF(data) {
//   dataded = data
// }
// timer = setInterval(() => {
//   // LG.GL(ddF)
//   if (dataded) {
//     mainWindow.webContents.send("new_data", dataded)
//   }
// }, 5000)

ipcMain.on("stopReading", () => {
  // clearInterval(timer)
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
    label: "Quarantine",
    submenu: [
      {
        label: "Q restore",
        click() {
          let cmd
          dialog
            .showOpenDialog(mainWindow, {
              properties: ["openFile"],
              defaultPath: "/home/egor/AV/Quarantine",
            })
            .then((result) => {
              if (!result.canceled) {
                cmd = result.filePaths
                SC.SD("Q_RES:::" + cmd)
              }
            })
            .catch((err) => {
              console.log(err)
            })
        },
      },
      {
        label: "Q delete",
        click() {
          let cmd
          dialog
            .showOpenDialog(mainWindow, {
              properties: ["openFile"],
              defaultPath: "/home/egor/AV/Quarantine",
            })
            .then((result) => {
              if (!result.canceled) {
                cmd = result.filePaths
                SC.SD("Q_DEL:::" + cmd)
              }
            })
            .catch((err) => {
              console.log(err)
            })
        },
      },
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
