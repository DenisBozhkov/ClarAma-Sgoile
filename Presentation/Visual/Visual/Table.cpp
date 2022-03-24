#include "Table.h"
struct CellData
{
	HWND content;
};
struct ColumnData
{
	std::string Text;
	HWND content;
};
struct TableData
{
	std::vector<ColumnData> columns;
	std::vector<std::string> rows;
	std::vector<std::vector<CellData>> cells;
};
LRESULT CALLBACK TableWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
	static TableData* pData;
	switch(Message)
	{
		case WM_NCCREATE:
			pData = new TableData;
            if(pData==NULL)
                return FALSE;
            SetWindowLongPtr(hwnd,0,(LONG_PTR)pData);
            return TRUE;
        case WM_NCDESTROY:
            if(pData != NULL)
                delete pData;
            return 0;
		case WM_PAINT:
		    PAINTSTRUCT ps;
		    HDC hdc;
		    RECT rect;

		    GetClientRect(hwnd, &rect);

		    hdc = BeginPaint(hwnd, &ps);
		    SetTextColor(hdc, RGB(0,0,0));
		    SetBkMode(hdc, TRANSPARENT);
		    DrawText(hdc, _T("Hello World!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		    EndPaint(hwnd, &ps);
			break;
		default:
			return DefWindowProc(hwnd,Message,wParam,lParam);
	}
	return 0;
}


void RegisterTableClass()
{
	WNDCLASSEX wc;
	wc.cbSize=sizeof(WNDCLASSEX);
	wc.style=CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc=TableWndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=sizeof(TableData*);
	wc.hInstance=NULL;
	wc.hIcon=NULL;
 	wc.hCursor=LoadCursor(NULL, IDC_ARROW);
 	wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
 	wc.lpszMenuName=NULL;
	wc.lpszClassName=WC_TABLE;
	wc.hIconSm=NULL;
	RegisterClassEx(&wc);
}
void UnregisterTableClass()
{
	UnregisterClass(WC_TABLE,NULL);
}