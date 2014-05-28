/**
 * @file hub_node.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * This contains the implementation of HubNode class.
 *
 * See the top of hub_node.h for a complete description.
 */
#include "hub_node.h"


/**
 * Default constructor.
 */
HubNode::HubNode()
    : name_(""), location_(""), flights_head_(NULL), next_(NULL) {
}

/**
 * Overloaded constructor.
 */
HubNode::HubNode(string hub, string hub_location)
    : name_(hub), location_(hub_location), flights_head_(NULL), next_(NULL) {
}

/**
* Destructor removes all FlightNode instnaces in this HubNode.
*/
HubNode::~HubNode() {
  DeleteFlightNodes(flights_head_);
}

/**
 * Frees all FlightNodes.
 */
void HubNode::DeleteFlightNodes(FlightNode *node) {
  if (node != NULL) {
    DeleteFlightNodes(node->next());
    delete node;
    node = NULL;
  }
}

/**
 * Adds new FlightNode to the flights_head_ of this HubNode.
 */
void HubNode::AddFlightNode(FlightNode *node) {
  node->set_next(flights_head_);
  flights_head_ = node;
}

/**
 * Formats this as name and location tab deliminated.
 */
string HubNode::ToString() {
  return name_ + "\t" + location_;
}

string HubNode::name() {
  return name_;
}

string HubNode::location() {
  return location_;
}

HubNode* HubNode::next() {
  return next_;
}

FlightNode* HubNode::flights_head() {
  return flights_head_;
}

void HubNode::set_name(string name) {
  name_ = name;
}

void HubNode::set_location(string location) {
  location_ = location;
}

void HubNode::set_next(HubNode* node) {
  next_ = node;
}

void HubNode::set_flights_head(FlightNode* node) {
  flights_head_ = node;
}
