#include "player.h"

/*
* 내가 받은 카드의 합이 17 이상이면 멈추고, 미만인 경우 계속 받도록 함
*/
Action DummyPlayer::checkAction() {
	if (myCardValue >= 17) return Action::STAND;
	return Action::HIT;
}

string DummyPlayer::getName() {
	return "__dummy player__";
}
void DummyPlayer::notifyDealerCard(Card card) {}
void DummyPlayer::notifyOtherPlayerCard(Card card) {}

/*
* 내가 받은 카드의 합을 계산
*/
void DummyPlayer::notifyMyCard(Card card) {
	if (card.getValue() > 10) myCardValue += 10;
	else myCardValue += card.getValue();
}
void DummyPlayer::notifyCardReset(int cardDeck) {}

/*
* 한 라운드가 종료되어서 카드 합을 0으로 초기화
*/
void DummyPlayer::notifyCompletedRound() {
	myCardValue = 0;
}
