# Assignment 1: 2D Pac-Man

## About

This project contains a remake of Pac-Man in C++ using OpenGL 4.3. In the game you're able to move around using the arrow keys and collect pellets. 
There's also 3 ghosts which roams around the map and tries to catch you. Both Pac-Man and ghosts are animated using a spritesheet and the level is 
loaded from a tilemap. The tilemap can be changed or it's also possible to add other levels. The current score is also being kept track of and 
displayed in the upper left corner. The soundtrack from the original game is also playing in the backround while the game is running. After collecting 
all pellets or being caught by a ghost causes the game to *freeze*. The game can also be ended by pressing *escape*

### Built With

This assignment was built using the following libraries:

* OpenGL ver. 4.3
* GLEW ver. 2.1.0
* GLFW ver. 3.3.2
* GLM ver. 0.9.9
* ImGui
* IrrKlang
* STB

### Getting Started

#### Windows

This is an example on how to set up the project locally using Visual Studio 2019 with Cmake addon.

##### Prerequisites

Before you begin make sure you have the following installed:

* Visual Studio 2019
* Cmake addon for Visual Studio 2019

##### Installation

1. Clone the repository using git
2. Right click on the root folder containing all files in repository
3. Click on "Open in Visual Studio"
4. The project will now be open in Visual Studio and Cmake should automatically generate the project
5. The project should now be set up locally and is ready to build

#### Linux

As both of us developed the project on Windows; we have no idea how to set it up on Linux. But it should be possible to just use Cmake as well.

### Creators

This project was developed by:

* Kristoffer Madsen
* Daniel Dahl

### Acknowledgements

* After all pellets are collected the game *freezes*, but the current score isn't updated with the score from the last pellet
