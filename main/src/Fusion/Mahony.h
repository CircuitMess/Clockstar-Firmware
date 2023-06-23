#ifndef CLOCKSTAR_FIRMWARE_MAHONY_H
#define CLOCKSTAR_FIRMWARE_MAHONY_H

#include "Filter.h"

namespace Fusion {

class Mahony : public Filter {
public:

	Orient update(IMU::Sample sample) override;
	Orient get() override;

private:
	static constexpr double twoKpDef = (2.0f * 0.5f); // 2 * proportional gain
	static constexpr double twoKiDef = (2.0f * 0.0f); // 2 * integral gain

	Quat q = { 1, 0, 0, 0 };

	double twoKp = twoKpDef;
	double twoKi = twoKiDef;
	double integralFBx = 0.0f,  integralFBy = 0.0f, integralFBz = 0.0f;

	static double invSqrt(double x);

};

}


#endif //CLOCKSTAR_FIRMWARE_MAHONY_H
