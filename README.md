# 🎹 Daktylos: The Keyboard Layout Designed for Efficiency! 🚀
![License](https://img.shields.io/github/license/whoiscircuit/daktylos)
![Build](https://img.shields.io/github/actions/workflow/status/whoiscircuit/daktylos/build_binaries.yaml)
![Stars](https://img.shields.io/github/stars/whoiscircuit/daktylos)

## 💫 What is This Magic?

**Daktylos** is a delightfully crafted [**QMK**](https://qmk.fm) layout for the elegant [**elephant42**](https://github.com/illness072/elephant42) keyboard, inspired by the [**Miryoku Layout**](https://github.com/manna-harbour/miryoku). Daktylos is paired with an optional companion app [**Hidrosis**](./hidrosis) to enable communication between the host and the keyboard.

### 🌟 Key Features

- 🌈 **Custom QMK Layout**: featuring home-row mods and multi layer thumb clusters keys
- 🎮 **Joystick Mode**: Transform your split keyboard into a retro gaming controller - play with friends using each half as a joystick!
- 📟 **Interactive OLED Menu**: Customize settings, view keyboard stats, and control features right from the keyboard's OLED display
- 🤝 **Host-Keyboard Communication**: Hidrosis keeps the keyboard and computer talking like best friends
- 🖥️ **Cross-Platform**: 
  - 🪟 Windows
  - 🐧 Linux (Both X11 and Wayland!)
  - 🍎 macOS

### 🔧 Technical Details
- 🏗️ Custom-built HID communication protocol
- 🔐 Cross-Platform Native USB HID interface implementation using `hidapi`
- 🛠️ Custom event handling system supporting X11, Wayland, and Win32 APIs
- 📦 CMake-based modular build system with cross-platform support
- 🔄 Automated CI/CD pipeline with GitHub Actions packaging the app for Windows, Linux and MacOS


<!-- ## 💝 Features
TODO

## 🚀 Getting Started

### 💾 Installation

#### 🎹 Keyboard Firmware
```bash
# Flash your Elephant42 with our magical firmware
qmk flash elephant42_daktylos.hex
```

#### 🌟 Hidrosis App
- 🪟 **Windows**: Run `Hidrosis-Installer.exe`
- 🐧 **Linux**: 
  - Debian/Ubuntu: `sudo dpkg -i hidrosis-linux-aarch64.deb`
  - Fedora: `sudo rpm -i hidrosis-linux-aarch64.rpm`
- 🍎 **macOS**: Coming soon! -->

## 🙏 Acknowledgments

- The amazing [QMK community](https://qmk.fm)
- [illness072](https://github.com/illness072) for creating the [elephant42 keyboard](https://github.com/illness072/elephant42)
- [manna-harbour](https://github.com/manna-harbour) for creating the [miryoku layout](https://github.com/manna-harbour/miryoku)
