#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_DIGITS 15

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define LEFT 1
#define RIGHT 2
#define SIN 5
#define COS 6
#define TAN 7
#define ACOS 8
#define ASIN 9
#define ATAN 10

extern char strValue[MAX_DIGITS+3];

extern int OperatorType ;
extern int OperandType ;
extern int NumDigits ;
extern double LeftOperand ;
extern double RightOperand ;

extern bool DecimalFlag ;
extern bool OperatorFlag ;
extern bool ContinueCalcFlag ;
extern bool FinalCalcFlag ;
extern bool FinalValueConversion ;


void save_to_history(const char* calculation);
void load_history();
void InsertStringNumber(char Value, char *strValue);
void DeleteStringNumber(char *strValue);
void InsertDecimalPoint(void);
void ValueConversion(void);
void InsertOperator(char Value, char *strValue);
void ChangeOperand(void);
void CalculateOperand(void);
void CalculateDoubleResult(void);
void CalculateStringResult(void);
void Reset(void);
void ChangeNumDigits(double Operand);
void RemoveStringDecimal(void);
void CalculateTrigonometricFunction(int function);
void CalculateSquareRoot(void);
void CalculateSquare(void);
void CalculateCube(void);
void CalculateReciprocal(void);
double factorial(double n);



#endif // CALC_H
