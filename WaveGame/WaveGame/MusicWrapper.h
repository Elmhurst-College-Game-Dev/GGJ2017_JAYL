#pragma once
#include "mp3player.h"
#include <map>
#include <string>

using namespace std;

class MusicWrapper
{
public:
	MusicWrapper() = default;
	void add(TCHAR* path, const string& alias);
	void stop(string alias);
	void play(string alias);
private:
	map<string, MP3Player> players;
	map<string, TCHAR*> paths;
};
