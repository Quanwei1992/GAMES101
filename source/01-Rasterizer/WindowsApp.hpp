#pragma once

#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <cassert>
#include <ctime>

class WindowsApplication
{
public:
	WindowsApplication(const char* name,int width,int height)
		:_name(name)
		,_width(width)
		,_height(height)
		,_hdc(NULL)
		,_hWnd(NULL)
		,_backDC(NULL)
		,_backBuffer(NULL)
		,_lastTime(0)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);


		// the handle for the window, filled by a function
		HWND hWnd;
		// this struct holds information for the window class
		WNDCLASSEX wc;

		// clear out the window class for use
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		// fill in the struct with the needed information
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = &WindowsApplication::WndProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = _name;

		// register the window class
		RegisterClassEx(&wc);

		// create the window and use the result as the handle
		hWnd = CreateWindowEx(0,
			_name,      // name of the window class
			_name,             // title of the window
			WS_OVERLAPPEDWINDOW,              // window style
			CW_USEDEFAULT,                    // x-position of the window
			CW_USEDEFAULT,                    // y-position of the window
			_width,             // width of the window
			_height,            // height of the window
			NULL,                             // we have no parent window, NULL
			NULL,                             // we aren't using menus, NULL
			hInstance,                        // application handle
			NULL);                            // used with multiple windows, NULL

		// display the window on the screen
		ShowWindow(hWnd, SW_SHOW);
		_hWnd = hWnd;
		_hdc = GetWindowDC(hWnd);
		_backDC = CreateCompatibleDC(_hdc);
		_backBuffer = CreateCompatibleBitmap(_hdc, _width, _height);
		SelectObject(_backDC, _backBuffer);
		_lastTime = std::clock();


	};
	virtual ~WindowsApplication() 
	{
		SelectObject(_backDC, _backBuffer);
		DeleteObject(_backBuffer);
		ReleaseDC(_hWnd, _backDC);
		ReleaseDC(_hWnd, _hdc);
	};


public:

	int GetWidth() { return _width; }
	int GetHeight() { return _height; }



	void Run()
	{

		MSG msg;
		while (!_quit)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				clock_t now = std::clock();
				double dt = ((double)now - (double)_lastTime) / CLOCKS_PER_SEC;
				_lastTime = now;
				OnTick(dt);		
				
			}
			
		}
	}


protected:
	virtual void OnTick(double dt)
	{

	}

	
	inline void SetPixel(int x, int y, COLORREF color)
	{
		::SetPixel(_backDC, x, _height - y,color);
	}

	inline void SwapBuffer()
	{
		BitBlt(_hdc, 0, 0, _width, _height, _backDC, 0, 0, SRCCOPY);
	}

	inline void Clear(COLORREF color)
	{
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.bottom = _height;
		rect.right = _width;

		HBRUSH brush = CreateSolidBrush(color);

		FillRect(_backDC, &rect, brush);
		DeleteObject(brush);

		
	}

	


	static LRESULT CALLBACK WndProc(
		_In_ HWND   hWnd,
		_In_ UINT   message,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	)
	{
		if (message == WM_DESTROY)
		{
			// close the application entirely
			PostQuitMessage(0);
			WindowsApplication::_quit = true;
				return 0;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}


	


private:
	int _width;
	int _height;
	const char* _name;
	HDC _hdc;
	HDC _backDC;
	HWND _hWnd;
	HBITMAP _backBuffer;
	static bool _quit;
	std::clock_t _lastTime;
};

bool WindowsApplication::_quit = false;