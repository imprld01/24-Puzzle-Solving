# 24-Puzzle-Solving

A program to find solution of a given 24-puzzle problem.  
Given a intial state of a 24-puzzle problem,  
and the program finds the best solution, the one with the fewest steps,  
by A* searching according to Manhattan Distance, a consistent heuristic. 

This is an assignment on NTOU Artificial Intelligence 2016 Spring.  
This repository as a note help me to find the code in the future! 😀

# Testing Input

&#35;1 |
------------ |
0ABCDEFGHIJKLMNOPQRSTUVWX

&#35;2 |
------------ |
F0BCDAKGHIEJLMNOPQSRTUVWX

&#35;3 |
------------ |
F0BCDAKGHIEJLMNOPQRSTUVWX

&#35;4 |
------------ |
EABCDFKGHITOLMNJ0PRSUVQWX

QUIT to end the program!

# Testing Output

&#35;1 |
------------ |
0ABCDEFGHIJKLMNOPQRSTUVWX is already a goal state.

&#35;2 |
------------ |
No solution for F0BCDAKGHIEJLMNOPQSRTUVWX!!

&#35;3 |
------------ |
Solution for F0BCDAKGHIEJLMNOPQRSTUVWX is:<br>move 0 to left<br>move 0 to down<br>move 0 to down<br>move 0 to right<br>move 0 to up<br>move 0 to up<br>move 0 to left

&#35;4 |
------------ |
Solution for EABCDFKGHITOLMNJ0PRSUVQWX is:<br>move 0 to left<br>move 0 to up<br>move 0 to right<br>move 0 to down<br>move 0 to right<br>move 0 to down<br>move 0 to left<br>move 0 to left<br>move 0 to up<br>move 0 to up<br>move 0 to right<br>move 0 to up<br>move 0 to left<br>move 0 to up