# Hangman

**********This program was made using beginning level C++ methologies - functions, arrays, loops and data files ************************

                                
## Game working
 
1. An input file "words.txt" contains 100 of words.
2. A word from the input file is chosen randomly and number of blanks are generated.
3. User tries to guess each letter. Each correct guess is 1 point and each wrong guess loses 1 point.
4. A part of the hangman figure is displayed for every wrong guess.
5. If the whole word is guessed, we recieve 2 more points. Guessing the whole word without errors gives additional 1 point.
6. When the full hangman is displayed, its game over.
7. In an output file "scores.txt", the word and its scores obtained are written into it.

## Project structure
                        
 1. Files
    
    a. words.txt        - Input file that consists of 100 words.
    
    b. scores.txt       - Output file that stores each score with its word.--
    
 2. Functions
    
    a. welcomeMessage() - Display a message about the instructions and working of the game.
    
    b. readWord()       - To read every word from "words.txt".
    
    c. wordLetters()    - To select a random word from "words.txt" using rand() and then displaying number of blanks equal to the length                           of the word.
    
    d. guessLetters()   - To check if every letter entered by the user existing in the word. It replaces its blanks with the letter if part                           of the word. It also keeps track of the scores.
    
    e. hangmanFigure()  - To display each part of the hangman for every wrong guess.
    
    f. writeFile()      - To store the score and its word in "scores.txt".--
    
  3. Input Validation   - To check if "words.txt" was opened successfully.--
  
  4. Arrays
     
     a. words           - String list consisting of all the words from "words.txt"
     
     b. blank_for_word  - Character list consisting of the blanks(underscore) for each word.
     
     c. score_list      - Integer list storing the scores of every game played.
     
     d. words_list      - String list storing each word of every game played.


