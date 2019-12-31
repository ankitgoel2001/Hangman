//Hangman game by Ankit Goel

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>

using namespace std;

void welcomeMessage();
void readWord(const int, ifstream &, string []);
void writeFile(ofstream &, const int [], const string [], int);
int wordLetters(const string [], char [], const int);
int hangmanFigure(int, const string[], int);
int guessLetters(const string[], char [], int &);

int main()
{
    const int MAX_LIST = 100; // You can not have a list of more than 100 words
    const int MAX_SIZE = 100; // You can not generate more than 100 blanks

    string words[MAX_SIZE]; // A word cannot have more than 100 letters

    unsigned seed = time(0); //To generate words randomly
    srand(seed);

    welcomeMessage();

    ifstream inputFile;
    inputFile.open("WordList.txt");

    if (!inputFile) //input validation
        cout << "Error! Couldn't open the word list! Game Crashed!!\n";
    else
    {
        int word_index, game_score;
        int try_index = 0;
        char blank_for_word[MAX_SIZE];
        int score_list[MAX_LIST];
        string words_list[MAX_LIST];
        char option;

        readWord(MAX_LIST, inputFile, words);

        do
        {
            word_index = wordLetters(words, blank_for_word, MAX_LIST);
            game_score = guessLetters(words, blank_for_word, word_index);

            cout << "\nDo you want to play again(press y or Y)?";
            cin >> option;

            system("cls");

            words_list[try_index] = words[word_index];
            score_list[try_index] = game_score;

            try_index++;

        } while (option == 'y' || option == 'Y');

        inputFile.close();

        ofstream outputFile;
        outputFile.open("scores.txt");

        writeFile(outputFile, score_list, words_list, try_index);

        outputFile.close();

    }

    return 0;
}

/**This function is to print a welcome
   message about the program**/
void welcomeMessage()
{
    char ch;
    cout << "\t\t\t~~~~~~WELCOME TO HANGMAN!!!~~~~~~\n\n\n";
    cout << "\t\tRules of the game:-\n";
    cout << "\t1. There were will be number of blanks generated depending on the word.\n";
    cout << "\t2. Try to guess each letter of the word.\n";
    cout << "\t3. Each wrong guess displays the parts of the hangman.\n";
    cout << "\t4. When the hangman is fully drawn, YOUR OUT!!.\n\n";
    cout << "\t\tScoring system:-\n";
    cout << "\t5. Correct guess: +1 point         Wrong guess: -1 point\n";
    cout << "\t6. Guessing full word: +2 points (AND) without errors: +3 points\n";
    cout << "\t\t. Good Luck!!\n\n";

    cout << "\tPress Y to continue to game: ";
    cin >> ch;

    if (ch == 'Y')
        system("cls");
}

/**This function is to take the word from the user
   and then generate the blanks**/
int wordLetters(const string words[], char blank_for_word[], const int MAX_LIST)
{
    int random_word = rand() % 12;

    for (int blanks = 0; blanks < words[random_word].length(); blanks++)
    {
        blank_for_word[blanks] = '_';
        cout << blank_for_word[blanks] << " ";
    }
    return random_word;
}

/**This function is to read each word from
   the input file**/
void readWord(const int MAX_LIST, ifstream &inputFile, string words[])
{
    int i = 0;

        while (i < MAX_LIST && getline(inputFile, words[i]))
        {
            i++;
        }
}

/**This function is to guess each letter and replace the blank
   with the corresponding letter and keep track of score**/
int guessLetters(const string words[], char blank_for_word[], int &word_index)
{
    char letter;
    int i = 0;
    int wrong_choice = 0;
    int score = 0, rounded_score = 0;
    const int MAX_GUESS = 26;

    while (i < MAX_GUESS)
    {
        cout << "\n\nEnter a letter to guess: ";
        cin >> letter;

        int search_letter = 0;
        int count_letter = 0;
        bool found_letter = false;

        //loop to search if the letter matches the word
        while (search_letter < words[word_index].length())
        {
            if (blank_for_word[search_letter] == letter)
            {
                cout << "You already guessed that letter!";
                score--;
            }
            if (words[word_index][search_letter] == letter)
            {
                blank_for_word[search_letter] = letter;
                found_letter = true;
                score++;
            }
            search_letter++;
        }
        i++;

        int j = 0;
        //loop to check if all the blanks are filled and count the letters found
        while (j < words[word_index].length())
        {
            if (blank_for_word[j] != '_')
                count_letter++;
            j++;
        }

        system("cls");

        int k = 0;
        //loop to generate the no.of blanks according to the length of the word
        while (k < words[word_index].length())
        {
            cout << blank_for_word[k] << " ";
            k++;
        }

        if (!found_letter)
        {
            cout << "\n\nWrong letter!\n";
            wrong_choice++;
            score--;
        }

        cout << "\n\n\n\n\nHANGMAN FIGURE DISPLAY\n\n\n\n";
        int check = hangmanFigure(wrong_choice, words, word_index);

        rounded_score = static_cast<double>(score) / words[word_index].length() * 10;

        if (count_letter == words[word_index].length() && check == 0)
        {
            cout << "\nYou guessed the word!";
            rounded_score += 2;

            if (wrong_choice == 0)
            {
                cout << "\nCONGRATS ON FIRST TRY!!";
                rounded_score++;
            }

            break;
        }
        else if (check == -1)
        {
            if (rounded_score < 0)
                rounded_score = 0;
            break;
        }
    }

    cout << "\nYour score is: " << rounded_score << "/10" ;

    return rounded_score;
}

/**This function is to display the hangman figure each time
   an answer is wrong**/
int hangmanFigure(int wrong_choice, const string words[], int word_index)
{
    char head = 'O', left_body = '/', right_body = '\\', body = '|';

    if (wrong_choice > 0)
        cout << "\t\t " << head << endl;
    if (wrong_choice == 2)
        cout << "\t\t " << body;
    else if (wrong_choice > 2)
        cout << "\t\t" << left_body << body;
    if (wrong_choice > 3)
        cout << right_body << endl;
    if (wrong_choice > 4)
        cout << "\t\t" << left_body;
    if (wrong_choice > 5)
        cout << " " << right_body;
    if (wrong_choice > 6)
    {
        cout << "\n\nGAME OVER!!";
        cout << "\nYour word was " << words[word_index];

        return -1;
    }
    return 0;
}

/**This function is to write each score to
   an output file scores.txt**/
void writeFile(ofstream &outputFile, const int score_list[], const string words_list[], int try_index)
{
    int i = 0;

    while (i < try_index)
    {
        outputFile << words_list[i] << ": " << score_list[i] << endl;
        i++;
    }

}
