
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>
#include "b23ch1039_b23me1016_b23cs1028_functions.h"


#define CALC_HEIGHT 392
#define CALC_WIDTH 300

#define ROW_GAP 5
#define screen_GAP 1
#define RESULT_X 1
#define RESULT_Y 1
#define RESULT_HEIGHT 40
#define RESULT_WIDTH 285

#define BUTTON_ROW_X 40
#define BUTTON_ROW_Y 45
#define BUTTON_HEIGHT 40
#define BUTTON_WIDTH 50

#define IDC_STATIC_RESULT 101
#define IDC_BUTTON_SEVEN 201
#define IDC_BUTTON_EIGHT 202
#define IDC_BUTTON_NINE 203
#define IDC_BUTTON_NEGATIVE 204
#define IDC_BUTTON_DEL 205
#define IDC_BUTTON_FOUR 206
#define IDC_BUTTON_FIVE 207
#define IDC_BUTTON_SIX 208
#define IDC_BUTTON_MULTIPLICATION 209
#define IDC_BUTTON_DIVISION 210
#define IDC_BUTTON_ONE 211
#define IDC_BUTTON_TWO 212
#define IDC_BUTTON_THREE 213
#define IDC_BUTTON_SUBTRACTION 214
#define IDC_BUTTON_EQUAL 215
#define IDC_BUTTON_CLEAR 216
#define IDC_BUTTON_ZERO 217
#define IDC_BUTTON_DECIMAL 218
#define IDC_BUTTON_ADDITION 219
#define IDC_BUTTON_SIN 220
#define IDC_BUTTON_COS 221
#define IDC_BUTTON_TAN 222
#define IDC_BUTTON_PI 223
#define IDC_BUTTON_TEN_POWER 224
#define IDC_BUTTON_ASIN 225
#define IDC_BUTTON_ACOS 226
#define IDC_BUTTON_ATAN 227
#define IDC_BUTTON_SQRT 228
#define IDC_BUTTON_SQUARE 229
#define IDC_BUTTON_RECIPROCAL 230
#define IDC_BUTTON_CUBE 231
#define IDC_BUTTON_EXPONENT 232
#define IDC_BUTTON_LOG 233
#define IDC_BUTTON_FACTORIAL 234
#define IDC_BUTTON_LOAD_HISTORY 235





LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX window_var;
    HWND hwnd;
    MSG msg;

    window_var.cbSize        = sizeof(WNDCLASSEX);
    window_var.style         = 0;
    window_var.lpfnWndProc   = WndProc;
    window_var.cbClsExtra    = 0;
    window_var.cbWndExtra    = 0;
    window_var.hInstance     = hInstance;
    window_var.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    window_var.hCursor       = LoadCursor(NULL, IDC_ARROW);
    window_var.hbrBackground = (HBRUSH)(COLOR_WINDOW-1);
    window_var.lpszMenuName  = NULL;
    window_var.lpszClassName = "MainWindowClass";
    window_var.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&window_var)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "MainWindowClass",
        "c",
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, CALC_WIDTH, CALC_HEIGHT,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndStatic;
    static char result_string[50];
    switch (message) {
        case WM_CREATE:
        {
            hwndStatic = CreateWindowEx(
                WS_EX_STATICEDGE, "STATIC", "0",
                WS_VISIBLE | WS_CHILD | SS_RIGHT,
                RESULT_X + screen_GAP, RESULT_Y, RESULT_WIDTH, RESULT_HEIGHT,
                hwnd, (HMENU) IDC_STATIC_RESULT, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "7",
                WS_VISIBLE | WS_CHILD,
                 ROW_GAP , BUTTON_ROW_Y * 1, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_SEVEN, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "8",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + ROW_GAP*2 + 15, BUTTON_ROW_Y * 1, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_EIGHT, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "9",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + 60*1 + ROW_GAP*5, BUTTON_ROW_Y * 1, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_NINE, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "+/-",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60*2 + ROW_GAP*4, BUTTON_ROW_Y * 1, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_NEGATIVE, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "DEL",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60* 3 + ROW_GAP*3, BUTTON_ROW_Y * 1 , BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_DEL, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "4",
                WS_VISIBLE | WS_CHILD,
                 ROW_GAP , BUTTON_ROW_Y * 2, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_FOUR, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "5",
                WS_VISIBLE | WS_CHILD,
               BUTTON_ROW_X  + ROW_GAP*2 + 15, BUTTON_ROW_Y * 2, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_FIVE, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "6",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + 60*1 + ROW_GAP*5, BUTTON_ROW_Y * 2, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_SIX, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "x",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60*2 + ROW_GAP*4, BUTTON_ROW_Y * 2, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_MULTIPLICATION, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "/",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60* 3 + ROW_GAP*3, BUTTON_ROW_Y * 2, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_DIVISION, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "1",
                WS_VISIBLE | WS_CHILD,
                ROW_GAP , BUTTON_ROW_Y * 3, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_ONE, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "2",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + ROW_GAP*2 + 15, BUTTON_ROW_Y * 3, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_TWO, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "3",
                WS_VISIBLE | WS_CHILD,
               BUTTON_ROW_X  + 60*1 + ROW_GAP*5, BUTTON_ROW_Y * 3, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_THREE, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "-",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60*2 + ROW_GAP*4, BUTTON_ROW_Y * 3, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_SUBTRACTION, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "=",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60* 3 + ROW_GAP*3, BUTTON_ROW_Y * 3, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_EQUAL, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "C",
                WS_VISIBLE | WS_CHILD,
                ROW_GAP , BUTTON_ROW_Y * 4, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_CLEAR, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "0",
                WS_VISIBLE | WS_CHILD,
               BUTTON_ROW_X  + ROW_GAP*2 + 15, BUTTON_ROW_Y * 4, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_ZERO, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", ".",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + 60*1 + ROW_GAP*5, BUTTON_ROW_Y * 4, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_DECIMAL, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "+",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60*2 + ROW_GAP*4, BUTTON_ROW_Y * 4, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_ADDITION, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "10^x",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60* 3 + ROW_GAP*3, BUTTON_ROW_Y * 4, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_TEN_POWER, GetModuleHandle(NULL), NULL);
        
             CreateWindow(
                "BUTTON", "sin",
                WS_VISIBLE | WS_CHILD,
                ROW_GAP , BUTTON_ROW_Y * 5, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_SIN, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "cos",
                WS_VISIBLE | WS_CHILD,
               BUTTON_ROW_X  + ROW_GAP*2 + 15, BUTTON_ROW_Y * 5, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_COS, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "tan",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + 60*1 + ROW_GAP*5, BUTTON_ROW_Y * 5, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_TAN, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "pi",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60*2 + ROW_GAP*4, BUTTON_ROW_Y * 5, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_PI, GetModuleHandle(NULL), NULL);

            
            CreateWindow(
                "BUTTON", "x^2",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60* 3 + ROW_GAP*3, BUTTON_ROW_Y * 5, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_SQUARE, GetModuleHandle(NULL), NULL);
           
            CreateWindow(
                "BUTTON", "asin",
                WS_VISIBLE | WS_CHILD,
                 ROW_GAP , BUTTON_ROW_Y * 6, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_ASIN, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "acos",
                WS_VISIBLE | WS_CHILD,
               BUTTON_ROW_X  + ROW_GAP*2 + 15, BUTTON_ROW_Y * 6, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_ACOS, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "atan",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + 60*1 + ROW_GAP*5, BUTTON_ROW_Y * 6, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_ATAN, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "Sqrt",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60*2 + ROW_GAP*4, BUTTON_ROW_Y * 6, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_SQRT, GetModuleHandle(NULL), NULL);
            
            CreateWindow(
                "BUTTON", "n!",
                WS_VISIBLE  | WS_CHILD,
                BUTTON_ROW_X + 60* 3 + ROW_GAP*3, BUTTON_ROW_Y * 6, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_FACTORIAL, GetModuleHandle(NULL), NULL);
           
            CreateWindow(
                "BUTTON", "1/x",
                WS_VISIBLE | WS_CHILD,
                 ROW_GAP , BUTTON_ROW_Y * 7, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_RECIPROCAL, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "x^3",
                WS_VISIBLE | WS_CHILD,
               BUTTON_ROW_X  + ROW_GAP*2 + 15, BUTTON_ROW_Y * 7, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_CUBE, GetModuleHandle(NULL), NULL);

             CreateWindow(
                "BUTTON", "e^x",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X  + 60*1 + ROW_GAP*5, BUTTON_ROW_Y * 7, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_EXPONENT, GetModuleHandle(NULL), NULL);

            CreateWindow(
                "BUTTON", "ln",
                WS_VISIBLE | WS_CHILD,
                BUTTON_ROW_X + 60*2 + ROW_GAP*4, BUTTON_ROW_Y * 7, BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU) IDC_BUTTON_LOG, GetModuleHandle(NULL), NULL);

            
            CreateWindow(
                "BUTTON", "History", WS_VISIBLE | WS_CHILD,
                 BUTTON_ROW_X+ 60*3+ ROW_GAP*2.5, BUTTON_ROW_Y *7, BUTTON_WIDTH+5, BUTTON_HEIGHT,
                 hwnd, (HMENU)IDC_BUTTON_LOAD_HISTORY, NULL, NULL);
    
        }
        break;
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED) {
                switch (LOWORD(wParam)) {
                    case IDC_BUTTON_ZERO:
                        InsertStringNumber('0', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_ONE:
                        InsertStringNumber('1', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_TWO:
                        InsertStringNumber('2', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_THREE:
                        InsertStringNumber('3', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_FOUR:
                        InsertStringNumber('4', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_FIVE:
                        InsertStringNumber('5', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);                    
                    break;
                    case IDC_BUTTON_SIX:
                        InsertStringNumber('6', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_SEVEN:
                        InsertStringNumber('7', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_EIGHT:
                        InsertStringNumber('8', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_NINE:
                        InsertStringNumber('9', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_TEN_POWER:
                        LeftOperand = pow(10, LeftOperand);
                        gcvt(LeftOperand, MAX_DIGITS, strValue);
                        RemoveStringDecimal();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_SQRT:
                        CalculateSquareRoot();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_SQUARE:
                        CalculateSquare();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_CUBE:
                        CalculateCube();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_ADDITION:
                        if (!FinalCalcFlag)
                            CalculateDoubleResult();
                        OperatorType = ADD;
                        InsertOperator('+', strValue);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_SUBTRACTION:
                        if (!FinalCalcFlag)
                            CalculateDoubleResult();
                        OperatorType = SUB;
                        InsertOperator('-', strValue);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_MULTIPLICATION:
                        if (!FinalCalcFlag)
                            CalculateDoubleResult();
                        OperatorType = MUL;
                        InsertOperator('x', strValue);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_DIVISION:
                        if (!FinalCalcFlag)
                            CalculateDoubleResult();
                        OperatorType = DIV;
                        InsertOperator('/', strValue);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_NEGATIVE:
                        if (!OperatorFlag)
                            ValueConversion();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_EQUAL:
                        if (!FinalCalcFlag && !FinalValueConversion) {
                            CalculateDoubleResult();
                            CalculateStringResult();
                        }
                        SetWindowText(hwndStatic, strValue);
                        LeftOperand = RightOperand = atof(strValue);
                        strcpy(result_string, strValue);  // Copy strValue into result_string
                        save_to_history(result_string);   // Save the final result to history
                        SetFocus(hwnd);
                    break;

                    case IDC_BUTTON_LOAD_HISTORY:
                          load_history();  // Load history when "Load History" button is clicked
                    break;
                    case IDC_BUTTON_DECIMAL:
                        InsertDecimalPoint();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_CLEAR:
                        Reset();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_DEL:
                        if (FinalCalcFlag) Reset();
                        DeleteStringNumber(strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_SIN:
                        CalculateTrigonometricFunction(SIN);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_COS:
                        CalculateTrigonometricFunction(COS);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_TAN:
                        CalculateTrigonometricFunction(TAN);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_ACOS:
                        CalculateTrigonometricFunction(ACOS);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_ASIN:
                        CalculateTrigonometricFunction(ASIN);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_ATAN:
                        CalculateTrigonometricFunction(ATAN);
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_LOG:
                        LeftOperand = log(OperandType == LEFT ? LeftOperand : RightOperand);
                        gcvt(LeftOperand, MAX_DIGITS, strValue);
                        RemoveStringDecimal();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_RECIPROCAL:
                        CalculateReciprocal();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_FACTORIAL:
                        LeftOperand = factorial(LeftOperand);
                        gcvt(LeftOperand, MAX_DIGITS, strValue);
                        RemoveStringDecimal();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_PI:
                        InsertStringNumber('3', strValue);
                        InsertStringNumber('.', strValue);
                        InsertStringNumber('1', strValue);
                        InsertStringNumber('4', strValue);
                        InsertStringNumber('1', strValue);
                        InsertStringNumber('5', strValue);
                        InsertStringNumber('9', strValue);
                        InsertStringNumber('2', strValue);
                        InsertStringNumber('6', strValue);
                        InsertStringNumber('5', strValue);
                        InsertStringNumber('3', strValue);
                        InsertStringNumber('5', strValue);
                        InsertStringNumber('9', strValue);
                        CalculateOperand();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                    break;
                    case IDC_BUTTON_EXPONENT:
                        LeftOperand = exp(LeftOperand);
                        gcvt(LeftOperand, MAX_DIGITS, strValue);
                        RemoveStringDecimal();
                        SetWindowText(hwndStatic, strValue);
                        SetFocus(hwnd);
                        break;
                }
            }
        break;
        case WM_KEYDOWN:
                switch (wParam) {
                    case VK_NUMPAD0:
                    case '0':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ZERO, 0);
                        break;
                    case VK_NUMPAD1:
                    case '1':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ONE, 0);
                        break;
                    case VK_NUMPAD2:
                    case '2':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_TWO, 0);
                        break;
                    case VK_NUMPAD3:
                    case '3':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_THREE, 0);
                        break;
                    case VK_NUMPAD4:
                    case '4':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_FOUR, 0);
                        break;
                    case VK_NUMPAD5:
                    case '5':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_FIVE, 0);
                        break;
                    case VK_NUMPAD6:
                    case '6':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SIX, 0);
                        break;
                    case VK_NUMPAD7:
                    case '7':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SEVEN, 0);
                        break;
                    case VK_NUMPAD8:
                    case '8':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EIGHT, 0);
                        break;
                    case VK_NUMPAD9:
                    case '9':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_NINE, 0);
                        break;
                    case VK_ADD:
                    case '+':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ADDITION, 0);
                        break;
                    case VK_SUBTRACT:
                    case '-':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SUBTRACTION, 0);
                        break;
                    case VK_MULTIPLY:
                    case '*':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MULTIPLICATION, 0);
                        break;
                    case VK_DIVIDE:
                    case '/':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_DIVISION, 0);
                        break;
                    case VK_DECIMAL:
                    case '.':
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_DECIMAL, 0);
                        break;
                    case VK_RETURN:
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
                        break;
                    case VK_BACK:
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_DEL, 0);
                        break;
                    case VK_ESCAPE:
                        SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLEAR, 0);
                        break;
                }
                break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}


