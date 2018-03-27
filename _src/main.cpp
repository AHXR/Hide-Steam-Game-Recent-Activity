/*
	@title
		Hide Steam Game Recent Activity
	@author
		AHXR
	@copyright
		2018

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
#include <string>
#include <iostream>
#include <Windows.h>

const char * c_app_ids[] = { // CS:GO Profile Videos
	"413851", 
	"413857",
	"413859",
	"413856"
};

int main() {
	char 
		c_buffer[MAX_PATH]
	;
	
	for (unsigned short us = 0; us < ( sizeof(c_app_ids) /  sizeof( c_app_ids [ 0 ] ) ); us++) {
		sprintf(c_buffer, "steam://run/%s", c_app_ids[us]);
		ShellExecute( NULL, "open", c_buffer, NULL, NULL, NULL);
		Sleep(1000);
	}

	/*
		Steam will detect that you are closing your CSGO Profile video and mark it 
		on your recent activity, hence why we are killing the Steam process.
	*/
	system("taskkill /f /im Steam.exe");
	Sleep(1000);
	system("taskkill /f /im html5app_steam.exe");
    return 0;
}

