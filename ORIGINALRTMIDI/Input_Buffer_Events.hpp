#pragma once
#include <windows.h>
#include <stdio.h>

//***
#define WIDTH 70
#define HEIGHT 35

HANDLE wHnd; /* write (output) handle */
HANDLE rHnd; /* read (input handle */


			 //***
int test1(const int mwidth, const int mheight);
int test();

void midi1_sendPrgChange(int thechannel, int prgnumber);
void sendMidiBank(int thechannel, int thebank);

HANDLE hStdin;
DWORD fdwSaveOldMode;
void setBpm(int updown);
void SetPosition(int X, int Y);

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
int MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

bool ispressed = 0;
extern int posX;
extern int posY;
extern int myMouseB;
extern int myKey;
//extern int thebpm;
//posX = 0;
//posY = 0;
//myMouseB = 0;

int input_Buffer_Events_main()
{
	/* int posX=0;
	 int posY =0;
     int myMouseB =0;
	 int myKey=0 ;*/

	

	bool leftispressed = 0;
	int counter = 0;

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	//int counter = 0;

	// Get the standard input handle. 

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		printf("GetStdHandle");

	// Save the current input mode, to be restored on exit. 

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		printf("GetConsoleMode");

	fdwMode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hStdin, fdwMode))
		printf("SetConsoleMode");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	//fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		printf("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 

//	while (1)
	//{
		// Wait for the events. 

	if (!ReadConsoleInput(
		hStdin,      // input buffer handle 
		irInBuf,     // buffer to read into 
		128,         // size of read buffer 
		&cNumRead)) // number of records read 
		printf("ReadConsoleInput");

	// Dispatch the events to the appropriate handler. 

	for (i = 0; i < cNumRead; i++)
	{
		switch (irInBuf[i].EventType)
		{
		case KEY_EVENT: // keyboard input 
			KeyEventProc(irInBuf[i].Event.KeyEvent);

			break;

		case MOUSE_EVENT: // mouse input 
			return MouseEventProc(irInBuf[i].Event.MouseEvent);
			
			break;

		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
			ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
			break;

		case FOCUS_EVENT:  // disregard focus events 

		case MENU_EVENT:   // disregard menu events 
			break;

		default:
			printf("Unknown event type");
			break;
		}
	}
	//} while

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}

VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	//printf("Key event: ");

	if (ker.bKeyDown) {
		myKey = 1;
		//printf("key pressed\n");
		if (ker.uChar.AsciiChar == 'a') {
			//ispressed = ++count % 2;

			sendMidiBank(0, 7);                 //channel - Bank number              
			midi1_sendPrgChange(0, 0);			//channel - Prg Number	
			
			sendMidiBank(1, 1);                 //channel - Bank number              
			midi1_sendPrgChange(1, 46);

			sendMidiBank(2, 1);                 //channel - Bank number              
			midi1_sendPrgChange(2, 52);
			
			sendMidiBank(3, 3);                 //channel - Bank number              
			midi1_sendPrgChange(3, 2);
			
			sendMidiBank(4, 1);                 //channel - Bank number              
			midi1_sendPrgChange(4, 2);
			
			sendMidiBank(5, 1);                 //channel - Bank number              
			midi1_sendPrgChange(5, 1);
		}
	}
	else {
		//	printf("key released\n");
		myKey = 0;
	}
}

int MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");
	int wheelX = 0;
	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			//printf("left button press \n");
			//SetPosition(mer.dwMousePosition.X, mer.dwMousePosition.Y);
			//setColor(10);
			//ispressed = 1;
			posX = mer.dwMousePosition.X;
			posY = mer.dwMousePosition.Y;
			myMouseB = 1;
			//print_colors();
			//printf("*");
			return 1;
			//printf("left button press \n");

			//printf("left clicked at x=%d, y=%d\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			//printf("right button press \n");
			myMouseB = 2;
			posX = mer.dwMousePosition.X;
			posY = mer.dwMousePosition.Y;
			return 1;
		}
		else
		{
			//	printf("button press\n");
			myMouseB = 0;
			ispressed = 0;
		}
		break;
	case DOUBLE_CLICK:
		//		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		//	printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		//printf("mouse moved\n");
		if (ispressed) {
			//SetPosition(mer.dwMousePosition.X, mer.dwMousePosition.Y);
			//
			//printf("*");
		}
		break;
	case MOUSE_WHEELED:
		//printf("vertical mouse wheel\n");
		wheelX = mer.dwButtonState;
		if (wheelX > 0) {
			//printf("PO");
			setBpm(1);
		}
		else {
			//printf("NE");
			setBpm(0);

		}

		break;
	default:
		printf("unknown\n");
		break;
	}
	return 0;
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	//printf("Resize event\n");
	//printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);

	//test();
	int muh = wbsr.dwSize.X;
	//test1(wbsr.dwSize.X, wbsr.dwSize.Y);
	HANDLE output_handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (output_handle == INVALID_HANDLE_VALUE)
		printf("FALSE");
	CONSOLE_SCREEN_BUFFER_INFO info = {};
	if (::GetConsoleScreenBufferInfo(output_handle, &info) == FALSE)
		printf("FALSE");
	size_t width = info.srWindow.Right - info.srWindow.Left;
	size_t height = info.srWindow.Bottom - info.srWindow.Top;

	//printf("Xs %d Y %d rows.\n", width, height);
	//bool suc = SetWindowSize(width + 1, height + 1);
	//test1(width, height);


}

int test() {
	int r, g, b;
	char s[10] = "HOHOHO";
	const int max = 255;
	for (int colnum = 0; colnum < max; colnum++) {
		r = 255 - (colnum * 255 / max - 1);
		g = (colnum * 510 / max - 1);
		b = (colnum * 255 / max - 1);
		if (r > 255) r = 510 - r;
		if (g > 255) g = 510 - g;
		if (b > 255) b = 510 - b;
		//printf("\x1b[38;2;%d;%d;%dmTRUECOLOR\x1b[0m\n",r,g,b);
		//printf("\x1b[48;2;%d;%d;%dmTRUECOLOR\x1b[0m\n",r,g,b);
		//printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dmTRUECOLOR\x1b[0m\n",r,g,b,b,r,g);
		printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dmTRUECOLOR\x1b[0m\n", r, g, b, r, g, b);

		//printf ("\033[48;2;%d;%d;%dmYUHUU\n"), r, g, b;
		//printf ("\033[38;2;%d;%d;%dmHOHO\n"), 255 - r, 255 - g, 255 - b;
	//	printf ("%s\033[0m", s);
	}

	return 444;
}

int test1(const int mwidth, const int mheight) {
	int x, y;

	//srand(time(0));

	/* Window size coordinates, be sure to start index at zero! */
	SMALL_RECT windowSize = { 0, 0, mwidth - 1, mheight - 1 };

	/* A COORD struct for specificying the console's screen buffer dimensions */
	COORD bufferSize = { mwidth, mheight };

	/* Setting up different variables for passing to WriteConsoleOutput */
	COORD characterBufferSize = { mwidth, mheight };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, mwidth - 1, mheight - 1 };

	/* A CHAR_INFO structure containing data about a single character */
	//const int mewidth = mwidth;
	//const int mewidth = 5;


	//CHAR_INFO *muh= new CHAR_INFO[mwidth];

	//CHAR_INFO consoleBuffer[WIDTH * HEIGHT];
	CHAR_INFO* consoleBuffer = new CHAR_INFO[mwidth * mheight];

	/* initialize handles */
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	/* Set the console's title */
	//SetConsoleTitle("Our shiny new title!");

	/* Set the window size */
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	for (y = 0; y < mheight; ++y)
	{
		for (x = 0; x < mwidth; ++x)
		{
			//consoleBuffer[x + mwidth * y].Char.AsciiChar = (unsigned char)219;
			consoleBuffer[x + mwidth * y].Char.AsciiChar = (unsigned char)97;
			consoleBuffer[x + mwidth * y].Attributes = rand() % 256;
		}
	}

	/* Write our character buffer (a single character currently) to the console buffer */
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);

	getchar();

	return 5;
}
