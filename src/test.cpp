/*
 * song.cpp
 * 
 * Copyright 2013 mooshmoosh <developerwill1@gmail.com>
 */
 
#include <iostream>
#include <cassert>
#include "song.hpp"
#include <cstdlib>

using namespace std;

void testNotesListWithoutDurations();
void testNotesListWithDurations();
void testNoteToXML();
void testNoteTypeString();
void testIntToNotation();

int main(int argc, char **argv)
{
	testNotesListWithoutDurations();
	testNotesListWithDurations();
	testIntToNotation();
	testNoteTypeString();
	testNoteToXML();	
	
	cout << "all tests fine" <<endl;
	return 0;
}

void testNotesListWithoutDurations() {
	NotesList list;
	for(int i=0;i<20;i++) {
		list.appendNote(i+5);
	}
	
	for(int i=0;i<20;i++) {
		assert(list.retrieveNote(i)==i+5);
	}
}

void testNotesListWithDurations() {
	NotesList list;
	
	for(int i=0;i<20;i++) {
		list.appendNote(i+5,i+1);
	}
	
	list.appendNote(REST,5);
	
	for(int i=0;i<20;i++) {
		assert(list.retrieveNoteAndDuration(i).note==i+5);
		assert(list.retrieveNoteAndDuration(i).duration==i+1);
	}
	
	assert(list.retrieveNote(20)==REST);
	assert(list.retrieveNoteAndDuration(20).duration==5);
}

void testIntToNotation() {
	NoteWithDuration note;
	Song song;
	note.note = 0;
	note.duration = 1;
	NoteAsNotation result = song.intToNotation(note.note);
	
	assert(result.letter == 'C');
	assert(result.octave == 5);
	assert(result.alteration == 0);
	
	note.note++;
	result = song.intToNotation(note.note);
	assert(result.letter == 'C');
	assert(result.octave == 5);
	assert(result.alteration == 1);
	
	note.note++;
	result = song.intToNotation(note.note);
	assert(result.letter == 'D');
	assert(result.octave == 5);
	assert(result.alteration == 0);
	
	note.note++;
	result = song.intToNotation(note.note);
	assert(result.letter == 'E');
	assert(result.octave == 5);
	assert(result.alteration == -1);
	
	note.note++;
	result = song.intToNotation(note.note);
	assert(result.letter == 'E');
	assert(result.octave == 5);
	assert(result.alteration == 0);
	
	note.note = 13;
	result = song.intToNotation(note.note);
	assert(result.letter == 'C');
	assert(result.octave == 6);
	assert(result.alteration == 1);
	
	note.note = -1;
	result = song.intToNotation(note.note);
	assert(result.letter == 'B');
	assert(result.octave == 4);
	assert(result.alteration == 0);
	
	note.note = -12;
	result = song.intToNotation(note.note);
	assert(result.letter == 'C');
	assert(result.octave == 4);
	assert(result.alteration == 0);
}

void testNoteTypeString() {
	Song song;
	song.setSmallestInterval(256);
	assert(song.noteTypeString(256)=="<type>whole</type>");
	assert(song.noteTypeString(128)=="<type>half</type>");
	assert(song.noteTypeString(64)=="<type>quarter</type>");
	assert(song.noteTypeString(32)=="<type>eighth</type>");
	assert(song.noteTypeString(16)=="<type>16th</type>");
	assert(song.noteTypeString(8)=="<type>32nd</type>");
	assert(song.noteTypeString(4)=="<type>64th</type>");
	assert(song.noteTypeString(2)=="<type>128th</type>");
	assert(song.noteTypeString(1)=="<type>256th</type>");
	assert(song.noteTypeString(1)=="<type>256th</type>");
	
}

void testNoteToXML() {
	NoteWithDuration note;
	note.note = 0;
	note.duration = 256/4;
	Song song;
	song.setSmallestInterval(256);
	
	//testing one octave above
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><alter>1</alter><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>D</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>E</step><alter>-1</alter><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>E</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>F</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>F</step><alter>1</alter><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>G</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>G</step><alter>1</alter><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>A</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>B</step><alter>-1</alter><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>B</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>6</octave></pitch><duration>1</duration><type>quarter</type></note>");
	
	//testing one octave below
	note.note = -12;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><alter>1</alter><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>D</step><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>E</step><alter>-1</alter><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>E</step><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>F</step><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>F</step><alter>1</alter><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>G</step><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>G</step><alter>1</alter><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>A</step><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>B</step><alter>-1</alter><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>B</step><octave>4</octave></pitch><duration>1</duration><type>quarter</type></note>");
	note.note++;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type></note>");
	
	//testing different note lengths
	note.note = 0;
	note.duration /= 2;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>eighth</type></note>");
	
	note.duration /= 2;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>16th</type></note>");
	
	note.duration /= 2;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>32nd</type></note>");
	
	note.duration /= 2;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>64th</type></note>");
	
	note.duration /= 2;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>128th</type></note>");
	
	note.duration /= 2;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>256th</type></note>");
	
	note.duration = 256/2;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>half</type></note>");
	
	note.duration = 256;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>whole</type></note>");
	
	//testing dotted notes
	note.duration = 3;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>128th</type><dot/></note>");
	
	note.duration = 6;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>64th</type><dot/></note>");
	
	note.duration = 12;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>32nd</type><dot/></note>");
	
	note.duration = 24;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>16th</type><dot/></note>");
	
	note.duration = 48;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>eighth</type><dot/></note>");
	
	note.duration = 96;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>quarter</type><dot/></note>");
	
	note.duration = 192;
	assert(song.noteToXML(note)=="<note><pitch><step>C</step><octave>5</octave></pitch><duration>1</duration><type>half</type><dot/></note>");
	
	//testing rests
	note.note = REST;
	note.duration = 64;
	assert(song.noteToXML(note)=="<note><rest/><duration>1</duration><type>quarter</type></note>");
}
