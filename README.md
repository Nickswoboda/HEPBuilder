# HEPDesigner

HEPDesigner is a desktop application designed for healthcare professionals to create and share **H**ome **E**xercise **P**rograms with their patients. The program allows for the creation, saving and loading of routines that patients can do at home.

### Download
1. Download HEPDesigner.zip from Releases section
2. Extract .zip file to desired location
3. Run .exe file

### Build (CMake/Qmake)
**Note: You must have Qt installed and the assets folder must be in the executable directory**
1. Download source code
2. `qmake HEPDesigner.pro`
3. `make`
- Currently CMake only works through QtCreator

## Features

#### Create an HEP
Creating a HEP is as simple as adding the desired exercises to the routine area, pressing the 'Preview' button to set the sets, reps and hold time of each exercise and pressing 'Ok' to print.

#### Loading and saving routines
Save commonly used sets of exercises to load for later use.

#### Searching
Search by name or 'tag' to quickly find the exercises you are looking for.

#### Creating new exercises
HEPDesigner comes prepackaged with some of the most common exercises, but it is far from complete. If you are looking for an exercises that does not exist, it is quick and easy to add your own.

## Dependencies
[Qt](https://qt.io)
