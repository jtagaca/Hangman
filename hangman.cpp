#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include<math.h>
using namespace std;

class Words

{

private:
    int minlen, maxlen;

    int count;

    string* choices;

public:
    Words()
    {
    }

    Words(int min, int max)

    {

        minlen = min;

        maxlen = max;

        count = count_candidates();

        load_words();
    }

    void reset(int min, int max)
    {
        minlen = min;
        maxlen = max;
        if (choices != NULL)
        {
            choices == NULL;
        }
        count_candidates();
        load_words();
    }

    int count_candidates()

    {

        count = 0;

        ifstream infile("enable1.txt");

        if (infile.fail())
        {

            cout << "Create input file enable1.txt.\n";

            exit(0);
        }

        string word;

        while (!infile.eof())
        {

            infile >> word;

            if (infile.eof())
                break;

            if (word.length() >= minlen && word.length() <= maxlen)

            {

                count++;
            }
        }

        infile.close();

        return count;
    }

    void load_words()

    {

        choices = new string[count];

        ifstream infile("enable1.txt");

        if (infile.fail())
        {

            cout << "Create input file enable1.txt.\n";

            exit(0);
        }

        int i = 0;

        string word;

        while (!infile.eof())
        {

            infile >> word;

            if (infile.eof())
                break;

            if (word.length() >= minlen && word.length() <= maxlen)

            {

                choices[i++] = word;
            }
        }

        infile.close();
    }

    string pick_word()

    {

        srand(time(NULL));

        int randNum = 1 + rand() % count;

        return choices[randNum];
    }

    int get_min()
    {
        return minlen;
    }
    int get_max()
    {
        return maxlen;
    }
};
int show_menu()
{
    int choice;
    cout << "1.Play the computer(auto select random range)\n";
    cout << "2.Play the computer(min:7,max:12)\n";
    cout << "3.Play the computer(user selects/changes range)\n";
    cout << "4.Play the computer(use same range stored in 3)\n";
    cout << "5.Two Player mode(user1 enters the word,user2 guesses)\n";
    cout << "6.Quit\n\n";
    cout << "Enter choice:";
    cin >> choice;
    return choice;
}

void show_menu(int ch)
{
    cout << "1.Play the computer(auto select random range)\n";
    cout << "2.Play the computer(min:7,max:12)\n";
    cout << "3.Play the computer(user selects/changes range)\n";
    cout << "4.Play the computer(use same range stored in 3)\n";
    cout << "5.Two Player mode(user1 enters the word,user2 guesses)\n";
    cout << "6.Quit\n\n";
    cout << "Enter choice:";
    cout << ch << "\n";
}

#include <string.h>

class Hangman

{

private:
    char word[40];

    char progress[40];

    int word_length;

    void clear_progress(int length)

    {

        int i = 0;

        for (i = 0; i < length; i++)

        {

            progress[i] = '-';
        }

        progress[i] = '\0';
    }

protected:
    int matches;

    char last_guess;

    string chars_guessed;

    int wrong_guesses;

    int remaining;

    void initialize(string start)

    {

        chars_guessed = "";

        wrong_guesses = 0;

        strcpy(word, start.c_str());

        word_length = strlen(word);

        remaining = 6;

        clear_progress(word_length);
    }

public:
    Hangman(string start)

    {

        initialize(start);
    }

    int get_remaining()

    {

        return remaining;
    }

    char* getWord()

    {

        return word;
    }

    char* get_progress()

    {

        return progress;
    }

    bool is_word_complete()

    {

        if (strcmp(progress, word) == 0)

            return true;

        else

            return false;
    }

protected:
    bool check(char user_guess)
    {

        if (last_guess != user_guess)
        {

            matches = 0;
            bool flag = false;

            if (strchr(word, user_guess) != NULL)

            {

                for (int i = 0; i < strlen(word); i++)

                {

                    if (word[i] == user_guess)

                    {

                        progress[i] = user_guess;

                        flag = true;

                        chars_guessed += user_guess;

                        matches++;
                    }
                }
            }

            else

            {

                wrong_guesses += 1;
            }

            remaining--;

            last_guess = user_guess;
        }
    }
};

class HangmanConsole : public Hangman

{

public:
    HangmanConsole(string start)
        : Hangman(start)

    {
    }

    void show_status(int stage)

    {

        switch (stage)

        {

            case 0:

                cout << " +-----\n";

                cout << " | \n";

                cout << " | \n";

                cout << " | \n";

                cout << " | \n";

                cout << " ----- \n";

                break;

            case 1:

                cout << " +------\n";

                cout << " |   O  \n";

                cout << " | \n";

                cout << " | \n";

                cout << " | \n";

                cout << " ----- \n";

                break;

            case 2:

                cout << " +-------\n";

                cout << " |   O \n";

                cout << " |     \\ \n";

                cout << " | \n";

                cout << " | \n";

                cout << " ----- \n";

                break;

            case 3:

                cout << " +--------\n";

                cout << " |  O\n";

                cout << " | / \\\n";

                cout << " | \n";

                cout << " | \n";

                cout << " ----- \n";

                break;

            

            case 4:

                cout << " +--------\n";

                cout << " | O\n";

                cout << " | /|\\ \n";

                cout << " | \n";

                cout << " | \n";

                cout << " ----- \n";

                break;

            case 5:

                cout << " +--------\n";

                cout << " | O\n";

                cout << " | /|\\" << endl;

                cout << " | /" << endl;

                cout << " | \n";

                cout << " ----- \n";

                break;

            case 6:

                cout << " +--------\n";

                cout << " | O \n";

                cout << " | /|\\" << endl;

                cout << " | /\\" << endl;

                cout << " | \n";

                cout << " ----- \n";

                cout << "Game over";

                break;
        }
    }

    void show_info()

    {

        chars_guessed = get_progress();
        int stage=6-remaining;
        if(wrong_guesses==0){ // forces visual as a clear visual screen
            stage=0;
            show_status(stage);
        }
        else if(stage==6){
            show_status(stage); // forces visual end sticks if remaining=0
        }

        else {for(int i=0; i<=wrong_guesses;i++){ //checks to see if wrong guess is getting added to show visual
        if(wrong_guesses==i){
        show_status(stage);
        break;
        }
        }
        }

        cout << endl
             << matches << " matches were found on the user’s last guessed character "
             << last_guess;

        cout << endl << wrong_guesses << " wrong guesses were made";

        cout << endl << remaining << " attempts are remaining";

        cout << endl << chars_guessed << " letters have been guessed so far";
    }

    friend void operator>>(istream& input, HangmanConsole& game)
    {

        char ch;

        cin >> ch;

        if (!game.is_word_complete())

        {

            bool status = game.check(ch);
        }
    }
};
void get_range_num(char* prompt, int min, int max, int& number)
{
    int value;
    cout << prompt << " : ";
    cin >> value;
    while (value < min || value > max)
    {
        if (value < min)
        {
            cout << "value smaller than min," << prompt << " again: ";
        }
        else
        {
            cout << "value larger than max," << prompt << " again: ";
        }
        cin >> value;
    }
    number = value;
}

int main()
{
    int ch;
    int minlen = 0, maxlen = 0, min, max;
    srand(time(NULL));
    do
    {
        string gameword;
        ch = show_menu();
        switch (ch)
        {
            case 1:
            {
                min = 1 + (rand() % 40);
                max = 0;
                while (max < min)
                {
                    max = 1 + (rand() % 40);
                }
                Words words1(min, max);
                gameword = words1.pick_word();
            }
            break;
            case 2:
            {
                min = 7;
                max = 12;
                Words wordsclear2(min, max);
                Words words2(min, max);
                gameword = words2.pick_word();
            }
            break;
            case 3:
            {
                char prompt1[] = "Enter minimum length";
                char prompt2[] = "Enter maximum length";
                int minNumber, maxNumber;
                get_range_num(prompt1, 2, 40, minNumber);
                get_range_num(prompt2, minNumber, 40, maxNumber);
                Words words4(minNumber, maxNumber);
                gameword = words4.pick_word();
            }
            break;
            case 4:
            {
                if (minlen == 0 && maxlen == 0)
                {
                    cout << "Enter minimum length :";
                    cin >> min;
                    cout << "Enterr maximum length : ";
                    cin >> max;
                    Words words5;
                    words5.reset(min, max);
                    gameword = words5.pick_word();
                }
                else
                {
                    Words words5(minlen, maxlen);
                }
            }
            break;
            case 5:
            {
                cout << "Enter word(User 1) : ";
                cin >> gameword;
                system("clear");
            }
            break;
            case 6:
                break;
            default:
                cout << "Wrong choice entered";
        }


        HangmanConsole game(gameword);


        while (!game.is_word_complete() && game.get_remaining() > 0)

        {
            cout << "HANGMAN" << endl << "-------" << endl << endl;

            cout << "Your word is: " << game.get_progress() << endl;

            cout << endl;

            cout << "Enter your guess: ";

            cin >> game;

            game.show_info();
        }

    } while (ch != 6);
    return 0;
}
