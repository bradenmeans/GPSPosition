// Name: Braden Means

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GpsPosition.h"
#include <math.h>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream inF;
	ofstream outF;

	string inputfile = argv[1];
	string outputfile = argv[2];
	string line;
	char c;
	char x, y, z, n;
	string str = "", str2, str3, str4;
	GpsPosition Position;
	string latitude, longitude, remove = "abcde,";
	string time, degrees, DMSmins, degrees2, DMSmins2;
	istringstream ss(str2);
	string delimiter = ",";
	string hrs, mins, secs;
	int count = 0;
	unsigned long timeSeconds = 0;
	double calcLat, calcLong;
	int k = 0, j =0, flag = 0, temp = 0, fill = 0, m = 0, flag2 = 0;
	int tempTime = 0;



	inF.open(inputfile);
	outF.open(outputfile);

	while (getline(inF, line)) {
		for (int i = 0; i < 6; i++) {
			c = line[i];
			str += c;
		}
		if (str.compare("$GPGGA") == 0) {
			size_t pos = 0;
			size_t pos2 = 0;
			size_t pos3 = 0;
			size_t pos4 = 0;
			string token;
			while ((pos = line.find(delimiter)) != string::npos) {

				if (count == 1 && line[0] == 'a') {
					line.erase(0, pos + line.length());
					flag2 = 1;
					count--;
				}

				// Converts time from UTC to seconds
				if (count == 1) {
					time = line.substr(0, pos);
					for (int i = 0; i < time.length(); i++) {
						x = time[i];
						str2 += x;
						if (i == 1) {
							hrs = str2;
							if (stoi(hrs) > 24) {
								line.erase(0, pos + line.length());
								flag2 = 1;
								count--;
							}
							str2.erase(0, pos2 + str2.length());
						}
						if (i == 3) {
							mins = str2;
							str2.erase(0, pos2 + str2.length());
						}
						else if (i > 3) {
							secs = str2;
						}
					}
				}
				
				// Converts latitude from DMS to decimal degrees
				if (count == 2) {
					latitude = line.substr(0, pos);
					for (int i = 0; i < latitude.length(); i++) {
						y = latitude[i];
						str3 += y;
						if (i == 1) {
							degrees = str3;
							str3.erase(0, pos3 + str3.length());
						}
						else if (i > 1) {
							DMSmins = str3;
						}
					}
				}

				// Converts longitude from DMS to decimal degrees
				if (count == 4) {
					longitude = line.substr(0, pos);
					for (int i = 0; i < longitude.length(); i++) {
						z = longitude[i];
						str4 += z;
						if (i == 2) {
							degrees2 = str4;
							str4.erase(0, pos4 + str4.length());
						}
						else if (i > 2) {
							DMSmins2 = str4;
						}
					}
				}

				count++;
				line.erase(0, pos + delimiter.length());

			}

			if (flag2 == 0) {
				calcLong = (stoi(degrees2)) + (stod(DMSmins2) / 60);
				calcLat = (stoi(degrees)) + (stod(DMSmins) / 60);
				timeSeconds = (stoi(hrs) * 3600) + (stoi(mins) * 60) + (stoi(secs));

				// Checks to make sure time in input file is valid
				if (tempTime > timeSeconds) {
					return -1;
				}
				tempTime = timeSeconds;

				// Signals that input times are skipped, must be filled
				if (temp != timeSeconds - 1 && k > 0) {
					flag = 1;
				}

				double average = (Position.CalcDistanceKmTo(GpsPosition(calcLat, calcLong, timeSeconds)) * 3600);

				// If not first line and no input times skipped, then just prints to file, otherwise fills input times to output file, divides by average
				if (k != 0 && flag == 0) {
					outF << timeSeconds << " " << Position.CalcDistanceKmTo(GpsPosition(calcLat, calcLong, timeSeconds)) * 3600 << endl;
				}
				else if (k != 0 && flag != 0) {

					for (fill = temp; fill < timeSeconds; fill++) {
						j++;
					}

					for (fill = temp + 1; fill <= timeSeconds; fill++) {
						outF << fill << " " << average / j << endl;
					}

					j = 0;
				}
				else {
					k++;
				}

				temp = timeSeconds;

				flag = 0;

				// Sets previous inputs to calculate next position
				Position.SetLatitude(calcLat);
				Position.SetLongitude(calcLong);
				Position.SetTime(timeSeconds);
			}
			flag2 = 0;

		}
		str4 = "";
		str3 = "";
		str2 = "";
		count = 0;
		str = "";
	}
	inF.close();
	outF.close();
	system("pause");
}
