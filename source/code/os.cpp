/*
===========================================================================
blockattack - Block Attack - Rise of the Blocks
Copyright (C) 2005-2015 Poul Sander

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

Source information and contacts persons can be found at
http://blockattack.net
===========================================================================
*/

#include "os.hpp"
#include <iostream>

#ifdef __unix__
#include <pwd.h>
#include <unistd.h>
#include <stdexcept>


/**
 * Retrives the effective user's home dir.
 * If the user is running as root we ignore the HOME environment. It works badly with sudo.
 * Writing to $HOME as root implies security concerns that a multiplatform program cannot be assumed to handle.
 * @return The home directory. HOME environment is respected for non-root users if it exists.
 */
static std::string getHome() {
	std::string res;
	int uid = getuid();
	const char* homeEnv = getenv("HOME");
	if ( uid != 0 && homeEnv) {
		//We only acknowlegde HOME if not root.
		res = homeEnv;
		return res;
	}
	struct passwd* pw = getpwuid(uid);
	if (!pw) {
		throw std::runtime_error("Unable to get passwd struct.");
	}
	const char* tempRes = pw->pw_dir;
	if (!tempRes) {
		throw std::runtime_error("User has no home directory");
	}
	res = tempRes;
	return res;
}
#endif

/*
 *Files will be saved in:
 * HOME/.gamesaves/"+GAMENAME (unix)
 *or DOCUMENTS/My Games/GAMENAME (Windows)
 */
#define GAMENAME "blockattack"

using namespace std;

#ifdef _WIN32
//Returns path to "my Documents" in windows:
string getMyDocumentsPath() {
	char pszPath[MAX_PATH];
	//if (SUCCEEDED(SHGetSpecialFolderPath(nullptr, pszPath, CSIDL_PERSONAL, FALSE))) {
	if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_PERSONAL, nullptr, 0, pszPath))) {
		// pszPath is now the path that you want
#if DEBUG
		cout << "MyDocuments Located: " << pszPath << endl;
#endif
		string theResult= pszPath;
		return theResult;
	}
	else {
		cout << "Warning: My Documents not found!" << endl;
		string theResult ="";
		return theResult;
	}
}


#endif

static std::string overrideSavePath = "";

/**
 * Returns the path to where all settings must be saved.
 * On unix-like systems this is the home-folder under: ~/.gamesaves/GAMENAME
 * In Windows it is My Documents/My Games
 * Consider changing this for Vista that has a special save games folder
 */
std::string getPathToSaveFiles() {
	if (overrideSavePath.length() > 0) {
		return overrideSavePath;
	}
#ifdef __unix__
	return (std::string)getenv("HOME")+(std::string)"/.gamesaves/"+GAMENAME;
#elif _WIN32
	return getMyDocumentsPath()+(string)"/My Games/"+GAMENAME;
#else
	return ".";
#endif
}

void setPathToSaveFiles(const std::string& path) {
	overrideSavePath = path;
}

std::string getStageClearSavePath() {
	std::string ret;
#if defined(__unix__)
	ret = getHome()+"/.gamesaves/blockattack/stageClear.SCsave";
#elif defined(_WIN32)
	ret = getMyDocumentsPath()+"/My Games/blockattack/stageClear.SCsave";
#else
	ret = "stageClear.SCsave";
#endif
	return ret;
}

std::string getPuzzleSetSavePath() {
	std::string ret;
#if defined(__unix__)
	ret = getHome()+"/.gamesaves/blockattack/puzzle.levels.save";
#elif defined(_WIN32)
	ret = getMyDocumentsPath()+"/My Games/blockattack/puzzle.levels.save";
#else
	ret = "puzzle.levels.save";
#endif
	return ret;
}

static void OsCreateFolderInSaveGames(const string& path) {
	string cmd = "mkdir -p "+getPathToSaveFiles()+"/"+path;
#if defined(__unix__)
	int retcode = system(cmd.c_str());
	if (retcode != 0) {
		cerr << "Failed to create: " << getPathToSaveFiles()+"/"+path << endl;
	}
#elif defined(_WIN32)
	//Now for Windows NT/2k/xp/2k3 etc.
	string tempA = getMyDocumentsPath()+"\\My Games";
	CreateDirectory(tempA.c_str(),nullptr);
	tempA += "/"+path;
	CreateDirectory(tempA.c_str(),nullptr);
#endif
}

void OsCreateFolders() {
	//We first create the folder there we will save (only on UNIX systems)
	//we call the external command "mkdir"... the user might have renamed this, but we hope he hasn't
	OsCreateFolderInSaveGames("screenshots");
	OsCreateFolderInSaveGames("replays");
	OsCreateFolderInSaveGames("puzzles");
}