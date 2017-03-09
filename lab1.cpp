#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include "resource.h"
BOOL CALLBACK DialogFun(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	char Text[64];
	double x,y;
	const double pi = 3.14159265358979323846;
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;
		case IDC_BUTTON1: 
		case IDC_BUTTON2: 
			SendDlgItemMessage(hwnd, IDC_EDIT1, WM_GETTEXT, 63, (LPARAM)Text); 		
				if (sscanf_s(Text, "%lf", &x)<1)
				{
					MessageBox(hwnd, "Íåâåðíûé ôîðìàò ïåðâîãî îïåðàíäà",
						"Îøèáêà ôîðìàòà", MB_OK | MB_ICONHAND);
					return TRUE;
				}
		
			char func[3];
			if (LOWORD(wParam) == IDC_BUTTON1) { y = sin(x*pi/180); func[0] = 's'; func[1] = 'i'; func[2] = 'n'; }
			if (LOWORD(wParam) == IDC_BUTTON2) { y = cos(x*pi/180); func[0] = 'c'; func[1] = 'o'; func[2] = 's'; }
			sprintf(Text, "%f", y);
			SendDlgItemMessage(hwnd, IDC_EDIT2, WM_SETTEXT, 0, (LPARAM)Text);  		
				sprintf_s(Text, "%c%c%c(%d) = %f", func[0], func[1], func[2], int(x), y);
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)Text);
			return TRUE;
		case IDC_BUTTON3: 
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
			return TRUE;
		}
	}
	return FALSE;
}
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int  nCmdShow)
{
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogFun);
	return 0;
}
