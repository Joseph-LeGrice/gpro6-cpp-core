// 4 - Realistic Volumentric Explosions.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Main.h"
#include "SystemsManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	int returnCode = 0;

	SystemsManager* sysManager = new SystemsManager();
	if (sysManager->InitializeAllSystems())
	{
		returnCode = sysManager->Run();
	}
	
	sysManager->ShutdownAllSystems();
	delete sysManager;

	return returnCode;
}
