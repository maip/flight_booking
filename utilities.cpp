/**
 * @file utilities.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * See the top of utilities.h for a complete description.
 */
#include "utilities.h"


/**
 * Prints user defined errors and exits the program.
 */
void Die(const char *msg) {
  if (errno == EDOM) {
    perror(msg);
  } else {
    cout << "ERROR: " << msg << endl;
  }
  exit(EXIT_FAILURE);
}

/**
 * Adds a HubNode to hubs_head.
 */
void AddHubNode(HubNode *node) {
  node->set_next(hubs_head);
  hubs_head = node;
}

/**
 * Adds a FlightPath to paths_head.
 */
void AddFlightPath(FlightPath *node) {
	node->set_next(paths_head);
	paths_head = node;
}

/**
 * Imports hub data as HubNode. Input file must be named Hub.csv.
 */
void ParseHub() {
  ifstream csv("Hub.csv");
  string line;
  if (!csv.is_open() || 0 != csv.fail()) {
    Die("Hub.csv cannot be opened.");
  }

  if (getline(csv, line)) {  // removes first line
    string name, location;
    while (getline(csv, line)) {
      stringstream str(line);
      getline(str, name, ',');
      getline(str, location, ',');
      HubNode *hub = new HubNode(name, location);
      AddHubNode(hub);  // adds new hub 
    }
  }
  csv.close();
}

/**
 * Returns a pointer to the HubNode that corresponds to the given string.
 */
HubNode* SearchByName(string hub_name) {
  HubNode *temp = hubs_head;

  while (temp != NULL) {
    if (temp->name().compare(hub_name) == 0) {
      return temp;
    }
    temp = temp->next();
  }

  return NULL;
}

/**
 * Parses string using delimiter '/' and returns a new DateTime object.
 */
DateTime ParseFromString(string str) { 
  string tokens[5];
  int min, hr, d, mo, yr;
  int x = 0;  // tokens index 

  istringstream ss(str);
  while (!ss.eof()) {
    getline(ss, tokens[x], '/');
    x++;
  }

  istringstream(tokens[0]) >> min;
  istringstream(tokens[1]) >> hr;
  istringstream(tokens[2]) >> d;
  istringstream(tokens[3]) >> mo;
  istringstream(tokens[4]) >> yr;

  return DateTime(min, hr, d, mo, yr);
}

/**
 * Imports flight data as FlightNode in the appropriate HubNode, so that each
 * hub contains a list of all of the outgoing flights. Flight file must be
 * named Flight.csv.
 */
void ParseFlight() {
  ifstream csv("Flight.csv");
  string line;
  if (!csv.is_open() || 0 != csv.fail()) {
    Die("Flight.csv cannot be opened.");
  }

  if (getline(csv, line)) {  // removes first line
    string date_time, num, company, source, destination, price_str, duration_str;
    double price;
    int duration;
  
    while (getline(csv, line)) {
      stringstream str(line);
      getline(str, num, ',');
      getline(str, price_str, ',');
      stringstream price_ss(price_str);
      price_ss >> price;
      getline(str, source, ',');
      getline(str, destination, ',');

      // uses DateTime class, need to parse out '/'
      getline(str, date_time, ',');
      DateTime parsed_departure = ParseFromString(date_time);
        
      getline(str, duration_str, ',');
      stringstream dur(duration_str);
      dur >> duration;
      getline(str, company, ',');

      // matches source airport to hub and adds flight
      HubNode *source_hub = SearchByName(source);
      HubNode *destination_hub = SearchByName(destination);
      FlightNode *flight;
      if (company.compare("Delta") == 0) {
        flight = new FlightDelta(num, company, price, parsed_departure,
                                 duration, source_hub, destination_hub);
      } else if (company.compare("USAirway") == 0) {
        flight = new FlightUSAirWay(num, company, price, parsed_departure,
                                    duration, source_hub, destination_hub);
      } else if (company.compare("SouthWest") == 0) {
        flight = new FlightSouthWest(num, company, price, parsed_departure,
                                     duration, source_hub, destination_hub);
      } else {
        flight = new FlightNode(num, company, price, parsed_departure,
                                duration, source_hub, destination_hub);
        cout << "ERROR: Unknown flight company " << company << endl;
      }
      source_hub->AddFlightNode(flight);
    }
  }

  csv.close();
}

/**
 * Prints all hub and flight data contained in hubs_head.
 */
void PrintHubsAndFlights() {
  if (hubs_head == NULL) {
    cout << "There is no imported hub and flight data." << endl;
  } else {
    HubNode *hub_iter = hubs_head;
    cout << left;
    while (hub_iter != NULL) {
      cout << setw(60) << hub_iter->name() << hub_iter->location() << endl;
     
      FlightNode *flight_iter = hub_iter->flights_head();
      while (flight_iter != NULL) { 
        cout.precision(2);
        cout << fixed;
    
        cout << setw(10) << flight_iter->flight_number()
             << setw(15) << flight_iter->flight_company() << setw(50)
             << flight_iter->destination()->name() << endl;
        cout << setw(25) << " " << flight_iter->destination()->location() << endl;
        cout << setw(25) << " " << "From: " << flight_iter->departure().ToString()
             << " To: " << flight_iter->GetArrivalTime().ToString() << endl;
        cout << setw(25) << " " << "$" << flight_iter->price() << endl;
        
        flight_iter = flight_iter->next();
      }

      hub_iter = hub_iter->next();
    }
  }
}

/**
 * Frees all HubNodes including their FlightNodes. Calls HubNode deconstructor.
 */
void DeleteHubNodes(HubNode *node) {
  if (node != NULL) {
    DeleteHubNodes(node->next());
    delete node;
    node = NULL;
  }
}

/**
 * Frees all FlightPaths. The FlightNodes are deleted when the HubNodes are.
 */
void DeleteFlightPaths(FlightPath *node) {
  if (node != NULL) {
    DeleteFlightPaths(node->next());
    delete node;
    node = NULL;
  }
}

/**
 * Searches for outgoing flights in the Phoenix Sky Harbor International hub
 * that match the user given departure, then checks if the destination matches.
 * If yes, adds to flight paths linked list. If no, follow the flight to the
 * destination hub and look in the outgoing flights and check if the
 * destination matches (connecting flight). If yes, add to flight paths.
 */
void FindFlight(string destination, DateTime departure, int num_bags) {
  // assume the phoenix hub is found
  HubNode *phx_hub = SearchByName("Phoenix Sky Harbor International Airport");
  FlightList flights = SearchByDeparture(phx_hub, departure);
  
  for (FlightNode *flight : flights) {  // for each outgoing phoenix flight
    HubNode *out_hub = flight->destination();
    if (out_hub->location().compare(destination) == 0) {
      // direct flight i.e. PHX to LA
      FlightPath *flight_path = new FlightPath(num_bags, flight);
      AddFlightPath(flight_path);
    } else {
      // check if this can be a connecting flight to destination i.e. PHX to LA to SF
      FlightNode *out_flights = out_hub->flights_head();
      while (out_flights != NULL) {
        if (out_flights->destination()->location().compare(destination) == 0 &&
            flight->GetArrivalTime().CompareTo(out_flights->departure()) <= 0) {
          FlightPath *flight_path = new FlightPath(num_bags, flight, out_flights);
          AddFlightPath(flight_path);
        }
        out_flights = out_flights->next();
      }
    }
  }
}

/**
 * Sorts the potential flight paths by given filter, (0) low to high by price or
 * (1) short to long by duration. Returns top result.
 */
FlightPath* GetBestFlightPath(int filter) {
  FlightPath *temp = paths_head;
  FlightPath *min_path = temp;

  if (filter == 0) {  // sort by price
    double min = temp->grand_price();
    while (temp != NULL) {
      if (temp->grand_price() < min) {
        min = temp->grand_price();
        min_path = temp;
      }
      temp = temp->next();
    }
  } else if (filter == 1) {  // sort by time
    int min = temp->grand_duration();
    while (temp != NULL) {
      if (temp->grand_duration() < min) {
        min = temp->grand_duration();
        min_path = temp;
      }
      temp = temp->next();
    }
  }

  return min_path;
}

/**
 * Returns a vector of flights in the given hub that match the given departure
 * time.
 */
FlightList SearchByDeparture(HubNode *hub, DateTime departure) {
  FlightNode *temp = hub->flights_head();

  FlightList paths_head;
  while (temp != NULL) {
    if (temp->departure().CompareTo(departure) >= 0) {
      paths_head.push_back(temp);
    }
    temp = temp->next();
  }

  return paths_head;
}
