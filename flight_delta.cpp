/**
 * @file flight_delta.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * This contains the implementation of FlightDelta class.
 *
 * See top of flight_delta.h for a complete description.
 */
#include "flight_delta.h"


/**
 * Default constructor.
 */
FlightDelta::FlightDelta()
    : FlightNode() {
}

/**
 * Overloaded constructor.
 */
FlightDelta::FlightDelta(string num, string company, double price,
                         DateTime departure, int duration,
                         HubNode *source, HubNode *destination)
    :  FlightNode(num, company, price, departure, duration, source, destination) {      
}

/**
 * Returns the baggage fees for Delta, which is no charge.
 */  
float FlightDelta::GetBaggageFees(int num_bags) {
  return 0.00;
}

/**
 * Returns the expected delay of a Delta flight in minutes, which is 20 minutes.
 */
int FlightDelta::GetDelay() {
  return 20;
}
