#include <windows.h>
//.\g++ -o list.exe list.c -mwindows
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Registra a classe da janela
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInstance, NULL, NULL, NULL, NULL, "ListBox Example", NULL };
    ::RegisterClassEx(&wc);

    // Cria a janela
    HWND hwnd = ::CreateWindow(wc.lpszClassName, "ListBox Example", WS_OVERLAPPEDWINDOW, 100, 100, 600, 400, NULL, NULL, wc.hInstance, NULL);

    // Cria a list box
    HWND hListBox = ::CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | LBS_HASSTRINGS | WS_VSCROLL | ES_AUTOVSCROLL, 0, 0, 400, 350, hwnd, NULL, hInstance, NULL);

    // Preenche a list box com os arquivos e diretórios do diretório atual
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile("*.*", &fd);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
            {
                ::SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)fd.cFileName);
            }
            else
            {
                ::SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)fd.cFileName);
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }

    // Exibe a janela
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Loop de mensagens
    MSG msg;
    while (::GetMessage(&msg, NULL, 0, 0))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    // Libera recursos
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            if (HIWORD(wParam) == LBN_SELCHANGE)
            {
                // Obtém o índice do item selecionado
                int nIndex = ::SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                // Obtém o texto do item selecionado
                char szText[MAX_PATH];
                ::SendMessage((HWND)lParam, LB_GETTEXT, nIndex, (LPARAM)szText);

                // Exibe uma mensagem box com o nome do arquivo selecionado
                ::MessageBox(hwnd, szText, "Arquivo selecionado", MB_OK);
            }
            break;

        case WM_DESTROY:
            ::PostQuitMessage(0);
            break;
            case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Define a cor de fundo da janela para azul
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            // Define a cor das linhas para branco
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);
            
            // Desenha as linhas com base nas coordenadas fornecidas
            
            
            // Libera os recursos utilizados
            DeleteObject(hPen);
            EndPaint(hwnd, &ps);
            break;
        }

        default:
            return ::DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}
