#include "framework.h"
#include "Project14.h"

#define MAX_LOADSTRING 100
#define THRESHOLD 50

// Глобальные переменные:
HINSTANCE hInst;
HWND hWndStatic;

// Функция генерации случайного вектора
void GenerateRandomVector(int& dx, int& dy) {
    // Генерация случайного числа в диапазоне [-10, 10]
    dx = rand() % 21 - 10;
    dy = rand() % 21 - 10;
}

// Функция перемещения статика
void MoveStatic(int x, int y) {
    RECT rect;
    GetWindowRect(hWndStatic, &rect);

    // Ограничение перемещения статика в пределах диалогового окна
    if (rect.left + x < 0) {
        x = -rect.left;
    }
    else if (rect.right + x > GetSystemMetrics(SM_CXSCREEN)) {
        x = GetSystemMetrics(SM_CXSCREEN) - rect.right;
    }
    if (rect.top + y < 0) {
        y = -rect.top;
    }
    else if (rect.bottom + y > GetSystemMetrics(SM_CYSCREEN)) {
        y = GetSystemMetrics(SM_CYSCREEN) - rect.bottom;
    }

    // Перемещение статика
    SetWindowPos(hWndStatic, NULL, rect.left + x, rect.top + y, 0, 0, SWP_NOSIZE);
}

// ...

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_MOUSEMOVE: {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        RECT rect;
        GetWindowRect(hWndStatic, &rect);

        int dx = x - (rect.left + rect.right) / 2;
        int dy = y - (rect.top + rect.bottom) / 2;

        int distance = sqrt(dx * dx + dy * dy);

        if (distance < THRESHOLD) {
            // "Убегание" статика
            GenerateRandomVector(dx, dy);
            MoveStatic(dx, dy);
        }
        break;
    }
                     // ...

                     return DefWindowProc(hWnd, message, wParam, lParam);
    }

    // ...

    int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPWSTR lpCmdLine,
        _In_ int nCmdShow) {
        // ...

        // Создание статического элемента управления
        hWndStatic = CreateWindowEx(0, WC_STATIC, "Убегающий статик", WS_CHILD | WS_VISIBLE,
            0, 0, 100, 50, hWnd, NULL, hInstance, NULL);

        // ...

        return (int)msg.wParam;
    }
