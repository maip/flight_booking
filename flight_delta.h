/**
 * @file flight_delta.h
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * The FlightDelta class represents flights from Delta and inherits FlightNode.
 */
#ifndef FLIGHTDELTA_H
#define FLIGHTDELTA_H

#include "flight_node.h"

using namespace std;


class FlightDelta : public FlightNode {
 public:
  FlightDelta();
  FlightDelta(string num, string company, double price,
              DateTime departure, int duration, HubNode *source,
              HubNode *destination);
  
  float GetBaggageFees(int num_bags);
  int GetDelay();
};

#endif
