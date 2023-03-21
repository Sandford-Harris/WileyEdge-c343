#pragma once
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#pragma comment(lib, "Winmm.lib")
using namespace std;

class Song {

private:
	string path;
	string album;

public:
	Song(string songAlbum, string filePath){
		album = album;
		path = filePath;
	}
	string GetPath() { return path; }
};

class SongList {

private:
	string path; // directory holding the mp3 files
	vector<Song> songs;
	int currentSong;


public:
	SongList(string filePath) {
		path = filePath;
		currentSong = -1;
		LoadSongs();
	}
	void LoadSongs();
	void Play();
	void Pause();
	void Seek(int dir);
	string GetCurrentSongName() { return songs.at(currentSong).GetPath(); }
	int GetCurrentSong() { return currentSong; }

};

void SongList::LoadSongs() {


	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind;

	string searchterm = path + "/*.mp3";
	hFind = FindFirstFileA(searchterm.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do{
			Song s("", FindFileData.cFileName);
			songs.push_back(s);
		}while (FindNextFileA(hFind, &FindFileData));
		FindClose(hFind);
		currentSong = 0;
	}

}

void SongList::Play() {

	string songpath = "open \"" + path + "/" + songs.at(currentSong).GetPath()  + "\" type mpegvideo alias " + to_string(currentSong);
	mciSendStringA(songpath.c_str(), NULL, 0, NULL);

	string play = "play " + to_string(currentSong);
	mciSendStringA(play.c_str(), NULL, 0, NULL);
}

void SongList::Pause() {

	string pause = "pause " + to_string(currentSong);
	mciSendStringA(pause.c_str(), NULL, 0, NULL);
}

void SongList::Seek(int dir) {

	string stop = "stop " + to_string(currentSong);
	mciSendStringA(stop.c_str(), NULL, 0, NULL);
	string close = "close " + to_string(currentSong);
	mciSendStringA(close.c_str(), NULL, 0, NULL);

	if (currentSong != -1) {
		if (dir == 0) {
			currentSong = (currentSong + 1) % songs.size();
		}
		else {
			if (currentSong == 0)
				currentSong = songs.size() - 1;
			else
				currentSong = currentSong - 1;
		}
	}
	
}