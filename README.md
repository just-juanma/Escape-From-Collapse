# Escape From Collapse
By Juan Manuel González Kapnik. Idea taken from Universidad Favaloro, Introduction to Networks and Internet (2021).
## 📋 Table of contents
1. [Proyect Description](#pdescription)
2. [Software Description](#sdescription)
3. [How to Install and Run the Project](#howtorun)
4. [How to Use the Project](#howtouse)
5. [License](#license)

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

## ⬇️ How to Install and Run the Project <a name="howtorun"></a>
The project is prepared to debug it in CMake (minimum version 3.0.0). For more information I recommend you to check the CMake documentation.

To run the project, we can go to its executable in [\Escape From Collapse\build\src\Debug](https://github.com/just-juanma/Escape-From-Collapse/tree/master/build/src/Debug)

## 🕹 How to Use the Project <a name="howtouse"></a>
To use the project, we simply have to run it. Once inside, it is quite interactive and easy to understand the menu of options that the program has. 

## ⚠️ Considerations <a name="considerations"></a>
There may be errors in the memory stack during the board generations. in case of any error at the time of board generation, restart the game. I will be working on a possible solution. Thanks for your understanding.

## ©️ License <a name="license"></a>
Escape From Collapse is licensed under the [GNU General Public License v3.0](https://github.com/just-juanma/Escape-From-Collapse/blob/master/LICENSE)
