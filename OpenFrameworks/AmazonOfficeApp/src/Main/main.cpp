#include "ofMain.h"
#include "AmazonOfficeApp.h"


#ifndef TARGET_WIN32
//========================================================================
int main() {

    ofGLWindowSettings settings;

    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
									// this kicks off the running of my app
	ofRunApp(new AmazonOfficeApp());

}

#else

#include "../../resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

    ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
    
	HWND hwnd = ofGetWin32Window();
	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);


	ofRunApp(new AmazonOfficeApp());

}

#endif




