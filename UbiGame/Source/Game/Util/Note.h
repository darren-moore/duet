#pragma once

struct Note{
	enum eStemType { none, start, middle, end };
	enum eNoteLength { whole=1, half=2, quarter=4, eighth=8 };

	Note(eNoteLength noteLength, eStemType stemType, bool isStemUp, bool isDotted, bool isRest) :
		noteLength(noteLength), stemType(stemType), isStemUp(isStemUp), isDotted(isDotted), isRest(isRest) {};

	eNoteLength noteLength;
	eStemType stemType;
	bool isStemUp;
	bool isDotted;
	bool isRest;

};
