#include <iostream>
#include <cassert>
#include<string>
// #include <bits/stdc++.h>
// #include "ss2.cpp"  // Include your actual class header file here
//#include "StudentSolution.cpp"// Include your actual class header file here
#include "code_final.cpp"
using namespace std;
int testCasesPassed = 0;

bool customAssert(bool condition, const char* message) {
    if (!condition) {
        std::cout << "Assertion failed: " << message << std::endl;
        return false;
    }
    else return true;
    
}

bool isBSTUtil(BinaryTreeNode* node, int minValue, int maxValue) {
    if (node == nullptr)
        return true;

    int nodeValue = node->getDepartureTime();
    if (nodeValue < minValue || nodeValue > maxValue)
        return false;

    return isBSTUtil(node->getLeftPtr(), minValue, nodeValue - 1) &&
           isBSTUtil(node->getRightPtr(), nodeValue + 1, maxValue);
}

bool isBST(BinaryTreeNode* node) {
    return isBSTUtil(node, INT_MIN, INT_MAX);
}

void test_height_BT() {
    class TempBinaryTree : public BinaryTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) : BinaryTree() {
            root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();

    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);

    bool flag1=customAssert(isBST(rootLocationA) , "Binary tree is not a valid BST.");

    int heightLocationA = temp1->getHeight();
    bool flag2=customAssert(heightLocationA == 4 ,"Height of the binary tree is not as expected.");
    if(flag1 && flag2)
    testCasesPassed++;
    
}
void test_noofnodes_BT() {
    class TempBinaryTree : public BinaryTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) : BinaryTree() {
            root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();

    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);

    bool flag1=customAssert(isBST(rootLocationA) ,"Binary tree is not a valid BST.");

    int num = temp1->getNumberOfNodes();
    bool flag2=customAssert(num == 7 , "Number of nodes in the binary tree is not as expected.");
    if(flag1 && flag2)testCasesPassed++;

    
}

void test_show_trips_by_time_destination() {
    TravelDesk travelDesk;
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationX", 950);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("ABC123", 4, "LocationZ", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationY", "LocationX", 1000);

    std::vector<Trip*> trips = travelDesk.showTripsbydestination("LocationA", "LocationB", 800, 1200);

    bool flag1=customAssert(trips.size() == 2 , "Number of trips is not as expected.");
    if(flag1)testCasesPassed++;

    
}
void test_show_trips_by_time() {
    TravelDesk travelDesk;
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("XYZ789", 3, "LocationX", "LocationY", 1500);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationX", 950);
    travelDesk.addTrip("ABC123", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("ABC123", 4, "LocationZ", "LocationB", 900);
    travelDesk.addTrip("ABC123", 4, "LocationY", "LocationX", 1000);

    std::vector<Trip*> trips = travelDesk.showTrips("LocationA", 800, 1200);

    // assert(trips.size() == 4 && "Number of trips is not as expected.");
    bool flag1=customAssert(trips.size() == 3 , "Number of trips is not as expected.");
    if(flag1)testCasesPassed++;

    
}



void test_searchkeyin_BST() {
    class TempBinaryTree : public BinarySearchTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) {
            this->root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();

    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);

    BinaryTreeNode* node = temp1->searchNodeWithKey(1200);
    bool flag1=customAssert( node!=nullptr && node->getDepartureTime() == 1200 , "Node with key 1200 not found or has incorrect departure time.");

 
    // BinaryTreeNode* node1 = temp1->searchNodeWithKey(1200);
    
    // bool flag2=customAssert(node1 == nullptr , "Node is not a nullptr");
    // if(flag1 && flag2)testCasesPassed++;

    if(flag1)
    testCasesPassed++;
}

void test_successor_predecessor_BST() {
    class TempBinaryTree : public BinarySearchTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) {
            root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();


    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);

   
    BinaryTreeNode* node = temp1->searchNodeWithKey(1000);
    BinaryTreeNode* node_ = temp1->getSuccessorNode(node);
    BinaryTreeNode* node__ = temp1->getPredecessorNode(node);

   
    bool flag1=customAssert(node!=nullptr && node_->getDepartureTime() == 1200 , "Successor node has incorrect departure time.");
    bool flag2=customAssert(node!=nullptr && node__->getDepartureTime() == 900 , "Predecessor node has incorrect departure time.");
    if(flag1 && flag2)testCasesPassed++;
    
}

void test_getmaxminkey_BST() {
    
    class TempBinaryTree : public BinarySearchTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) {
            root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

   
    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();


    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);


    BinaryTreeNode* node = temp1->getElementWithMaximumKey();
    BinaryTreeNode* node1 = temp1->getElementWithMinimumKey();
    bool flag1=customAssert(node!=nullptr && node->getDepartureTime() == 1500 ,"Node with maximum key has incorrect departure time.");
    bool flag2=customAssert(node!=nullptr && node1->getDepartureTime() == 800 , "Node with minimum key has incorrect departure time.");
    if(flag1 && flag2)testCasesPassed++;
    
}

void test_successor_predecessor_withkey() {
    class TempBinaryTree : public BinarySearchTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) {
            root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

   
    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();

  
    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);

   
    BinaryTreeNode* node = temp1->getSuccessorNodeByKey(1000);
    BinaryTreeNode* node1 = temp1->getPredecessorNodeByKey(1000);
    bool flag1=customAssert(node!=nullptr && node->getDepartureTime() == 1200 , "Successor node with key 1000 has incorrect departure time.");
    bool flag2=customAssert(node!=nullptr && node1->getDepartureTime() == 900 , "Predecessor node with key 1000 has incorrect departure time.");
    if(flag1 && flag2)testCasesPassed++;
    
}

void countNodes(BinaryTreeNode* node, int& count, string pickup, string drop) {
    if (node == nullptr) {
        return;
    }

    if (node->getTripNodePtr()->getPickUpLocation() == pickup && node->getTripNodePtr()->getDropLocation() == drop)
        count++;

    
    countNodes(node->getLeftPtr(), count, pickup, drop);
    countNodes(node->getRightPtr(), count, pickup, drop);
}

void test_correct_pickup_drop() {
    
    TravelDesk travelDesk;
    for (int i = 0; i < 15; ++i) {
        std::string vehicleNumber = "A" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 4, "LocationA", "LocationX", 1000 + i * 100);
    }
    for (int i = 0; i < 10; ++i) {
        std::string vehicleNumber = "X" + std::to_string(i);
        travelDesk.addTrip(vehicleNumber, 3, "LocationA", "LocationY", 1500 + i * 100);
    }
    int nodeCount = 0;
    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationX")->getBSTHead();

    
    countNodes(rootLocationA, nodeCount, "LocationA", "LocationX");

   
    bool flag1=customAssert(nodeCount == 15, "Number of nodes with specified pickup and drop locations is not as expected.");
    if(flag1)testCasesPassed++;
    
}

void test_change_vehicle() {
   
    class TempBinaryTree : public BinarySearchTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) {
            root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

   
    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();

    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);

    BinaryTreeNode* node = temp1->searchNodeWithKey(1200);
    customAssert( node!=nullptr && node->getDepartureTime() == 1200 , "Node with key 1200 not found or has incorrect departure time.");
    if(node==nullptr)return;
    Trip* t = node->getTripNodePtr();
    t->getVehicle()->setSeatingCapacity(10);

    
    BinaryTreeNode* node1 = temp1->searchNodeWithKey(1200);
    bool flag1=customAssert( node!=nullptr && node->getDepartureTime() == 1200 , "Node with key 1200 not found or has incorrect departure time.");
    if(node1==nullptr)return;
    Trip* t1 = node1->getTripNodePtr();
    bool flag2=customAssert(t1!=nullptr && t1->getVehicle()->getSeatingCapacity() == 10 , "Seating capacity of the vehicle has not changed.");
    if(flag1 && flag2)testCasesPassed++;
    
}

void test_book_trip() {
    TravelDesk travelDesk;
    travelDesk.addTrip("XYZ", 2, "LocationX", "LocationY", 1500);

    Trip* firstBooking = travelDesk.bookTrip("LocationX", "LocationY", "XYZ", 1500);
    bool flag1=customAssert(firstBooking != nullptr,"wrong booking");
    bool flag2=customAssert(firstBooking->getBookedSeats() == 1,"wrong booking");


    Trip *Booking = travelDesk.bookTrip("LocationX", "LocationZ", "XYZ", 1500);

    bool flag3=customAssert(Booking ==nullptr ,"Trip is not there but booking function is not returning nullptr ");
    if(flag1 && flag2 && flag3)testCasesPassed++;
}











int main() {

    test_height_BT();
    test_show_trips_by_time_destination();
    test_show_trips_by_time();
    test_searchkeyin_BST();  //change slightly
    test_successor_predecessor_BST();
    test_getmaxminkey_BST();
    test_successor_predecessor_withkey();
    test_correct_pickup_drop();
    test_change_vehicle();
    test_noofnodes_BT();
    test_book_trip();
    

    std::cout << "Number of test cases passed: " << testCasesPassed << "/" << 11 << std::endl;

    return 0;
}