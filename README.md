SuperSimpleSongSynthesiser
==========================

One Sentence Description
------------------------
This is a low power, low boilerplate C++ class for generating music notation.

Possible Applications
---------------------
When learning a new instrument you often want to practice reading music. In particular specific patterns of notes in specific keys. When the notes are thought of as a sequence of integers representing semitones above (or below) middle C, its quite tempting to want to generate musical exercises with a computer. This class bridges the gap between just generating a sequence of numbers, and outputting a sheet of music.

When composing a piece of music, or writing an instrumental solo, typically a composer sits with a piano and randomly plays whatever comes to them until they play something that sounds like what they're after. The artist's intuition is what is generating the notes and rhythms. Suppose you have a very firm grasp of your own musical intuition, to the point you could codeify the mood, tone, and flow of the music you're after into C++ code. This class will let you listen to hours and hours of your musings while you're not sitting specifically at a piano. When you hear something you like, you have the notes in a format MuseScore/Sibelius understands.

Examples
--------
The following code generates two octaves of the C-chromatic scale in quarter notes.

```
int main() {
	Song song;
	song.setSmallestInterval(4);

	for(int note=-12;note<=12;note++) {
		song.appendNote(note);
	}

	song.renderSingleNotelistToXML("out.xml");
}
```

The output when rendered by [MuseScore](http://musescore.org/) looks like [this](https://github.com/mooshmoosh/SuperSimpleSongSynthesiser/blob/master/CChromatic-1.png)

The following code generates a short C-Blues solo.

```
int main() {
	int note;
	int duration;

	int bluesScaleNotes[] = {-12,-9,-7,-6,-5,-2,0,3,5,6,7,10,12};

	Song song;
	song.setSmallestInterval(4);

	for(int i=0;i<=16;i++) {
		note = bluesScaleNotes[rand() % 13];
		duration = rand() % 3 + 1;
		song.appendNote(note,duration);
	}

	song.renderSingleNotelistToXML("out.xml");
}
```

The output when rendered by [MuseScore](http://musescore.org/) looks like [this](https://github.com/mooshmoosh/SuperSimpleSongSynthesiser/blob/master/CBlues-1.png)

About the code
--------------
Unit tests can be run with `make check`

If you are familiar with Valgrind, you can check for memory leaks with `make check_memory`

Over time, whenever I have free time I'll be cleaning up bits and pieces of the code, if you have any suggestions or complaints, don't hesitate to write to me. If you want write access just ask.

To Do
-----
- When generating notes that are an eighth or shorter, they need to be grouped. Create a new function for generating XML code from a NoteWithDuration object. Take an argument which decides if the note is at the beginning, middle or end of a grouping of notes.
	- the first note it the set has `<beam number="1">begin</beam>` added
	- the last note in the set has `<beam number="1">continue</beam>` added
	- All notes in between have `<beam number="1">end</beam>` added
	
- Write a function that takes a number of beats left in a bar, and creates a sequence of NoteAndDuration objects that fill that much time.

- A new version of noteToXML function that can print out notes that are tied together.
	- the first tied note has `<notations><tied type="start"/></notations>`
	- the last has `<notations><tied type="stop"/></notations>`
	- all in between have `<notations><tied type="stop"/><tied type="start"/></notations>`

- Make the main generator take bar lines into account
	- in the main loop keep track of how many beats are left in the bar after adding each note
	- if the next note will go over the amount of time left, use the above function to create a list of notes to add to fill the rest of the bar
	- Add these to the file, all tied together
	- write the bar line
	- write the remainder of the note tied to the previous ones.
