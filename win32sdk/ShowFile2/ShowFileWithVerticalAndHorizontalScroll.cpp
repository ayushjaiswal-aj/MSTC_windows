#include <Windows.h>
#include <stdio.h>
#include "StringVector.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileName);
void ReleaseAll(void);

PSTRINGVECTOR gpStrVec = NULL;
LPSTR glpCmdLine = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iShowCmd)
{
    static TCHAR szClassName[] = TEXT("Standard Window");
    static TCHAR szWindowCaption[] = TEXT("ShowFile");
    glpCmdLine = lpCmdLine;

    WNDCLASSEX wndEx;
    MSG msg;
    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hWnd = NULL;
    ATOM bIsWindowClassRegistered = 0;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    FAIL_EXIT_IF(hBrush == NULL, "Failed to get handle to brush", "GetStockObject");

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    FAIL_EXIT_IF(hCursor == NULL, "Failed to get handle to cursor", "LoadCursor");

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIcon == NULL, "Failed to get handle to icon", "LoadIcon");

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIconSm == NULL, "Failed to get handle to icon", "LoadIcon");

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
    FAIL_EXIT_IF(bIsWindowClassRegistered == 0, "Failed to register window class", "RegisterClassEx");

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName, 
        szWindowCaption,
        WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_VSCROLL | WS_HSCROLL | WS_CAPTION,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        350,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    FAIL_EXIT_IF(hWnd == NULL, "Failed to get handle to window", "CreateWindowEx");

    ShowWindow(hWnd, iShowCmd);
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
    static int iVScrollPos = 0, iHScrollPos = 0;
    static int iMaxWidth;
    static int iHMax;
    int iCnt;

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
            SetScrollPos(hWnd, SB_VERT, iVScrollPos, TRUE);

            iMaxWidth = 48 * cxChar + 12 * cxCaps;
            iHMax = 2 + iMaxWidth/cxChar;
            SetScrollRange(hWnd, SB_HORZ, 0, iHMax, FALSE);
            SetScrollPos(hWnd, SB_HORZ, iHScrollPos, TRUE);
            break;
        
        case WM_VSCROLL:
            switch(LOWORD(wParam))
            {
                case SB_LINEUP:
                    iVScrollPos -= 1;
                    break;
                    
                case SB_LINEDOWN:
                    iVScrollPos += 1;
                    break;
                
                case SB_PAGEDOWN:
                    iVScrollPos += (cyClient/cyChar);
                    break;
                
                case SB_PAGEUP:
                    iVScrollPos -= (cyClient/cyChar);
                    break;
                
                case SB_THUMBPOSITION:
                    iVScrollPos = HIWORD(wParam);
                    break;
                default:
                    break;
            }
            if(iVScrollPos < 0)
            {
                iVScrollPos = 0;
            }
            else if(iVScrollPos > gpStrVec->iVectorSize - 1)
            {
                iVScrollPos = gpStrVec->iVectorSize - 1;
            }
            else 
            {
                SetScrollPos(hWnd, SB_VERT, iVScrollPos, TRUE);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        
        case WM_HSCROLL:
            switch(LOWORD(wParam))
            {
                case SB_LINELEFT:
                    iHScrollPos -= 1;
                    break;
                    
                case SB_LINERIGHT:
                    iHScrollPos += 1;
                    break;
                
                case SB_PAGELEFT:
                    iHScrollPos += (cxClient/cxChar);
                    break;
                
                case SB_PAGERIGHT:
                    iHScrollPos -= (cxClient/cxChar);
                    break;
                
                case SB_THUMBPOSITION:
                    iHScrollPos = LOWORD(wParam);
                    break;
                
                default:
                    break;
            }
            if(iHScrollPos < 0)
            {
                iHScrollPos = 0;
            }
            else if(iHScrollPos > iHMax)
            {
                iHScrollPos = iHMax;
            }
            else 
            {
                SetScrollPos(hWnd, SB_HORZ, cxChar * iHScrollPos, TRUE);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            for(iCnt = 0; iCnt < gpStrVec->iVectorSize; iCnt++)
            {
                TextOutA(hdc, 0, (iCnt - iVScrollPos) * cyChar, gpStrVec->ppString[iCnt], strlen(gpStrVec->ppString[iCnt]));
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
    #define BUFFERSIZE 128

    FILE *fp = NULL;
    CHAR chBuffer[BUFFERSIZE];
    memset(chBuffer, 0, BUFFERSIZE);
    PCHAR pStr = NULL;
    int iStrlen;

    gpStrVec = CreateStringVector();
    
    fp = fopen(lpFileName, "r");
    FAIL_EXIT_IF(fp == NULL, "Failed to open file", "fopen");
    while(fgets(chBuffer, BUFFERSIZE, fp) != NULL){
        iStrlen = strnlen_s(chBuffer, BUFFERSIZE);
        pStr = (PCHAR)Xcalloc(1, iStrlen + 1);
        strncpy(pStr, chBuffer, iStrlen);
        PushBack(gpStrVec, pStr);
        memset(chBuffer, 0, BUFFERSIZE);
    }

    fclose(fp);
    fp = NULL;

    return gpStrVec;
}

void ReleaseAll()
{
    if(gpStrVec != NULL)
    {
        DestroyStringVector(gpStrVec);
        gpStrVec = NULL;
    }
}