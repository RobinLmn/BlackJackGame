#include "blackjack.cpp"
#include <iostream>

using namespace std;

int main()
{
    cout << endl;
    cout << " \t Welcome to the BlackJack game !" << endl << endl;
    BlackJackGame game;
    // The main loop of the game
    bool playAgain = true;
    char answer = 'y';

    while (playAgain)
    {
        game.play();
        
        cout << "Would you like another round ? (y/n)";
        cin >> answer;
        cout << endl << endl;
        playAgain = ( answer == 'y' ? true:false);

    }

    cout << "Gave over !";
    cout << endl;

    return 0;
}