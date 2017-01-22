#include "MusicWrapper.h"

void MusicWrapper::add(TCHAR* path, const string& alias)
{
	if (paths.find(path) == paths.end())
	{
		players[alias] = MP3Player();
		players[alias].OpenFromFile(path);
		paths[alias] = path;
	}
}

void MusicWrapper::stop(string alias)
{
	players[alias].Close();
	players[alias].OpenFromFile(paths[alias]);
}

void MusicWrapper::play(string alias)
{
	players[alias].Play();
}