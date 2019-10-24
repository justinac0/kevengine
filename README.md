># kevin-engine
**kevin-engine** is a 3D game engine written in C99. This project is a WIP.
**kevin-engine** is released under the Unlicense (http://unlicense.org/).
Read LICENSE.md to see what this implies.
___

##### Third party libraries used
* [glfw 3.3](#https://www.glfw.org/)
* [glad](#https://github.com/Dav1dde/glad)

>## Table of contents
* ~~Website~~
* [Build Source](#build)
* [Documentation](#documentation)
* [Change Log](#change-log)
* [Bugs](#bugs)

>## Build Source
The following sub-sections cover how to setup the build system and how to compile **kevin-engine** source.

#### Windows
##### Setting up the enviroment
This project uses GLFW. You will need to download the binaries from this following link.
Download 64 bit binaries if your computer supports it.
https://www.glfw.org/download.html

For compiling on windows we use MinGW (install gcc options)
http://mingw.org/

Extract the GLFW binary files -> open containing folder ```lib-mingw-w64``` or ```lib-mingw32-w32```
Inside you will see 3 files: ```glfw3.dll```, ```libglfw3.a``` and ```libglfw3dll.a```
Copy these files and place then inside of the folder ```lib``` found inside of the MinGW installation path.
```
MinGW
├───bin                              
├───include                          
├───lib                              
│   └─  ** Copied Files **                   
├───libexec 
├───mingw32
├───share
└───var                              
```

##### Compiling
For compilation run ```mingw32-make all```
The executable can be found in the bin folder of kevin-engine ```bin/kevin.exe```
For removing generated files run ```mingw32-make clean```

### Linux
#### Setting up the enviroment
You will need to install a couple of packages:
```make```, ```libgl1-mesa-dev``` and ```gcc```

##### Compiling
For compilation run ```make all```
The executable can be found in the bin folder of kevin-engine ```bin/kevin```
For removing generated files run ```make clean```

>## Documentation

>## Change Log
A change log will be released after every release.
-- Currently working on **kevin-engine** release v0.0.1

>## Bugs
...
