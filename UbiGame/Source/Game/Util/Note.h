#pragma once

struct Note{
	enum eStemType { none, start, middle, end };

	Note(int noteLength, eStemType stemType, bool isStemUp, bool isRest) :
		noteLength(noteLength), stemType(stemType), isStemUp(isStemUp), isRest(isRest) {
			isDotted = noteLength == 3 || noteLength == 6 || noteLength == 12;
	};

	int noteLength;
	eStemType stemType;
	bool isStemUp;
	bool isRest;
	bool isDotted;

};
