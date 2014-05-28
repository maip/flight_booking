/**
 * @file date_time.h
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * The DateTime class is used to represent dates including month, day, and year
 * as well as times in 24 hour clock.
 */
#ifndef DATETIME_H
#define DATETIME_H

#include <iostream> 
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;


class DateTime {
 public: 
  DateTime();
  DateTime(int min, int hr, int d, int mo, int yr);
  
  void AddMinutes(int min);
  int CompareTo(DateTime other);
  string ToString();
  
  int minutes();
  int hours();
  int day();
  int month();
  int year();
  void set_hours(int hr);
  void set_minutes(int min);
  void set_day(int d);
  void set_month(int mo);
  void set_year(int yr);

 private:
  int minutes_;
  int hours_;
  int day_;
  int month_;
  int year_;
};

#endif
