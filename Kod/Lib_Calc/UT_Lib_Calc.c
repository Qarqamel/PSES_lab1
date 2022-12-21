/** ==================================================================================================================*\
  @file UT_Lib_Calc.c

  @brief Testy jednostkowe do Lib_Calc

\*====================================================================================================================*/

#include "acutest.h"
#include "Std_Types.h"

#include "Lib_Calc.c"   /* To nie pomyłka - taki include eksponuje zmienne statyczne dla testów */

/**
  @brief Test dodawania

  Funkcja testująca dodawanie w bibliotece. Funkcje testowe acutest nie mogą zwracać ani przyjmować danych!
*/
void Test_Of_Lib_Calc_Add(void)
{
    sint32 result;
    Std_ReturnType retv;

    retv = Lib_Calc_Add(0L, 0L, &result);

    TEST_CHECK(result == 0);       /* Test przejdzie jeżeli wyrażenie w nawiasach jest prawdziwe */
    TEST_CHECK(retv == E_OK);
    
    retv = Lib_Calc_Add(1L, 1L, &result);

    TEST_CHECK(result == 2);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Add(1L, -1L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Add(-1L, 1L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Add(-1L, -1L, &result);

    TEST_CHECK(result == -2);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Add(MAX32, 1L, &result);

    TEST_CHECK(result == (sint32)((sint64)MAX32 + (sint64)1L));
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Add(MIN32, -1L, &result);

    TEST_CHECK(result == (sint32)((sint64)MIN32 - (sint64)1L));
    TEST_CHECK(retv == E_NOT_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
}


/**
  @brief Test odejmowania

  Funkcja testująca odejmowanie w bibliotece.
*/
void Test_Of_Lib_Calc_Sub(void)
{
    sint32 result;
    Std_ReturnType retv;

    retv = Lib_Calc_Sub(0L, 0L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);
    
    retv = Lib_Calc_Sub(1L, 1L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Sub(1L, -1L, &result);

    TEST_CHECK(result == 2);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Sub(-1L, 1L, &result);

    TEST_CHECK(result == -2);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Sub(-1L, -1L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Sub(MAX32, -1L, &result);

    TEST_CHECK(result == (sint32)((sint64)MAX32 + (sint64)1L));
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Sub(MIN32, 1L, &result);

    TEST_CHECK(result == (sint32)((sint64)MIN32 - (sint64)1L));
    TEST_CHECK(retv == E_NOT_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
}

/**
  @brief Test mnozenia

  Funkcja testująca mnozenie w bibliotece.
*/
void Test_Of_Lib_Calc_Mul(void)
{
    sint32 result;
    Std_ReturnType retv;

    retv = Lib_Calc_Mul(0L, 0L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);
    
    retv = Lib_Calc_Mul(1L, 1L, &result);

    TEST_CHECK(result == 1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Mul(1L, -1L, &result);

    TEST_CHECK(result == -1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Mul(-1L, 1L, &result);

    TEST_CHECK(result == -1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Mul(-1L, -1L, &result);

    TEST_CHECK(result == 1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Mul(MAX32, 2L, &result);

    TEST_CHECK(result == (sint32)((sint64)MAX32 * (sint64)2L));
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Mul(MIN32, -2L, &result);

    TEST_CHECK(result == (sint32)((sint64)MIN32 * (sint64)(-2L)));
    TEST_CHECK(retv == E_NOT_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
}

/**
  @brief Test dzielenie

  Funkcja testująca dzielenie w bibliotece.
*/
void Test_Of_Lib_Calc_Div(void)
{
    sint32 result;
    Std_ReturnType retv;
    
    retv = Lib_Calc_Div(0L, 1L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Div(1L, 1L, &result);

    TEST_CHECK(result == 1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Div(1L, -1L, &result);

    TEST_CHECK(result == -1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Div(-1L, 1L, &result);

    TEST_CHECK(result == -1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Div(-1L, -1L, &result);

    TEST_CHECK(result == 1);
    TEST_CHECK(retv == E_OK);

    retv = Lib_Calc_Div(0L, 0L, &result);

    TEST_CHECK(result == 0);
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Div(1L, 0L, &result);

    TEST_CHECK(result == ZERO_DIV_POS);
    TEST_CHECK(retv == E_NOT_OK);

    retv = Lib_Calc_Div(-1L, 0L, &result);

    TEST_CHECK(result == ZERO_DIV_NEG);
    TEST_CHECK(retv == E_NOT_OK);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
}

/**
  @brief Test ZapisMem

  Funkcja testująca zapis do pamieci w bibliotece.
*/
void Test_Of_Lib_Calc_MemS(void)
{    
    Lib_Calc_MemS(0L);

    TEST_CHECK(memory_value == 0);

    Lib_Calc_MemS(1L);

    TEST_CHECK(memory_value == 1);

    Lib_Calc_MemS(-1L);

    TEST_CHECK(memory_value == -1);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
}

/**
  @brief Test OdczytMem

  Funkcja testująca odczyt z pamieci w bibliotece.
*/
void Test_Of_Lib_Calc_MemR(void)
{
    sint32 result;
    
    memory_value = 0L;
    result = Lib_Calc_MemR();

    TEST_CHECK(result == 0);

    memory_value = 1L;
    result = Lib_Calc_MemR();

    TEST_CHECK(result == 1);

    memory_value = -1L;
    result = Lib_Calc_MemR();

    TEST_CHECK(result == -1);

    /* TUTAJ DOPISZ WIĘCEJ TESTÓW */
}

/*
  Lista testów - wpisz tutaj wszystkie funkcje które mają być wykonane jako testy.
*/
TEST_LIST = {
    { "Test of Lib_Calc_Add", Test_Of_Lib_Calc_Add },   /* Format to { "nazwa testu", nazwa_funkcji } */
    { "Test of Lib_Calc_Sub", Test_Of_Lib_Calc_Sub },
    { "Test of Lib_Calc_Mul", Test_Of_Lib_Calc_Mul },
    { "Test of Lib_Calc_Div", Test_Of_Lib_Calc_Div },
    { "Test of Lib_Calc_MemS", Test_Of_Lib_Calc_MemS },
    { "Test of Lib_Calc_MemR", Test_Of_Lib_Calc_MemR },
    { NULL, NULL }                                      /* To musi być na końcu */
};

