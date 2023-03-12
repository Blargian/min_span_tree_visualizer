# Minimum Spanning Tree Algorithm Visualizer

A beginner C++ project to visualize how two popular minimum spanning tree algorithms work - mainly Kruskal's and Prim's.

The project was inspired by the following two youtube videos, which I thought would be fun to try implement myself in C++:

[Prim's Algorithm Animation](https://www.youtube.com/watch?v=wpV1wvHqyuY&t=62s)

[Kruskal's Algorithm Animation](https://www.youtube.com/watch?v=o8Sqm1_3BRo)

## Technologies 

[![C++](https://skillicons.dev/icons?i=cpp,cmake)](https://skillicons.dev)

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
