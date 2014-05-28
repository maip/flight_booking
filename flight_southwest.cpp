/**
 * @file flight_southwest.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * This contains the implementation of FlightSouthwest class.
 *
 * See top of flight_southwest.h for a complete description.
 */
 #include "flight_southwest.h"


/**
 * Default constructor.
 */
FlightSouthWest::FlightSouthWest()
    : FlightNode() {
}

/**
 * Overloaded constructor.
 */
FlightSouthWest::FlightSouthWest(string num, string company, double price,
                                 DateTime departure, int duration,
                                 HubNode *source, HubNode *destination)
    :  FlightNode(num, company, price, departure, duration, source, destination) {      
}

/**
 * Returns the baggage fees for SouthWest, which is $25 per bag.
 */  
float FlightSouthWest::GetBaggageFees(int num_bags) {
  return (float) num_bags * 25;
}

/**
 * Returns the expected delay of a Southwest flight in minutes, which is 30
 * minutes between 07:00 and 17:00, otherwise no delay.
 */
int FlightSouthWest::GetDelay() {
  if (departure_.hours() >= 7 && departure_.hours() <= 17) {
    return 30;  
  } else {
    return 0;
  }
}
