#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include "player.h"
#include "constants.h"
#include "student.h"
using namespace std;

void Dealer::changeDeck() {
	cardList.clear();

	for (int i = 0; i < cardDeck; i++) {
		for (int j = 1; j <= 13; j++) {
			cardList.push_back(Card(Shape::CLOVER, j));
			cardList.push_back(Card(Shape::DIAMOND, j));
			cardList.push_back(Card(Shape::HEART, j));
			cardList.push_back(Card(Shape::SPADE, j));
		}
	}
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(cardList.begin(), cardList.end(), default_random_engine(seed));
	//random_shuffle(cardList.begin(), cardList.end());

	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		(*player)->notifyCardReset(cardDeck);
	}
}

void Dealer::calculateDealerCard(Card card) {
	if (card.getValue() == 1) {
		sum += 11;
		aCard++;
	}
	else if (card.getValue() <= 10) {
		sum += card.getValue();
	}
	else {
		sum += 10;
	}
	cardCount++;
}

Card Dealer::drawCardOnCardList() {
	Card card = cardList.back();
	cardList.pop_back();
	return card;
}
void Dealer::giveCard(bool dealerCardOpened) {
	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		Card card = drawCardOnCardList();

		(*player)->notifyMyCard(card);
		for (vector<Seat*>::iterator other = players.begin(); other != players.end(); other++) {
			if (player == other) continue;

			(*other)->notifyOtherPlayerCard(card);
		}
	}
		
	Card card = drawCardOnCardList();
	calculateDealerCard(card);

	if (!dealerCardOpened) {
		hiddenCard = card;
		return;
	}
	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		(*player)->notifyDealerCard(card);
	}
}

void Dealer::completeRound() {
	sum = 0;
	aCard = 0;
	cardCount = 0;

	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		(*player)->notifyCompletedRound();
	}
}
void Dealer::playPlayerTurn() {
	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		while ((*player)->checkAction() == Action::HIT && !(*player)->isBust()) {
			Card card = drawCardOnCardList();
			(*player)->notifyMyCard(card);
			(*player)->checkAction();
			for (vector<Seat*>::iterator other = players.begin(); other != players.end(); other++) {
				if (player == other) continue;
				(*other)->notifyOtherPlayerCard(card);
			}
		}
	}
}

void Dealer::playDealerTurn() {
	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		(*player)->notifyDealerCard(hiddenCard);
	}

	while (sum < 16) {
		Card card = drawCardOnCardList();
		calculateDealerCard(card);
		for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
			(*player)->notifyDealerCard(card);
		}
		if (sum > 21 && aCard > 0) {
			aCard--;
			sum -= 10;
		}
	}
}

void Dealer::judge() {
	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		if ((*player)->getScore() > 21) {
			(*player)->plusLose();
		} 
		else if ((*player)->getScore() == 21 && sum == 21) {
			if ((*player)->getCardCount() == 2 && cardCount == 2) {
				(*player)->plusDraw();
			}
			else if (cardCount == 2) {
				(*player)->plusLose();
			}
			else if ((*player)->getCardCount() == 2) {
				(*player)->plusWin();
			}
			else {
				(*player)->plusDraw();
			}
		}
		else if (sum > 21) {
			(*player)->plusWin();
		}
		else {
			if ((*player)->getScore() == sum) {
				(*player)->plusDraw();
			}
			else if ((*player)->getScore() < sum) {
				(*player)->plusLose();
			}
			else {
				(*player)->plusWin();
			}
		}
	}
}


Dealer::Dealer(int gameRound, int cardDeck, int playerCount) {
	sum = 0;
	aCard = 0;
	cardCount = 0;

	this->cardDeck = cardDeck;
	this->playerCount = playerCount;
	this->gameRound = gameRound;

	players.push_back(new Seat(new Student()));
	for (int i = 1; i < playerCount; i++) {
		players.push_back(new Seat(new DummyPlayer()));
	}
}

void Dealer::playGame() {
	for (int playRound = 0; playRound < gameRound; playRound++) {
		if (cardList.size() < 13 * 4 * cardDeck * 0.1) {
			changeDeck();
		}
		giveCard(true);
		giveCard(false);

		playPlayerTurn();
		playDealerTurn();
		judge();
		completeRound();
	}
}

void Dealer::printResult() {
	for (vector<Seat*>::iterator player = players.begin(); player != players.end(); player++) {
		cout << (*player)->toString() << endl;
	}
}
