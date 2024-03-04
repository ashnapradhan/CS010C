
#pragma once



#include <iostream>
using namespace std;

class PlaylistNode {
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:

  PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr){}
  PlaylistNode(const std::string& id, const std::string& name, const std::string& artist, int length) : uniqueID(id), songName(name), artistName(artist), songLength(length), nextNodePtr(nullptr) {}

  void InsertAfter(PlaylistNode* node) {
    PlaylistNode* temp = nextNodePtr;
    nextNodePtr = node;
    node->nextNodePtr = temp;
  }
  void SetNext(PlaylistNode* node) {
    nextNodePtr = node;
  }


  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength;
  }
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail;
public:

  Playlist()
    : head(nullptr),tail(nullptr)
  {}
  //destructor declaration
  ~Playlist();

  //copy constructor declaration + delete
  // = delete stops C++ from creating default constructor
  Playlist(const Playlist &copy) = delete;

  //assignment operator declaration + delete
  Playlist& operator=(const Playlist& copy) = delete;

  //other function declarations
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

