#include <iostream>
#include "player.h"
using namespace std;
int main() {
	Dealer dealer = Dealer(100000, 8, 8);
	dealer.playGame();
	dealer.printResult();
	return 0;
}