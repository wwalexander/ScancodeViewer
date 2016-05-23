#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <wincon.h>

void printError(void)
{
	LPVOID lpMsgBuf;

	if (FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		0,
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	) == 0) {
		return;
	}

	fputs((char *)lpMsgBuf, stderr);
	LocalFree(lpMsgBuf);
}

int main(VOID)
{
	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	INPUT_RECORD ir;
	DWORD cNumRead;

	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	if (hStdin == INVALID_HANDLE_VALUE) {
		printError();
		return 1;
	}

	if (GetConsoleMode(hStdin, &fdwSaveOldMode) == 0) {
		printError();
		return 1;
	}

	if (SetConsoleMode(hStdin, ENABLE_PROCESSED_INPUT) == 0) {
		printError();
		return 1;
	}

	while (ReadConsoleInput(hStdin, &ir, 1, &cNumRead) != 0) {
		TCHAR lpString[128];

		if (ir.EventType != KEY_EVENT) {
			continue;
		}

		printf("%02x ", ir.Event.KeyEvent.wVirtualScanCode);

		if (GetKeyNameText(ir.Event.KeyEvent.wVirtualScanCode << 16,
		                   lpString,
		                   128) == 0) {
			SetConsoleMode(hStdin, fdwSaveOldMode);
			printError();
			return 1;
		}

		printf("%ws\n", lpString);
	}

	if (SetConsoleMode(hStdin, fdwSaveOldMode) == 0) {
		printError();
		return 1;
	}

	return 0;
}