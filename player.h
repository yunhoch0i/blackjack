#pragma once
#include "constants.h"
#include <vector>
using namespace std;

class Player {
public:
	virtual Action checkAction() = 0;
	virtual string getName() = 0;
	virtual void notifyDealerCard(Card card) = 0;
	virtual void notifyOtherPlayerCard(Card card) = 0;
	virtual void notifyMyCard(Card card) = 0;
	virtual void notifyCardReset(int cardDeck) = 0;
	virtual void notifyCompletedRound() = 0;
};

class DummyPlayer : public Player {
private:
	int myCardValue;

public:
	Action checkAction();
	string getName();
	void notifyDealerCard(Card card);
	void notifyOtherPlayerCard(Card card);
	void notifyMyCard(Card card);
	void notifyCardReset(int cardDeck);
	void notifyCompletedRound();
};

class Seat {
private:
	int win;
	int lose;
	int draw;
	vector<Card> playerCardList;
	Player* player;

public: 
	Seat(Player* player);
	Action checkAction();
	int getCardCount() const;
	void notifyDealerCard(Card card);
	void notifyOtherPlayerCard(Card card);
	void notifyMyCard(Card card);
	void notifyCardReset(int cardDeck);
	void notifyCompletedRound();
	void plusWin();
	void plusLose();
	void plusDraw();
	bool isBust();
	int getScore();
	string toString() const;
};


class Dealer {
private:
	int sum;
	int aCard;
	int cardCount;

	int gameRound;
	int cardDeck;
	int playerCount;
	vector<Seat*> players;
	vector<Card> cardList;
	Card hiddenCard;

	void changeDeck();
	void calculateDealerCard(Card card);
	Card drawCardOnCardList();
	void giveCard(bool dealerCardOpened);
	void completeRound();
	void playPlayerTurn();
	void playDealerTurn();
	void judge();

public:
	Dealer(int gameRound, int cardDeck, int playerCount);
	void playGame();
	void printResult();
};