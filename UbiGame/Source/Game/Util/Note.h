#pragma once

struct Note{
	enum eStemType { none, start, middle, end };
	enum eNoteLength { whole, half, quarter, eighth, sixteenth };

	Note(eStemType stemType, bool isStemUp, bool isDotted, bool isRest) :
		stemType(stemType), isStemUp(isStemUp), isDotted(isDotted), isRest(isRest) {};

	eNoteLength noteLength;
	eStemType stemType;
	bool isStemUp;
	bool isDotted;
	bool isRest;

};