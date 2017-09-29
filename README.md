# Terminal based space invaders.

### Info

A space invaders-like game written in C using the ncurses library.
While it requires tweaking and could be with more features, it is in a playable condition.

Uses the Catch testing framework as Clion (current IDE) has built in support for the framework.

### Build
#### Requires:
* gcc
* Cmake
* Ncurses

Personal system is OpenSUSE Tumbleweed.
To install the required components.

    sudo zypper install gcc cmake ncurses-devel

    ch terminal-invaders
    cmake .
    make

Game will be built in the build directory.

On a Debian based system I would imagine the command would be:

    sudo apt install gcc cmake ncurses-dev

However did not have a system to test this on.

### TODO:
Incorporate colours.
Build more tests.

### TOFIX:
If possible, remove the delay when holding a key down. However from what I understand it is out of ncurses scope.

