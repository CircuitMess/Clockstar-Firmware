#ifndef CLOCKSTAR_FIRMWARE_HYSTERESIS_H
#define CLOCKSTAR_FIRMWARE_HYSTERESIS_H


#include <initializer_list>
#include <vector>

class Hysteresis {
public:
	struct threshold {
		int low;
		int high;
		int level;
	};

	Hysteresis(std::initializer_list<threshold> thresholds);

	[[nodiscard]] int get() const;
	int update(int val);
	void reset(int toVal = 0);

private:
	const std::vector<threshold> thresholds;

	int discrete_level = 0;
	int prev_val = 0;
};


#endif //CLOCKSTAR_FIRMWARE_HYSTERESIS_H
