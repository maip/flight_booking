/**
* @file flight_path.h
* @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
*
* The FlightPath class represents possible flight paths, either direct or with
* a connecting flight. It is implemented as a linked list.
*/
#ifndef FLIGHTPATH_H
#define FLIGHTPATH_H

#include <iomanip>

#include "flight_node.h"

using namespace std;

class FlightNode;


class FlightPath {
 public:
  FlightPath();
  FlightPath(int num_bags, FlightNode *flight1);
  FlightPath(int num_bags, FlightNode *flight1, FlightNode *flight2);

  void PrintItinerary();

  int num_bags();
  int grand_duration();
  double grand_price();
  FlightPath* next();
  void set_num_bags(int num_bags);
  void set_grand_price(double grand_price);
  void set_grand_duration(int grand_duration);
  void set_next(FlightPath *next);

 private:
  FlightNode *path_[2];
  int num_bags_;
  double grand_price_;
  int grand_duration_;
  FlightPath *next_;

  int GetGrandDuration();
  double GetGrandPrice();
};

#endif