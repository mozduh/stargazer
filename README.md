# Star Gazer

# Overview
Star Gazer is a 2D isometric view MMORPG game created with c++ and olcPixelGameEngine.

# Install Dependencies
The following dependencies are used to compile and run the Server and Client.
- gcc
- glibc
- libpng
- mesa
- asio

run the following commands to install the dependencies if you use `ubuntu` based distros:

`sudo apt update`

`sudo apt install build-essential libglu1-mesa-dev libpng-dev asio`

run the following commands to install the dependencies if you use `arch` based distros:

`sudo pacman -Sy`

`sudo pacman -S gcc glibc libpng mesa asio`

# Build
run `make` in the root directory of the repo.

run `make client` to only compile the client binaries.

run `make server` to only compile the server binaries.

# Run
The result of running build should output two binaries in the debug folder:
- server
- client

cd to the debug directory. Run the Server binary first. Then open up another terminal and run the client binary. Make sure to run these programs inside the debug directory or the sprites won't load.

# Examples
Check out the Inspiration directory README file located in `./docs/inspiration` for information about the inspiration of this project and instructions to run example programs.

# Contribution
To Contribute:
- check the issues in this repo
- find an issue you want to solve
- create a branch and link it to that issue
- write code that solves the issue
- once complete, create a pull request for review

# Discussion
Discussions will be had periodically to discuss design, implementation, and lore. Use the Discussion tab in Github to be apart of the discussion.