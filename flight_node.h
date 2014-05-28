/**
 * @file flight_node.h
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * The FlightNode class is the base class for all flights. It is implemented as
 * a linked list.
 */
#ifndef FLIGHTNODE_H
#define FLIGHTNODE_H

#include <iostream>
#include <string>

#include "date_time.h"
#include "hub_node.h"

using namespace std;

class HubNode;


class FlightNode {
 public:
  FlightNode();
  FlightNode(string num, string company, double price, DateTime departure,
             int duration, HubNode* source, HubNode* destination);
  
  DateTime GetArrivalTime();
  double GetTotalPrice(int num_bags);
  string ToString();

  string flight_number();
  string flight_company();
  double price();
  DateTime departure();
  int duration();  
  HubNode* source();
  HubNode* destination();
  FlightNode* next();
  void set_flight_number(string num);
  void set_flight_company(string company);
  void set_price(double price);
  void set_departure(DateTime departure);
  void set_duration(int duration);
  void set_source(HubNode* source);
  void set_destination(HubNode* destination);
  void set_next(FlightNode* node);
  
  // polymorphic functions in derived classes
  virtual float GetBaggageFees(int num_bags) { return 0.0; }
  virtual int GetDelay() { return 0; }

 protected:
  string flight_number_;
  string flight_company_;
  double price_;
  DateTime departure_;
  int duration_;
  HubNode *source_;
  HubNode *destination_;
  FlightNode *next_;
};

#endif
