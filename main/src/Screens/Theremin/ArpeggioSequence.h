#ifndef CLOCKSTAR_FIRMWARE_ARPEGGIOSEQUENCE_H
#define CLOCKSTAR_FIRMWARE_ARPEGGIOSEQUENCE_H

#include "Util/Notes.h"
#include <random>

class ArpeggioSequence {
	typedef uint16_t Note;
public:
	void setBaseNoteIndex(uint16_t index);
	void setBaseNote(Note note);
	void setSize(uint8_t size);
	void refresh();

	[[nodiscard]] uint16_t getBaseNoteIndex() const;
	[[nodiscard]] uint16_t getBaseNote() const;
	[[nodiscard]] uint8_t getSize() const;
	[[nodiscard]] const std::vector<Note>& getTones() const;


	static constexpr Note NotesArray[] = {
			NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_B2,
			NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3,
			NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4,
			NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
			NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6,
			NOTE_C7, NOTE_D7, NOTE_E7, NOTE_F7, NOTE_G7, NOTE_A7, NOTE_B7,
			NOTE_C8, NOTE_D8
	};
	static constexpr uint16_t NotesArraySize = sizeof(NotesArray) / sizeof(NotesArray[0]);
	static constexpr uint8_t MaxSequenceSize = 6;
	static constexpr uint16_t MaxBaseNoteIndex = (NotesArraySize - MaxSequenceSize);

private:

	uint16_t baseNoteIndex = 7; //defaults to NOTE_E3, ranges from 0 to (NumNotes - MaxSequenceSize)
	uint8_t sequenceSize = 1; // ranges from 1 to MaxSequenceSize
	std::vector<Note> sequence{};
	void addRandomNotes(uint8_t num);
};


#endif //CLOCKSTAR_FIRMWARE_ARPEGGIOSEQUENCE_H
