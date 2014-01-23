/*
 * song.cpp
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 */

#include <iostream>
#include <fstream>

#ifndef SONG_HPP
#define SONG_HPP

#define NOTE_LIST_SEGMENT_SIZE 10
#define REST 2000000

static const char NOTE_LETTERS[] = "CCDEEFFGGABBC";
static const int NOTE_ALTERATIONS[] = {0,1,0,-1,0,0,1,0,1,0,-1,0,0};
static const char NOTE_LENGTH_NAMES[][8] = { "whole", "half", "quarter", "eighth", "16th", "32nd", "64th", "128th", "256th"}; 

bool isPowerOf2(int n);
int logBase2(int n);

struct NoteAsNotation {
	char letter;
	int octave;
	int alteration;
};

struct NoteWithDuration {
	int note;
	int duration;
};

class NotesList {
	private:
		int note[NOTE_LIST_SEGMENT_SIZE];
		int duration[NOTE_LIST_SEGMENT_SIZE];
		NotesList * next;
	public:
		NotesList();
		~NotesList();
		
		void appendNote(int);
		int retrieveNote(int);
		
		void appendNote(int, int);
		NoteWithDuration retrieveNoteAndDuration(int);
		
};

class Song
{
	public:
		Song();
		~Song();
		
		void setNotesList(NotesList);
		void setSmallestInterval(int);
		
		void appendNote(int);
		void appendNote(int, int);
		int retrieveNote(int);
		
		void renderSingleNotelistToXML(std::string);
		
		std::string noteToXML(NoteWithDuration&);
		NoteAsNotation intToNotation(int note);
		std::string noteTypeString(int duration);
	
	private:
		NotesList notes;
		int division;	//if this is 8, the smallest note is an 8th note and there can be no more than 8 notes in a bar.
		
		//Methods used internally
		void renderOpeningMusicXML(std::ofstream &file);
		void renderClosingMusicXML(std::ofstream &file);
		

};

#endif /* SONG_HPP */ 
