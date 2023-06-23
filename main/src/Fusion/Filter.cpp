#include "Filter.h"

Fusion::Filter::Quat Fusion::Filter::QuatMul(const Fusion::Filter::Quat L, const Fusion::Filter::Quat R){
	return {
			(L.q1 * R.q1) - (L.q2 * R.q2) - (L.q3 * R.q3) - (L.q4 * R.q4),
			(L.q1 * R.q2) + (L.q2 * R.q1) + (L.q3 * R.q4) - (L.q4 * R.q3),
			(L.q1 * R.q3) - (L.q2 * R.q4) + (L.q3 * R.q1) + (L.q4 * R.q2),
			(L.q1 * R.q4) + (L.q2 * R.q3) - (L.q3 * R.q2) + (L.q4 * R.q1)
	};
}

void Fusion::Filter::QuatMulScalar(Fusion::Filter::Quat& q, double scalar){
	q.q1 *= scalar;
	q.q2 *= scalar;
	q.q3 *= scalar;
	q.q4 *= scalar;
};

Fusion::Filter::Quat Fusion::Filter::QuatAdd(const Fusion::Filter::Quat l, const Fusion::Filter::Quat r){
	return {
			l.q1 + r.q1,
			l.q2 + r.q2,
			l.q3 + r.q3,
			l.q4 + r.q4
	};
}

Fusion::Filter::Quat Fusion::Filter::QuatSub(const Fusion::Filter::Quat l, const Fusion::Filter::Quat r){
	return {
			l.q1 - r.q1,
			l.q2 - r.q2,
			l.q3 - r.q3,
			l.q4 - r.q4
	};
}

Fusion::Filter::Quat Fusion::Filter::QuatConjug(Fusion::Filter::Quat q){
	q.q2 = -q.q2;
	q.q3 = -q.q3;
	q.q4 = -q.q4;
	return q;
}

double Fusion::Filter::QuatNorm(const Fusion::Filter::Quat q){
	return std::sqrt(q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3 + q.q4 * q.q4);
}

void Fusion::Filter::QuatNormalize(Fusion::Filter::Quat& q){
	float norm = QuatNorm(q);
	q.q1 /= norm;
	q.q2 /= norm;
	q.q3 /= norm;
	q.q4 /= norm;
}

Fusion::Orient Fusion::Filter::QuatToEuler(Fusion::Filter::Quat q){
	double yaw = atan2f((2.0 * q.q2 * q.q3 - 2.0 * q.q1 * q.q4), (2.0 * q.q1 * q.q1 + 2.0 * q.q2 * q.q2 - 1.0));  // equation (7)
	double pitch = -asinf(2.0 * q.q2 * q.q4 + 2.0 * q.q1 * q.q3);                                  // equatino (8)
	double roll = atan2f((2.0 * q.q3 * q.q4 - 2.0 * q.q1 * q.q2), (2.0 * q.q1 * q.q1 + 2.0 * q.q4 * q.q4 - 1.0));

	yaw *= (180.0 / M_PI);
	pitch *= (180.0 / M_PI);
	roll *= (180.0 / M_PI);

	return { -roll, yaw, -pitch };
}

Fusion::Filter::Quat Fusion::Filter::EulerToQuat(double pitch, double yaw, double roll){
	double c1 = cos(yaw/2.0);
	double s1 = sin(yaw/2.0);
	double c2 = cos(pitch/2.0);
	double s2 = sin(pitch/2.0);
	double c3 = cos(roll/2.0);
	double s3 = sin(roll/2.0);
	double c1c2 = c1*c2;
	double s1s2 = s1*s2;
	double w =c1c2*c3 - s1s2*s3;
	double x =c1c2*s3 + s1s2*c3;
	double y =s1*c2*c3 + c1*s2*s3;
	double z =c1*s2*c3 - s1*c2*s3;
	return { w, x, y, z };
}
