// Name: Braden Means
// NetId: bradenmeans
// Date: 12/3/18
// Project: Project 5

#include "GpsPosition.h"
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

GpsPosition::GpsPosition() {
	_longitude = 0;
	_latitude = 0;
	_timeSeconds = 0;
}

GpsPosition::GpsPosition(double latitude, double longitude, unsigned long timeSeconds) {
	_longitude = longitude;
	_latitude = latitude;
	_timeSeconds = timeSeconds;
}

double GpsPosition::GetLatitude() const {
	return _latitude;
}

double GpsPosition::GetLongitude() const {
	return _longitude;
}

unsigned long GpsPosition::GetTime() const {
	return _timeSeconds;
}

void GpsPosition::SetLatitude(double latitude) {
	_latitude = latitude;
}

void GpsPosition::SetLongitude(double longitude) {
	_longitude = longitude;
}

void GpsPosition::SetTime(unsigned long timeSeconds) {
	_timeSeconds = timeSeconds;
}

double GpsPosition::CalcDistanceKmTo(GpsPosition toPosition) {
	const double EarthRadiusKm = 6371.0;
	const double PI = 3.14159265358979323846;
	double fromLatitudeRad;
	double fromLongitudeRad;
	double toLatitudeRad;
	double toLongitudeRad;
	double deltaLatitude;
	double deltaLongitude;
	double a;
	double c;

	// Convert to radians
	fromLatitudeRad = PI * this->GetLatitude() / 180.0;
	fromLongitudeRad = PI * this->GetLongitude() / 180.0;
	toLatitudeRad = PI * toPosition.GetLatitude() / 180.0;
	toLongitudeRad = PI * toPosition.GetLongitude() / 180.0;

	// Calculate delta for latituce and longitud
	deltaLatitude = toLatitudeRad - fromLatitudeRad;
	deltaLongitude = toLongitudeRad - fromLongitudeRad;

	// Calculate great-circle distance using haversine formula
	a = (sin(deltaLatitude / 2) * sin(deltaLatitude / 2)) +
		(sin(deltaLongitude / 2) * sin(deltaLongitude / 2) *
			cos(fromLatitudeRad) * cos(toLatitudeRad));
	c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return EarthRadiusKm * c;
}