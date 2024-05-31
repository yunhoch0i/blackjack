#include "player.h"
Seat::Seat(Player* player) {
	this->player = player;
	win = 0;
	lose = 0;
	draw = 0;
}

Action Seat::checkAction() {
	return player->checkAction();
}

int Seat::getCardCount() const {
	return playerCardList.size();
}

void Seat::notifyDealerCard(Card card) {
	player->notifyDealerCard(card);
}

void Seat::notifyOtherPlayerCard(Card card) {
	player->notifyOtherPlayerCard(card);
}

void Seat::notifyMyCard(Card card) {
	player->notifyMyCard(card);
	playerCardList.push_back(card);
}

void Seat::notifyCardReset(int cardDeck) {
	player->notifyCardReset(cardDeck);
}

void Seat::notifyCompletedRound() {
	player->notifyCompletedRound();
	playerCardList.clear();
}

void Seat::plusWin() {
	win++;
}

void Seat::plusLose() {
	lose++;
}

void Seat::plusDraw() {
	draw++;
}

bool Seat::isBust() {
	return (getScore() > 21);
}

int Seat::getScore() {
	int sum = 0, aCard = 0;
	for (vector<Card>::iterator card = playerCardList.begin(); card != playerCardList.end(); card++) {
		if ((*card).getValue() == 1) {
			aCard++;
			sum += 11;
		}
		else if ((*card).getValue() <= 10) {
			sum += (*card).getValue();
		}
		else {
			sum += 10;
		}
	}

	while (aCard > 0 && sum > 21) {
		sum -= 10;
		aCard--;
	}

	return sum;
}


string Seat::toString() const {
	return player->getName() + "\t½Â¸® " + to_string(win) + "È¸\tÆÐ¹è " + to_string(lose) + "È¸\t¹«½ÂºÎ " + to_string(draw) + "È¸\t(½Â·ü : " + to_string((double)win / (win + lose + draw) * 100) + ")";
}