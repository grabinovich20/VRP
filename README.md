## Table of Contents
- [Build Instructions](#build-instructions)

## Build Instructions

To build the VRP project, follow these instructions:

1. Clone this directory. Open a terminal and navigate to the root folder of the project. You should be in the same directory as the CMakeLists.txt.

2. Create the build directory by running the following command:

   ```shell
   cmake . -B build

3. Once you have run the cmake command, a build directory should have been made for you. Navigate into that directory by doing:

   ```shell
   cd build

4. To compile the code use the following command:

    ```shell
    make

5. To run the program use the following command:

    ```shell
    ./VRP [input_file.txt]
