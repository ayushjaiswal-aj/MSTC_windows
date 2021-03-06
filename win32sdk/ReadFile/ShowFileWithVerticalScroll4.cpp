#include <Windows.h>
#include <stdio.h>
#include "StringVector.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ReleaseAll(void);
PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileLine);
/*
#define FAIL_EXIT_IF(COND,MSG,CAPTION)  do\
                                        {\
                                            if(COND == TRUE)\
                                            {\
                                                MessageBox((HWND)NULL, TEXT(MSG), TEXT(CAPTION), MB_ICONERROR);\
                                                ReleaseAll();\
                                                ExitProcess(EXIT_FAILURE);\
                                            }\
                                        }while(0)
*/
PSTRINGVECTOR gpStrVec = NULL;
LPSTR glpCmdLine = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("Standard window");
    static TCHAR szWindowCaption[] = TEXT("Show File");
    HWND hWnd = NULL;
    ATOM bIsWindowClassRegistered = 0;

    glpCmdLine = lpCmdLine;

    WNDCLASSEX wndEx;
    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    HBRUSH hBrush = NULL;
    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    FAIL_EXIT_IF(hBrush == NULL, "Failed to get handle to brush", "GetStockObject");

    HCURSOR hCursor = NULL;
    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    FAIL_EXIT_IF(hCursor == NULL, "Failed to get handle to cursor", "LoadCursor");

    HICON hIcon = NULL;
    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIcon == NULL, "Failed to get handle to icon", "LoadIcon");

    HICON hIconSm = NULL;
    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIconSm == NULL, "failed to get handle to icon", "LoadIcon");

    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.hInstance = hInstance;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    bIsWindowClassRegistered = RegisterClassEx(&wndEx);
    FAIL_EXIT_IF(bIsWindowClassRegistered == 0, "Failed to  register window class", "RegisterClassEx");

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCaption,
        WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION | WS_VSCROLL,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    FAIL_EXIT_IF(hWnd == NULL, "Failed to create handle to window", "CreateWindowEx");
    
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ReleaseAll();
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    static int cxChar, cyChar, cxCaps;
    static int nVScrollPos = 0;
    int nCnt;

    HDC hdc = NULL;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch(uMsg)
    {
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        
        case WM_CREATE: 
            hdc = GetDC(hWnd);
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
            ReleaseDC(hWnd, hdc);
            hdc = NULL;
            gpStrVec = ReadFileInMemory(glpCmdLine);
            SetScrollRange(hWnd, SB_VERT, 0, gpStrVec->iVectorSize, FALSE);
            SetScrollPos(hWnd, SB_VERT, nVScrollPos, TRUE);
            break;
        
        case WM_VSCROLL:
            switch(LOWORD(wParam))
            {
                case SB_LINEUP: 
                    nVScrollPos -= 1;
                    break;
                
                case SB_LINEDOWN:
                    nVScrollPos += 1;
                    break;
                
                case SB_PAGEUP:
                    nVScrollPos -= (cyClient/cyChar);
                    break;
                
                case SB_PAGEDOWN:
                    nVScrollPos += (cyClient/cyChar);
                    break;
                
                case SB_THUMBPOSITION:
                    nVScrollPos = HIWORD(wParam);
                    break;
                
                default:
                    break;
            }
            if(nVScrollPos < 0)
            {
                nVScrollPos = 0;
            }
            else if(nVScrollPos > gpStrVec->iVectorSize - 1)
            {
                nVScrollPos = gpStrVec->iVectorSize-1;
            }
            else 
            {
                SetScrollPos(hWnd, SB_VERT, nVScrollPos, TRUE);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            for(nCnt = 0; nCnt < gpStrVec->iVectorSize; nCnt++)
            {
                TextOutA(hdc, 10, (nCnt - nVScrollPos)*cyChar, gpStrVec->ppString[nCnt], strlen(gpStrVec->ppString[nCnt]));
            }
            EndPaint(hWnd, &ps);
            hdc = NULL;
            break;

        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileName)
{
    #define BUFFER_SIZE 128

    int strlen;
    FILE *fp = NULL;
    CHAR chBuffer[BUFFER_SIZE];
    memset(chBuffer, 0, BUFFER_SIZE);
    PCHAR pStr = NULL;

    fp = fopen(lpFileName, "r");
    FAIL_EXIT_IF(fp == NULL, "failed to open file", "fopen");

    gpStrVec = CreateStringVector();

    while(fgets(chBuffer, BUFFER_SIZE, fp) != NULL)
    {
        strlen = strnlen_s(chBuffer, BUFFER_SIZE);
        pStr = (PCHAR)Xcalloc(1, strlen + 1);
        strncpy(pStr, chBuffer, strlen);
        PushBack(gpStrVec, pStr);
        memset(chBuffer, 0, BUFFER_SIZE);
    }
    fclose(fp);
    fp = NULL;

    return (gpStrVec);
}

void ReleaseAll(void)
{
    if(gpStrVec != NULL)
    {
        DestroyStringVector(gpStrVec);
        gpStrVec = NULL;
    }
}

