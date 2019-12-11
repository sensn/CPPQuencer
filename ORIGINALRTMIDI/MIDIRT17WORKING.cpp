//*****************************************//
//  midiout.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI output.
//
//*****************************************//

#include <chrono>
#include <cstdlib>
#include <iostream>
#include "rtmidi17/rtmidi17.hpp"
//#include "rtmidi17.hpp"
#include <thread>

///****Cquencer Includes****//
//#include <cstddef>
#include <stdlib.h>
#include "rlutil.h"
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include "Input_Buffer_Events.hpp"
#include "DS.c"
//**HEADER
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>  
#include "math.h"
#include "string.h"

#include "rlutil.h"
//#include "../RtMidi17-master/rtmidi17/rtmidi17.hpp"
#define _USE_MATH_DEFINES



#define MAX 35
#define X_COUNT 8
#define Y_COUNT 16

void draw_buttons(int xb, int yb, int yoffset1, int xoff);
//int playSequence(struct dat lib[X_COUNT + 1][Y_COUNT + 1])
int input_Buffer_Events_main();

void midi1_all_notesoff();
void midi1_noteout(int chan, int noten, int velo);

struct dat
{
	int posX;
	int posY;
	int triggerX;
	int notenumber;
	char playerChr;
	char name[MAX];

	struct date {
		int day;
		int month;
		int year;
	}date;
};
typedef struct {
	int trigger[16];
	int notenumber;
	int vel;
	int channel;

}Room;
struct channel {
	struct dat lib[X_COUNT + 1][Y_COUNT + 1] = { '\0' };
};
typedef struct {
	int screenX;
	int screenY;
	//dat lib[8];
	Room room[8];
}House;
//***
typedef struct IDirectSound* LPDIRECTSOUND;
//***
//int playSequence(struct dat lib[Y_COUNT + 1][X_COUNT]);

//int input_Buffer_Events_main();
int call_raster_main();
void draw_buttons(int xb, int yb, int yoffset1);


extern int posX;
extern int posY;
extern int myMouseB;
extern int thebpm;
extern int myKey;
int posX = 0;
int posY = 0;
int myMouseB = 0;
int thebpm = 150;
int myKey = 0;
double ms;
double dur;
double swing = 0;
double theswing = 0.33;

//asd
int xs = X_COUNT + 1;
int ys = Y_COUNT + 1;

int yoffset = 1;
//int s_main(const char** fpath, int nr);
const char* fpath[] = { "C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\snare.wav", "C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\kick.wav" };
int active = 0;
channel chan[8];
rtmidi::midi_out midiout;
std::vector<unsigned char> message(3, 0);     //the Midi message Container
std::vector<unsigned char> message1(2, 0);     //the Midi message Container
int playSequence(dat[9][17]);



// This function should be embedded in a try/catch block in case of
// an exception.  It offers the user a choice of MIDI ports to open.
// It returns false if there are no ports available.
bool chooseMidiPort(rtmidi::midi_out& rtmidi)
{
	std::cout << "\nWould you like to open a virtual output port? [y/N] ";

	std::string keyHit;
	std::getline(std::cin, keyHit);
	if (keyHit == "y")
	{
		rtmidi.open_virtual_port();
		return true;
	}

	std::string portName;
	unsigned int i = 0, nPorts = rtmidi.get_port_count();
	if (nPorts == 0)
	{
		std::cout << "No output ports available!" << std::endl;
		return false;
	}

	if (nPorts == 1)
	{
		std::cout << "\nOpening " << rtmidi.get_port_name() << std::endl;
	}
	else
	{
		for (i = 0; i < nPorts; i++)
		{
			portName = rtmidi.get_port_name(i);
			std::cout << "  Output port #" << i << ": " << portName << '\n';
		}

		do
		{
			std::cout << "\nChoose a port number: ";
			std::cin >> i;
		} while (i >= nPorts);
	}

	std::cout << "\n";
	// rtmidi.open_port(i);
	rtmidi.open_port(0);
	
	return true;
}

int main1(void) try
{
	using namespace std::literals;

	//std::vector<unsigned char> message;

	// Call function to select port.
	if (chooseMidiPort(midiout) == false)
		return 0;

	// Send out a series of MIDI messages.

	// Program change: 192, 5
	//message.push_back(192);
	//message.push_back(5);
	//midiout.send_message(message);

	//std::this_thread::sleep_for(500ms);

	//message[0] = 0xF1;
	//message[1] = 60;
	//midiout.send_message(message);

	//// Control Change: 176, 7, 100 (volume)
	//message[0] = 176;
	//message[1] = 7;
	//message.push_back(100);
	//midiout.send_message(message);

	//// Note On: 144, 64, 90
	//message[0] = 144;
	//message[1] = 64;
	//message[2] = 90;
	//midiout.send_message(message);

	//std::this_thread::sleep_for(500ms);

	//// Note Off: 128, 64, 40
	//message[0] = 128;
	//message[1] = 64;
	//message[2] = 40;
	//midiout.send_message(message);

	//std::this_thread::sleep_for(500ms);

	//// Control Change: 176, 7, 40
	//message[0] = 176;
	//message[1] = 7;
	//message[2] = 40;
	//midiout.send_message(message);

	//std::this_thread::sleep_for(500ms);

	//// Sysex: 240, 67, 4, 3, 2, 247
	//message[0] = 240;
	//message[1] = 67;
	//message[2] = 4;
	//message.push_back(3);
	//message.push_back(2);
	//message.push_back(247);
	//midiout.send_message(message);

	return 0;
}
catch (const rtmidi::midi_exception & error)
{
	std::cerr << error.what() << std::endl;
	exit(EXIT_FAILURE);
}


//*****************************SEQUENCER*****************
int s_main(const char** fpath, int nr);


DWORD WINAPI ThreadFunc(void* data) {
	playSequence(chan[active].lib);
	// Do stuff.  This will be the first function called on the new thread.
	// When this function returns, the thread goes away.  See MSDN for more details.
	return 0;
}
DWORD WINAPI ThreadFunc1(void* data) {
	//s_main(fpath, 0);

	// Do stuff.  This will be the first function called on the new thread.
	// When this function returns, the thread goes away.  See MSDN for more details.
	return 0;
}

int main(int argc, char argv[]) {
	//HRESULT WINAPI DirectSoundCreate(LPGUID lpGuid, LPDIRECTSOUND * ppDS, LPUNKNOWN  pUnkOuter);
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);   //Playsequence in own Thread
				//midi_main(0, 0);													//open Midi Port, set up Midi
	main1();
	//getch();
	call_raster_main();													// Print Raster etc..								


	//s_main(fpath, 0);
	//s_main(fpath, 1);
	//printf("this is the end");
	//input_Buffer_Events_main();
//	rlutil::setColor(10);  //				reset to white;

}

int call_raster_main() {

	sendMidiBank(0, 7);                 //channel - Bank number              
	midi1_sendPrgChange(0, 0);

	//***
	int xb = 1;
	int yb = 8;
	int yoffset1 = 0;
	int xoff = 6;
	//***



	int tx = 0;  //tmp for trigger print

	char player[2] = { 'X','O' };
	int p = 2;
	int eingabe = 1;
	int yoffset = 1;
	//lib[1][1].posY = 1;
	//lib[1][1].posX =1;
	//lib[1][1].playerChr ='x';
	//playSequence(lib);
	HANDLE    hIOMutex = CreateMutex(NULL, TRUE, NULL);


	do
	{
		//WaitForSingleObject(hIOMutex, INFINITE);
		system("cls");  // Clean the screen!
						//Print the Rastaman!
		rlutil::setColor(7);
		for (int i = 0; i < yoffset; i++) {
			puts("");

		}
		for (size_t x = 0; x < ys * 2 - 2; x += 2) {
			SetPosition(x, yoffset);
			printf(" %c", '_');
			//printf(" ");
			/*SetPosition(x+1, yoffset);
			printf("%c ",'_');*/
		}
		puts("");
		for (size_t x = 1; x < xs; x++) {
			for (size_t y = 1; y < ys; y++) {
				//(y>1)? SetPosition(y+y, x + yoffset): 
				SetPosition(y + y - 2, x + yoffset);

				printf("|");

				//printf("%c", ((lib[x][y].posX > 0 && lib[x][y].posY > 0) && (x == lib[x][y].posX && y == lib[x][y].posY)) ? lib[x][y].playerChr : '_');
				if ((chan[active].lib[x][y].posX > 0 && chan[active].lib[x][y].posY > 0) && (x == chan[active].lib[x][y].posX && y == chan[active].lib[x][y].posY)) {
					rlutil::setColor(10);
					printf("%c", chan[active].lib[x][y].playerChr);
					rlutil::setColor(7);
				}
				else {
					printf("%c", '_');
				}

				//printf("%s", ((chan[active].lib[x][y].posX >0 && chan[active].lib[x][y].posY >0) && (x == chan[active].lib[x][y].posX && y == chan[active].lib[x][y].posY)) ? "T" :"_" );
				if (y == ys - 1) {
					printf("|");
				}

			}
			puts("");
		}

		draw_buttons(1, 8, 0, 6);     //rows, colums, yoffset, xpos
		//draw_buttons(1, 2, 0, 6);     //rows, colums, yoffset, xpos
		draw_buttons(2, 3, 4, 6);
		/*printf("MOUSEchan[active].lib X: %d Y:%d\n", chan[active].lib[posX][posY].posX, chan[active].lib[posX][posY].posY);
		printf("MOUSEPOS X: %d Y:%d", posX, posY);*/


		do
		{
			//printf("NULL");
		} while (input_Buffer_Events_main() == 0);
		//	rlutil::setColor(10);
			//printf("MOUSE X: %d Y:%d",posX,posY);
		//	printf("NOTNULL");
		//if (input_Buffer_Events_main()) {
		//	if (posX < xs && posY < ys) {


		if (myMouseB != 0) {
			tx = posX;

			if (posX == 1) {

			}
			else if (posX > 1) {
				posX = posX - (posX / 2);                                // Cast Mousecklick to cells
			}
			posY = posY - yoffset;
			if (posX < Y_COUNT + 1 && posY < X_COUNT + 1 + yoffset && posY> yoffset - 1) {          //Click inside Rectangle?
				chan[active].lib[posY][posX].posY = posX;
				chan[active].lib[posY][posX].posX = posY;
				if (myMouseB == 1) {
					chan[active].lib[posY][posX].playerChr = '*';
					//printf("outyout");
				}
				else if (myMouseB == 2) {
					chan[active].lib[posY][posX].playerChr = ' ';
					//	midi1_close();
				}

				chan[active].lib[posY][posX].triggerX = tx;


			}

			else if (posX >= xoff - 2 && posX < xoff - 2 + yb && posY > X_COUNT + yoffset + yoffset1 && posY < X_COUNT + 1 + yoffset + yoffset1 + xb) {
				active = posX - (xoff - 2);
				printf("HIT %d", (posX - (xoff - 3)));
				printf("\033[%d;%dH\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm%c\x1b[0m\n", posY, posX, 255, 255, 255, 12, 12, 12, "X");
				//draw_buttons(int xb, int yb, int yoffset1, int xoff)
				//draw_buttons(1, 8, 0, 6);     //rows, colums, yoffset, xpos
			}
			//}
		//	ReleaseMutex(hIOMutex);

	/*	else {                           //Mouseclick outside struct
			printf("outyout");
		}*/

		}
		//printf("MOUSE");
	} while (eingabe != 0);

	return 1;
}

void setBpm(int updown) {
	(updown > 0) ? thebpm++ : thebpm--;
	//(updown > 0) ? active++ : active--;

	ms = ((60000.0 / (double)thebpm) / (double)4);  //Milliseconds per quarternote
	//ms = 125;  //Millisecond per quarternote
	dur = (ms / 1000) * CLOCKS_PER_SEC;
	//printf("MILLIS PER QUATER:%f\n", ms);
	//printf("ms/Clocks :%f\n", dur);
	SetPosition(0, 0);
	printf("%d BPM", thebpm);
	printf("%d active", active);
}

int playSequence(dat[9][17]) {
	HANDLE    hIOMutex = CreateMutex(NULL, TRUE, NULL);

	WaitForSingleObject(hIOMutex, INFINITE);

	setBpm(1);



	bool isplaying = 1;

	//double time_spent = 0.0;

	long begin = clock();
	// do some stuff here
	//Sleep(3);
	//long end = clock();
	double theend = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	//time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	//	printf("Time elpased is %f seconds", time_spent);

		//
	int index = 1;

	//******MS

		//
	for (size_t c = 0; c < 8; c++) {
		for (size_t x = 1; x < xs; x++) {
			for (size_t y = 1; y < ys; y++) {
				chan[c].lib[x][y].notenumber = 35 + x;    //assign Notenumbers
			}
		}
	}

	//if (myHouse.room[i].trigger[index]) {

	/*House myHouse = { 640,400,.room[0] = {{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},64,127,1},
							   .room[1] = {{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},64,127,1},
							   .room[2] = {{1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},64,127,1} };*/
							   //printf("THE ROOM: %d\n", myHouse.room[1].notenumber);

	while (isplaying) {
		begin = clock();
		if ((double)begin > theend) {

			theend = (double)clock() + dur + (dur * (swing));
			swing = (index % 2) ? 0 : theswing;
			//printf("%f", swing);
			//printf("*");									 //Do things...
			SetPosition(index * 2 - 1, 1);		//cursorPosition as Step Indicator   Curser
			midi1_all_notesoff();    //ALLNOTES OFF
//midi1_reset();
			for (int i = 1; i < xs; i++) {

				//if (myHouse.room[i].trigger[index]) {
				for (int j = 0; j < 8; j++) {
					if (chan[j].lib[i][index].playerChr == '*') {

						// SetPosition(chan[active].lib[i][index].triggerX, X_COUNT+1+ yoffset + i);
						// SetPosition(chan[active].lib[i][index].triggerX, 1);
						// printf("T");

					//	printf("X: %d Y: %d J:%d", i, index,j);
						// s_main(fpath, 0);
									 //    midi1_noteout(1, chan[active].lib[i][index].notenumber, 100);            // NOTE OUT
						midi1_noteout(j, chan[j].lib[i][index].notenumber, 100);            // NOTE OUT

	   // HANDLE thread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);

		   //PlaySound("C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\snare.wav", NULL, SND_ASYNC);  //   PLAY THE SOUND using win api
		   //PlaySound("C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\kick.wav", NULL, SND_ASYNC);

					}
					else {
						//	printf("-");
					}
				}
			}//for



			index++;
		} //if beginn > end


		if (index == 17) { //reset things
			//tickindex = 0;
			index = 1;
			//system("cls");
			//puts("");
			ReleaseMutex(hIOMutex);
		}

	}
	return 0;
}

void draw_buttons(int xb, int yb, int yoffset1, int xoff) {
	/*for (int i = 0; i < yoffset; i++) {
		puts("");

	}*/

	//int xoff = 5;
	//int yoff = 3;   //unused

	for (size_t x = 0 + xoff; x < ((yb + 1) * 2 - 2) + xoff; x += 2) {
		SetPosition(x, yoffset + X_COUNT + 1 + yoffset1);
		printf(" %c", '_');
		//printf(" ");
		/*SetPosition(x+1, yoffset);
		printf("%c ",'_');*/
	}
	puts("");
	for (size_t x = 1; x < xb + 1; x++) {
		for (size_t y = 1; y < yb + 1; y++) {
			//(y>1)? SetPosition(y+y, x + yoffset): 
			SetPosition(y + y - 2 + xoff, x + yoffset + X_COUNT + 1 + yoffset1);

			printf("|");

			//if
			//else
			printf("%c", '_');


			if (y == yb + 1 - 1) {
				printf("|");
			}
			//printf("%c", ((chan[active].lib[x][y].posX > 0 && chan[active].lib[x][y].posY > 0) && (x == chan[active].lib[x][y].posX && y == chan[active].lib[x][y].posY)) ? chan[active].lib[x][y].playerChr : '_');

			/*if ((chan[active].lib[x][y].posX > 0 && chan[active].lib[x][y].posY > 0) && (x == chan[active].lib[x][y].posX && y == chan[active].lib[x][y].posY)) {
				rlutil::setColor(10);
				printf("%c", chan[active].lib[x][y].playerChr);
				rlutil::setColor(7);
			}
			else {
				printf("%c", '_');
			}*/

			//printf("%s", ((lib[x][y].posX >0 && lib[x][y].posY >0) && (x == lib[x][y].posX && y == lib[x][y].posY)) ? "T" :"_" );

		}
		puts("");

	}


}


void SetPosition(int X, int Y)
{
	HANDLE Screen;
	Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { X, Y };

	SetConsoleCursorPosition(Screen, Position);
}
void midi1_noteout(int chan, int noten, int velo) {
	// Note On: 144, 64, 90
	message[0] = 144 + chan;
	message[1] = noten;
	message[2] = velo;
	midiout.send_message(message);
}


void midi1_all_notesoff() {
	for (int j = 0; j < 15; j++) {
		message[0] = 176 + j;
		message[1] = 123;  //ALL notes off
		message[2] = 0;  //ALL notes off
		//message.data[3] = 0;
		midiout.send_message(message);
	}
}
void midi1_sendPrgChange(int thechannel, int prgnumber) {
	message1[0] = 192 + thechannel;
	message1[1] = prgnumber;
	midiout.send_message(message1);
}

void sendMidiBank(int thechannel, int thebank) {

	message[0] = 176 + thechannel; //0-15;
	message[1] = 0;  //ALL notes off
	message[2] = thebank;  //ALL notes off
	midiout.send_message(message);
	//message1.data[3] = 32;
	//message1.data[4] = 0;  //ALL notes off
	//message1.data[5] = 192 + thechannel;
	//message1.data[6] = theprg;

	//flag = midiOutShortMsg(device, message1.word);
	//printf("OOO");
	//flag = midiOutShortMsg();
	//flag = midiOutMessage(device,message1.word,8,8);
   //ALL notes off
}
