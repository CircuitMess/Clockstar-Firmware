#include "ArpeggioSequence.h"
#include <algorithm>
#include <esp_random.h>

void ArpeggioSequence::setBaseNote(Note note){
	const auto it = std::find(std::begin(NotesArray), std::end(NotesArray), note);
	if(it == std::end(NotesArray)) return;

	auto index = std::distance(std::begin(NotesArray), it);

	setBaseNoteIndex(index);
}

void ArpeggioSequence::setBaseNoteIndex(uint16_t index){
	if(index > MaxBaseNoteIndex) return;

	const auto diff = index - baseNoteIndex;
	if(diff == 0) return;

	for(auto& note : sequence){
		const auto i = std::find(std::begin(NotesArray), std::end(NotesArray), note);
		const auto noteIndex = std::distance(NotesArray, i);
		note = NotesArray[noteIndex + diff];
	}
	baseNoteIndex = index;
}

void ArpeggioSequence::setSize(uint8_t size){
	if(size < 1 || size > MaxSequenceSize) return;

	const auto diff = int(size) - int(sequenceSize);
	const auto absDiff = abs(diff);
	if(diff == 0) return;

	sequenceSize = size;
	if(diff < 0){
		for(auto i = 0; i < absDiff; i++){
			sequence.pop_back();
		}
	}else{
		addRandomNotes(absDiff);
	}
}

void ArpeggioSequence::addRandomNotes(uint8_t num){
	if(num == 0 || num > MaxSequenceSize) return;

	std::vector<Note> possibleNotes = { NotesArray + baseNoteIndex, NotesArray + baseNoteIndex + sequenceSize };

	for(auto& note : sequence){
		const auto it = std::find(std::begin(possibleNotes), std::end(possibleNotes), note);
		if(it != std::end(possibleNotes)){
			possibleNotes.erase(it);
		}
	}

	for(auto i = 0; i < num; i++){
		sequence.push_back(possibleNotes[esp_random() % possibleNotes.size()]);
	}
}

void ArpeggioSequence::refresh(){
	sequence.clear();
	sequence.push_back(NotesArray[baseNoteIndex]);
	addRandomNotes(sequenceSize - 1);
}

const std::vector<ArpeggioSequence::Note>& ArpeggioSequence::getTones() const{
	return sequence;
}

uint16_t ArpeggioSequence::getBaseNoteIndex() const{
	return baseNoteIndex;
}

uint16_t ArpeggioSequence::getBaseNote() const{
	return NotesArray[baseNoteIndex];
}

uint8_t ArpeggioSequence::getSize() const{
	return sequenceSize;
}
