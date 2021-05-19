# Reversi-Terminal-Game
A Reversi game to be played in the Linux terminal

The source code is in the 'src' folder.

Go to the terminal and execute the command 'make', to compile all the files in the folder.

It will show up a executable file named 'reversi.exe', that you can run 
on the terminal by typing './reversi'.

The game will appear on the terminal with a menu.
-> If you want to read information from a text file, type 'L' followed by the file name
  Example: 'L board.txt'.
-> If you want to write information to a text file, type 'E' followed by the file name
  Example: 'E board.txt'.
-> If you want to play a move on the board, inserting a coordinate of the move you want,
type 'J' followed by the coordinates of your move.
  Example: 'J 1 2'(inserts your piece in the coordinate (1,2) of the boad).
-> If you want to see where you can play, type 'S'.
  Example: 'S' and the available positions to play will appear on the board with a '.'. 
-> If you want a suggestion of one possible move, type 'H'
  Example: 'H' and the best imidiate score gaining play will appear on the board with a '?'. 
-> If you want to start a new game against a human player, type 'N' 
followed by the starting piece 'X' or 'O'.
  Example: 'N O'.
-> If you want to start a new game against a bot, type 'A' 
followed by the starting piece 'X' or 'O', followed by the difficulty from 1 to 3.
  Example: 'A O 3'.
  
The game follows the regular Reversi game rules.
