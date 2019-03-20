# Compilers Generator

## Project structure

### src
 All of the project source code will be contained in the src directory.
 Each phase will have its own subdirectory. General purpose modules and utils will exist in the top level directory as well.
 Any phase directory can have a util subdirectory for utils specific for that phase.

### test
The unit tests will reside in this directory. It contains two subdirectories.

- src_tests

   contains a hierarchy of dirs resembling to that of the src and has all the unit tests.
- lib

   the source code of the gtest library to be compiled

### documents
   any documentation or style guides.

## Installation
1. Import the project into clion to make sure it generates the appropriate cmake files
2. In the generated cmake file, add the lines
```cmake
 add_subdirectory(tests)
```
3. In the tests subdirectory create a cmakefile with the following code.
Note that you should replace the project with your project name to match the cmake in the top level directory.
```cmake
project(porject)

add_subdirectory(lib/gtest)
```

> see the [readme](tests/README.me) in the tests library for more on using gtest with clion

4. load the cmake at the top level directory of your project
5. Happy Coding!

## Notes
- If you use clion, the ide files are already added to the gitignore. If not, take a little time to add your generated files to the ignore file.
- Use this [CheatSheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) to update readme files properly.