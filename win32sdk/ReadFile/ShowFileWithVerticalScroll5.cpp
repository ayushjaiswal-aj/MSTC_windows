#include <stdio.h>
#include <Windows.h>
#include "StringVector.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib")

PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileName);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ReleaseAll(void);

PSTRINGVECTOR gpStrVec = NULL;
LPSTR glpCmdLine = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("Standard Window");
    static TCHAR szWindowCaption[] = TEXT("Show File");
    
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
    FAIL_EXIT_IF(hBrush == NULL, "Failed to get handle to hbrush", "GetStockObject");

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    FAIL_EXIT_IF(hCursor == NULL, "Failed to get handle to cursor", "LoadCursor");

    hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIcon == NULL, "failed to get handle to icon", "LoadIcon");

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    FAIL_EXIT_IF(hIconSm == NULL, "Failed to get handle to icon", "loadIcon");

    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.hInstance = hInstance;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    bIsWindowClassRegistered = RegisterClassEx(&wndEx);
    FAIL_EXIT_IF(bIsWindowClassRegistered == NULL, "Failed to register window class", "RegisterClassEx");

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCaption,
        WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_VSCROLL | WS_CAPTION,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    FAIL_EXIT_IF(hWnd == NULL, "Failed to get handle to window", "CreateWindowEx");

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, (HWND)NULL, 0, 0))
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
            cyChar = tm.tmHeight;
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
                nVScrollPos = gpStrVec->iVectorSize - 1;
            }
            else 
            {
                SetScrollPos(hWnd, SB_VERT, nVScrollPos, TRUE);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
            
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            for (nCnt = 0; nCnt < gpStrVec->iVectorSize; nCnt++)
            {
                TextOutA(hdc, 10, (nCnt - nVScrollPos) * cyChar, gpStrVec->ppString[nCnt], strlen(gpStrVec->ppString[nCnt]));
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

    int nStrlen;
    FILE *fp;
    PCHAR pStr = NULL;
    CHAR chBuffer[BUFFERSIZE];
    memset(chBuffer, 0, BUFFERSIZE);
    
    gpStrVec = CreateStringVector();
    fp = fopen(lpFileName, "r");
    FAIL_EXIT_IF(fp == NULL, "failed to open file", "fopen");
    
    while(fgets(chBuffer, BUFFERSIZE, fp) != NULL)
    {
        nStrlen = strnlen_s(chBuffer, BUFFERSIZE);
        pStr  = (PCHAR)Xcalloc(1, nStrlen+1);
        strncpy(pStr, chBuffer, nStrlen);
        PushBack(gpStrVec, pStr);
        memset(chBuffer, 0, BUFFERSIZE);
    }

    fclose(fp);
    fp = NULL;
    return gpStrVec;
}

void ReleaseAll(void)
{
    if(gpStrVec != NULL)
    {
        DestroyStringVector(gpStrVec);
        gpStrVec = NULL;
    }
}