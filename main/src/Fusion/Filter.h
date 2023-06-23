#ifndef CLOCKSTAR_FIRMWARE_FILTER_H
#define CLOCKSTAR_FIRMWARE_FILTER_H

#include "Devices/IMU.h"

namespace Fusion {

struct Orient { double pitch, yaw, roll; };

class Filter {
public:

	virtual Orient update(IMU::Sample sample) = 0;
	virtual Orient get() = 0;

protected:

	static constexpr double DeltaT = 1.0/104.0; // 104Hz sample rate

	struct Quat {
		double q1, q2, q3, q4;
	};

	static Quat QuatMul(Quat l, Quat r);
	static void QuatMulScalar(Quat& q, double scalar);
	static Quat QuatAdd(Quat l, Quat r);
	static Quat QuatSub(Quat l, Quat r);
	static Quat QuatConjug(Quat q);
	static double QuatNorm(Quat q);
	static void QuatNormalize(Quat& q);
	static Quat EulerToQuat(double pitch, double yaw, double roll);

	static Orient QuatToEuler(Quat q);

};

}


#endif //CLOCKSTAR_FIRMWARE_FILTER_H
