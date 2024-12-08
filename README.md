### Hey!
This script will install gpgpusim on your system.</br>
Currently it can only install gpgpusim with cuda 9 but maybe if i can find some spare time in future i will add cuda 11.x to it as well.</br>

### What it does
1. Bootstrap debian 7.
2. Install GCC 5 on it.
3. Install CUDA 9 on it.
4. Install gpgpusim on it.
5. Generate some scripts for ease of use.

### Requirements
**Debian/Ubuntu**</br>
```
sudo apt install debootstrap make gcc git wget
```
**Arch**</br>
```
sudo pacman -S debootstrap make gcc git wget
```
**Fedora**</br>
```
dnf install debootstrap make gcc git wget
```

### Build
```
git clone https://github.com/thegraveyardwarden/gpgpusim-install.git && cd gpgpusim-install && make
```

### How to install
```
usage: bin/gpgpusim-install COMMAND [OPTIONS]

COMMANDS:
         reinstall: restart the operation and ignore checkpoints
         install: start installation

OPTIONS
         -g: path to gcc 5 tar file (if not present it will be downloaded)
         -c: path to cuda 9 run file (if not present it will be downloaded)
         -d: path to install debian (if not present /opt/wheezy)
```
So if it's your first time trying to install you probably don't have cuda 9 runfile or gcc 5 tar file. just run:
```
bin/gpgpusim-install install
```
It will download them for you.</br>
</br>
When installer wants to install cuda it will ask you some questions:
1. Installing cuda 9...Do you accept the previously read EULA? -> **y**
2. You are attempting to install on an unsupported configuration. Do you wish to continue? -> **y**
3. Install NVIDIA Accelerated Graphics Driver for Linux-x86_64 384.81? -> **n**
4. Install the CUDA 9.0 Toolkit? -> **y**
5. Enter Toolkit Location -> **leave blank for default**
6. Do you want to install a symbolic link at /usr/local/cuda? -> **y**
7. Install the CUDA 9.0 Samples? -> **y**
8. Enter CUDA Samples Location -> **/opt**
</br>
This is my prefrence. Change them if you want.

### How to use
Now you can run this command when you want to chroot to debian and use gpgpusim:
```
gpgpusim-use
```
Ctrl+D pops you out into your own os.</br>
gpgpusim files are under root directory.</br>
