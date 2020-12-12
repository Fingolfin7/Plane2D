# Plane2D
A C++ header file I worked that allows you to create 2D planes and "draw" on them. You can set points, draw lines, save, and load in your planes.

## Getting Started
Visual Studio 2019 is recommended,

Start by cloning the repository or downloading the zip file.

Once downloaded, open folder and run the `GenerateProject.bat` file, which will be inside the "Generate Project" folder. This will run the "premake5.lua" and create a Visual Studio 2019 solution.

Alternatively, you can enter this command on the command prompt within the folder -> `premake5.exe vs2019`
You can generate solutions for vs2019, vs2017, vs2010 etc.

`Plane2D.h` is the header file containing the "Plane2D" class and it's definitions.

`Source.cpp` is an interface for users to create planes/canvases, setpoints and drawLines. It also allows users to load in previous projects and to save current projects.
Source.cpp also contains an example of a Cube created using `Plane2D.h`

### The Plane2D class:  

-> Contains a two dimensional vector, called `plane`, that holds "pointStates" that determine if a given point is empty, contains a dot, or is occupied.
    
-> Has a `drawPlane()` method that draws the plane onto the screen

-> Has a `setPoint()` method that takes in a row, and column index to set a point on the plane
    
-> Has a `makeLine()` method that takes int two points and draws a line between those two points

-> Has a `makeShell()` method that draws an outer shell for a given set of points
    
-> Has a `save()` method that saves the plane into two files, one containing indexes for all the points, and another containing the indexes for lines. 

-> Has a `loadsave()` method that loads in the plane from the two files mentioned above. 

-> An array holding all the points made on the plane, called `pointsArr`

-> An array holding the indexes of "from-to" points in pointsArr for making lines, called `linesArr`. E.g a line from the point at index 0 to the point at index 1


### Contribute to the project

Take a look, run the code, and contribute if you'd like!
