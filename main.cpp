/*
	@title
		Hide Steam Game Recent Activity
	@author
		AHXR
	@copyright
		2017

	Hide Steam Game Recent Activity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Hide Steam Game Recent Activity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with Hide Steam Game Recent Activity. If not, see <http://www.gnu.org/licenses/>.
*/
//=======================================================

#include							"stdafx.h"
#include							"ahxrlogger.h"
#include							<ShlObj.h>
#include							<fstream>
#include							<string>

#pragma comment						( lib, "shell32.lib")

using namespace						System;
using namespace						std;

#define								SPACEWAR_DIR				"\\Steam\\steamapps\\common\\Spacewar\\"
#define								SPACEWAR_INSTALL			"steam://install/480/"
#define								SPACEWAR_RUN				"\\Steam\\steamapps\\common\\Spacewar\\SteamworksExample.exe"
#define								SPACEWAR_KILL				"taskkill /F /IM SteamworksExample.exe"

#define								WRITE_APPID( a, b ) { \
										f_spacewar.open(a, ios::out); \
										f_spacewar << b; \
										f_spacewar.close(); \
									}

#define								RUN_HIDER() { \
										ShellExecute(NULL, "open", c_spacewarexec, 0, 0, 0);  \
										Sleep(500); \
									}

void main()
{
	TCHAR				c_program_buffer[MAX_PATH];
	string				s_spacewar;
	fstream				f_spacewar;
	const char *		c_spacewar;
	
	LOG("[COLOR:GREEN]Hide Steam Game Recent Activity by AHXR (github.com/ahxr)");
	SHGetSpecialFolderPath(0, c_program_buffer, CSIDL_PROGRAM_FILES, FALSE);

	s_spacewar = c_program_buffer + string(SPACEWAR_DIR) + string("steam_appid.txt");
	c_spacewar = s_spacewar.c_str();

	f_spacewar.open(c_spacewar, ios::in);

	if (!f_spacewar.is_open()) {
		ERROR("The game \"Spacewar\" is not installed!");
		ShellExecute(NULL, "open", SPACEWAR_INSTALL, 0, 0, 0);

		Sleep(2000);
		exit(EXIT_FAILURE);
	}
	f_spacewar.close();

	string				s_spacewarexec;
	const char *		c_spacewarexec;
	const char *		c_app_ids[] = { "399220", "399080", "399480" };

	s_spacewarexec = c_program_buffer + string(SPACEWAR_RUN);
	c_spacewarexec = s_spacewarexec.c_str();

	for (int i = 0; i < sizeof(c_app_ids) / sizeof(c_app_ids[0]); i++) {
		WRITE_APPID(c_spacewar, c_app_ids[ i ]);
		RUN_HIDER();
	}
	system(SPACEWAR_KILL);
}