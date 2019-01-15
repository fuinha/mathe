///////////////////////////////////////
//                                   //
//	 ROYAL       Game	             //
//                                   //
// (R)Copyright: TPUS                //
// 15/01/2019  By  ABE	             //
// universalindustries@usa.com       //
///////////////////////////////////////

#ifndef BANK_H_
#define BANK_H_

#pragma once

#include <iostream>
#include <cstddef>

#define BANK_BALANCE	0.20 // 020%
#define BANK_OSCILLATOR	5	 // 005%

class Bank
{
public:
	/* Call current method in initialize with database informations */
	void init(double input, double output);
	//----------------------- Get argument to save game
	double getInput() const;
	//----------------------- Get argument to save game
	double getOutput() const;
	/* Call current method in insert credits */
	void addInput(double input);
	/* Call current method in cash out */
	void addOutput(double output);
	/* Call current method in mathe::play(...) */
	void updateGame();
	/* Call current method in mathe::play(...) */
	bool isVeryHard() const;
private:
	int _direction { 0 };
	double _modifier { 0 };
	double _input { 0 };
	double _output { 0 };
	bool _isVeryHard { false };
};

#endif /* BANK_H_ */
