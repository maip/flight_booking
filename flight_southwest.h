/**
 * @file flight_southwest.h
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * The FlightSouthwest class represents flights from FlightSouthwest and
 * inherits FlightNode.
 */
#ifndef FLIGHTSOUTHWEST_H
#define FLIGHTSOUTHWEST_H

#include "flight_node.h"

using namespace std;


class FlightSouthWest : public FlightNode {
 public:
  FlightSouthWest();
  FlightSouthWest(string num, string company, double price,
                  DateTime departure, int duration, HubNode *source,
                  HubNode *destination);

  float GetBaggageFees(int num_bags);
  int GetDelay();
};

#endif
