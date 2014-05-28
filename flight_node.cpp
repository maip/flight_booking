/**
 * @file flight_node.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * FlightNode class.
 */
#include "flight_node.h"


/**
 * Default constructor.
 */
FlightNode::FlightNode()
    : flight_number_(""), flight_company_(""), price_(0.0),
      departure_(DateTime()), duration_(0), source_(NULL),
      destination_(NULL), next_(NULL) {
}

/**
 * Overloaded constructor.
 */
FlightNode::FlightNode(string num, string company, double price,
                       DateTime departure, int duration, HubNode* source,
                       HubNode* destination)
    : flight_number_(num), flight_company_(company), price_(price),
      departure_(departure), duration_(duration), source_(source),
      destination_(destination), next_(NULL) {
}

/**
 * Formats all flight information tab deliminated.
 */
string FlightNode::ToString() {
  return (flight_number_ + "\t" + to_string(price_) + "\t" +
         source_->name() + "\t" + destination_->name() + "\t" +
         departure_.ToString() + "\t" + to_string(duration_) + "\t" +
	    	 flight_company_);
}

/**
 * Returns the total price of a flight including the baggage fees and base
 * price of a flight. Calls polymorphic function GetBaggageFees for appropriate
 * derived class.
 */
double FlightNode::GetTotalPrice(int num_bags) {
  return (double) GetBaggageFees(num_bags) + price_;
}

/**
 * Returns a new DateTime representing the arrival time by adding the duration
 * and delay to the departure DateTime. Calls polymorphic function GetDelay for
 * appropriate derived class.
 */
DateTime FlightNode::GetArrivalTime() {  
  DateTime arrival = DateTime(departure_.minutes(), departure_.hours(),
                              departure_.day(), departure_.month(),
                              departure_.year());
  int min = duration_ + GetDelay(); 
  arrival.AddMinutes(min);
  
  return arrival;
}

string FlightNode::flight_number() {
  return flight_number_;
}

void FlightNode::set_flight_number(string num) {
  flight_number_ = num;
}

string FlightNode::flight_company() {
  return flight_company_;
}

void FlightNode::set_flight_company(string company) {
  flight_company_ = company;
}

double FlightNode::price() {
  return price_;
}

void FlightNode::set_price(double price) {
  price_ = price;
}

DateTime FlightNode::departure() {
  return departure_;
}

void FlightNode::set_departure(DateTime departure) {
  departure_ = departure;
}

HubNode* FlightNode::source() {
  return source_;
}

void FlightNode::set_source(HubNode* source) {
  source_ = source;
}

HubNode* FlightNode::destination() {
  return destination_;
}

void FlightNode::set_destination(HubNode* destination) {
  destination_ = destination;
}

FlightNode* FlightNode::next() {
  return next_;
}

void FlightNode::set_next(FlightNode* node) {
  next_ = node;
}

int FlightNode::duration() {
  return duration_;
}

void FlightNode::set_duration(int duration) {
  duration_ = duration;
}
