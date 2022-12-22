/**===================================================================================================================*\
  @file Lib_Calc.c

  @brief Bibiloteka Lib_Calc - implementacja
  
  Implementacja funkcjonalności podstawowej kalkukatora 4-działaniowego z pamięcią.

  @see Lib_Calc.pdf

\*====================================================================================================================*/

/*====================================================================================================================*\
    Załączenie nagłówków
\*====================================================================================================================*/
#include "Lib_Calc.h"

/*====================================================================================================================*\
    Makra lokalne
\*====================================================================================================================*/
#define MAX32   	(2147483647L)
#define MIN32   	(-2147483648L)
#define ZERO_DIV_POS	(0x7FFFFFFF)
#define ZERO_DIV_NEG	(0x80000000)

/*====================================================================================================================*\
    Typy lokalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne globalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne lokalne (statyczne)
\*====================================================================================================================*/
static sint32 memory_value;     /**< Reprezentacja pamięci kalkulatora [P11] */

/*====================================================================================================================*\
    Deklaracje funkcji lokalnych
\*====================================================================================================================*/

/*====================================================================================================================*\
    Kod globalnych funkcji inline i makr funkcyjnych
\*====================================================================================================================*/

/*====================================================================================================================*\
    Kod funkcji
\*====================================================================================================================*/


/**
  @brief Dodawanie

  Implementacja dodawania liczb 32-bitowych z kontrolą przepełnienia.
  Element projektu: [P2]
*/
Std_ReturnType Lib_Calc_Add(sint32 arg1, sint32 arg2, sint32* result)
{
    sint64 tmp = (sint64)arg1 + (sint64)arg2;
    Std_ReturnType ret = E_OK;
    if((tmp > MAX32) || (tmp < MIN32))
    {
        ret = E_NOT_OK;
    }
    *result = (sint32)tmp;
    return ret;
}

/**
  @brief Odejmowanie

  Implementacja odejmowania liczb 32-bitowych z kontrolą przepełnienia.
  Element projektu: [P3]
*/
Std_ReturnType Lib_Calc_Sub(sint32 arg1, sint32 arg2, sint32* result)
{
    sint64 tmp = (sint64)arg1 - (sint64)arg2;
    Std_ReturnType ret = E_OK;
    if((tmp > MAX32) || (tmp < MIN32))
    {
        ret = E_NOT_OK;
    }
    *result = (sint32)tmp;
    return ret;
}

/**
  @brief Mnozenie

  Implementacja mnozenia liczb 32-bitowych z kontrolą przepełnienia.
  Element projektu: [P4]
*/
Std_ReturnType Lib_Calc_Mul(sint32 arg1, sint32 arg2, sint32* result)
{
    sint64 tmp = (sint64)arg1 * (sint64)arg2;
    Std_ReturnType ret = E_OK;
    if((tmp > MAX32) || (tmp < MIN32))
    {
        ret = E_NOT_OK;
    }
    *result = (sint32)tmp;
    return ret;
}

/**
  @brief Dzielenie

  Implementacja dzielenia liczb 32-bitowych z kontrolą przepełnienia.
  Element projektu: [P5 P6 P7 P8]
*/
Std_ReturnType Lib_Calc_Div(sint32 arg1, sint32 arg2, sint32* result)
{
    sint64 tmp;
    Std_ReturnType ret = E_OK;
    if(arg2 == 0)
    {
        ret = E_NOT_OK;
        if(arg1 > 0)
        {
            tmp = ZERO_DIV_POS;
        }
        else if(arg1 < 0)
        {
            tmp = ZERO_DIV_NEG;
        }
        else
        {
            tmp = 0;
        }
    }
    else
    {
        tmp = arg1 / arg2;
    }
    *result = (sint32)tmp;
    return ret;
}

/**
  @brief ZapisMem

  Implementacja zapisu do pamieci liczb 32-bitowych.
  Element projektu: [P9]
*/
void Lib_Calc_MemS(sint32 arg1)
{
    memory_value = arg1;
}

/**
  @brief OdczytMem

  Implementacja odczytu z pamieci liczb 32-bitowych.
  Element projektu: [P10]
*/
sint32 Lib_Calc_MemR(void)
{
    sint32 ret = memory_value;
    return ret;
}

