
#include "b23ch1039_b23me1016_b23cs1028_functions.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>


char strValue[MAX_DIGITS+3];

int OperatorType = ADD;
int OperandType = LEFT;
int NumDigits = 0;
double LeftOperand = 0;
double RightOperand = 0;

bool DecimalFlag = false;
bool OperatorFlag = false;
bool ContinueCalcFlag = false;
bool FinalCalcFlag = false;
bool FinalValueConversion = false;

void save_to_history(const char* calculation) {
    FILE *file = fopen("history.txt", "a");
    if (file == NULL) {
        perror("Could not open history file");
        return;
    }
    fprintf(file, "%s\n", calculation);
    fclose(file);
}

void load_history() {
    FILE *file = fopen("history.txt", "r");
    if (file == NULL) {
        MessageBox(NULL, "No history found.", "History", MB_OK);
        return;
    }

    char line[256];
    char history[2048] = "";

    while (fgets(line, sizeof(line), file)) {
        strcat(history, line);
    }
    fclose(file);

    MessageBox(NULL, history, "Calculation History", MB_OK);
}


void InsertStringNumber(char Value, char *strValue)
{
    if (FinalCalcFlag)
        Reset();

    OperatorFlag = false;

    if (DecimalFlag) {
        if (NumDigits < MAX_DIGITS+1) {
            strValue[NumDigits++] = Value;
            strValue[NumDigits] = '\0';
        }
    } else {
        if (NumDigits < MAX_DIGITS) {
            strValue[NumDigits++] = Value;
            strValue[NumDigits] = '\0';
        }
    }
}

void DeleteStringNumber(char *strValue)
{
    if (FinalCalcFlag == false && OperatorFlag == false) {
        if (strValue[--NumDigits] == '.')
            DecimalFlag = false;
        if (NumDigits < 1) {
            strValue[0] = '0';
            NumDigits = 0;
        }
        else
            strValue[NumDigits] = '\0';
    }
}

void InsertDecimalPoint(void)
{
    if (!DecimalFlag) {
        if (NumDigits == 0) {
            InsertStringNumber('0', strValue);
            InsertStringNumber('.', strValue);
        } else
            InsertStringNumber('.', strValue);
        DecimalFlag = true;
    }
}

void ValueConversion(void)
{
    if (FinalCalcFlag) {
        FinalValueConversion = true;
        LeftOperand *= -1;
        ChangeNumDigits(LeftOperand);
        gcvt(LeftOperand, MAX_DIGITS, strValue);
    } else {
        if (OperandType == LEFT) {
            LeftOperand *= -1;
            ChangeNumDigits(LeftOperand);
            gcvt(LeftOperand, MAX_DIGITS, strValue);
        } 
        if (OperandType == RIGHT) {
            RightOperand *= -1;
            ChangeNumDigits(RightOperand);
            gcvt(RightOperand, MAX_DIGITS, strValue);
        }       
    }
    RemoveStringDecimal();
}

void InsertOperator(char Value, char *strValue)
{
    ChangeOperand();
    FinalCalcFlag = false;
    FinalValueConversion = false;

    if (LeftOperand == 0) {
        strValue[0] = '0';
        strValue[1] = ' ';
        strValue[2] = Value;
        strValue[3] = '\0';
    } else {
        gcvt(LeftOperand, MAX_DIGITS, strValue);
        RemoveStringDecimal();
        strValue += sprintf(strValue, "%s %c", strValue, Value);
    }
    OperatorFlag = true;
}

void ChangeOperand(void)
{
    OperandType = RIGHT;
    NumDigits = 0;
    DecimalFlag = false;
}

void CalculateOperand() {
    if (OperandType == LEFT) {
        LeftOperand = atof(strValue); 
        }
    else {
        RightOperand = atof(strValue); 
    }
}

void CalculateDoubleResult()
{
    if (!OperatorFlag) {
        if (OperatorType == ADD)
            LeftOperand += RightOperand;
        if (OperatorType == SUB)
            LeftOperand -= RightOperand;
        if (OperatorType == MUL)
            LeftOperand *= RightOperand;
        if (OperatorType == DIV)
            LeftOperand /= RightOperand;
    }
}

void CalculateStringResult()
{
    gcvt(LeftOperand, MAX_DIGITS, strValue);
    RemoveStringDecimal();
    FinalCalcFlag = true;
}

void Reset(void)
{
    strValue[0] = '0';
    strValue[1] = '\0';

    // Global vars
    OperatorType = ADD;
    OperandType = LEFT;
    NumDigits = 0;
    LeftOperand = 0;
    RightOperand = 0;

    // Flags
    DecimalFlag = false;
    OperatorFlag = false;
    ContinueCalcFlag = false;
    FinalCalcFlag = false;
    FinalValueConversion = false;
}

void ChangeNumDigits(double Operand)
{
    if (Operand < 0)
        ++NumDigits;
    if (Operand > 0)
        --NumDigits;
}

void RemoveStringDecimal(void)
{
    char *PtrStrValue = strValue;
    while (*PtrStrValue) {
        PtrStrValue++;
    }
    if (*(PtrStrValue-1) == '.') {
        *(PtrStrValue-1) = '\0';
    }
}

void CalculateTrigonometricFunction(int function) {
    double result = 0.0;
    switch (function) {
        case SIN:
            result = sin(OperandType == LEFT ? LeftOperand : RightOperand);
            break;
        case COS:
            result = cos(OperandType == LEFT ? LeftOperand : RightOperand);
            break;
        case TAN:
            result = tan(OperandType == LEFT ? LeftOperand : RightOperand);
            break;
        case ACOS:
            result = acos(OperandType == LEFT ? LeftOperand : RightOperand);
            break;

        case ASIN:
            result = asin(OperandType == LEFT ? LeftOperand : RightOperand);
            break;

        case ATAN:
            result = atan(OperandType == LEFT ? LeftOperand : RightOperand);
            break;
    }
    gcvt(result, MAX_DIGITS, strValue);
    RemoveStringDecimal();
    CalculateOperand();
}

void CalculateSquareRoot() {
    double result = sqrt(OperandType == LEFT ? LeftOperand : RightOperand);
    if (OperandType == LEFT) {
        LeftOperand = result;
    } else {
        RightOperand = result;
    }
    gcvt(result, MAX_DIGITS, strValue);
    RemoveStringDecimal();
}

void CalculateSquare() {
    double operand = OperandType == LEFT ? LeftOperand : RightOperand;
    double result = pow(operand, 2);
    
    if (OperandType == LEFT) {
        LeftOperand = result;
    } else {
        RightOperand = result;
    }
    gcvt(result, MAX_DIGITS, strValue);
    RemoveStringDecimal();
}

void CalculateCube() {
    double result = pow(OperandType == LEFT ? LeftOperand : RightOperand, 3);
    if (OperandType == LEFT) {
        LeftOperand = result;
    } else {
        RightOperand = result;
    }
    gcvt(result, MAX_DIGITS, strValue);
    RemoveStringDecimal();
}

void CalculateReciprocal(void)
{
    double result = 1.0 / (OperandType == LEFT ? LeftOperand : RightOperand);
    LeftOperand = result;
    gcvt(result, MAX_DIGITS, strValue);
    RemoveStringDecimal();
}

double factorial(double n)
{
    if (n < 1 || n-(int)n != 0) return NAN;
    if (n == 0) return 1;   
    double result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

