# Maze-solver-robot. -
This project is for the ATmega328P microcontroller written for an Elegoo robot to solve a maze.
The gold of the project is to write code for an ATMega328P microcontroller in C. Upon completion, the code was uploaded on the microcontroller using Atmel Studio. The microcontroller was the installed on an Arduino board and wired to an Elegoo robot.

How it works. 
The robot tries to solve a maze with a minute. If the robot solves the maze, a line tracking sensor is triggered by a black tape at the end of the maze. It then stops and activates its Bluetooth module for manual control. If however the robot did not solve the maze in one minute, is automatically stops and activates it Bluetooth module for manual control. This switching between the automatic and manual control is handled entirely by the code. There is not human interference.
