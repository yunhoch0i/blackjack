#pragma once

#include <string>
using namespace std;

enum Action {
	HIT,
	STAND,
};

enum Shape {
	SPADE,
	HEART,
	DIAMOND,
	CLOVER
};

class Card {
private:
	Shape shape;
	int value;

public:
	Card() { }

	Card(Shape shape, int value) {
		this->shape = shape;
		this->value = value;
	}

	Shape getShape() {
		return shape;
	}
	int getValue() {
		return value;
	}
};