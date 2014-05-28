/**
 * @file utilities.h
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * This contains functions for error handling, processing csv files, and
 * sorting algorithms.
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "date_time.h"
#include "flight_delta.h"
#include "flight_node.h"
#include "flight_path.h"
#include "flight_southwest.h"
#include "flight_usairway.h"
#include "hub_node.h"

using namespace std;

class DateTime;
class FlightNode;
class FlightPath;
class HubNode;

typedef vector<FlightNode*> FlightList;

extern HubNode* hubs_head;  // imported hubs
extern FlightPath* paths_head;  // potential flight paths reset per search


void AddHubNode(HubNode *node);
void AddFlightPath(FlightPath *node);
void DeleteHubNodes(HubNode *node);
void DeleteFlightPaths(FlightPath *node);
void Die(const char *msg);
void ParseFlight();
void ParseHub();
DateTime ParseFromString(string str);
void PrintHubsAndFlights();
HubNode* SearchByName(string hub_name);
FlightList SearchByDeparture(HubNode *hub, DateTime departure); 
void FindFlight(string destination, DateTime departure, int num_bags);
FlightPath* GetBestFlightPath(int filter);

#endif
