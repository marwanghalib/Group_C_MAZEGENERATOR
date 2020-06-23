###Maze Generator###

*Organization : Carleton University

*Authors
-Tareq Dawoudiah, 7136770 (uOttawa), haiduowad 
-Marwan Ghalib, 100859950, marwanghalib
-Griffin Barrett, 100978436, xlirate
-Manojkumar Chandrasekaran, (uOttawa) 101130903, mchandra5034

*Description

Maze Generator collects and canonicalizes the input from the user
for maze generation. When generating a maze, the user should specify the size, bias,
algorithm, characters used to represent the walls of the maze in the output, as well as
where to send the output (stdout or print to a file).

In this project we have used Recursive Backtracking, Sidewinder and Kruskal algorithm 
We have also included the ability to solve a maze provided by the user as
input. In this case, instead of providing console arguments, the user pipes a maze in on
stdin or specifies a file path in the first argument. This maze solution will come in the
form of a set of '.' marking the path form entrance to exit.

*Instructions and setup

1.	You need to use the command line git clone  https://github.com/marwanghalib/Group_C_MAZEGENERATOR.git to download the repo.
2.	Once the repo is downloaded then go to cd Group_C_MAZEGENERATOR.git
3.	Then run make
4.	Once it compiled you need to change the directory to bin and run cmaze

Step by step with instructions below

git clone  https://github.com/marwanghalib/Group_C_MAZEGENERATOR.git 
cd Group_C_MAZEGENERATOR.git 
make
cd bin
cmaze -options 

*User and Developer Guide
The detailed description for the user and the developer guide is in doc folder. Once you clone the repo in the local repository you need to go to cd doc and you will find all the information 

