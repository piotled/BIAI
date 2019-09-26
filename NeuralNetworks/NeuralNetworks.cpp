#pragma once

extern "C" {

	__declspec(dllexport) bool _cdecl LoadNetwork(char* filePath) {
		return true;
	}

}