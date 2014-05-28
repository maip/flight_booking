/**
* @file flight_path.cpp
* @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
*
* This contains the implementation of FlightPath class.
*
* See the top of flight_path.h for complete description.
*/
#include "flight_path.h"


/**
 * Default constructor.
 */
FlightPath::FlightPath()
    : num_bags_(0), grand_price_(0.0), grand_duration_(0), next_(NULL) {
  path_[0] = NULL;
  path_[1] = NULL;
}

/**
 * Overloaded constructor for direct flight.
 */
FlightPath::FlightPath(int num_bags, FlightNode *flight1)
    : num_bags_(num_bags), next_(NULL) {
  path_[0] = flight1;
  path_[1] = NULL;
  grand_duration_ = GetGrandDuration();
  grand_price_ = GetGrandPrice();
}

/**
 * Overloaded constructor for connecting flight.
 */
FlightPath::FlightPath(int num_bags, FlightNode *flight1, FlightNode *flight2)
    : num_bags_(num_bags), next_(NULL) {
  path_[0] = flight1;
  path_[1] = flight2;
  grand_duration_ = GetGrandDuration();
  grand_price_ = GetGrandPrice();
}

/**
 * Prints flight path details including base price, baggage fees and grand
 * total.
 */
void FlightPath::PrintItinerary() {
  int w = 10;

  // displays first flight info
  double total_cost1 = path_[0]->GetTotalPrice(num_bags_);
  
  cout << left;
 
  cout << setw(w) << path_[0]->flight_number()
       << setw(w)<< path_[0]->flight_company()
       << setw(2*w) << path_[0]->source()->location()
       << path_[0]->departure().ToString() << endl; 
      
  cout << setw(2*w) << " " << setw(2*w) << path_[0]->destination()->location()
       << path_[0]->GetArrivalTime().ToString() << endl;

  cout.precision(2);
  cout << fixed;
  
  cout << setw(2*w) << " " << "$" << path_[0]->price() << " Base Price"; 
  
  if (path_[0]->GetBaggageFees(num_bags_) > 0) {
    cout << " + $" << path_[0]->GetBaggageFees(num_bags_) << " Baggage Fees";
  }
  
  cout << " = $" << total_cost1 << endl;

  // displays second flight info
  if (path_[1] != NULL) {
    cout << left;
   
    cout << setw(w) << path_[1]->flight_number()
         << setw(w) << path_[1]->flight_company()
         << setw(2*w) << path_[1]->source()->location()
         << path_[1]->departure().ToString() << endl; 
    
    cout << setw(2*w) << " " << setw(2*w) << path_[1]->destination()->location()
         << path_[1]->GetArrivalTime().ToString() << endl;

    double total_cost2 = path_[1]->GetTotalPrice(num_bags_);
    
    cout << setw(2*w) << " " << "$" << path_[1]->price() << " Base Price";
    
    if (path_[1]->GetBaggageFees(num_bags_) > 0.0) {  
      cout << " + $" << path_[1]->GetBaggageFees(num_bags_) << " Baggage Fees";
    }
    
    cout << " = $" << total_cost2 << endl;
  }

  cout << endl << "Check-in " << num_bags_ << " Bags" << endl;
  cout << "Grand Total: $" << grand_price_  << endl;  
} 

/**
 * Calculates total duration of flight path including delays.
 */
int FlightPath::GetGrandDuration() {
  if (path_[1] != NULL) {
    return (path_[0]->duration() + path_[0]->GetDelay() + path_[1]->duration() +
            path_[1]->GetDelay());
  } else {
    return path_[0]->duration() + path_[0]->GetDelay();
  }
}

/**
 * Calculates total price of flight path including baggage fees.
 */
double FlightPath::GetGrandPrice() {
  if (path_[1] != NULL) {
    return (path_[0]->GetTotalPrice(num_bags_) +
            path_[1]->GetTotalPrice(num_bags_));
  } else {
    return path_[0]->GetTotalPrice(num_bags_);
  }
}

int FlightPath::num_bags() {
  return num_bags_;
}

void FlightPath::set_num_bags(int num_bags) {
  num_bags_ = num_bags;
}

int FlightPath::grand_duration() {
  return grand_duration_;
}

void FlightPath::set_grand_duration(int grand_duration) {
  grand_duration_ = grand_duration;
}

double FlightPath::grand_price() {
  return grand_price_;
}

void FlightPath::set_grand_price(double grand_price) {
  grand_price_ = grand_price;
}

FlightPath* FlightPath::next() {
  return next_;
}

void FlightPath::set_next(FlightPath *next) {
  next_ = next;
}
