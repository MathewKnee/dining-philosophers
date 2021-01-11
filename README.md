# dining-philosophers
Simple C program solving Dining philosophers problem

This program is using linux system libraries so it will only run on linux!

In the approach that I used unique ids from 1 to 5 are assigned to philosophers. Then philosopher with even ids first reach for the left fork an those with uneven reach for the right fork. 

Project consits of:
- philosopher.c - code of individual philosopher
- run.sh - script that compiles(GCC) and runs 5 philosophers
- clean.sh - script that removes semaphore and by this stopping the program

