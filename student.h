#pragma once
#include "player.h"
#include "constants.h"  // Card 클래스를 정의한 파일을 포함합니다
#include <vector>
#include <algorithm>

class Student : public Player {
private:
    string name = "yunhochoi";
    int myCardValue;
    std::vector<Card> deck;

    void initializeDeck() {
        deck.clear();
        // Assuming a standard deck of 52 cards
        for (int i = 1; i <= 13; ++i) { // 1 is Ace, 11 is Jack, 12 is Queen, 13 is King
            for (int j = 0; j < 4; ++j) { // 4 suits
                deck.push_back(Card(i));
            }
        }
    }

    double calculateProbabilityOfLowCard() {
        int lowCardCount = 0;
        for (const auto& card : deck) {
            if (card.getValue() <= 4) {  // Assuming card.getValue() returns int
                ++lowCardCount;
            }
        }
        return static_cast<double>(lowCardCount) / deck.size();
    }

public:
    Student() {
        initializeDeck();
        myCardValue = 0;
    }

    virtual Action checkAction() override {
        double probabilityOfLowCard = calculateProbabilityOfLowCard();
        if (myCardValue < 17 && probabilityOfLowCard >= 0.5) {
            return Action::HIT;
        }
        return Action::STAND;
    }

    virtual string getName() override {
        return "yunho";
    }

    virtual void notifyDealerCard(Card card) override {
        auto it = std::find_if(deck.begin(), deck.end(), [&card](const Card& c) { return c.getValue() == card.getValue(); });
        if (it != deck.end()) {
            deck.erase(it);
        }
    }

    virtual void notifyOtherPlayerCard(Card card) override {
        auto it = std::find_if(deck.begin(), deck.end(), [&card](const Card& c) { return c.getValue() == card.getValue(); });
        if (it != deck.end()) {
            deck.erase(it);
        }
    }

    virtual void notifyMyCard(Card card) override {
        if (card.getValue() > 10) {
            myCardValue += 10;
        } else {
            myCardValue += card.getValue();
        }
        auto it = std::find_if(deck.begin(), deck.end(), [&card](const Card& c) { return c.getValue() == card.getValue(); });
        if (it != deck.end()) {
            deck.erase(it);
        }
    }

    virtual void notifyCardReset(int cardDeck) override {
        initializeDeck();
    }

    virtual void notifyCompletedRound() override {
        myCardValue = 0;
    }
};
