#pragma once
#include "player.h"

//�Ʒ��� �ڵ常 �����Ұ�.
class Student : public Player {
private:
	string name = "2024000000 ȫ�浿";
public:
	/*
	* � �ൿ�� ���� ��ȯ�ϴ� �żҵ�
	* HIT = ī�带 ��� �ްڴ�.
	* STAND = ī�� �ޱ⸦ ���߰ڴ�.
	*/
	Action checkAction() {
		return Action::STAND;
	}
	
	/*
	* ���� ��� ��¿� ����� �̸��� ��ȯ�ϴ� �żҵ�
	*/
	string getName() {
		return name;
	}

	/*
	* ������ ���� ī�尡 ���� �� �� �ִ� �żҵ�
	*/
	void notifyDealerCard(Card card) {

	}

	/*
	* �ٸ� �÷��̾ ���� ī�尡 ���� �� �� �ִ� �żҵ�
	*/
	void notifyOtherPlayerCard(Card card) {

	}

	/*
	* ���� ���� ī�尡 ���� �� �� �ִ� �żҵ�
	*/
	void notifyMyCard(Card card) {

	}

	/*
	* ������ ����ϴ� ī�� ���̸� ���� ������
	* ��� �÷��� ī��� ����������� �˷��ִ� �żҵ�
	*/
	void notifyCardReset(int cardDeck) {

	}

	/*
	* �ѹ��� ���尡 �������� �˷��ִ� �żҵ�
	*/
	void notifyCompletedRound() {
		
	}
};