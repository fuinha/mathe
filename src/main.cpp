//============================================================================
// Name        : main.cpp
// Author      : abraham
// Version     :
// Copyright   : pandorabox
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "mathe.h"
#include "bank.h"

int main(int argc, char **argv) {
	Mathe mMath;
	Bank mBank;
	mBank.init(100.0, 200.0);
	mBank.addInput(100.0);
	mBank.addOutput(100.0);
	mBank.updateGame();
	std::cout << mBank.isVeryHard() << std::endl;
	std::cout << mBank.getInput() << std::endl;
	std::cout << mBank.getOutput() << std::endl;
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	return 0;
}
