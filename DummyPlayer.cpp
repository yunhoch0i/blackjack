#include "player.h"

/*
* ���� ���� ī���� ���� 17 �̻��̸� ���߰�, �̸��� ��� ��� �޵��� ��
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
* ���� ���� ī���� ���� ���
*/
void DummyPlayer::notifyMyCard(Card card) {
	if (card.getValue() > 10) myCardValue += 10;
	else myCardValue += card.getValue();
}
void DummyPlayer::notifyCardReset(int cardDeck) {}

/*
* �� ���尡 ����Ǿ ī�� ���� 0���� �ʱ�ȭ
*/
void DummyPlayer::notifyCompletedRound() {
	myCardValue = 0;
}
