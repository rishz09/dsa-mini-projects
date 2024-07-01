#include <iostream>
#include <cassert>
// #include <bits/stdc++.h>  
#include <string>  
#include "code_final.cpp"// Include your actual class header file here

int testCasesPassed = 0;

// Utility function to check BST property recursively
bool isBSTUtil(BinaryTreeNode* node, int minValue, int maxValue) {
    if (node == nullptr)
        return true;

    int nodeValue = node->getDepartureTime();
    if (nodeValue < minValue || nodeValue > maxValue)
        return false;

    return isBSTUtil(node->getLeftPtr(), minValue, nodeValue - 1) &&
           isBSTUtil(node->getRightPtr(), nodeValue + 1, maxValue);
}

// Function to check if a tree is a proper BST
bool isBST(BinaryTreeNode* node) {
    return isBSTUtil(node, INT_MIN, INT_MAX);
}


// Test Case: Adding more trips and accessing the root of the tree by location and service
void test_add_trip() {
    TravelDesk travelDesk;

    // Add trips
    for (int i = 0; i < 10; ++i) {
        std::string vehicleNumber = "A" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 4, "LocationA", "LocationB", 1000 + i * 100);
    }

    // Add trips for LocationX
    for (int i = 0; i < 10; ++i) {
        std::string vehicleNumber = "X" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 3, "LocationX", "LocationY", 1500 + i * 100);
    }
    
    // Verify that the tree is a proper BST
    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead(); // Add a function to get root by location
    assert(isBST(rootLocationA));

    BinaryTreeNode* rootLocationX = travelDesk.getLocation("LocationX")->getServicePtr("LocationY")->getBSTHead(); // Add a function to get root by location
    assert(isBST(rootLocationX));

    std::vector<Trip*> tripsFromLocationA = travelDesk.showTrips("LocationA", 0, 2000);
    std::vector<Trip*> tripsFromLocationX = travelDesk.showTrips("LocationX", 0, 2000);

    // Assert the number of trips from LocationA and LocationX
    assert(tripsFromLocationA.size() == 10);
    assert(tripsFromLocationX.size() == 5);

    testCasesPassed++;
}


// Test Case 2: Booking a trip and checking booked seats
void test_book_trip() {
    TravelDesk travelDesk;
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);

    Trip* bookedTrip = travelDesk.bookTrip("LocationX", "LocationY", "XYZ789", 1500);
    assert(bookedTrip != nullptr);
    assert(bookedTrip->getBookedSeats() == 1);
    testCasesPassed++;
}

// Test Case 3: Trying to book more seats than available
void test_book_trip_max_capacity() {
    TravelDesk travelDesk;
    travelDesk.addTrip("LMN456", 2, "LocationP", "LocationQ", 1200);

    Trip* bookedTrip = travelDesk.bookTrip("LocationP", "LocationQ", "LMN456", 1200);
    assert(bookedTrip != nullptr);
    assert(bookedTrip->getBookedSeats() == 1);

    Trip* secondBooking = travelDesk.bookTrip("LocationP", "LocationQ", "LMN456", 1200);
    assert(secondBooking != nullptr);
    assert(secondBooking->getBookedSeats() == 2);
    testCasesPassed++;
}

// Test Case 4: Showing trips within a specific time range
void test_show_trips_by_time() {
    TravelDesk travelDesk;
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);

    std::vector<Trip*> trips = travelDesk.showTrips("LocationA", 800, 1200);
    assert(trips.size() == 1);
    testCasesPassed++;
}

// Test Case 5: Setting and getting the location name
void test_location_name() {
    Location location("LocationC");
    assert(location.getName() == "LocationC");

    location.setName("NewLocation");
    assert(location.getName() == "NewLocation");
    testCasesPassed++;
}

// Test Case 6: Adding a trip to a vehicle
void test_add_trip_to_vehicle() {
    Vehicle vehicle("ABC123", 4);
    Trip trip(&vehicle, "LocationA", "LocationB", 1000);

    vehicle.addTrip(&trip);
    const std::vector<Trip*>& trips = vehicle.getTrips();
    assert(trips.size() == 1);
    testCasesPassed++;
}

// Test Case 7: Setting and getting the departure time of a trip
void test_trip_departure_time() {
    Vehicle vehicle("ABC123", 4);
    Trip trip(&vehicle, "LocationA", "LocationB", 1000);

    trip.setDepartureTime(1100);
    assert(trip.getDepartureTime() == 1100);
    testCasesPassed++;
}



int main() {
    // Run the test cases
    test_add_trip();
    test_book_trip();
    test_book_trip_max_capacity();
    test_show_trips_by_time();
    test_location_name();
    test_add_trip_to_vehicle();
    test_trip_departure_time();


    std::cout << "Number of test cases passed: " << testCasesPassed << "/" << 7 << std::endl;
    
    return 0;
}