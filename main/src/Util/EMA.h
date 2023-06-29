#ifndef CLOCKSTAR_FIRMWARE_EMA_H
#define CLOCKSTAR_FIRMWARE_EMA_H


class EMA {
public:
	EMA(double a);

	double get();
	double update(double val);
	void reset(double toVal = 0);

private:
	double a;
	double val = 0;

};


#endif //CLOCKSTAR_FIRMWARE_EMA_H
