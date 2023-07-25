#ifndef CLOCKSTAR_FIRMWARE_HYSTERESIS_H
#define CLOCKSTAR_FIRMWARE_HYSTERESIS_H


#include <initializer_list>
#include <vector>

class Hysteresis {
public:

	/**
	 * @param thresholds Ordered low to high. Should include min and max values
	 * count(levels) = count(thresholds)-1
	 */
	Hysteresis(std::initializer_list<int> thresholds, int margin);

	int get() const;

	int update(int val);
	int reset(int val = 0);

private:
	// define input to output conversion table/formula by specifying endpoints of the levels.
	// the number of end points is equal to the number of output levels plus one.
	// in the example below, output level 0 results from an input of between 0 and 112.
	// 1 results from an input of between 113 and 212 etc.
	const std::vector<int> Thresholds;

	// set the number of output levels. These are numbered starting from 0.
	const int LevelCount;  // 0..9

	// margin sets the 'stickyness' of the hysteresis or the relucatance to leave the current state.
	// It is measured in units of the the input level. As a guide it is a few percent of the
	// difference between two end points. Don't make the margin too wide or ranges may overlap.
	const int Margin;

	int currentLevel;

	int findLevel(int val);

};


#endif //CLOCKSTAR_FIRMWARE_HYSTERESIS_H
