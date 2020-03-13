// Header blackjack.h

using namespace std;
#include <vector>

enum Rank
{
    ACE = '1',
    TWO = '2',
    THREE = '3',
    FOUR = '4',
    FIVE = '5',
    SIX = '6',
    SEVEN = '7',
    EIGHT = '8',
    NINE = '9',
    TEN = 'T',
    JACK = 'J',
    QUEEN = 'Q',
    KING = 'K',
};

enum Type
{
    DIAMONDS = 'D',
    SPADES = 'S',
    CLUBS = 'C',
    HEARTS = 'H',
};

class Card
{
    // Fields
    private:
        Rank rank;
        Type type;

    // Methods
    public:
        Card(Rank r, Type t);
        void setRank(Rank r);
        Rank getRank();
        void setType(Type t);
        Type getType();
        int getValue();
        void displayCard();
};

class Hand
{

    // Field
    private: 
        vector<Card> hand;
        int countAces = 0;

    // Methods
    public:
        vector<Card> getVecHand();
        void add(Card c);
        void clear();
        int getTotal() const;
};

class Deck
{

    // Field
    private:
        vector<Card> deck;

    // Methods
    public:
        vector<Card> getDeck();
        void populate();
        void shuffle();
        Card deal();
        void clear();
};

class AbstractPlayer
{

    // Field
    public:
        Hand hand;

    // Methods
    public:
        Hand getHand();
        virtual bool isDrawing() const = 0;
        bool isBusted();
        void displayHand();
};

enum Status {
    LOST,
    WIN,
    TIE,
};

class HumanPlayer : public AbstractPlayer
{

    // Inherited methods and fields : hand, isDrawing(), isBusted()

    // Methods
    public:
        bool isDrawing() const override;
        void announce(Status status);
};

class ComputerPlayer : public AbstractPlayer
{

    // Inherited methods and fields : hand, isDrawing(), isBusted()

    public:
        bool isDrawing() const override;
};

class BlackJackGame
{

    // Fields
    private:
        Deck m_deck;
        ComputerPlayer m_casino;

    public:
        void play();
        void endRound();
};