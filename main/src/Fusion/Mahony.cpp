#include "Mahony.h"
#include "../lib/glm/glm/gtc/quaternion.hpp"

Fusion::Orient Fusion::Mahony::update(IMU::Sample sample){
	double ax = sample.accelX;
	double ay = sample.accelY;
	double az = sample.accelZ;
	double gx = sample.gyroX;
	double gy = sample.gyroY;
	double gz = sample.gyroZ;

	double recipNorm;
	double halfvx, halfvy, halfvz;
	double halfex, halfey, halfez;
	double qa, qb, qc;

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Estimated direction of gravity and vector perpendicular to magnetic flux
		halfvx = q.q2 * q.q4 - q.q1 * q.q3;
		halfvy = q.q1 * q.q2 + q.q3 * q.q4;
		halfvz = q.q1 * q.q1 - 0.5f + q.q4 * q.q4;

		// Error is sum of cross product between estimated and measured direction of gravity
		halfex = (ay * halfvz - az * halfvy);
		halfey = (az * halfvx - ax * halfvz);
		halfez = (ax * halfvy - ay * halfvx);

		// Compute and apply integral feedback if enabled
		if(twoKi > 0.0f) {
			integralFBx += twoKi * halfex * DeltaT;	// integral error scaled by Ki
			integralFBy += twoKi * halfey * DeltaT;
			integralFBz += twoKi * halfez * DeltaT;
			gx += integralFBx;	// apply integral feedback
			gy += integralFBy;
			gz += integralFBz;
		}
		else {
			integralFBx = 0.0f;	// prevent integral windup
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}

	// Integrate rate of change of quaternion
	gx *= (0.5f * DeltaT);		// pre-multiply common factors
	gy *= (0.5f * DeltaT);
	gz *= (0.5f * DeltaT);
	qa = q.q1;
	qb = q.q2;
	qc = q.q3;
	q.q1 += (-qb * gx - qc * gy - q.q4 * gz);
	q.q2 += (qa * gx + qc * gz - q.q4 * gy);
	q.q3 += (qa * gy - qb * gz + q.q4 * gx);
	q.q4 += (qa * gz + qb * gy - qc * gx);

	// Normalise quaternion
	recipNorm = invSqrt(q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3 + q.q4 * q.q4);
	q.q1 *= recipNorm;
	q.q2 *= recipNorm;
	q.q3 *= recipNorm;
	q.q4 *= recipNorm;

	glm::dquat qConverted = { q.q1, q.q2, q.q3, q.q4 };
	auto euler = glm::eulerAngles(qConverted);
	glm::vec3 derotAngles = { 0, 0, -euler.z };
	auto derot = glm::dquat{ derotAngles };
	qConverted = derot * qConverted;
	qConverted = glm::normalize(qConverted);
	q.q1 = qConverted.w;
	q.q2 = qConverted.x;
	q.q3 = qConverted.y;
	q.q4 = qConverted.z;

	return get();
}

Fusion::Orient Fusion::Mahony::get(){

	glm::dquat glmQuat = { q.q1, q.q2, q.q3, q.q4 };
	auto final = glm::eulerAngles(glmQuat);

	auto pitch = glm::degrees(M_PI - final.x);
	if(pitch > 180){
		pitch -= 360;
	}

	return { pitch, glm::degrees(final.z), glm::degrees(final.y) };
}

double Fusion::Mahony::invSqrt(double x){
	double halfx = 0.5 * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
