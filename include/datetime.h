#ifndef DATETIME_H
#define DATETIME_H
#include <iostream>

struct DateTime
{
  DateTime();

  DateTime(int hh, int mm, int ss, int year, int month, int day);

  /**
   * Return true if the timestamp is less-than other's
   *
   * @return result of less-than comparison of timestamp
   */
  bool operator<(const DateTime& other) const;

  /**
   * Return true if the timestamp is greater-than other's
   *
   * @return result of greater-than comparison of timestamp
   */
  bool operator>(const DateTime& other) const;

  /**
   * Outputs the timestamp to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS
   *
   * @return the ostream passed in as an argument
   */
  friend std::ostream& operator<<(std::ostream& os, const DateTime& other);

  int hour, min, sec, y, m, d;

};

#endif