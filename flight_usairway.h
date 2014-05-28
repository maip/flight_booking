/**
 * @file flight_usairway.h
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * The FlightUSAirway class represents flights from USAirway and inherits
 * FlightNode.
 */
#ifndef FLIGHTUSAIRWAY_H
#define FLIGHTUSAIRWAY_H

#include "flight_node.h"

using namespace std;


class FlightUSAirWay : public FlightNode {
 public:
  FlightUSAirWay();
  FlightUSAirWay(string num, string company, double price,
                  DateTime departure, int duration, HubNode *source,
                  HubNode *destination);

  float GetBaggageFees(int num_bags);
  int GetDelay();
};

#endif
