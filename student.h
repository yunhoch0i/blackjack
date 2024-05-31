#pragma once
#include "player.h"

//아래의 코드만 수정할것.
class Student : public Player {
private:
	string name = "2024000000 홍길동";
public:
	/*
	* 어떤 행동을 할지 반환하는 매소드
	* HIT = 카드를 계속 받겠다.
	* STAND = 카드 받기를 멈추겠다.
	*/
	Action checkAction() {
		return Action::STAND;
	}
	
	/*
	* 최종 결과 출력에 사용할 이름을 반환하는 매소드
	*/
	string getName() {
		return name;
	}

	/*
	* 딜러가 받은 카드가 뭔지 알 수 있는 매소드
	*/
	void notifyDealerCard(Card card) {

	}

	/*
	* 다른 플레이어가 받은 카드가 뭔지 알 수 있는 매소드
	*/
	void notifyOtherPlayerCard(Card card) {

	}

	/*
	* 내가 받은 카드가 뭔지 알 수 있는 매소드
	*/
	void notifyMyCard(Card card) {

	}

	/*
	* 딜러가 사용하는 카드 더미를 새로 만들어낼때
	* 몇개의 플레잉 카드로 만들어졌는지 알려주는 매소드
	*/
	void notifyCardReset(int cardDeck) {

	}

	/*
	* 한번의 라운드가 끝났음을 알려주는 매소드
	*/
	void notifyCompletedRound() {
		
	}
};