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
#include							"ahxrlogger.h"

#include							<sys/stat.h>
#include							<ShlObj.h>
#include							<fstream>
#include							<string>

#pragma comment						( lib, "shell32.lib")

using namespace						System;
using namespace						std;

#define								STEAM_DIR					"\\Steam\\steam.exe"
#define								STEAM_OFFLINE				"steam://friends/status/offline"
#define								STEAM_ONLINE				"steam://friends/status/online"
#define								SPACEWAR_DIR				"\\Steam\\steamapps\\common\\Spacewar\\"
#define								SPACEWAR_INSTALL			"steam://install/480/"
#define								SPACEWAR_RUN				"\\Steam\\steamapps\\common\\Spacewar\\SteamworksExample.exe"
#define								SPACEWAR_KILL				"taskkill /F /IM SteamworksExample.exe >nul 2>&1"
#define								EXIT_WAIT					4000

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
	string				s_steam;
	string				s_spacewar;
	fstream				f_spacewar;
	const char *		c_spacewar;
	struct stat			exist_buffer;
	
	LOG("[COLOR:GREEN]Hide Steam Game Recent Activity by AHXR (github.com/ahxr)");
	SHGetSpecialFolderPath(0, c_program_buffer, CSIDL_PROGRAM_FILES, FALSE);

#if _WIN64
	strcat(c_program_buffer, " (x86)");
#endif

	/*
		If Steam isn't installed in the default directory (Program Files)
		then we're going to search the current folder this application is run.

		In the case of steam.exe not being present (assuming this isn't in the Steam folder)
		then this program will exit with an error.
	*/
	s_steam = c_program_buffer + string(STEAM_DIR);
	if (stat(s_steam.c_str(), &exist_buffer) != 0) {
		char		lp_path[MAX_PATH];
		string		s_path;
		string		s_steam;

		GetModuleFileName(NULL, lp_path, MAX_PATH);

		s_path		= string(lp_path);
		s_path		= s_path.substr(0, s_path.find_last_of('\\'));
		s_steam		= s_path + string("\\steam.exe");

		if (stat(s_steam.c_str(), &exist_buffer) != 0) {
			ERROR("Could not find your Steam directory. Considering that is the case, next time, please run this application in your Steam directory.");
			Sleep(EXIT_WAIT);
			exit(EXIT_FAILURE);
		}

		s_path = s_path.substr(0, s_path.find_last_of('\\'));
		strcpy(c_program_buffer, s_path.c_str());
	}

	s_spacewar = c_program_buffer + string(SPACEWAR_DIR) + string("steam_appid.txt");
	c_spacewar = s_spacewar.c_str();

	f_spacewar.open(c_spacewar, ios::in);

	if (!f_spacewar.is_open()) {
		ERROR("The game \"Spacewar\" is not installed!");
		ShellExecute(NULL, "open", SPACEWAR_INSTALL, 0, 0, 0);

		Sleep(EXIT_WAIT);
		exit(EXIT_FAILURE);
	}
	f_spacewar.close();

	LOG("Everything seems good to go. Going offline mode...");
	ShellExecute(NULL, "open", STEAM_OFFLINE, 0, 0, 0);

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

	LOG("Done. Going back online! Please wait...");
	Sleep(EXIT_WAIT);

	ShellExecute(NULL, "open", STEAM_ONLINE, 0, 0, 0);
}