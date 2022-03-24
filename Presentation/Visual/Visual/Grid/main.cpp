#include <windows.h>
#include<tchar.h>
#include<commctrl.h>

extern "C"
{
	#include "simplegrid.h"
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void LoadGrid4(HWND);

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

    HWND grid=New_SimpleGrid(hwnd,2);

	MoveWindow(grid,0,0,640,480,true);
	ShowWindow(grid,true);
	LoadGrid4(grid);


	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
#define NELEMS(a) (int)(sizeof(a) / sizeof((a)[0]))
void LoadGrid4(HWND hGrid)
{
    // Set Row height to accommodate the graphics
    SimpleGrid_SetRowHeight(hGrid,34);

    //
    // Create Columns
    //

    // Column type
    // Column header text
    // Optional data (ex: combobox choices)
    SGCOLUMN lpColumns[] = {
        GCT_COMBO, "Combo Column",
          (LPSTR)"Ford\0Chevy\0Zaparozhets\0Volkswagen\0Toyota\0Honda\0Citroen\0Fiat\0Volvo\0",
        GCT_BUTTON, "Button Column", NULL,
        GCT_LINK, "Link Column", NULL
    };

    // Add the columns
    for(int k = NELEMS(lpColumns), m = 0; 0 < k; --k, ++m)
    {
        SimpleGrid_AddColumn(hGrid, &lpColumns[m]);
        SimpleGrid_SetColWidth(hGrid, m, 100);
    }

    //
    // Add some rows
    //
    for(int i = 0; i < 2; ++i)
        SimpleGrid_AddRow(hGrid, ""); //Don't care about row header text

    //
    // Set cells to data
    //

    // Column number
    // Row number
    // Item (cell) value
    SGITEM lpItems[] = {
        // Combo column
        0, 0, (LPARAM)"Zaparozhets",
        0, 1, (LPARAM)"Citroen",

        // Button column
        1, 0, (LPARAM)"#1 On",
        1, 1, (LPARAM)"#2 On",

        // Link column
        3, 0, (LPARAM)"The Code Project\0http:\\\\www.codeproject.com\0",
        3, 1, (LPARAM)"Information Technology\0http:\\\\www.thedailywtf.com\0"
    };

    for(int i = 0; i < NELEMS(lpItems); ++i)
    {
        SimpleGrid_SetItemData(hGrid, &lpItems[i]);
    }

}