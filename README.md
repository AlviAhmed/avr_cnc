# avr_cnc
This is my attempt (work in progress) at making a simple basic cnc stepper motor control system  
in AVR-C for AVR chips like in this case the atmega 328p.  
The program for now is designed to accept simple user inputs like direction and amount of steps,  
however as time goes on I planning to incorporate python to interpret actual g-code for my c program to run 

I have also recently added a second variation of the code(avr_sing.c), in which the user instead of sending one command at a time 
then compiling, the user can now have a whole list of commands, and the program will go through them one by one,  
I am also currently including functionality for simultaneous stepper movement as well.
