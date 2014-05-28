/**
 * @file flight_usairway.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * This contains the implementation of FlightUSAirway class.
 *
 * See top of flight_usairway.h for a complete description.
 */
#include "flight_usairway.h"


/**
 * Default constructor.
 */
FlightUSAirWay::FlightUSAirWay()
    : FlightNode() {
}

/**
 * Overloaded constructor.
 */
FlightUSAirWay::FlightUSAirWay(string num, string company, double price,
                               DateTime departure, int duration,
                               HubNode *source, HubNode *destination)
    :  FlightNode(num, company, price, departure, duration, source, destination) {      
}

/**
 * Returns the baggage fees for USAirway, which is no charge for 1 bag,
 * otherwise $25 per additional bag.
 */  
float FlightUSAirWay::GetBaggageFees(int num_bags) {
  if (num_bags <= 1) {
    return 0.00;
  } else {
    return (float) (num_bags - 1) * 25;
  }
}

/**
 * Returns the expected delay of a USAirway flight in minutes, which is 10
 * minutes between 07:00 and 17:00, no delay between 01:01 and 06:59, otherwise
 * 15 minutes.
 */
int FlightUSAirWay::GetDelay() {
  if(departure_.hours() >= 7 && departure_.hours() <= 17) {
    return 10;
  } else if (departure_.hours() >= 1 && departure_.minutes() >=1 &&
        departure_.hours() <= 6 && departure_.minutes() <= 59) {
      return 0;
  } else {
    return 15;
  }
}
