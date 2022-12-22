/** ==================================================================================================================*\
  @file UT_Calc_Ab.c

  @brief Testy jednostkowe do Calc_Ab

\*====================================================================================================================*/
#include "../Std_Types.h"

#include "../acutest.h"
#include "../fff.h"

#include "Calc_Ab.c"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Add, sint32, sint32, sint32*);
FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Sub, sint32, sint32, sint32*);
FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Mul, sint32, sint32, sint32*);
FAKE_VALUE_FUNC(Std_ReturnType, Lib_Calc_Div, sint32, sint32, sint32*);

FAKE_VOID_FUNC(Lib_Calc_MemS, sint32);
FAKE_VALUE_FUNC(sint32, Lib_Calc_MemR);

/**
  @brief Test ustawiania akumulatora

  Funkcja testująca ustawianie akumulatora.
*/
void Test_Of_Calc_Set_A(void)
{

    Calc_Set_A(0L);

    TEST_CHECK(akumulator == 0L);

    Calc_Set_A(1L);

    TEST_CHECK(akumulator == 1L);

    Calc_Set_A(ERR);

    TEST_CHECK(akumulator == ERR);

    akumulator = ERR;
    Calc_Set_A(1L);

    TEST_CHECK(akumulator == ERR);
}

/**
  @brief Test odczytu akumulatora

  Funkcja testująca odczyt akumulatora.
*/
void Test_Of_Calc_Get_A(void)
{
    Std_ReturnType retv;
    sint32 result;

    akumulator = 0L;
    retv = Calc_Get_A(&result);

    TEST_CHECK(retv == E_OK);
    TEST_CHECK(result == 0L);

    akumulator = 1L;
    retv = Calc_Get_A(&result);

    TEST_CHECK(retv == E_OK);
    TEST_CHECK(result == 1L);

    akumulator = ERR;
    retv = Calc_Get_A(&result);

    TEST_CHECK(retv == E_NOT_OK);
    TEST_CHECK(result == ERR);

}

/**
  @brief Test operacji

  Funkcja testująca operacje.
*/
void Test_Of_Calc_Oper(void)
{
    int Lib_Calc_Add_Ctr = 0;
    int Lib_Calc_Sub_Ctr = 0;
    int Lib_Calc_Mul_Ctr = 0;
    int Lib_Calc_Div_Ctr = 0;

    akumulator = ERR;
    Calc_Oper(CALC_ADD, 1L);

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == Lib_Calc_Mul_Ctr);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == Lib_Calc_Div_Ctr);
    TEST_CHECK(akumulator == ERR);

    akumulator = 2L;
    Calc_Oper(CALC_ADD, 1L);

    Lib_Calc_Add_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == Lib_Calc_Mul_Ctr);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == Lib_Calc_Div_Ctr);
    TEST_CHECK(Lib_Calc_Add_fake.arg0_val == 2L);
    TEST_CHECK(Lib_Calc_Add_fake.arg1_val == 1L);
    TEST_CHECK(akumulator == 0L);

    akumulator = 2L;
    Calc_Oper(CALC_SUB, 1L);

    Lib_Calc_Sub_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == Lib_Calc_Mul_Ctr);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == Lib_Calc_Div_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.arg0_val == 2L);
    TEST_CHECK(Lib_Calc_Sub_fake.arg1_val == 1L);
    TEST_CHECK(akumulator == 0L);

    akumulator = 2L;
    Calc_Oper(CALC_MUL, 1L);

    Lib_Calc_Mul_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == Lib_Calc_Mul_Ctr);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == Lib_Calc_Div_Ctr);
    TEST_CHECK(Lib_Calc_Mul_fake.arg0_val == 2L);
    TEST_CHECK(Lib_Calc_Mul_fake.arg1_val == 1L);
    TEST_CHECK(akumulator == 0L);

    akumulator = 2L;
    Calc_Oper(CALC_DIV, 1L);

    Lib_Calc_Div_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_Mul_fake.call_count == Lib_Calc_Mul_Ctr);
    TEST_CHECK(Lib_Calc_Div_fake.call_count == Lib_Calc_Div_Ctr);
    TEST_CHECK(Lib_Calc_Div_fake.arg0_val == 2L);
    TEST_CHECK(Lib_Calc_Div_fake.arg1_val == 1L);
    TEST_CHECK(akumulator == 0L);
}

/**
  @brief Test operacji na pamieci

  Funkcja testująca operacje na pamieci.
*/
void Test_Of_Calc_Mem(void)
{
    int Lib_Calc_Add_Ctr = 0;
    int Lib_Calc_Sub_Ctr = 0;
    int Lib_Calc_MemR_Ctr = 0;
    int Lib_Calc_MemS_Ctr = 0;

    akumulator = ERR;
    Calc_Mem(CALC_MEM_ADD);

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == Lib_Calc_MemR_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);
    TEST_CHECK(akumulator == ERR);

    akumulator = 1L;
    Calc_Mem(CALC_MEM_ADD);

    Lib_Calc_Add_Ctr++;
    Lib_Calc_MemR_Ctr++;
    Lib_Calc_MemS_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == Lib_Calc_MemR_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);    
    TEST_CHECK(Lib_Calc_Add_fake.arg0_val == 0L);
    TEST_CHECK(Lib_Calc_Add_fake.arg1_val == 1L);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    TEST_CHECK(akumulator == 1L);

    akumulator = 1L;
    Calc_Mem(CALC_MEM_SUB);

    Lib_Calc_Sub_Ctr++;
    Lib_Calc_MemR_Ctr++;
    Lib_Calc_MemS_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == Lib_Calc_MemR_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.arg0_val == 0L);
    TEST_CHECK(Lib_Calc_Sub_fake.arg1_val == 1L);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    TEST_CHECK(akumulator == 1L);

    akumulator = 1L;
    Calc_Mem(CALC_MEM_STO);

    Lib_Calc_MemS_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == Lib_Calc_MemR_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 1L);
    TEST_CHECK(akumulator == 1L);

    akumulator = 1L;
    Calc_Mem(CALC_MEM_ZERO);

    Lib_Calc_MemS_Ctr++;

    TEST_CHECK(Lib_Calc_Add_fake.call_count == Lib_Calc_Add_Ctr);
    TEST_CHECK(Lib_Calc_Sub_fake.call_count == Lib_Calc_Sub_Ctr);
    TEST_CHECK(Lib_Calc_MemR_fake.call_count == Lib_Calc_MemR_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    TEST_CHECK(akumulator == 1L);
}

/**
  @brief Test zerowania modułu

  Funkcja testująca reset modułu.
*/
void Test_Of_Calc_Reset(void)
{
    int Lib_Calc_MemS_Ctr = 0;

    akumulator = 0L;

    Calc_Reset();
    Lib_Calc_MemS_Ctr++;

    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    TEST_CHECK(akumulator == 0L);

    akumulator = 1L;

    Calc_Reset();
    Lib_Calc_MemS_Ctr++;

    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    TEST_CHECK(akumulator == 0L);

    akumulator = ERR;

    Calc_Reset();
    Lib_Calc_MemS_Ctr++;

    TEST_CHECK(Lib_Calc_MemS_fake.call_count == Lib_Calc_MemS_Ctr);
    TEST_CHECK(Lib_Calc_MemS_fake.arg0_val == 0L);
    TEST_CHECK(akumulator == 0L);
}

/*
  Lista testów - wpisz tutaj wszystkie funkcje które mają być wykonane jako testy.
*/
TEST_LIST = {
    { "Test of Calc_Set_A", Test_Of_Calc_Set_A },
    { "Test of Calc_Get_A", Test_Of_Calc_Get_A },
    { "Test of Calc_Oper", Test_Of_Calc_Oper },
    { "Test of Calc_Mem", Test_Of_Calc_Mem },
    { "Test of Calc_Reset", Test_Of_Calc_Reset },   /* Format to { "nazwa testu", nazwa_funkcji } */
    { NULL, NULL }                                        /* To musi być na końcu */
};
    
