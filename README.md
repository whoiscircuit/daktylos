# Installation
## Debian/Ubuntu
```sh
    wget -O /tmp/hidrosis.deb https://github.com/whoiscircuit/daktylos/releases/latest/download/hidrosis-linux-aarch64.deb
    sudo apt install -y /tmp/hidrosis.deb
    sudo udevadm control --reload
    sudo udevadm trigger
    systemctl --user reload-daemon
    systemctl --user enable hidrosis.service --now
```
