///////////////////////////////////////
//                                   //
//	 ROYAL       Game            //
//                                   //
// (R)Copyright: TPUS                //
// 19/09/2012  By  FUINHA            //
// universalindustries@usa.com       //
///////////////////////////////////////

#ifndef MATHE_H_
#define MATHE_H_

#pragma once

#include <random>
#include <cstddef>
#include <ctime>
#include <algorithm>

#include "bank.h"

// #include "defines.h"
#define MINIMUM_CREDITS_INSERTED_TO_BONUS 50.00    // + R$50,00
//commnet for use rand
#define USERAND

class Mathe
{

private:
    bool trava;
    bool ctr99;
    bool caraca;

    // The 0th values of the arrays are not used
    int tabela[ 16 ];
    int fech[ 4 ];

    int randomKey; // Static111

    bool saiuac;
    double acumulado, acumefect, acummax;

    int aposta;
    float porcento;

    typedef std::mt19937 rand_t;
    rand_t _randomizer;
    double _totalCreditsInserted;
    //------------------------------------------------------------------
    template <class RandomAccessIterator>
    inline void shuffleVector(RandomAccessIterator first, RandomAccessIterator last)
    {
        auto dist = [this](const ptrdiff_t n) { return std::uniform_int_distribution<ptrdiff_t>(0, n - 1)(_randomizer); };
        std::random_shuffle(first, last, dist);
    }

    void alea1( int size, int arg );

    void faixa( int arg1, int arg2, int arg3, int arg4, int arg5, int arg6,
                int arg7, int arg8, int arg9, int arg10, int arg11, int arg12 );

    void bingo10();

    void setTabela( int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                    int v8, int v9, int v10, int v11, int v12, int v13,
                    int v14, int v15 );

    void initTabela();

    int randInt(int low, int high);
    void initRand();

public:

    Mathe( bool trava_ = false, bool ctr99_ = false );

    void setTotalCreditsInserted(double totalCreditsInserted);
    double getMatchCredits(double currentCredits);
    bool isMatchCredits(double currentCredits);

    // result is an array of 15 elements which represents the reels,
    // up to down, left to right.
    void play(const int aposta_, const int linhas_, const bool lock_, const int gamePosition, const int favPosition, int *result , const float porcent, double currentCredits, Bank& bank);
    int  testLine(int lineTest,int premiunTest,int numberSlotsTest);
    void changeSlot(int LinePosition,int premiunToChanged,int premiunSlots);
    int testPremiun(int slot1,int slot2,int slot3,int slot4,int slot5,int premiunToVerify,int numberSlotsTest);
};

// Bonus with the strawberries
class Bonus11
{
    int multiplier;
    int berries[ 12 ];
    bool firstPick;
    bool wormFound;
public:

    Bonus11( int bonusMultiplier );

    class AlreadyPicked {};
    class WormWasFound {};
    class BadNumber {};

    // The num value is 0..11, the result is a value of credits won,
    // or zero when the worm is found.No more calls must be made after
    // the worm is found. num values may not repeat.
    int chooseNextStrawberry( int num ) noexcept(false);
};
int get_randi();

// Plays bonus with the cauldrons. Picks the num-th (zero-based) cauldron
// and returns its value. In case it is zero, the third bonus is to be played.
// The 'others' array is filled with the values for other cauldrons.
// Perce seems to chose one of percentages, and can be setup up from 0 to 4.
// It's one by default.
int bonus22( int multiplier,  int others[ 4 ], int perce = 1 );

class UnknownPerces {};

// Plays bonus with the pumpkins. In game, it is only played after
// the bonus2 has returned 0 (pumpkin). This bonus is similar to the
// bonus2, except that there is no pumpkin to win and the prizes are larger.
// Note that there is an error in the original program which leads to
// unknown results with perce > 1.

int bonus33( int multiplier,  int others[ 4 ], int perce = 1 )noexcept(false);

#endif /* MATHE_H_ */
