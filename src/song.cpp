/*
 * song.cpp
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 */


#include "song.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool isPowerOf2(int n) {
	//taken from http://graphics.stanford.edu/~seander/bithacks.html
	return (n & (n - 1)) == 0;
}

int logBase2(int n) {
	//taken from http://stackoverflow.com/a/994623
	int result = 0;
	while (n >>= 1) ++result;
	return result;
}

NotesList::NotesList() {
	for(int i=0;i<NOTE_LIST_SEGMENT_SIZE;i++) {
		note[i] = 0;
		duration[i] = 0;
	}
	next = NULL;
}

NotesList::~NotesList() {
	if(next!=NULL)
	{
		delete next;
	}
}

void NotesList::appendNote(int n) {
	appendNote(n,1);
}

int NotesList::retrieveNote(int n) {
	if(n<NOTE_LIST_SEGMENT_SIZE) {
		return note[n];
	}
	else if(next==NULL) {
		return 0;
	}
	else {
		return next->retrieveNote(n-NOTE_LIST_SEGMENT_SIZE);
	}
}

NoteWithDuration NotesList::retrieveNoteAndDuration(int n) {
	NoteWithDuration result;
	result.note = 0;
	result.duration=0;
	
	if(n<NOTE_LIST_SEGMENT_SIZE) {
		result.note = note[n];
		result.duration = duration[n];
		return result;
	}
	else if(next==NULL) {
		return result;
	}
	else {
		return next->retrieveNoteAndDuration(n-NOTE_LIST_SEGMENT_SIZE);
	}
}

void NotesList::appendNote(int n, int length) {
		if(note[NOTE_LIST_SEGMENT_SIZE - 1]!=0) {
		if(next!=NULL) {
			next->appendNote(n,length);
		}
		else {
			next = new NotesList;
			next->appendNote(n,length);
		}
	}
	else {
		int i=0;
		while(note[i]!=0) {
			i++;
		}
		note[i] = n;
		duration[i] = length;
	}
}

Song::Song()
{
	division = 4;
}


Song::~Song()
{
	
}

void Song::renderSingleNotelistToXML(std::string filename) {
	ofstream outfile;
	outfile.open(filename.c_str());
	if(!outfile.is_open()) {
		cout << "Error opening \"" << filename << "\" aborting rendering." << endl;
		return;
	}
	
	renderOpeningMusicXML(outfile);
	
	NoteWithDuration nextNote = notes.retrieveNoteAndDuration(0);
	int i = 0;
	
	
	while(nextNote.duration>0) {
			outfile << noteToXML(nextNote)<<endl;
			i++;
			nextNote = notes.retrieveNoteAndDuration(i);	
	}
	
	renderClosingMusicXML(outfile);
	
	outfile.close();
}

std::string Song::noteToXML(NoteWithDuration &note) {
	stringstream result;
	if(note.note!=REST) {
		result << "<note><pitch><step>";
		NoteAsNotation converted = intToNotation(note.note);
		
		result << converted.letter << "</step>";
		
		if(converted.alteration!=0) {
			result << "<alter>" << converted.alteration << "</alter>";
		}
		
		result << "<octave>" << converted.octave << "</octave></pitch><duration>1</duration>" << noteTypeString(note.duration) << "</note>";
		//try replacing "1" in the above line with "<< (float)note.duration / division <<"
		return result.str();
	}
	else {
		result << "<note><rest/><duration>1</duration>" << noteTypeString(note.duration) << "</note>";
		
		return result.str();
	}
}

void Song::renderOpeningMusicXML(ofstream &file) {
	ifstream sourceFile("res/boilerplateopening.xml", std::ifstream::in);
	string lineRead;
	while(sourceFile.good())
	{
		getline(sourceFile, lineRead);
		file << lineRead << endl;
	}
	
}

void Song::renderClosingMusicXML(ofstream &file) {
		ifstream sourceFile("res/boilerplateclosing.xml", std::ifstream::in);
	string lineRead;
	while(sourceFile.good())
	{
		getline(sourceFile, lineRead);
		file << lineRead << endl;
	}
}

void Song::setSmallestInterval(int _division) {
	division = _division;
}

void Song::appendNote(int a) {
	notes.appendNote(a);
}

int Song::retrieveNote(int n) {
	return notes.retrieveNote(n);
}

void Song::appendNote(int a, int b) {
	notes.appendNote(a,b);
}

NoteAsNotation Song::intToNotation(int note) {
	NoteAsNotation result;
	
	if(note<0) {
		result.octave = 4 - (note+1) / 12;
		result.alteration = NOTE_ALTERATIONS[12 - (-note) % 12];
		result.letter = NOTE_LETTERS[12 - (-note) % 12];
	}
	else {
		result.octave = 5 + note / 12;
		result.alteration = NOTE_ALTERATIONS[note % 12];
		result.letter = NOTE_LETTERS[note % 12];
	}
	
	return result;
}

std::string Song::noteTypeString(int duration) {
	std::stringstream result;
	result << "<type>";
	if(division%duration == 0 and isPowerOf2(division/duration)) {
		result << NOTE_LENGTH_NAMES[logBase2(division/duration)];
		result << "</type>";
	}
	else if(isPowerOf2(division*3/duration / 2)) {
		//if the note is dotted
		result << NOTE_LENGTH_NAMES[logBase2(division*3/2 / duration)];
		result << "</type><dot/>";
	}
	else {
		result << "quarter";
		result << "</type>";
	}
	
	return result.str();
}
