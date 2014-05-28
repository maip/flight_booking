/**
 * @file hub_node.h
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * The HubNode class represents airports. It is implemented as a linked list.
 */
#ifndef HUBNODE_H
#define HUBNODE_H

#include <iostream>
#include <string>

#include "flight_node.h"

using namespace std;

class FlightNode;


class HubNode {
 public:
  HubNode();
  HubNode(string hub, string hub_location);
  ~HubNode();
  void DeleteFlightNodes(FlightNode *node);

  void AddFlightNode(FlightNode *node);
  string ToString();

  string name();
  string location();
  HubNode* next();
  FlightNode* flights_head();
  void set_name(string name);
  void set_location(string location);
  void set_next(HubNode* node);
  void set_flights_head(FlightNode* node);

 private:
  string name_;
  string location_;
  HubNode *next_;
  FlightNode *flights_head_;
};

#endif
