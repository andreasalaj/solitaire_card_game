# Simple Solitaire card game implementation in C

Compile the program:

    username@computer_name ~/Desktop/soliter/solitaire $ gcc -Wall solitaire.c


Run the game with one of the provided deck shuffles (`config.txt` and `config2.txt`):

    username@computer_name ~/Desktop/soliter/solitaire $ ./a.out config.txt 
    0   | 1   | 2   | 3   | 4   | DEP | DEP
    ---------------------------------------
    X   | BK  | BQ  | BJ  | RK  |     |    
    X   |     | RQ  | B10 | B9  |     |    
    X   |     |     | B8  | B3  |     |    
    X   |     |     |     | B2  |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    X   |     |     |     |     |     |    
    R9  |     |     |     |     |     |    
    esp> help
    possible command:
     - move <color> <value> to <stacknumber>
     - help
     - exit
    esp> 
