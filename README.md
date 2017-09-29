# Terminal based space invaders.

### Info

A space invaders-like game written in C using the ncurses library.
While it requires tweaking and could be with more features, it is in a playable condition.


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

### Tests
Uses the Catch testing framework as Clion (current IDE) has built in support for the framework.
By default the tests are not build.
To create the tests run:

    cmake -Dbuild_test=ON .

### Controls
Arrow keys left and right control movement.
Arrow up shoots.
Arrow down quits the game.
Keys A, S, D and W can also be used.
Key h pauses the game and displays a help screen.

### TODO:
Incorporate colours.
Build more tests.

### TOFIX:
If possible, remove the delay when holding a key down. However from what I understand it is out of ncurses scope.

