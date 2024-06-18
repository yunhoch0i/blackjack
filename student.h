#pragma once
#include "player.h"
#include "constants.h"
#include <vector>
#include <algorithm>
#include <numeric>

class Student : public Player {
private:
    string name = "yunhochoi";
    int myCardValue;
    int opponentCardValue;
    std::vector<int> deckCounts;

    void initializeDeckCounts() {
        deckCounts = std::vector<int>(13, 4); // 각 카드(1~13) 4개씩 초기화
    }

    double calculateProbability(int threshold) {
        int totalCards = std::accumulate(deckCounts.begin(), deckCounts.end(), 0);
        int favorableCards = 0;
        for (int i = 0; i < 13; ++i) {
            if ((i + 1) <= threshold) {
                favorableCards += deckCounts[i];
            }
        }
        return static_cast<double>(favorableCards) / totalCards;
    }

    bool shouldHit(int threshold) {
        double probability = calculateProbability(threshold);
        return probability >= 0.5;
    }

    bool needsToTakeRisk() {
        return myCardValue < opponentCardValue;
    }

public:
    Student() {
        myCardValue = 0;
        opponentCardValue = 0;
        initializeDeckCounts();
    }

    Action checkAction() {
        if (needsToTakeRisk()) {
            return Action::HIT;
        }
        
        if (myCardValue >= 20) {
            return Action::STAND;
        }
        if (myCardValue >= 15 && myCardValue <= 19) {
            if (shouldHit(myCardValue - 15 + 1)) {
                return Action::HIT;
            }
            return Action::STAND;
        }
        return Action::HIT;
    }

    string getName() {
        return "yunho";
    }

    void notifyDealerCard(Card card) {
        int cardValue = card.getValue();
        if (cardValue > 0 && cardValue <= 13) {
            deckCounts[cardValue - 1]--;
        }
    }

    void notifyOtherPlayerCard(Card card) {
        int cardValue = card.getValue();
        if (cardValue > 0 && cardValue <= 13) {
            deckCounts[cardValue - 1]--;
            opponentCardValue += cardValue > 10 ? 10 : cardValue;
        }
    }

    void notifyMyCard(Card card) {
        int cardValue = card.getValue();
        if (cardValue > 0 && cardValue <= 13) {
            if (cardValue > 10) myCardValue += 10;
            else myCardValue += cardValue;
            deckCounts[cardValue - 1]--;
        }
    }

    void notifyCardReset(int cardDeck) {
        myCardValue = 0;
        opponentCardValue = 0;
        initializeDeckCounts();
    }

    void notifyCompletedRound() {
        myCardValue = 0;
        opponentCardValue = 0;
        initializeDeckCounts();
    }
};

