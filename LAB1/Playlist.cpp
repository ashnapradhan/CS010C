#include "Playlist.h"

//destructor
//delete nodes while traverse the list 
Playlist::~Playlist() {
    //start from head by using current pointer
    PlaylistNode* current = head;
    //"while not @ end"
    while (current != nullptr) {
        //get next node
        PlaylistNode* next = current->GetNext();
        //delete current node
        delete current;
        //move to next node
        current = next;
    }
    //set head to null
    head = nullptr;
}

//PrintMenu() function
//output all playlist functions
//output title that was obtained in main.cpp
void Playlist::PrintMenu(const string& title) const {
    cout << endl;
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;   
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:";
}

//AddSong() function
//adds new song by creating new node at end of list
void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
    //create new node for added song
    PlaylistNode* newNode = new PlaylistNode(id, song, artist, length);

    //if playlist empty, add to start
    if (head == nullptr) {
        head = newNode;
    } 
    else {
        //begin traverse
        PlaylistNode* current = head;
        //while not at end
        while (current->GetNext() != nullptr) {
            current = current->GetNext();
        }
        //move to next node
        current->SetNext(newNode);
    }
  
}

//RemoveSong() function
//deletes node and pointer of song to be removed    
void Playlist::RemoveSong() {

    //handle empty
    if (head == nullptr) {
        return;
    }

    //get id to remove
    string removeID;
    cout << endl;
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> removeID;
    //check for input error
    if (!cin) {
        throw runtime_error("Input Error");
    }
    //name of song to be removed
    string removeName;

    //if first node ID is id to remove:
    if (head->GetID() == removeID) {
        //id is found so name of song is obtained
        removeName = head->GetSongName(); //get name of song to be removed
        cout << removeName << " removed." << endl;
        PlaylistNode* temp = head; //node of song
        head = head->GetNext();
        delete temp; //remove song
    } 

    //else, traverse list to find the song to remove
    PlaylistNode* current = head;
    PlaylistNode* previous = nullptr;

    //traverse list
    while ((current != nullptr) ) {
        //id of current node
        string currID = current->GetID();

        //if id is found at current node:
        if (currID == removeID) {
            //node of the song to be removed
            PlaylistNode* removing = current;
            //new pointer to help skip over removing node
            PlaylistNode* skip = current->GetNext();
            //skip node
            previous->SetNext(skip);
            removeName = removing->GetSongName();
            cout << '"' << removeName << '"' << " removed." << endl;
            //delete song
            delete removing;
        }
        //move to next node
        previous = current;
        current = current->GetNext();

    }
  
}
    
void Playlist::ChangePositionSong() {

    //if empty
    if (head == nullptr) {
        return;
    }

    //user inputted positions
    int pos1;
    int pos2;

    //ask for positions
    cout << endl;
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> pos1;
    //check for input error
    if (!cin) {
        throw runtime_error("Input Error");
    }
    cout << "Enter new position for song:" << endl;
    cin >> pos2;
    //check for input error
    if (!cin) {
        throw runtime_error("Input Error");
    }

    //handle if new positions is < 1
    if (pos2 < 1) {
        pos2 = 1;
    }

    //traverse list
    PlaylistNode* current = head;
    PlaylistNode* previous = nullptr;
    //traverse until first position is found
    for (int i = 1; i < pos1 && current != nullptr; ++i) {
        previous = current;
        //move to next
        current = current->GetNext();
    }

    //calculate number of songs
    int nodeSum = 0;
    //begin traverse
    PlaylistNode* count = head;

    //traverse full list to get number of songs
    while (count != nullptr) {
        //increment until all songs are totaled
        ++nodeSum;
        count = count->GetNext();
    }

    //handle if new position is > than number of nodes
    if (pos2 > nodeSum) {
        pos2 = nodeSum;
    }

    //change what head points to
    if (previous == nullptr) {
        head = current->GetNext();
    } else { //skip over the changed node
        previous->SetNext(current->GetNext());
    }

    //start new traverse through list
    PlaylistNode* newPrev = nullptr;
    //beginning of list
    PlaylistNode* newNode = head;

    //traverse until new position found
    for (int i = 1; i < pos2 && newNode != nullptr; ++i) {
        //move to next node until new position found and not at end
        newPrev = newNode;
        newNode = newNode->GetNext();
    }

    //change nodes
    if (newPrev == nullptr) {
        head = current;
        current->SetNext(newNode);
    } 
    else {
        //move the previous to next
        newPrev->SetNext(current);
        //place newNode
        current->SetNext(newNode);
    }

    //output
    cout << '"' << current->GetSongName() << '"' << " moved to position " << pos2 << endl;

}

//OutputSongsByArtists() function
//finds all songs by a specific artist
//outputs only those songs   
void Playlist::OutputSongsByArtist() const {

    //if empty
    if (head == nullptr) {
        return;
    }

    //to get user inputted name
    string inputName;
    cout << endl;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    //ignore newline
    cin.ignore();
    //get full line of inputted artist name
    getline(cin, inputName);
    //check for input error
    if (!cin) {
        throw runtime_error("Input Error");
    }

    //song number
    int songNum = 1;
    //to traverse list
    PlaylistNode* current = head;

    //traverse list
    //if inputted artist name is found, then PrintPlaylistNode()
    while (current != nullptr) {
        //string currArtist = current->GetArtistName();
        if (current->GetArtistName() == inputName) {
            cout << endl;
            //print song number
            cout << songNum << "." << endl;
            //print song if artist is found
            current->PrintPlaylistNode();
            cout << endl;
        }

        //move to next node
        current = current->GetNext();
        //increment song number
        ++songNum;
    }

}

//OutputTotalTime() function
//calculates total of song lengths and outputs  
void Playlist::OutputTotalTime() const {

    //if empty
    if (head == nullptr) {
        return;
    }

    //to calculate total time
    //initialize integer
    int time = 0;
    cout << endl;
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;

    //traverse list and add song lengths to time
    for(const PlaylistNode* current = head; current != nullptr; current = current->GetNext()) {
        //add current song length to time integer
        time += current->GetSongLength();
    }

    //output
    cout << "Total time: " << time << " seconds" << endl;
     
}

//OutputFullPlaylist() function
//outputs songs using PrintPlaylistNode() function
void Playlist::OutputFullPlaylist() const {
    //title
    cout << " - OUTPUT FULL PLAYLIST";

    //if playlist is empty
    if (head == nullptr) {
        cout << "\nPlaylist is empty" << endl;
        //return if empty
        return;
    }

    else {
        //to output song number
        int songNum = 1;
        //begin traverse
        const PlaylistNode* current = head;
        
        //traverse list
        while (current != nullptr) {
            cout << endl;
            //output song number
            cout << songNum << "." << std::endl;
            //use print function
            current->PrintPlaylistNode();
            //get next node
            current = current->GetNext();
            
            //"if not at end"
            if (current != tail) {
                cout << endl;
            }

            //increment song number
            songNum++;
        }
        cout << endl;
    }
   
}
    

