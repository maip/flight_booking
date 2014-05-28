/**
 * @file date_time.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * This contains the implementation of DateTime class.
 *
 * See top of date_time.h for a complete description.
 */
#include "date_time.h"
 

/**
 * Default constructor.
 */
DateTime::DateTime()
    : minutes_(0), hours_(0), day_(0), month_(0), year_(0) {
}

/**
 * Overloaded constructor.
 */
DateTime::DateTime(int min, int hr, int d, int mo, int yr)
    : minutes_(min), hours_(hr), day_(d), month_(mo), year_(yr) {
}

/**
 * Adds minutes. If the new sum is at least 60 minutes, it carries over to
 * hours. If the new sum of hours is at least 24 hours, it carries over to days.
 * Stops checking at days.
 */
void DateTime::AddMinutes(int min) {
  minutes_ += min;
  if (minutes_ >= 60){
    hours_ += minutes_ / 60;
    minutes_ = minutes_ % 60;
    if (hours_ >= 24) {
      day_ += hours_ / 24;
      hours_ = hours_ % 24;
    }
  }   
}

/**
 * Returns 1 if both DateTime objects are equal, -1 if this is before the other
 * DateTime, and 1 if this is after the other DateTime.
 */
int DateTime::CompareTo(DateTime other) {
  int other_yr = other.year();
  int other_mo = other.month();
  int other_day = other.day();
  int other_min = other.minutes();
  int other_hr = other.hours();
  
  if (year_ < other_yr) {
    return -1;
  } else if (year_ > other_yr) {
    return 1;
  } else {  // if years are equal
    if (month_ < other_mo) {
      return -1;
    } else if (month_ > other_mo) {
      return 1;
    } else {  // if months are equal
      if (day_ < other_day) {
        return -1;
      } else if (day_ < other_day) {
        return 1;
      } else {  // if days are equal
        if (hours_ < other_hr) {
          return -1;
        } else if (hours_ > other_hr) {
          return 1;
        } else {  // if hours are equal
          if (minutes_ < other_min) {
            return -1;
          } else if (minutes_ > other_min) {
            return 1;
          } else {
            return 0; // both flights have exact same time and date
          }
        }
      }
    }
  }
}


/**
 * Formats DateTime as XX/XX/XXXX XX:XX in this order:
 * month, day, year, hours, minutes.
 */
string DateTime::ToString() {
  string hours_str = to_string(hours_);
  string minutes_str = to_string(minutes_);
  
  if (hours_ < 10) {
    hours_str = "0" + hours_str;
  }
  if (minutes_ < 10) {
    minutes_str = "0" + minutes_str;
  }

  return (to_string(month_) + "/" + to_string(day_) + "/" + to_string(year_) +
          "\t" + hours_str + ":" + minutes_str);
}

int DateTime::minutes() {
  return minutes_;
}

int DateTime::hours() {
  return hours_;
}

int DateTime::day() {
  return day_;
}

int DateTime::month() {
  return month_;
}

int DateTime::year() {
  return year_;
}

void DateTime::set_minutes(int min) {
  minutes_ = min;
}

void DateTime::set_hours(int hr) {
  hours_ = hr;
}

void DateTime::set_day(int d) {
  day_ = d;
}

void DateTime::set_month(int mo) {
  month_ = mo;
}

void DateTime::set_year(int yr) {
  year_ = yr;
}
