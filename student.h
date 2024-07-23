#pragma once
#include "player.h"
#include <vector>
#include <array>
#include <numeric>
using namespace std;
class Student : public Player {
private:
    string name = "";
    int myCardValue = 0;
    int aceCount = 0; // A 카드의 수
    vector<Card> seenCards;
    array<int, 14> cardCount; // 카드 별 남은 수를 추적 (1-13, 인덱스 0은 사용 안 함)

public:
    Student() {
        cardCount.fill(4 * 8); // 8 덱, 각 카드 4장씩 있다고 가정
    }

    Action checkAction() override {
        // A 카드가 버스트 상태일 경우 조정
        if (myCardValue > 21 && aceCount > 0) {
            myCardValue -= 10;
            aceCount--;
        }

        // 스탠드 기준 설정
        if (myCardValue >= 17) return Action::STAND;

        // 딜러 카드 파악 (첫 번째 카드)
        int dealerValue = seenCards.front().getValue();
        dealerValue = (dealerValue > 10) ? 10 : (dealerValue == 1 && aceCount > 0) ? 11 : dealerValue;

        // 딜러 카드가 강하면 더 공격적으로 플레이
        if (dealerValue >= 7 && myCardValue < 17) return Action::HIT;

        // 안전한 카드 뽑기 여지 계산
        double safeProbability = calculateSafeProbability();

        // 안전하게 플레이할 수 있는 확률이 낮으면 스탠드
        if (safeProbability < 0.5) return Action::STAND;

        return Action::HIT;
    }

    double calculateSafeProbability() {
        int needed = 21 - myCardValue;
        needed = min(needed, 13);  // cardCount 배열의 최대 인덱스는 13이므로 needed를 13으로 제한

        int safeCards = accumulate(cardCount.begin() + 1, cardCount.begin() + needed + 1, 0);
        int remainingCards = accumulate(cardCount.begin() + 1, cardCount.end(), 0);

        return static_cast<double>(safeCards) / remainingCards;
    }


    void notifyDealerCard(Card card) override {
        seenCards.push_back(card);
        cardCount[card.getValue()]--;
        if (card.getValue() == 1) aceCount++;
    }

    void notifyOtherPlayerCard(Card card) override {
        seenCards.push_back(card);
        cardCount[card.getValue()]--;
    }

    void notifyMyCard(Card card) override {
        int cardValue = (card.getValue() > 10) ? 10 : card.getValue();
        myCardValue += (card.getValue() == 1) ? 11 : cardValue;
        if (card.getValue() == 1) aceCount++;
    }

    void notifyCardReset(int cardDeck) override {
        seenCards.clear();
        cardCount.fill(4 * cardDeck);
        myCardValue = 0;
        aceCount = 0;
    }

    void notifyCompletedRound() override {
        myCardValue = 0;
        aceCount = 0;
        seenCards.clear();
    }

    string getName() override {
        return name;
    }
};
