/**
 * @file main.cpp
 * @author Melissa Ip, Ayushi Jain, Alex Nazareno, Adam Tse
 *
 * This is the driver of a flight booking program for CSE240 Cheng.
 */
#include "flight_path.h"
#include "hub_node.h"
#include "utilities.h"

using namespace std;

typedef enum {
  January=1, February, March, April, May, June,
  July, August, September, October, November, December
} months;

typedef enum {
  Reserve=1, Quit
} menu_options;

// global variables
HubNode* hubs_head = NULL;
FlightPath* paths_head = NULL;

int minute, hour, day, month, year, bag;
string destination;

// forward declarations
class FlightPath;
class HubNode;

void ChooseDate();
void ChooseYear();
void ChooseMonth();
void ChooseDay();
void ChooseHour();
void ChooseMinute();
void ChooseDestination();
void ChooseBags();
void ReserveFlight();


int main() {
  int choice = 0;
  string choice_str;
  
  ParseHub();  // load Hub.csv
  ParseFlight();  // load Flight.csv

  cout << "Welcome to flight booking system." << endl;
  
  while (choice != 2) {
    try {
      cout << endl << endl << "Menu Options:" << endl
           << "---------------------" << endl;
      cout << "1. Reserve a flight" << endl;
      cout << "2. Quit" << endl;
  
      cout << endl << "Please enter a choice: " << endl; 

      getline(cin, choice_str);
      istringstream iss(choice_str);
      iss >> choice >> ws;
      if (iss.fail() || !iss.eof()) {
        throw -1;
      }

      switch (choice) {
      case Reserve:
        ChooseDate();
        ChooseDestination();
        ChooseBags();
        ReserveFlight();
        break;
      case Quit:
        break;
      default:
        throw -1;
        break;
      }
    } catch (int ie) {
      cout << endl << "Invalid Input. Try again." << endl;
      choice = 0;
    }
  }

  DeleteHubNodes(hubs_head); 
  return 0;
}

void ChooseDate() {
  cout << endl << "When would you like to depart?" << endl << endl;

  ChooseYear();
  ChooseMonth();
  ChooseDay();
  ChooseHour();
  ChooseMinute();
}

void ChooseYear() {
  string year_str;
  do {
    try {
      cout << "Enter the year (yyyy): ";
      getline(cin, year_str);
      istringstream iss(year_str);
      iss >> year >> ws;

      if (iss.fail() || !iss.eof()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }

      if (year < 0) {
        throw -2;
      }
    } catch (int ie) {
      year = -1;
      if (ie == -1) {
        cout << endl << "ERROR: Invalid input. Try again." << endl << endl;
      } else {
        cout << endl << "ERROR: Invalid year. Try again." << endl << endl;
      }
    }
  } while (year < 0);
}

void ChooseMonth() {
  string month_str;
  do {
    try {
      cout << endl << "Enter a month (Jan=1, Feb=2, ...): ";
      getline(cin, month_str);
      istringstream iss(month_str);
      iss >> month >> ws;

      if (iss.fail() || !iss.eof()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }

      if (month < 1 || month > 12) {
        throw -2;
      }
    } catch (int ie) {
      month = -1;
      if (ie == -1) {
        cout << endl << "ERROR: Invalid input. Try again." << endl;
      } else {
        cout << endl << "ERROR: Invalid month. Try again." << endl;
      }
    }
  } while (month < 1 || month > 12);
}

void ChooseDay() {
  string day_str;
  int correct_day = 1;
  do {
    correct_day = 1;
    try {
      cout << endl << "Enter a day: ";
      getline(cin, day_str);
      istringstream iss(day_str);
      iss >> day >> ws;

      switch (month) {
      case January:
        if (day < 1 || day > 31) { correct_day = 0; }
        break;
      case February:
        if (day < 1 || day > 29) {
          correct_day = 0; 
        } else if (day == 29 && year%4 != 0) {
          correct_day = 0;
        }
        break;
      case March:
        if (day < 1 || day > 31) { correct_day = 0; }
        break;
      case April:
        if (day < 1 || day > 30) { correct_day = 0; }
        break;
      case May:
        if (day < 1 || day > 31) { correct_day = 0; }
        break;
      case June:
        if (day < 1 || day > 30) { correct_day = 0; }
        break;
      case July:
        if (day < 1 || day > 31) { correct_day = 0; }
        break;
      case August:
        if (day < 1 || day > 31) { correct_day = 0; }
        break;
      case September:
        if (day < 1 || day > 30) { correct_day = 0; }
        break;
      case October:
        if (day < 1 || day > 31) { correct_day = 0; }
        break;
      case November:
        if (day < 1 || day > 30) { correct_day = 0; }
        break;
      case December:
        if (day < 1 || day > 31) { correct_day = 0; }
        break;
      }
  
      if (iss.fail() || !iss.eof()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }

      if (correct_day == 0) { 
        throw -2; 
      }
    } catch (int ie) {
      correct_day = 0;
      day = 0;
      if (ie == -1) {
        cout << endl << "ERROR: Invalid input. Try again." << endl;
      } else {
        cout << endl << "ERROR: Invalid day. Try again." << endl; 
      }
    }
  } while (correct_day == 0);
}

void ChooseHour() {
  string hour_str;
  do {
    try {
      cout << endl << "Enter hour: ";
      getline(cin, hour_str);
      istringstream iss(hour_str);
      iss >> hour >> ws;

      if (iss.fail() || !iss.eof()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }

      if (hour < 0 || hour > 23) {
        throw -2;
      }
    } catch (int ie) {
      hour = -1;
      if (ie == -1) {
        cout << endl << "ERROR: Invalid input. Try again." << endl;
      } else {
        cout << endl << "ERROR: Invalid hour. Try again." << endl;
      }
    }
  } while (hour < 0 || hour > 23);
}

void ChooseMinute() {
  string minute_str;
  do {
    try {
      cout << endl << "Enter minute: ";
      getline(cin, minute_str);
      istringstream iss(minute_str);
      iss >> minute >> ws;

      if (iss.fail() || !iss.eof()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }

      if (minute < 0 || minute > 59) {
        throw -2;
      }
    } catch (int ie) {
      minute = -1;
      if (ie == -1) {
        cout << endl << "ERROR: Invalid input. Try again." << endl;
      } else {
        cout << endl << "Invalid minute. Try again." << endl;
      }
    }
  } while (minute < 0 || minute > 59); 
 }

void ChooseBags() {
  string bag_str;
  do {
    try {
      cout << endl << "Enter the number of baggages: ";
      getline(cin, bag_str);
      istringstream iss(bag_str);
      iss >> bag >> ws;

      if (bag < 0 || iss.fail() || !iss.eof()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }
    } catch (int ie) {
      bag = -1;
      cout << endl << "ERROR: Invalid input. Try again." << endl;
    }
  } while (bag < 0);
}

void ChooseDestination() {
  int flag = 0;

  do {
    HubNode *temp = hubs_head;
    try {
      cout << endl << "Please enter a destination: ";

      getline(cin, destination);
      while (temp != NULL) {
        if (destination.compare(temp->location()) == 0) {        
          flag = 1;
        }

        temp = temp->next();
      }
      
      if (cin.fail()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }

      if (flag == 0) {
        throw -2;
      }
    } catch (int ie) {
      if (ie == -1) {
        cout << endl << "ERROR: Invalid input. Try again." << endl;
      } else {
        cout << endl << "ERROR: The destination is invalid. Try again." << endl;
      }
    }
  } while (flag == 0);
}

int ChooseFilter() {
  int filter = -1;
  string filter_str;

  do {
    try {
      cout << endl << "Choose a filter (0=Lowest price, 1=Shortest distance): ";
      getline(cin, filter_str);
      istringstream iss(filter_str);
      iss >> filter >> ws;
      
      if (iss.fail() || !iss.eof()) { 
        cin.sync();
        cin.clear();
        throw -1; 
      }

      if (filter != 0 && filter != 1) {
        throw -1;
      }
    } catch (int ie) {
      filter = -1;
      cout << endl << "ERROR: Invalid input. Try again." << endl;
    }
  } while (filter != 0 && filter != 1);

  return filter;
}

void ReserveFlight() {
  int confirm = -1;
  string confirm_str;
  DateTime date = DateTime(minute, hour, day, month, year);
  FindFlight(destination, date, bag);

  if (paths_head != NULL) {
    FlightPath *userChoice = GetBestFlightPath(ChooseFilter());  

    cout << endl << "------------------------------Flight details------------------------------" << endl;
    userChoice->PrintItinerary();
    cout << "--------------------------------------------------------------------------" << endl;

    do {
      try {
        cout << endl << "Would you like to confirm these details and buy your ticket? (0=No, 1=Yes): ";
        getline(cin, confirm_str);
        istringstream iss(confirm_str);
        iss >> confirm >> ws;
        
        if (iss.fail() || !iss.eof()) { 
          cin.sync();
          cin.clear();
          throw -1; 
        }

        if (confirm != 0 && confirm != 1) {
          throw -1;
        }
      } catch (int ie) {
        confirm = -1;
        cout << endl << "ERROR: Invalid input. Try again." << endl;
      }
    } while (confirm != 0 && confirm != 1);

    if (confirm == 1) {
      cout << endl << "----------------------------Your final ticket-----------------------------" << endl;
      userChoice->PrintItinerary();
      cout << "--------------------------------------------------------------------------" << endl;
      cout << endl << "Thank you for making a reservation! Redirecting to main menu...";
    } else {
      cout << endl << "Redirecting to main menu...";
    }

    DeleteFlightPaths(paths_head);  // if user cancels clears paths_head
    paths_head = NULL;  // if user cancels clears paths_head
    cout << endl;
  } else {
    cout << endl << "No flights match your specification. Redirecting to main menu...";
  }
}
