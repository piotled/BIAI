#include "Controller.h"

extern "C" {
	__declspec(dllexport) bool _cdecl LoadNetwork(char* filePath) {
		Controller networkController;
		return networkController.LoadNetwork(filePath);
	}
}

