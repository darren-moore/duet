#pragma once

struct Note{
	enum eStemType { none, start, halfStart, end, halfEnd };

	Note(int noteLength, int notePitch, eStemType stemType, int stemHeight, bool isStemUp, bool isRest) :
		noteLength(noteLength), notePitch(notePitch), stemType(stemType), stemHeight(stemHeight), isStemUp(isStemUp), isRest(isRest) {
		isDotted = noteLength == 3 || noteLength == 6 || noteLength == 12;
	};

	int noteLength;	// Each unit denotes a 1/16th note value.
	int notePitch;	// No accidentals. Each unit denotes one line/space movement above a 'G' below the staff.
	eStemType stemType;
	int stemHeight;
	bool isStemUp;
	bool isRest;
	bool isDotted;

	float distToNextNote;

};
