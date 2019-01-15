///////////////////////////////////////
//                                   //
//	 ROYAL       Game	             //
//                                   //
// (R)Copyright: TPUS                //
// 15/01/2019  By  ABE	             //
// universalindustries@usa.com       //
///////////////////////////////////////

#include "bank.h"

//-----------------------
void Bank::init(double input, double output)
{
	this->addInput(input);
	this->addOutput(output);
	this->updateGame();
}
//-----------------------
double Bank::getInput() const
{
	return this->_input;
}
//-----------------------
double Bank::getOutput() const
{
	return this->_output;
}
//-----------------------
void Bank::addInput(double input)
{
	this->_input += input;
}
//-----------------------
void Bank::addOutput(double output)
{
	this->_output += output;
	if (this->_direction != 0) {
		this->_modifier -= 0.01;
	} else {
		this->_direction = rand() % 2 ? 1 : -1;
		this->_modifier = static_cast<double>(rand() % BANK_OSCILLATOR + 1) / 100.0;
	}
}
//-----------------------
void Bank::updateGame()
{
	double retenction = this->_input * (BANK_BALANCE - (this->_direction * this->_modifier));
	double balance = this->_input - this->_output;
	this->_isVeryHard = balance < retenction;
}
//-----------------------
bool Bank::isVeryHard() const
{
	return this->_isVeryHard;
}
