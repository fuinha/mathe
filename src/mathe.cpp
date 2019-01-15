///////////////////////////////////////
//                                   //
//	 ROYAL       Game            //
//                                   //
// (R)Copyright: TPUS                //
// 19/09/2012  By  FUINHA            //
// universalindustries@usa.com       //
///////////////////////////////////////

#include "mathe.h"

#include <math.h>
#include <stdlib.h>
// #include <QtCore>
#include <stdio.h>
//#include <QGlobal.h>

#ifndef USERAND
#include <QTime>
#endif

#include <iostream>
#include <string>

//INITH CLASS
Mathe::Mathe(bool trava_, bool ctr99_)
    : trava(trava_)
    , ctr99(ctr99_)
    , caraca(false) //never more
    , randomKey(get_randi() % 3199 + 1)
    , saiuac(false) //LOCK
    , acumulado(1007.1345)
    , acumefect(7.1345)
    , acummax(4000.0) // 4000 is not confirmed, it's in binary in dbf
    , aposta(0)
    , porcento(0)
    , _totalCreditsInserted(0)
{
    initRand();//generate seed
    initTabela();//TESTE TO VALID GAME IN TABLE
}
//------------------------------------------------------------------

int Mathe::randInt(int low, int high)
{
    // Random number between low and high
    return rand() % ((high + 1) - low) + low;
}

void Mathe::initRand()
{
    // Create seed for the random
    // That is needed only once on application startup

#ifndef USERAND
    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));
#else
    srand((unsigned long long int) time(NULL));
#endif
}
//------------------------------------------------------------------
//sort the numbers of 3x5 slots
void Mathe::alea1(int size, int arg)
{
    int s1, s2, s3;
    do
    {
        s1 = get_randi() % 33999 + 1;
        s2 = get_randi() % 33999 + 1;
        s3 = get_randi() % 33999 + 1;
    } while(s1 == s2 || s1 == s3 || s2 == s3);
    double seed1 = double(s1), seed2 = double(s2), seed3 = double(s3);
    double local2;
    for(int x = 1; x <= size; ++x)
    {
        seed1 = 171.0 * double(int(seed1) % 177) - 2.0 * (seed1 / 177.0);
        seed2 = 172.0 * double(int(seed2) % 176) - 35.0 * (seed2 / 176.0);
        seed3 = 170.0 * double(int(seed3) % 178) - 63.0 * (seed3 / 178.0);
        if (seed1 < 0)
            seed1 += 30269.0;
        if (seed2 < 0)
            seed2 += 30307.0;
        if (seed3 < 0)
            seed3 += 30323.0;
        local2 = seed1 / 30269.0 + seed2 / 30307.0 + seed3 / 30323.0;
        fech[ x ] = 1 + int(arg * (local2 - floor(local2)));
        //printf("%d ", fech[ x ]);
    }
    //printf("\n");
}
//------------------------------------------------------------------
//test if jackpot
void Mathe::faixa(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6,
                   int arg7, int arg8, int arg9, int arg10, int arg11,
                   int arg12)
{
    if (trava) // win
    {
        if(saiuac && caraca)
        {
            //win acum
            switch(get_randi() % 5)
            {
            case 0:
                // - - - - -
                // x x x x x
                // - - - - -
                setTabela(9, 7, 3, 8, 7, 6, 2, 7, 9, 8, 7, 6, 9, 7, 3);
                break;
            case 1:
                // x x x x x
                // - - - - -
                // - - - - -
                setTabela(7, 5, 2, 7, 10, 3, 7, 10, 2, 7, 10, 6, 7, 5, 9);
                break;
            case 2:
                // - - - - -
                // - - - - -
                // x x x x x
                setTabela(3, 2, 7, 1, 6, 7, 6, 1, 7, 4, 6, 7, 8, 2, 7);
                break;
            case 3:
                // x - - - x
                // - x - x -
                // - - x - -
                setTabela(7, 6, 3, 2, 7, 3, 3, 5, 7, 8, 7, 1, 7, 4, 1);
                break;
            case 4:
                // - - x - -
                // - x - x -
                // x - - - x
                setTabela(2, 5, 7, 1, 7, 3, 7, 6, 2, 8, 7, 6, 4, 1, 7);
                break;
            }
        }
        else
            if (acumefect >= acummax && !saiuac && aposta >= 2 && arg1 + arg2 == 15)
            {
                if (get_randi() % 3199 + 1 == randomKey)
                {
                    // Use one of five key tabelas

                    switch(get_randi() % 5)
                    {
                    case 0:
                        // - - - - -
                        // x x x x x
                        // - - - - -
                        setTabela(9, 7, 3, 8, 7, 6, 2, 7, 9, 8, 7, 6, 9, 7, 3);
                        break;
                    case 1:
                        // - - - - -
                        // x x x x x
                        // - - - - -
                        setTabela(1, 5, 7, 1, 10, 7, 2, 10, 7, 3, 10, 7, 2, 5, 9);
                        break;
                    case 2:
                        // - - - - -
                        // x x x x x
                        // - - - - -
                        setTabela(7, 2, 10, 7, 6, 9, 7, 1, 9, 7, 6, 9, 8, 2, 10);
                        break;
                    case 3:
                        // - - - - -
                        // x x x x x
                        // - - - - -
                        setTabela(9, 6, 3, 7, 6, 3, 7, 5, 2, 7, 4, 1, 7, 4, 1);
                        break;
                    case 4:
                        // - - - - -
                        // x x x x x
                        // - - - - -
                        setTabela(2, 5, 8, 1, 5, 7, 6, 6, 7, 8, 4, 7, 4, 1, 7);
                        break;
                    }
                }
                else
                    if (fech[ arg1 ] < arg3)
                    {
                        if (acumefect < acummax && !saiuac && aposta >= 2)
                        {
                            if (arg1 + arg2 == 13 || arg1 + arg2 == 14 || arg1 + arg2 == 15)
                                tabela[ arg1 + arg2 ] = get_randi() % 6 + 1;
                            else
                                tabela[ arg1 + arg2 ] = 7;
                        }
                        else
                            tabela[ arg1 + arg2 ] = 7;
                    }
                    else
                        if (fech[ arg1 ] < arg4)
                            tabela[ arg1 + arg2 ] = 10;
                        else
                            if (fech[ arg1 ] < arg5)
                                tabela[ arg1 + arg2 ] = 1;
                            else
                                if (fech[ arg1 ] < arg6)
                                    tabela[ arg1 + arg2 ] = 2;
                                else
                                    if (fech[ arg1 ] < arg7)
                                        tabela[ arg1 + arg2 ] = 3;
                                    else
                                        if (fech[ arg1 ] < arg8)
                                            tabela[ arg1 + arg2 ] = 6;
                                        else
                                            if (fech[ arg1 ] < arg9)
                                                tabela[ arg1 + arg2 ] = 4;
                                            else
                                                if (fech[ arg1 ] < arg10)
                                                    tabela[ arg1 + arg2 ] = 9;
                                                else
                                                    if (fech[ arg1 ] < arg11)
                                                        tabela[ arg1 + arg2 ] = 8;
                                                    else
                                                        if (fech[ arg1 ] < arg12)
                                                            tabela[ arg1 + arg2 ] = 5;
            }
            else
                if (fech[ arg1 ] < arg3)
                {
                    if (acumefect < acummax && !saiuac && aposta >= 2)//not acum efet
                    {
                        if (arg1 + arg2 == 13 || arg1 + arg2 == 14 || arg1 + arg2 == 15)
                            tabela[ arg1 + arg2 ] = get_randi() % 6 + 1;
                        else
                            tabela[ arg1 + arg2 ]= 7;
                    }
                    else
                        tabela[ arg1 + arg2 ]= 7;
                }
                else
                    if (fech[ arg1 ] < arg4)
                        tabela[ arg1 + arg2 ] = 10;
                    else
                        if (fech[ arg1 ] < arg5)
                            tabela[ arg1 + arg2 ] = 1;
                        else
                            if (fech[ arg1 ] < arg6)
                                tabela[ arg1 + arg2 ] = 2;
                            else
                                if (fech[ arg1 ] < arg7)
                                    tabela[ arg1 + arg2 ] = 3;
                                else
                                    if (fech[ arg1 ] < arg8)
                                        tabela[ arg1 + arg2 ] = 6;
                                    else
                                        if (fech[ arg1 ] < arg9)
                                            tabela[ arg1 + arg2 ] = 4;
                                        else
                                            if (fech[ arg1 ] < arg10)
                                                tabela[ arg1 + arg2 ] = 9;
                                            else
                                                if (fech[ arg1 ] < arg11)
                                                    tabela[ arg1 + arg2 ] = 8;
                                                else
                                                    if (fech[ arg1 ] < arg12)
                                                        tabela[ arg1 + arg2 ] = 5;
    }
    else //  trava WIN JACKPOT
        if (acumulado >= acummax &&  !saiuac && aposta >= 2 && arg1 + arg2 == 15)
        {
            if (get_randi() % 3199 + 1 == randomKey)
            {
                // Use one of five key tabelas

                switch(get_randi() % 5)
                {
                case 0:
                    setTabela(9, 7, 3, 8, 7, 6, 2, 7, 9, 8, 7, 6, 9, 7, 3);
                    break;
                case 1:
                    setTabela(1, 5, 7, 1, 10, 7, 2, 10, 7, 3, 10, 7, 2, 5, 9);
                    break;
                case 2:
                    setTabela(7, 2, 10, 7, 6, 9, 7, 1, 9, 7, 6, 9, 8, 2, 10);
                    break;
                case 3:
                    setTabela(9, 6, 3, 7, 6, 3, 7, 5, 2, 7, 4, 1, 7, 4, 1);
                    break;
                case 4:
                    setTabela(2, 5, 8, 1, 5, 7, 6, 6, 7, 8, 4, 7, 4, 1, 7);
                    break;
                }
            }
            else //NOT JACKPOT
                if (fech[ arg1 ] < arg3)
                {
                    if (acumulado < acummax && !saiuac && aposta >= 2)
                    {
                        if (arg1 + arg2 == 13 || arg1 + arg2 == 14 || arg1 + arg2 == 15)
                            tabela[ arg1 + arg2 ] = get_randi() % 6 + 1;
                        else
                            tabela[ arg1 + arg2 ] = 7;
                    }
                    else
                        tabela[ arg1 + arg2 ] = 7;
                }
                else
                    if (fech[ arg1 ] < arg4)
                        tabela[ arg1 + arg2 ] = 10;
                    else
                        if (fech[ arg1 ] < arg5)
                            tabela[ arg1 + arg2 ] = 1;
                        else
                            if (fech[ arg1 ] < arg6)
                                tabela[ arg1 + arg2 ] = 2;
                            else
                                if (fech[ arg1 ] < arg7)
                                    tabela[ arg1 + arg2 ] = 3;
                                else
                                    if (fech[ arg1 ] < arg8)
                                        tabela[ arg1 + arg2 ] = 6;
                                    else
                                        if (fech[ arg1 ] < arg9)
                                            tabela[ arg1 + arg2 ] = 4;
                                        else
                                            if (fech[ arg1 ] < arg10)
                                                tabela[ arg1 + arg2 ] = 9;
                                            else
                                                if (fech[ arg1 ] < arg11)
                                                    tabela[ arg1 + arg2 ] = 8;
                                                else
                                                    if (fech[ arg1 ] < arg12)
                                                        tabela[ arg1 + arg2 ] = 5;
        }
        else
            if (fech[ arg1 ] < arg3)
            {
                if (acumulado < acummax && !saiuac && aposta >= 2) //not
                {
                    if (arg1 + arg2 == 13 || arg1 + arg2 == 14 || arg1 + arg2 == 15)
                        tabela[ arg1 + arg2 ] = get_randi() % 6 + 1;
                    else
                        tabela[ arg1 + arg2 ] = 7;
                }
                else
                    tabela[ arg1 + arg2 ] = 7;
            }
            else
                if (fech[ arg1 ] < arg4)
                    tabela[ arg1 + arg2 ] = 10;
                else
                    if (fech[ arg1 ] < arg5)
                        tabela[ arg1 + arg2 ] = 1;
                    else
                        if (fech[ arg1 ] < arg6)
                            tabela[ arg1 + arg2 ] = 2;
                        else
                            if (fech[ arg1 ] < arg7)
                                tabela[ arg1 + arg2 ] = 3;
                            else
                                if (fech[ arg1 ] < arg8)
                                    tabela[ arg1 + arg2 ] = 6;
                                else
                                    if (fech[ arg1 ] < arg9)
                                        tabela[ arg1 + arg2 ] = 4;
                                    else
                                        if (fech[ arg1 ] < arg10)
                                            tabela[ arg1 + arg2 ] = 9;
                                        else
                                            if (fech[ arg1 ] < arg11)
                                                tabela[ arg1 + arg2 ] = 8;
                                            else
                                                if (fech[ arg1 ] < arg12)
                                                    tabela[ arg1 + arg2 ] = 5;
}
//------------------------------------------------------------------
//INIT PLAY  JACKPOT LOCKED
void Mathe::bingo10()
{

    for(int i = 1; i <= 3; ++i)
    {
        alea1(3, 84);

        if (ctr99)
            faixa(i, 0, 12, 29, 43, 46, 52, 57, 74, 77, 80, 85);
        else
            faixa(i, 0, 2, 9, 18, 29, 42, 57, 74, 77, 80, 85);
    }

    for(int i = 1; i <= 3; ++i)
    {
        alea1(3, 85);

        if (ctr99)
            faixa(i, 3, 13, 30, 39, 42, 47, 58, 75, 78, 81, 86);
        else
            faixa(i, 3, 3, 10, 19, 30, 43, 58, 75, 78, 81, 86);
    }

    for(int i = 1; i <= 3; ++i)
    {
        alea1(3, 86);

        if (ctr99)
            faixa(i, 6, 14, 31, 40, 51, 64, 69, 76, 79, 82, 87);
        else
            faixa(i, 6, 4, 11, 20, 31, 44, 59, 76, 79, 82, 87);
    }

    for(int i = 1; i <= 3; ++i)
    {
        alea1(3, 85);

        if (ctr99)
            faixa(i, 9, 13, 30, 39, 40, 53, 58, 75, 78, 81, 86);
        else
            faixa(i, 9, 3, 10, 19, 30, 43, 58, 75, 78, 81, 86);
    }

    for(int i = 1; i <= 3; ++i)
    {
        alea1(3, 84);

        if (ctr99)
            faixa(i, 12, 12, 29, 38, 49, 52, 57, 74, 77, 80, 85);
        else
            faixa(i, 12, 2, 9, 18, 29, 42, 57, 74, 77, 80, 85);
    }
}
//------------------------------------------------------------------
void Mathe::setTabela(int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                       int v8, int v9, int v10, int v11, int v12, int v13,
                       int v14, int v15)
{
    tabela[ 1 ] = v1;
    tabela[ 2 ] = v2;
    tabela[ 3 ] = v3;
    tabela[ 4 ] = v4;
    tabela[ 5 ] = v5;
    tabela[ 6 ] = v6;
    tabela[ 7 ] = v7;
    tabela[ 8 ] = v8;
    tabela[ 9 ] = v9;
    tabela[ 10 ] = v10;
    tabela[ 11 ] = v11;
    tabela[ 12 ] = v12;
    tabela[ 13 ] = v13;
    tabela[ 14 ] = v14;
    tabela[ 15 ] = v15;
}
//------------------------------------------------------------------
//TEST FOR VALID NUMBER
void Mathe::initTabela()
{
    for(int x = 1; x <= 15; ++x)
        tabela[ x ] = x < 11 ? x : x - 10;
    //first reel
    /*
    /// firt reel
    xca[1][1]= result[0];
    xca[2][1]= result[1];
    xca[3][1]= result[2];
    //second reel
    xca[1][2]= result[3];
    xca[2][2]= result[4];
    xca[3][2]= result[5];
    //thirty reel
    xca[1][3]= result[6];
    xca[2][3]= result[7];
    xca[3][3]= result[8];
    //fourty reel
    xca[1][4]= result[9];
    xca[2][4]= result[10];
    xca[3][4]= result[11];
    //fivy reel
    xca[1][5]= result[12];
    xca[2][5]= result[13];
    xca[3][5]= result[14];
    //*/

    //*/
}
////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// WARNING!
////////////////////////////////////////////////////////////
// to header
// @TODO
//#define MINIMUM_CREDITS_INSERTED_TO_BONUS 50.00    // + R$50,00
/*
typedef std::mt19937 rand_t;
rand_t _randomizer;
double _totalCreditsInserted { 0 };
//------------------------------------------------------------------
template <class RandomAccessIterator>
inline void shuffleVector(RandomAccessIterator first, RandomAccessIterator last)
{
    auto dist = [this](const ptrdiff_t n) { return std::uniform_int_distribution<ptrdiff_t>(0, n - 1)(_randomizer); };
    std::random_shuffle(first, last, dist);
}
*/
////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// WARNING!
////////////////////////////////////////////////////////////
//------------------------------------------------------------------
void Mathe::setTotalCreditsInserted(double totalCreditsInserted)
{
    _totalCreditsInserted += totalCreditsInserted;
}
//------------------------------------------------------------------
// Unused
double Mathe::getMatchCredits(double currentCredits)
{
    const double FACTOR_D = 0.50;    // 50%
    const int FACTOR_I = static_cast<int>(0.50 * 200); // 50%
    const int FACTOR_RTP_I = 75;     // 75%
    double res = 0.0;
    if (currentCredits <= (_totalCreditsInserted * FACTOR_D) + (_totalCreditsInserted * (static_cast<double>(get_randi() % FACTOR_I) / 100.0)))
    {
        res = _totalCreditsInserted * (static_cast<double>(get_randi() % FACTOR_RTP_I) / 100.0);
        _totalCreditsInserted = 0.0;
    }
    return res;
}
//------------------------------------------------------------------
bool Mathe::isMatchCredits(double currentCredits)
{
    const double FACTOR_D = 0.50;    // 50%
    const int FACTOR_I = static_cast<int>(0.50 * 200); // 50%
    if (currentCredits <= (_totalCreditsInserted * FACTOR_D) + (_totalCreditsInserted * (static_cast<double>(get_randi() % FACTOR_I) / 100.0)) &&
            _totalCreditsInserted >= MINIMUM_CREDITS_INSERTED_TO_BONUS)
    {
        _totalCreditsInserted = 0.0;
        return true;
    }
    return false;
}
//------------------------------------------------------------------
void Mathe::play(const int aposta_, const int linhas_,const  bool lock_, const int gamePosition,const int favPosition, int * result,const float porcent, double currentCredits) {
	/* Launch Bonus */
	if (isMatchCredits(currentCredits))
	{
		int sym = 4; // No init necessary, just a safeguard ghost
		int count = 0;
		int index = get_randi() % 4;
		if (index == 0)
		{
			sym = 0; // calderon
			count = 3;
		}
		else
		if (index == 1)
		{
			sym = 9; // kat
			count = 3;
		}
		else
		if (index == 2)
		{
			sym = 2; // witch
			count = 4;
		}
		if (count) // Go to win
		{
			int linesToWin = (get_randi() % 20) + 1;	// sort 1 to 20 lines
			changeSlot(linesToWin,sym, count);			// lines premiun n slots
		}
	    for(int x = 0; x < 15; ++x)
	    {
	        result[ x ] = tabela[x + 1]; // return the injected result
	    }
		return;
	}
	///////////////////////////////////////////////
    porcento = porcent;
    aposta = aposta_;
    saiuac = false;
    trava = false;
    caraca = false;
    if((lock_== 0) && (gamePosition >= favPosition) && (aposta >=2) && (linhas_>=20))
    {
        //unlock acum
        saiuac = true;
        trava = true;
        caraca = true;
    }
    // bingo10();//PLAY
    // doSpin();
    // See if we need to have easy or difficult game
    // currentDev = (aposta*linhas_) / porcento;
    bool easyGame = false;
    bool normalGame = false;
    bool hardGame = false;
    bool skipThisGame = false;
    int porcento = static_cast<int>(porcent);
    //in this time retention < 50
    if ((aposta > 15 || (porcento < 1)) /*&& = (AND) (porcent > 1)*/)
    {
        hardGame = true;
    }
    // else
    // if ((porcento < 1)) // || = OR
    // {
    //     hardGame = true;
    // }
    ///////////////
    /* my insert */
    ///////////////
    else
    if (!(get_randi() % 150)) // !!!!! 150
    {
        normalGame = true;
    }
    else
    {
        easyGame = true;
    }
    // Try making a spin until we get what we like from it
    while (!false)
    {
        bingo10();
        //tabelaToScreenshot();
        if (easyGame) // Easy game
        {
            int sym = 4; // No init necessary, just a safeguard ghost
            int count = 0;
            //int seedss;
            //seedss = get_randi() % 200;
            //seedss = get_randi() % 150;
            //seedss = get_randi() % 150;
            if (!(get_randi() % 200))//200
            {
                sym = 0;//devil
                count = 3;
            }
            else
            if (!(get_randi() % 150))//150
            {
                sym = 9;// kat
                count = 3;
            }
            else
            if (!(get_randi() % 150))//150
            {
                sym = 2;//with
                count = 4;
            }
            if (count)//GO TO WIN
            {
                int linesToWin = (get_randi() % 20) + 1;// sort 1 to 20 lines
                changeSlot(linesToWin,sym,count);//lines premiun n slots
            }
        }
        // winlines = analyzer.analyze(&screenshot->front(), getLines(), getBet());
        // hard game
        else
        if (hardGame)
        {
            for(int ii = 0; ii != linhas_;++ii)
            {
                // Understand what kind of combination this is
                if(testLine(ii,8,3))//if have tree devils resort
                {
                    skipThisGame = true;
                    break;
                }
                if(testLine(ii,9,4))//if have four kat resort
                {
                    skipThisGame = true;
                    break;
                }
                if(testLine(ii,5,5))//if have five moonwich resort
                {
                    skipThisGame = true;
                    break;
                }
                if(testLine(ii,10,5))//if have five cald resort
                {
                    skipThisGame = true;
                    break;
                }
            }
        }
        else
        if (normalGame)
        {
            /////////////////////////////////////////////
            // Create tails.
            // 0=caldeirao bonus
            // 1=espantalho      premio menor valor
            // 2=witch bonus
            // 3=dracula
            // 4=fantasma
            // 5=bruxa
            // 6=monster
            // 7=abobora
            // 8=demo
            // 9=magic KAT    premio maior valor
            std::vector<int> l_strip = {
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				3, 3, 3, 3, 3, 3, 3, 3,
				4, 4, 4, 4, 4, 4, 4,
				5, 5, 5, 5, 5, 5, 5,
				6, 6, 6, 6, 6,
				7, 7, 7, 7, 7,
				8, 8,
				9, 9,
				2,
				0
			};
			std::vector<int> c_strip = {
				1, 1, 1,
				3, 3, 3,
				4, 4, 4,
				5, 5, 5,
				6, 6, 6,
				7, 7, 7,
				8, 8, 8,
				9, 9,
				2, 2,
				0
			};
			std::vector<int> r_strip = {
				1, 1, 1, 1, 1, 1, 1,
				3, 3, 3, 3, 3, 3,
				4, 4, 4, 4, 4, 4,
				5, 5, 5, 5, 5, 5, 5,
				6, 6, 6,
				7, 7, 7, 7, 7,
				8, 8, 8,
				9, 9,
				2, 2,
				0
			};
            // //first reel
			shuffleVector(l_strip.begin(), l_strip.end());
			result[0] = l_strip[static_cast<std::size_t>(get_randi()) % l_strip.size()];
			result[5] = l_strip[static_cast<std::size_t>(get_randi()) % l_strip.size()];
			result[10] = l_strip[static_cast<std::size_t>(get_randi()) % l_strip.size()];
			// //second reel
			shuffleVector(c_strip.begin(), c_strip.end());
			result[1] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			result[6] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			result[11] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			// //thirt reel
			shuffleVector(c_strip.begin(), c_strip.end());
			result[2] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			result[7] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			result[12] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			// //fourth reel
			shuffleVector(c_strip.begin(), c_strip.end());
			result[3] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			result[8] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			result[13] = c_strip[static_cast<std::size_t>(get_randi()) % c_strip.size()];
			// //fivy reel
			shuffleVector(r_strip.begin(), r_strip.end());
			result[4] = r_strip[static_cast<std::size_t>(get_randi()) % r_strip.size()];
			result[9] = r_strip[static_cast<std::size_t>(get_randi()) % r_strip.size()];
			result[14] = r_strip[static_cast<std::size_t>(get_randi()) % r_strip.size()];
        }
        if (skipThisGame)
        {
            continue;
        }
        else
        {
            break;//end sort
        }
    }
	// Calculate total win and bonus multipliers
	// return win;
	// end for sort
    for(int x = 0; x < 15; ++x)
    {
        result[ x ] = tabela[x + 1];//RETURN IN RESULT
    }
    skipThisGame= 0;
    /*
    /// firt reel
    xca[1][1]= result[0];
    xca[2][1]= result[1];
    xca[3][1]= result[2];
    //second reel
    xca[1][2]= result[3];
    xca[2][2]= result[4];
    xca[3][2]= result[5];
    //thirty reel
    xca[1][3]= result[6];
    xca[2][3]= result[7];
    xca[3][3]= result[8];
    //fourty reel
    xca[1][4]= result[9];
    xca[2][4]= result[10];
    xca[3][4]= result[11];
    //fivy reel
    xca[1][5]= result[12];
    xca[2][5]= result[13];
    xca[3][5]= result[14];
    //*/
}
//------------------------------------------------------------------
//-----------------------------------------------------------------
void Mathe::changeSlot(int LinePosition,int premiunToChanged,int premiunSlots)
{
    //int premiunSlots,number of total;
    //premiun to change = new value
    switch(LinePosition)
    {
    case 1:
        if(premiunSlots==5)
        {
            tabela[2] = premiunToChanged; tabela[5] = premiunToChanged;tabela[8] = premiunToChanged;tabela[11] = premiunToChanged;tabela[14] = premiunToChanged;

        }
        else if(premiunSlots==4)
        {
            tabela[2] = premiunToChanged; tabela[5] = premiunToChanged;tabela[8] = premiunToChanged;tabela[11] = premiunToChanged;

        }
        else if(premiunSlots==3)
        {
            tabela[2] = premiunToChanged; tabela[5] = premiunToChanged;tabela[8] = premiunToChanged;
        }
        break;
    case 2:
        if(premiunSlots==5)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged;tabela[7] = premiunToChanged;tabela[10] = premiunToChanged;tabela[13] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged;tabela[7] = premiunToChanged;tabela[10] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged;tabela[7] = premiunToChanged;
        }
        break;
    case 3:
        if(premiunSlots==5)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged;tabela[9] = premiunToChanged;tabela[12] = premiunToChanged;tabela[15] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged;tabela[9] = premiunToChanged;tabela[12] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged;tabela[9] = premiunToChanged;
        }
        break;
    case 4:
        if(premiunSlots==5)
        {
            tabela[1] = premiunToChanged; tabela[5] = premiunToChanged; tabela[9] = premiunToChanged; tabela[11] = premiunToChanged; tabela[13] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[1] = premiunToChanged; tabela[5] = premiunToChanged; tabela[9] = premiunToChanged; tabela[11] = premiunToChanged;
        }
        else if(premiunSlots==3)

        {
            tabela[1] = premiunToChanged; tabela[5] = premiunToChanged; tabela[9] = premiunToChanged;
        }
        break;
    case 5:
        if(premiunSlots==5)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[7] = premiunToChanged; tabela[11] = premiunToChanged; tabela[15] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[7] = premiunToChanged; tabela[11] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[7] = premiunToChanged;
        }
        break;
    case 6:
        if(premiunSlots==5)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[8] = premiunToChanged; tabela[12] = premiunToChanged; tabela[15] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[8] = premiunToChanged; tabela[12] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[8] = premiunToChanged;
        }
        break;
    case 7:
        if(premiunSlots==5)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[8] = premiunToChanged; tabela[10] = premiunToChanged; tabela[13] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[8] = premiunToChanged; tabela[10] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[8] = premiunToChanged;
        }
        break;
    case 8:
        if(premiunSlots==5)
        {
            tabela[2] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged; tabela[14] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[2] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[2] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged;
        }
        break;
    case 9:
        if(premiunSlots==5)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged; tabela[14] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged;
        }
        break;
    case 10:
        if(premiunSlots==5)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[8] = premiunToChanged; tabela[12] = premiunToChanged; tabela[14] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[8] = premiunToChanged; tabela[12] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[8] = premiunToChanged;
        }
        break;
    case 11:
        if(premiunSlots==5)
        {
            tabela[2] = premiunToChanged; tabela[5] = premiunToChanged; tabela[8] = premiunToChanged; tabela[10] = premiunToChanged; tabela[14] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[2] = premiunToChanged; tabela[5] = premiunToChanged; tabela[8] = premiunToChanged; tabela[10] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[2] = premiunToChanged; tabela[5] = premiunToChanged; tabela[8] = premiunToChanged;
        }
        break;
    case 12:
        if(premiunSlots==5)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged; tabela[13] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged;

        }
        else if(premiunSlots==3)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[7] = premiunToChanged;
        }
        break;
    case 13:
        if(premiunSlots==5)
        {
            tabela[1] = premiunToChanged; tabela[5] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged; tabela[15] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[1] = premiunToChanged; tabela[5] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged;

        }
        else if(premiunSlots==3)
        {
            tabela[1] = premiunToChanged; tabela[5] = premiunToChanged; tabela[9] = premiunToChanged;
        }
        break;
    case 14:
        if(premiunSlots==5)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[11] = premiunToChanged; tabela[15] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[11] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged;
        }
        break;
    case 15:
        if(premiunSlots==5)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[11] = premiunToChanged; tabela[13] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[11] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged;
        }
        break;
    case 16:
        if(premiunSlots==5)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged; tabela[14] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[1] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged;        }
        break;
    case 17:
        if(premiunSlots==5)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged; tabela[14] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[3] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged;
        }
        break;
    case 18:
        if(premiunSlots==5)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged; tabela[13] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged; tabela[10] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[2] = premiunToChanged; tabela[4] = premiunToChanged; tabela[7] = premiunToChanged;
        }
        break;
    case 19:
        if(premiunSlots==5)
        {
            tabela[2] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged; tabela[15] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[2] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged; tabela[12] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[2] = premiunToChanged; tabela[6] = premiunToChanged; tabela[9] = premiunToChanged;
        }
        break;
    case 20:
        if(premiunSlots==5)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[8] = premiunToChanged; tabela[11] = premiunToChanged; tabela[13] = premiunToChanged;
        }
        else if(premiunSlots==4)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[8] = premiunToChanged; tabela[11] = premiunToChanged;
        }
        else if(premiunSlots==3)
        {
            tabela[3] = premiunToChanged; tabela[5] = premiunToChanged; tabela[8] = premiunToChanged;
        }
        break;
    case 21:
        if(premiunSlots==3)
        {
            tabela[1] = premiunToChanged; tabela[2] = premiunToChanged; tabela[3] = premiunToChanged;
        }
        break;
    case 22:
        if(premiunSlots==3)
        {
            tabela[4] = premiunToChanged; tabela[5] = premiunToChanged; tabela[6] = premiunToChanged;
        }
        break;
    case 23:
        if(premiunSlots==3)
        {
            tabela[7] = premiunToChanged; tabela[8] = premiunToChanged; tabela[9] = premiunToChanged;
        }
        break;
    case 24:
        if(premiunSlots==3)
        {
            tabela[10] = premiunToChanged; tabela[11] = premiunToChanged; tabela[12] = premiunToChanged;
        }
        break;
    case 25:
        if(premiunSlots==3)
        {
            tabela[13] = premiunToChanged; tabela[14] = premiunToChanged; tabela[15] = premiunToChanged;
        }
        break;
    }
}
//------------------------------------------------------------------------------
int Mathe::testLine(int lineTest, int premiunTest, int numberSlotsTest)
{
    int returnos = 0;
    //BlockPremium(0,30,4,DeuBonus);//change caldeirao if < 30 Null chances to 4 premiun=ghost
    //int premiunChanged,testeNull;
    //testeNull = 30;//chances pay zero
    //premiunChanged = 4;//chnge to ghost
    switch(lineTest)
    {
    case 1:
        if((testPremiun(tabela[2],tabela[5],tabela[8],tabela[11],tabela[14],premiunTest , numberSlotsTest)) )
        {
            returnos = 1;
        }
        break;
    case 2:
        if((testPremiun(tabela[1],tabela[4],tabela[7],tabela[10],tabela[13],premiunTest , numberSlotsTest)) )
        {
            returnos = 2;
        }

        break;
    case 3:

        if((testPremiun(tabela[3],tabela[6],tabela[9],tabela[12],tabela[15],premiunTest , numberSlotsTest)) )
        {
            returnos = 3;
        }
        break;
    case 4:
        /*
 * x   x
 *  x x
 *   x
 */
        if((testPremiun(tabela[1],tabela[5],tabela[9],tabela[11],tabela[13],premiunTest , numberSlotsTest)) )
        {
            returnos = 4;
        }
        break;
    case 5:
        /*
         *   x
         *  x x
         * x   x
         */
        if((testPremiun(tabela[3],tabela[5],tabela[7],tabela[11],tabela[15],premiunTest , numberSlotsTest)) )
        {
            returnos = 5;
        }
        break;
    case 6:
        /*
         * xx
         *   x
         *    xx
         */

        if((testPremiun(tabela[1],tabela[4],tabela[8],tabela[12],tabela[15],premiunTest , numberSlotsTest)) )
        {
            returnos = 6;
        }
        break;
    case 7:
        /*
         *    xx
         *   x
         * xx
         */

        if((testPremiun(tabela[3],tabela[6],tabela[8],tabela[10],tabela[13],premiunTest , numberSlotsTest)) )
        {
            returnos = 7;
        }
        break;
    case 8:
        /*
         *
         * x   x
         *  xxx
         */

        if((testPremiun(tabela[2],tabela[6],tabela[9],tabela[12],tabela[14],premiunTest , numberSlotsTest)) )
        {
            returnos = 8;
        }
        break;
    case 9:
        /*
         *  xxx
         * x   x
         *
         */

        if((testPremiun(tabela[2],tabela[4],tabela[7],tabela[10],tabela[14],premiunTest , numberSlotsTest)) )
        {
            returnos = 9;
        }
        break;
    case 10:
        /*
         *  x
         * x x x
         *    x
         */

        if((testPremiun(tabela[2],tabela[4],tabela[8],tabela[12],tabela[14],premiunTest , numberSlotsTest)) )
        {
            returnos = 10;
        }
        break;
    case 11:
        /*
         *    x
         * x x x
         *  x
         */

        if((testPremiun(tabela[2],tabela[5],tabela[8],tabela[10],tabela[14],premiunTest , numberSlotsTest)) )
        {
            returnos = 11;
        }
        break;
    case 12:
        /*
         *   xxx
         *  x
         * x
         */

        if((testPremiun(tabela[3],tabela[5],tabela[7],tabela[10],tabela[13],premiunTest , numberSlotsTest)) )
        {
            returnos = 12;
        }
        break;
    case 13:
        /*
         * x
         *  x
         *   xxx
         */

        if((testPremiun(tabela[1],tabela[5],tabela[9],tabela[12],tabela[15],premiunTest , numberSlotsTest)) )
        {
            returnos = 13;
        }
        break;
    case 14:
        /*
         * xxx
         *    x
         *     x
         */

        if((testPremiun(tabela[1],tabela[4],tabela[7],tabela[11],tabela[15],premiunTest , numberSlotsTest)) )
        {
            returnos = 14;
        }
        break;
    case 15:
        /*
         *     x
         *    x
         * xxx
         */

        if((testPremiun(tabela[3],tabela[6],tabela[9],tabela[11],tabela[13],premiunTest , numberSlotsTest)) )
        {
            returnos = 15;
        }
        break;
    case 16:
        /*
         * xxxx
         *     x
         *
         */

        if((testPremiun(tabela[1],tabela[4],tabela[7],tabela[10],tabela[14],premiunTest , numberSlotsTest)) )
        {
            returnos = 16;
        }
        break;
    case 17:
        /*
         *
         *     x
         * xxxx
         */

        if((testPremiun(tabela[3],tabela[6],tabela[9],tabela[12],tabela[14],premiunTest , numberSlotsTest)) )
        {
            returnos = 17;
        }
        break;
    case 18:
        /*
         *  xxxx
         * x
         *
         */

        if((testPremiun(tabela[2],tabela[4],tabela[7],tabela[10],tabela[13],premiunTest , numberSlotsTest)) )
        {
            returnos = 18;
        }
        break;
    case 19:
        /*
         *
         * x
         *  xxxx
         */

        if((testPremiun(tabela[2],tabela[6],tabela[9],tabela[12],tabela[15],premiunTest , numberSlotsTest)) )
        {
            returnos = 19;
        }
        break;
    case 20:
        /*
         *     x
         *  xxx
         * x
         */

        if((testPremiun(tabela[3],tabela[5],tabela[8],tabela[11],tabela[13],premiunTest , numberSlotsTest)) )
        {
            returnos = 20;
        }
        break;
    case 21:

        // premio linha 21 a 25
        if((testPremiun(tabela[1],tabela[2],tabela[3],0,0 ,premiunTest , numberSlotsTest)) )
        {
            returnos = 21;
        }
        break;
    case 22:

        if((testPremiun(tabela[4],tabela[5],tabela[6],0,0 ,premiunTest , numberSlotsTest)) )
        {
            returnos = 22;
        }
        break;
    case 23:

        if((testPremiun(tabela[7],tabela[8],tabela[9],0,0 ,premiunTest , numberSlotsTest)) )
        {
            returnos = 23;
        }
        break;
    case 24:

        if((testPremiun(tabela[10],tabela[11],tabela[12],0,0,premiunTest , numberSlotsTest)) )
        {
            returnos = 24;
        }
        break;
    case 25:

        if((testPremiun(tabela[13],tabela[14],tabela[15],0,0,premiunTest , numberSlotsTest)) )
        {
            returnos = 25;
        }
    }
    return returnos;
}
//-------------------------------------------------------------
int Mathe::testPremiun(int slot1,int slot2,int slot3,int slot4,int slot5,int premiunToVerify,int numberSlotsTest)
{
    int retornus = 0;
    if(numberSlotsTest==5)
    {
        if((slot1==premiunToVerify)&&(slot2==premiunToVerify)&&(slot3==premiunToVerify)&&
                (slot4==premiunToVerify)&&(slot5==premiunToVerify))
        {
            retornus = 5;
        }
    }
    else if(numberSlotsTest==4)
    {
        if((slot2==premiunToVerify)&&(slot3==premiunToVerify)&&
                (slot4==premiunToVerify)&&(slot5==premiunToVerify))
        {
            retornus =  4;
        }
        else if((slot1==premiunToVerify)&&(slot2==premiunToVerify)&&(slot3==premiunToVerify)&&
                (slot4==premiunToVerify))
        {
            retornus =  4;
        }
    }
    else if(numberSlotsTest==4)
    {

        if((slot1==premiunToVerify)&&(slot2==premiunToVerify)&&(slot3==premiunToVerify))
        {
            retornus =  3;
        }
        else if((slot2==premiunToVerify)&&(slot3==premiunToVerify)&&(slot4==premiunToVerify))
        {
            retornus =  3;
        }
        else if((slot3==premiunToVerify)&&(slot4==premiunToVerify)&&(slot5==premiunToVerify))
        {
            retornus =  3;
        }
        else
            if((slot1==premiunToVerify)&&(slot2==premiunToVerify)&&(slot3==premiunToVerify))
            {
                retornus =  3;
            }
    }
    return retornus ;
}
//-------------------------------------------------------------
Bonus11::Bonus11(int bonusMultiplier): multiplier(bonusMultiplier),
    firstPick(true), wormFound(false)
{
    int amounts[ 12 ] = { 0, 2, 2, 5, 5, 10, 10, 20, 20, 50, 50, 100 };

    for(int x = 0; x < 12; ++x)
        berries[ x ] = -1;

    for(int i = 0; i < 12; ++i)
    {

        // Put a prize to a berry which we haven't already used
        // The algorithm can be simplified, but was left intact.

        for(;;)
        {
            int x = get_randi() % 12;

            if (berries[ x ] == -1)
            {
                berries[ x ] = amounts[ i ];
                break;
            }
        }
    }
}
//------------------------------------------------------------------
int Bonus11::chooseNextStrawberry(int num) noexcept(false)
{
    if (num < 0 || num > 11)
        throw BadNumber();

    if (wormFound)
        throw WormWasFound();

    int prize = berries[ num ];

    if (!prize)
    {
        if (firstPick)
        {
            // swap the worm for something else

            int x;
            do { x = get_randi() % 12; } while(x == num);

            prize = berries[ x ];
            berries[ x ] = 0;
        }
        else
        {
            wormFound = true;

            return 0;
        }
    }

    if (prize == -1)
        throw AlreadyPicked();

    berries[ num ] = -1;

    firstPick = false;

    return prize * multiplier;
}
//------------------------------------------------------------------
int get_randi()
{
#ifndef USERAND
	return qrand();
#else
	return rand();
#endif
}
//------------------------------------------------------------------
int bonus22(int multiplier,  int others[ 4 ], int perce)
{
    int left[ 5 ] = { 50, 75, 100, 150, 0 };

    int pick;

    int r = get_randi() % 100;

    if (!perce)
    {
        if (r < 22)
            pick = 0;
        else
            if (r < 44)
                pick = 1;
            else
                if (r < 66)
                    pick = 2;
                else
                    if (r < 88)
                        pick = 3;
                    else
                        pick = 4;
    }
    else
    {
        if (r < 20)
            pick = 0;
        else
            if (r < 40)
                pick = 1;
            else
                if (r < 60)
                    pick = 2;
                else
                    if (r < 80)
                        pick = 3;
                    else
                        pick = 4;
    }

    int win = left[ pick ] * multiplier;

    // Now distribute the others randomly

    for(int i = 4; i; --i)
    {
        // Kill out the one we picked

        for(int x = pick; x < i; ++x)
            left[ x ] = left[ x + 1 ];

        // Now choose from the ones that are left

        pick = get_randi() % i;

        others[ 4 - i ] = left[ pick ] * multiplier;
    }

    return win;
}
//------------------------------------------------------------------
int bonus33(int multiplier, int others[ 4 ], int perce) noexcept(false)
{
    // Should be 5, but due to the problem in the original game where perce > 1
    // would presumably choose zero win in some cases, we introduce the 6th
    // value to implement that behaviour.

    int left[ 6 ] = { 150, 200, 250, 500, 1000, 0 };

    int r;

    int pick = 5;

    switch(perce)
    {
    case 0:
        r = get_randi() % 12;

        if (r < 8)
            pick = 0;
        else
            if (r < 9)
                pick = 1;
            else
                if (r < 10)
                    pick = 2;
                else
                    if (r < 11)
                        pick = 3;
                    else
                        pick = 4;

        break;

    case 1:

        r = get_randi() % 20;

        if (r < 15)
            pick = 0;
        else
            if (r < 16)
                pick = 1;
            else
                if (r < 17)
                    pick = 2;
                else
                    if (r < 19)
                        pick = 3;
                    else
                        pick = 4;

        break;

    case 2:

        r = get_randi() % 22;

        if (r < 14)
            pick = 0;
        else
            if (r < 15)
                pick = 1;
            else
                if (r < 16)
                    pick = 2;
                else
                    if (r < 18)
                        pick = 3;
                    else
                        if (r < 20)
                            pick = 4;
        // else by default, presumably 5, this was the bug. same for perce >2

        break;

    case 3:
        r = get_randi() % 25;

        if (r < 5)
            pick = 0;
        else
            if (r < 10)
                pick = 1;
            else
                if (r < 15)
                    pick = 2;
                else
                    if (r < 18)
                        pick = 3;
                    else
                        if (r < 20)
                            pick = 4;

        break;

    case 4:

        r = get_randi() % 30;

        if (r < 4)
            pick = 0;
        else
            if (r < 9)
                pick = 1;
            else
                if (r < 14)
                    pick = 2;
                else
                    if (r < 17)
                        pick = 3;
                    else
                        if (r < 20)
                            pick = 4;

        break;

    default:
        throw UnknownPerces();
    }

    int win = left[ pick ] * multiplier;

    // Now distribute the others randomly

    for(int i = 4; i; --i)
    {
        // Kill out the one we picked

        for(int x = pick; x < i; ++x)
            left[ x ] = left[ x + 1 ];

        // Now choose from the ones that are left

        pick = get_randi() % i;

        others[ 4 - i ] = left[ pick ] * multiplier;
    }

    return win;
}
/*
 *
 * #include "math.hh"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
  srand(time(0));
  Math m;
  int bet = 2, lines = 20;
  unsigned long long in = 0, outReels = 0, outBonus = 0;
  for(int g = 0; g < 100000000; ++g)//CICLE 100.000.000
  {
    int result[ 15 ];
    // Make spin
    in += bet * lines;
    m.play(10, result);
    FILE * f = fopen("input", "w");
    fprintf(f, "%d\n%d\n", bet, lines);
    for(int x = 0; x < 15; ++x)
      fprintf(f, "%d\n", result[ x ]);
    fclose(f);
   //TEST SLOTS
    system("./test > output");
    f = fopen("output", "r");
    int win, b1, b2;
    fscanf(f, "%d %d %d", &win, &b1, &b2);
    fclose(f);
    outReels += win;
   //PRINT GAME   WIN   BONUS 1 AND BONUS 2
    printf("Game %d: %d,%d,%d\n", g, win, b1, b2);
    if (b1)//BONUS 1 WIN
    {
      Bonus1 b(b1);
      int sum = 0;
      printf("Bonus1: ");
      for(int x = 0; x < 12; ++x)
      {
        int prize = b.chooseNextStrawberry(x);
        printf("%d ", prize);
        if (!prize)
          break;
        sum += prize;
      }
      printf("= %d\n\n", sum);
      outBonus += sum;
    }
    if (b2)//BONUS 2 WIN
    {
      int others[ 4 ];
      int win = bonus2(b2, 0, others);
      printf("Bonus2: <%d> %d %d %d %d\n\n", win, others[ 0 ], others[ 1 ],
              others[ 2 ], others[ 3 ]);
      outBonus += win;
      if (!win)
      {
        // Now play the bonus3
        win = bonus3(b2, 0, others);
        printf("Bonus3: <%d> %d %d %d %d\n", win, others[ 0 ], others[ 1 ],
                others[ 2 ], others[ 3 ]);
        outBonus += win;
      }
    }
    printf("RTPf = %f, RTPr = %f, RTPb = %f\n",
            double((outReels + outBonus) * 10000 / in) / 100.0,
            double(outReels * 10000 / in) / 100.0,
            double(outBonus * 10000 / in) / 100.0);
    printf("%02d %02d %02d %02d %02d\n", result[ 0 ], result[ 3 ], result[ 6 ], result[ 9 ], result[ 12 ]);
    printf("%02d %02d %02d %02d %02d\n", result[ 1 ], result[ 4 ], result[ 7 ], result[ 10 ], result[ 13 ]);
    printf("%02d %02d %02d %02d %02d\n", result[ 2 ], result[ 5 ], result[ 8 ], result[ 11 ], result[ 14 ]);
    printf("\n");
    // Now play the bonus1
    printf("Bonus1: ");
    Bonus1 b(1);
    int sum = 0;
    for(int x = 0; x < 12; ++x)
    {
      int prize = b.chooseNextStrawberry(x);
      printf("%d ", prize);
      if (!prize)
        break;
      sum += prize;
    }
    printf("= %d\n\n", sum);
    // Now play the bonus2
    int others[ 4 ];
    int win = bonus2(1, 0, others);
    printf("Bonus2: <%d> %d %d %d %d\n\n", win, others[ 0 ], others[ 1 ],
            others[ 2 ], others[ 3 ]);
    // Now play the bonus3
    win = bonus3(1, 0, others);
    printf("Bonus3: <%d> %d %d %d %d\n", win, others[ 0 ], others[ 1 ],
            others[ 2 ], others[ 3 ]);
  }
}
*/
/*
 * void Class::playMaxBet()
{
  if (!math.canChangeBet())
    return;
  if (math.getBet() != 10 || math.getLines() != 20)
  {
    math.setBet(10);
    math.setLines(20);
    updateReelsCounters();
    showLines();
    reelsShowLines = true;
    sounds("reels/line_choice5").play();
    if (math.canSpinBeMade())
      sleep(0.5);
  }
  if (math.canSpinBeMade())
  {
    math.makeSpin();
    updateReelsCounters();
  }
}

 */
