# Escape From Collapse
By Juan Manuel González Kapnik. Idea taken from Universidad Favaloro, Introduction to Networks and Internet (2021).
## 📋 Table of contents
1. [Proyect Description](#pdescription)
2. [Software Description](#sdescription)
3. [How to Install and Run the Project](#howtorun)
4. [How to Use the Project](#howtouse)
5. [License](#howtouse)

## 🚀 Project Description <a name="pdescription"></a>
This project has as main objective to demonstrate my knowledge in C language and the CMake tool over the objective of the program itself. However, in this description we will deal with the objective of the program itself.

It is a videogame whose objective is to avoid the obstacles (collapses) to reach the other side of the map before your opponents. This game is prepared to play with up to 4 players and has a detailed map. Inside the game you can read in detail how to play, or you can choose to read the howtoplay.md file. By means of a saving system, you can keep track of your won and lost games.

## 💻 Software Description <a name="sdescription"></a>
The software prepared to run the game is in C language, and uses the CMake packaging tool. It allowed me to better manage multiple files and to be able to carry out a better compilation process.

The system of saving players is in a binary file (.bin) using the functions that allow to manipulate the FILE pointer, both to record the number of players, as well as reading and writing them. It allows to save all the data of the structure 'player_t' and 'coords_t'.

The saving system works from the data control performed in the registration system (loginPlayer() and registeredPlayer()). By means of different lists I obtain a record of all data input.

The movement of players and board (as a whole) is dimensioned in a Cartesian plane of coordinates (x,y) where as the player moves, the board is released/covered. This relationship is fundamental to the operation of the video game.

The game is prepared to, in individual games, play against an Artificial Intelligence sufficiently prepared to try to win.

The display of the board was made in ASCII code, where all the boxes formed by columns have, in their center, a number that represents the player (or a square in case of being collapsed).
