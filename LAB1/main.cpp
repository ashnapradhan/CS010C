#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {

  //title variable declaration
  string title;
  cout << "Enter playlist's title:" << endl;
  //get title usin getline
  getline(cin, title);

  //create playlist in main.cpp
  Playlist P;

  while(true) {
    //print menu using playlist title
    P.PrintMenu(title);

    //get user command/option
    string command;
    if (!(cin >> command)) break;

    if (command == "a") {
      //variable declarations
      string addID;
      string addSong;
      string addArtist;
      int addLength;
      cout << endl;
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      std::cin.ignore(); //ignore newline
      std::getline(std::cin, addID); //get full line of input
      if (!cin) {
        throw runtime_error("Input Error");
      }
      
      cout << "Enter song's name:" << endl;
      std::getline(std::cin, addSong);
      //check for input error
      if (!cin) {
        throw runtime_error("Input Error");
      }
     
      cout << "Enter artist's name:" << endl;
      std::getline(std::cin, addArtist);
      //check for input error
      if (!cin) {
        throw runtime_error("Input Error");
      }
      
      cout << "Enter song's length (in seconds):" << endl;
      cin >> addLength;
      //check for input error
      if (!cin) {
        throw runtime_error("Input Error");
      }

      P.AddSong(addID, addSong, addArtist, addLength);
      
    } else if (command == "d") {
      P.RemoveSong();
    } else if (command == "c") {
      P.ChangePositionSong();
    } else if (command == "s") {
      P.OutputSongsByArtist();
    } else if (command == "t") {
      P.OutputTotalTime();
    } else if (command == "o") {
      //output playlist title
      cout << endl;
      cout << title;
      P.OutputFullPlaylist();
    } else if (command == "q") {
      cout << endl;
      break;
    }
  }
  //g++ main.cpp Playlist.cpp
  //./a.out

  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  return 0;
}
