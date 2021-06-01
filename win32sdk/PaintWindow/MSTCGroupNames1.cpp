#include <Windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    static TCHAR szClassName[] = TEXT("Window");
    static TCHAR szWindowCaption[] = TEXT("MSTC GROUP LIST");

    WNDCLASSEX wndEx;
    MSG msg;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hWnd = NULL;

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if(hBrush == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to brush"), TEXT("GetStockObject"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    if(hCursor == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to cursor"), TEXT("LoadCursor"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(hIcon == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    if(hIconSm == NULL){
        MessageBox((HWND)NULL, TEXT("Failed to get handle to icon"), TEXT("LoadIcon"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

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
    wndEx.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL, TEXT("Failed to register class window"), TEXT("RegisterClassEx"), MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szClassName,
        szWindowCaption,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

    if(hWnd == NULL){
        MessageBox((HWND)NULL, TEXT("failed to create window handle"), TEXT("CreateWindowEx"), MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, (HWND)NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    static int cxClient;
    static int cyClient;
    static int cxChar;
    static int cyChar;

    TCHAR *GroupList[] = {
                            TEXT("Dennis Ritche Group"), 
                            TEXT("Ken Thompson Group"), 
                            TEXT("Alan Turing Group"),
                            TEXT("Jon Von Neumann"),
                            TEXT("David Cutler Group"),
                            TEXT("Lady Ada Lovelace Group"),
                            TEXT("Donald Kanuth Group"),
                            TEXT("Linus Torvalds Group"),
                            TEXT("Helen Custer Group"),    
                        };

    HDC hdc = NULL;
    TEXTMETRIC tm;
    PAINTSTRUCT ps;

    switch(uMsg){
        case WM_CREATE:
            hdc = GetDC(hWnd);
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hWnd, hdc);
            hdc = NULL;
            break;

        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            SetTextAlign(hdc, TA_LEFT | TA_TOP);
            TextOut(hdc, 0, 0, GroupList[0], lstrlen(GroupList[0]));
            SetTextAlign(hdc, TA_CENTER | TA_TOP);
            TextOut(hdc, cxClient/2, 0, GroupList[1], lstrlen(GroupList[1]));
            SetTextAlign(hdc, TA_RIGHT | TA_TOP);
            TextOut(hdc, cxClient, 0, GroupList[2], lstrlen(GroupList[2]));
            SetTextAlign(hdc, TA_LEFT | TA_CENTER);
            TextOut(hdc, 0, cyClient/2, GroupList[3], lstrlen(GroupList[3]));
            SetTextAlign(hdc, TA_CENTER | TA_CENTER);
            TextOut(hdc, cxClient/2, cyClient/2, GroupList[4], lstrlen(GroupList[4]));
            SetTextAlign(hdc, TA_RIGHT | TA_CENTER);
            TextOut(hdc, cxClient, cyClient/2, GroupList[5], lstrlen(GroupList[5]));
            SetTextAlign(hdc, TA_LEFT | TA_BOTTOM);
            TextOut(hdc, 0, cyClient, GroupList[6], lstrlen(GroupList[6]));
            SetTextAlign(hdc, TA_CENTER | TA_BOTTOM);
            TextOut(hdc, cxClient/2, cyClient, GroupList[7], lstrlen(GroupList[7]));
            SetTextAlign(hdc, TA_RIGHT | TA_BOTTOM);
            TextOut(hdc, cxClient, cyClient, GroupList[8], lstrlen(GroupList[8]));
            EndPaint(hWnd, &ps);
            hdc = NULL;
            break;

        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}