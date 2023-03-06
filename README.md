# Minimum Spanning Tree Algorithm Visualizer

A beginner C++ project to visualize how two popular minimum spanning tree algorithms, Kruskal's and Prim's, work. 

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
