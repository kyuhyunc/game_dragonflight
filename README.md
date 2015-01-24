# Game - Programming Assignments Private Repository
### Student Information
  + Name: Kyu Hyun Chang
  + USC Email: kyuhyunc@usc.edu

### Game Information
  + Game Name: Dragon Flight
  + Game Description: Control flying dragon and avoid obstacles coming toward
  + [Game Design Doc](GameDesignDoc.md)

### Compile & Run Instructions
The grader should use the following procedure to compile and run the code:
```shell
#Compile Instructions
qmake -project
qmake
make
#Doxygen Instructions
doxygen -g config.txt
doxygen config.txt
#Command to run
./game_dragonflight
*side note1: the name of output file can be differ by the name of directory
*side note2: the executable file may not be in the current directory depending which OS you use.
(for the mac users, it might be under "public_dragonflight.app/Contents/MacOS/") 
```

### Screenshots
**Playing screen**
<img src="./pics/playing_screen.png" alt="playing screen"/>
