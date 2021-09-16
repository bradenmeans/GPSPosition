// Name: Braden Means
// NetId: bradenmeans
// Date: 12/3/18
// Project: Project 5

#ifndef GPSPOSITION_H
#define GPSPOSITION_H

#include <iostream>
#include <string>

using namespace std;

class GpsPosition {
private:
	double _longitude;
	double _latitude;
	unsigned long _timeSeconds;
public:
	GpsPosition();
	GpsPosition(double latitude, double longitude, unsigned long timeSeconds);
	double GetLongitude() const;
	double GetLatitude() const;
	unsigned long GetTime() const;
	void SetLongitude(double longitude);
	void SetLatitude(double latitude);
	void SetTime(unsigned long timeSeconds);
	double CalcDistanceKmTo(GpsPosition toPosition);
};


#endif