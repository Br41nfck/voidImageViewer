//
// Copyright 2025 voidtools / David Carpenter
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// debugging functions

#include "viv.h"

#ifdef _DEBUG
static HANDLE debug_log_file = INVALID_HANDLE_VALUE;
static CRITICAL_SECTION debug_lock;
static BYTE debug_initialized = 0;

void debug_init(void)
{
	wchar_t path[MAX_PATH];
	wchar_t filename[MAX_PATH];

	if (debug_initialized)
	{
		return;
	}

	InitializeCriticalSection(&debug_lock);
	debug_initialized = 1;

	if (config_log_mode == CONFIG_LOG_CONSOLE || config_log_mode == CONFIG_LOG_BOTH)
	{
		if (!GetConsoleWindow())
		{
			AllocConsole();
		}
	}

	if (config_log_mode != CONFIG_LOG_CONSOLE)
	{
		if (GetModuleFileNameW(NULL, path, MAX_PATH))
		{
			wchar_t *slash = wcsrchr(path, L'\\');
			if (slash)
			{
				*slash = 0;
			}
			wsprintfW(filename, L"%s\\voidImageViewer.log", path);
			debug_log_file = CreateFileW(filename, FILE_APPEND_DATA, FILE_SHARE_READ,
				NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
	}
}

void debug_shutdown(void)
{
	if (debug_initialized)
	{
		EnterCriticalSection(&debug_lock);
		if (debug_log_file != INVALID_HANDLE_VALUE)
		{
			CloseHandle(debug_log_file);
			debug_log_file = INVALID_HANDLE_VALUE;
		}
		LeaveCriticalSection(&debug_lock);
		DeleteCriticalSection(&debug_lock);
		debug_initialized = 0;
	}
}
#endif

// fatal error, does not return
// gives a UI message to the user and bails.
void DECLSPEC_NORETURN debug_fatal(const char *format,...)
{
	wchar_t wbuf[STRING_SIZE];
	va_list args;
	
	va_start(args,format);
	string_vprintf(wbuf,format,args);
	va_end(args);

	MessageBox(0,wbuf,L"voidImageViewer",MB_OK|MB_ICONERROR|MB_SYSTEMMODAL);
	ExitProcess(0);
}

#ifdef _DEBUG
void debug_printf(const char *format,...)
{
	wchar_t wbuf[STRING_SIZE];
	va_list args;
	DWORD number_of_chars_written;
	int write_console;
	int write_file;
	
	va_start(args,format);
	string_vprintf(wbuf,format,args);
	va_end(args);

	write_console = config_log_mode == CONFIG_LOG_CONSOLE || config_log_mode == CONFIG_LOG_BOTH;
	write_file = config_log_mode == CONFIG_LOG_FILE || config_log_mode == CONFIG_LOG_BOTH;

	if (!debug_initialized)
	{
		debug_init();
	}

	EnterCriticalSection(&debug_lock);
	if (write_console)
	{
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),wbuf,string_length(wbuf),&number_of_chars_written,NULL);
	}
	if (write_file && debug_log_file != INVALID_HANDLE_VALUE)
	{
		int size = WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, NULL, 0, NULL, NULL);
		if (size > 1)
		{
			char *buf = (char *)HeapAlloc(GetProcessHeap(), 0, size);
			if (buf)
			{
				WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, buf, size, NULL, NULL);
				WriteFile(debug_log_file, buf, size - 1, &number_of_chars_written, NULL);
				HeapFree(GetProcessHeap(), 0, buf);
			}
		}
	}
	LeaveCriticalSection(&debug_lock);
}
#endif							
