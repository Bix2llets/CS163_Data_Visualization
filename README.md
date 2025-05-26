# CS163_Data_Visualization

## Introduction
This application is made as a "solo" project for the CS163 - Data Structures course. 

The developers of this app:
 - Nguyen Hoang Thuan Phat (Bix2llets) [Github](https://github.com/Bix2llets).
 - Huynh Chi Ton (hikito-otikih) [Github](https://github.com/hikito-otikih).

## Features
The application features visualization of popular data structures: graph, trie, AVL tree, hash map and linked list. The visualization is heavily inspired by the style at [USFCA](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html).

## How to build and run
To build this project, CMake, Makefile and a C++ compiler must be installed.

To build the project, execute these command in command line or Powershell

```
git clone https://github.com/Bix2llets/CS163_Data_Visualization
cd CS163_Data_Visualization
mkdir build
cd build
cmake .. -G"Unix Makefiles"
cmake --build .
```

Then, the executable file should be found inside the `build/` folder
