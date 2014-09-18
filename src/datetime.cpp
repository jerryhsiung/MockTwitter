#include "../include/datetime.h"

using namespace std;

DateTime::DateTime()
{}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
  hour = hh;
  min = mm;
  sec = ss;
  y = year;
  m = month;
  d = day;
}

bool DateTime::operator<(const DateTime& other) const
{
	if (y != other.y) {
		return (y < other.y);
	}
	else if (m != other.m) {
		return (m < other.m);
	}
	else if (d != other.d) {
		return (d < other.d);
	}
	else if (hour != other.hour) {
		return (hour < other.hour);
	}
	else if (min != other.min) {
		return (min < other.min);
	} 
	else if (sec != other.sec) {
		return (sec < other.sec);
	} 
	else {
		return false;
	}
}

bool DateTime::operator>(const DateTime& other) const
{
	if (y != other.y) {
		return (y > other.y);
	}
	else if (m != other.m) {
		return (m > other.m);
	}
	else if (d != other.d) {
		return (d > other.d);
	}
	else if (hour != other.hour) {
		return (hour > other.hour);
	}
	else if (min != other.min) {
		return (min > other.min);
	} 
	else if (sec != other.sec) {
		return (sec > other.sec);
	} 
	else {
		return false;
	}
}

ostream& operator<<(ostream& os, const DateTime& other)
{
   os << other.y << "-" << other.m << "-" << other.d << " " << other.hour << ":" << other.min << ":" << other.sec;
   return os;
}