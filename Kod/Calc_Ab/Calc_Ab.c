/** ==================================================================================================================*\
  @file Calc_Ab.c

  @brief Implementacja kalkulatora
  
  Implementacja kalkukatora 4-działaniowego z pamięcią.

  @see Calc_Ab.pdf

\*====================================================================================================================*/

/*====================================================================================================================*\
    Załączenie nagłówków
\*====================================================================================================================*/
#include "../Lib_Calc/Lib_Calc.h"

/*====================================================================================================================*\
    Makra lokalne
\*====================================================================================================================*/
#define ERR   	(0xFFFFFFFF)

/*====================================================================================================================*\
    Typy lokalne
\*====================================================================================================================*/
typedef enum
{
    CALC_ADD,
    CALC_SUB,
    CALC_MUL,
    CALC_DIV
} Calc_Operation_T;		/** Typ do wyboru rodzaju operacji [P4]*/

typedef enum
{
    CALC_MEM_ADD,
    CALC_MEM_SUB,
    CALC_MEM_STO,
    CALC_MEM_ZERO
} Calc_MemOp_T;		/** Typ do wyboru rodzaju operacji na pamieci [P8]*/

/*====================================================================================================================*\
    Zmienne globalne
\*====================================================================================================================*/

/*====================================================================================================================*\
    Zmienne lokalne (statyczne)
\*====================================================================================================================*/
static sint32 akumulator;     /**< Akumulator kalkulatora [P2] */

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
  @brief Zapis do akumulatora

  Funkcja zapisuje wartość do akumulatora.
  Realizuje [P3]
*/
void Calc_Set_A(sint32 a)
{
    if(akumulator != ERR)
    {
        akumulator = a;
    }
}

/**
  @brief Odczyt z akumulatora

  Funkcja odczytuje wartość z akumulatora.
  Realizuje [P3]
*/
Std_ReturnType Calc_Get_A(sint32* a)
{
    Std_ReturnType retv = E_OK;
    sint32 a_tmp = akumulator;
    if(a_tmp == ERR)
    {
        retv = E_NOT_OK;
    }
    *a = a_tmp;
    return retv;
}

/**
  @brief Wykonanie operacji

  Funkcja wykonuje zadana operacje na akumulatorze i podanym operandzie.
  Realizuje [P5 P6]
*/
void Calc_Oper(Calc_Operation_T op, sint32 arg2)
{
    Std_ReturnType calc_ret = E_OK;
    sint32 result = 0;
    if (akumulator == ERR)
    {
        calc_ret = E_NOT_OK;
    }
    else
    {
        switch(op)
        {
            case CALC_ADD:
                calc_ret = Lib_Calc_Add(akumulator, arg2, &result);
                break;
            case CALC_SUB:
                calc_ret = Lib_Calc_Sub(akumulator, arg2, &result);
                break;
            case CALC_MUL:
                calc_ret = Lib_Calc_Mul(akumulator, arg2, &result);
                break;
            case CALC_DIV:
                calc_ret = Lib_Calc_Div(akumulator, arg2, &result);
                break;
        }
    }
    if(calc_ret == E_NOT_OK)
    {
        result = ERR;
    }
    akumulator = result;
}

/**
  @brief Wykonanie operacji na pamieci

  Funkcja wykonuje zadana operacje na pamieci kalkulatora.
  Realizuje [P5 P9]
*/
void Calc_Mem(Calc_MemOp_T op)
{
    Std_ReturnType calc_ret = E_OK;
    sint32 mem_tmp;
    sint32 result = 0;
    if(akumulator == ERR && op != CALC_MEM_ZERO)
    {
        calc_ret = E_NOT_OK;
    }
    else
    {
        switch(op)
        {
            case CALC_MEM_ADD:
	        mem_tmp = Lib_Calc_MemR();
	        calc_ret = Lib_Calc_Add(mem_tmp, akumulator, &result);
	        break;
            case CALC_MEM_SUB:
	        mem_tmp = Lib_Calc_MemR();
	        calc_ret = Lib_Calc_Sub(mem_tmp, akumulator, &result);
	        break;
            case CALC_MEM_STO:
	        calc_ret = E_OK;
	        result = akumulator;
	        break;
            case CALC_MEM_ZERO:
	        calc_ret = E_OK;
	        result = 0;
	        break;
        }
    }
    if(calc_ret == E_OK)
    {
        Lib_Calc_MemS(result);
    }
}

/**
  @brief Zerowanie modułu

  Funkcja zeruje wartość akumulatora i pamięci.
  Realizuje [P9]
*/
void Calc_Reset(void)
{
    akumulator = 0L;
    Lib_Calc_MemS(0L);
}

