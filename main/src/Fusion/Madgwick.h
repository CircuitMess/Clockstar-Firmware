#ifndef CLOCKSTAR_FIRMWARE_MADGWICK_H
#define CLOCKSTAR_FIRMWARE_MADGWICK_H

#include "Filter.h"

namespace Fusion {

class Madgwick : public Filter {
public:

	Orient update(IMU::Sample sample) override;
	Orient get() override;

private:
	Quat q_est = { 1, 0, 0, 0 };

	static constexpr double GyroMeanError = M_PI * (5.0/180.0);
	static constexpr double Beta =  GyroMeanError * 0.8660254; // sqrt(3/4)

};

}


#endif //CLOCKSTAR_FIRMWARE_MADGWICK_H
