using namespace std;
#include "blackjack.h"
#include <string> 
#include <iostream>

#include <cstdlib>
#include <ctime>


// Card

Card::Card(Rank r, Type t)
{
    this->rank = r;
    this->type = t;
};

Rank Card::getRank()
{
    return this->rank;
}

Type Card::getType()
{
    return this->type;
}


void Card::setRank(Rank r)
{
    this->rank = r;
};

void Card::setType(Type t)
{
    this->type = t;
};

int Card::getValue()
{
    int value;

    // Convert card.rank char to int according to its value

    if (this->rank == 'T' || this->rank == 'J' ||this->rank == 'Q' || this->rank == 'K')
    {
        value = 10;
    }
    else
    {
        // convert char to int : '1' -> 1
        value = this->rank - '0';
    }
    
    return value;
};

void Card::displayCard()
{
    string rankString;

    if (this->rank == 'T')
    {
        rankString = "10";
    }
    else
    {
        std::string s(1, this->rank);
        rankString = s;
    }

    std::string typeString(1, this->type);
    string cardString = rankString + typeString;

    cout << cardString;
};

/////////////////////////////////////////////////////

// Hand

void Hand::add(Card c)
{

    if (c.getRank() == '1')
    {
        this->countAces++;
    }

    hand.push_back(c);
};

void Hand::clear()
{
    (this->countAces) = 0;
    (this->hand).clear();
};

int Hand::getTotal() const
{
    vector<Card> h = this->hand;

    int total = 0;
    for (Card card: h)
    {
        total += card.getValue();
    }

    int countA = this->countAces;

    while (total != 21 && countA > 0)
    {
        // Make aces count for 11 instead of 1
        if (total <= 11)
        {
            total += 10;
            countA -= 1;
        }
        else
        {
            break;
        }
    }

    return total;
};

vector<Card> Hand::getVecHand()
{
    return this->hand;
}

////////////////////////////////////////////////////

// Deck

vector<Card> Deck::getDeck()
{
    return this->deck;
};

void Deck::populate()
{
    Rank vRank[] = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    Type vType[] = {CLUBS, DIAMONDS, SPADES, HEARTS};

    // Create cards 1 to 9 of every type
    for (Rank r : vRank)
    {
        for (Type t : vType)
        {
            Card newCard(r, t);
            (this->deck).push_back(newCard);
        }
    }
};

void Deck::shuffle()
{
    for (int i=0; i<deck.size(); i++)
    {
        int indexToSwap = rand() % deck.size();   // random index between 0 and 51
        Card temp = deck[indexToSwap];
        deck[indexToSwap] = deck[i];
        deck[i] = temp;
    }
}

Card Deck::deal()
{
    Card cDealt = deck.back();
    (this->deck).pop_back();
    return cDealt;
}

void Deck::clear()
{
    this->deck.clear();
}

////////////////////////////////////////////////////

// Abstract Player

Hand AbstractPlayer::getHand()
{
    return this->hand;
};

bool AbstractPlayer::isBusted()
{
    return (this->hand.getTotal() > 21);
};

void AbstractPlayer::displayHand()
{
    for (Card card: (this->hand).getVecHand())
    {
        card.displayCard();
        cout << " ";
    }

    cout << "[" << (this->hand).getTotal() << "]";
};

////////////////////////////////////////////////////

// Human Player

bool HumanPlayer::isDrawing() const
{
    cout << "Do you want to draw ? (y/n) " << endl;

    string inputPlayer;
    bool isValid = false;
    cin >> inputPlayer;

    while (!isValid)
        if (inputPlayer == "y")
        {
            return true;
        }   
        else if (inputPlayer == "n")
        {
            return false;
        }
        else
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Input invalid. Tap 'y' to draw a card, 'n' to pass." << endl;
            cin >> inputPlayer;

            isValid = false;
        }
};

void HumanPlayer::announce(Status status)
{
    if (status == WIN)
    {
        cout << "Player wins." << endl;
    }
    else if (status == LOST)
    {
        cout << "Casino Wins." << endl;
    }
    else if (status == TIE)
    {
        cout << "Push: No one wins." << endl;
    }
};

////////////////////////////////////////////////////

// ComputerPlayer

bool ComputerPlayer::isDrawing() const
{
    return hand.getTotal() <= 16;
};
 
////////////////////////////////////////////////////

// BlackJackGame

void BlackJackGame::endRound()
{
    m_casino.hand.clear();
    m_deck.clear();
}

void BlackJackGame::play()
{
    srand((unsigned) time(0));
    
    // Create deck, populate, shuffle
    m_deck.populate();
    m_deck.shuffle();
    
    // create player
    HumanPlayer *player = new HumanPlayer();

    // Player is dealt 2 open card.
    (*player).hand.add( m_deck.deal() );
    (*player).hand.add( m_deck.deal() );

    cout << "Player: ";
    (*player).displayHand();
    cout << endl;

    // Computer is dealt one card.
    m_casino.hand.add( m_deck.deal() );

    cout << "Casino: ";
    m_casino.displayHand();
    cout << endl;

    // while Player chooses to draw a card
    while ((*player).isDrawing())
    {
        // Player is dealt a card
        (*player).hand.add( m_deck.deal() );

        // Print player's hand
        cout << "Player: ";
        (*player).displayHand();
        cout << endl;
        
        // Check if busted.
        if ((*player).isBusted())
        {
            cout << "Player busts." << endl;
            (*player).announce(LOST);
            endRound();
            return;
        }

    }

    // Computer draws card until he reaches a sum of 16
    while (m_casino.isDrawing())
    {
        m_casino.hand.add( m_deck.deal() );

        cout << "Casino: ";
        m_casino.displayHand();
        cout << endl;
    }

    // Check if the computer busted
    if (m_casino.isBusted())
    {
        (*player).announce(WIN);
    }
    else 
    {
        // compare values to see who's the closest to 21
        int playerDiff = (21 - (*player).hand.getTotal());
        int compDiff = (21 - m_casino.hand.getTotal());

        if (playerDiff > compDiff)
        {
            (*player).announce(LOST);
        }
        else if (compDiff > playerDiff)
        {
            (*player).announce(WIN);
        }
        else if (compDiff == playerDiff)
        {
            (*player).announce(TIE);
        }
    }

    // end of round. Clear casino and player's hand. Shuffle the deck.
    endRound();
}

