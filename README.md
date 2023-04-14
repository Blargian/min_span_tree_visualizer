# Minimum Spanning Tree Algorithm Visualizer

A beginner C++ project to visualize how two popular minimum spanning tree algorithms work - mainly Kruskal's and Prim's.

![Recording 2023-04-14 at 19 50 48](https://user-images.githubusercontent.com/41984034/232121501-df875a28-c6f4-4a47-9ce1-95ce731cdbe0.gif)

The project was inspired by the following two youtube videos, which I thought would be fun to try implement myself in C++:

[Prim's Algorithm Animation](https://www.youtube.com/watch?v=wpV1wvHqyuY&t=62s)

[Kruskal's Algorithm Animation](https://www.youtube.com/watch?v=o8Sqm1_3BRo)

## Technologies 

- C++ 
- CMake
- Dear ImGui 
- Catch2 

## Local development guide Windows

`git clone` the repository to your local machine. 

Next, `cd lib` and add download Catch2 by running the following command:

`git clone https://github.com/catchorg/Catch2.git`

`cd ..` back up to the root directory. There you'll need to run:

`git clone https://github.com/Microsoft/vcpkg.git`

Once done, `cd` to the vcpkg folder and run: 

`./bootstrap-vcpkg.sh` 

Finally, run:

`./vcpkg integrate install`

You can now open the folder in visualize studio code. Open up the CMakeLists.txt file, `ctrl + save` and the project should compile. 

There are two executables which can be run. To run the main project select `min_span_tree_visualizer.exe` or to run the test suite select `tests.exe`

![Different executables](https://user-images.githubusercontent.com/41984034/224997758-9a8e42b5-bfa5-47cb-82f5-29a08713ca00.png)

