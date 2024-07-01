#include <iostream>
#include <vector>
#include <map>
//#include <bits/stdc++.h>

using namespace std;

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, string pick_up_location, string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    string getPickUpLocation() const {
        return pick_up_location;
    }

    string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(string location) {
        pick_up_location = location;
    }

    void setDropLocation(string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    string pick_up_location;
    string drop_location;
    int departure_time;
    int booked_seats;
};

//class BinaryTreeNode;

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class TransportService {
public:
    TransportService(string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip)
    {
        BinaryTreeNode* node=new BinaryTreeNode();
        node->setDepartureTime(trip->getDepartureTime());
        node->setTripNodePtr(trip);

        if(BSThead==nullptr)
        {
            setBSTHead(node);
            return;
        }

        BinaryTreeNode* ptr=BSThead;
        while(true) 
        {
            if(key<ptr->getDepartureTime()) 
            {
                if(ptr->getLeftPtr()!=nullptr) 
                ptr=ptr->getLeftPtr();
                
                else
                {
                    ptr->setLeftPtr(node);
                    node->setParentPtr(ptr);
                    break;
                }
            } 

            else 
            {
                if(ptr->getRightPtr()!=nullptr) 
                ptr=ptr->getRightPtr();
                
                else
                {
                    ptr->setRightPtr(node);
                    node->setParentPtr(ptr);
                    break;
                }
            }
        }
    }

    BinaryTreeNode* deleteTrip(BinaryTreeNode* root, int key)
    {
        if(root==nullptr)
        return root;

        if(key<root->getDepartureTime())
        root->setLeftPtr(deleteTrip(root->getLeftPtr(), key));

        else 
        if(key>root->getDepartureTime())
        root->setRightPtr(deleteTrip(root->getRightPtr(), key));

        else 
        {
            if(root->getLeftPtr()==nullptr) 
            {
                BinaryTreeNode* temp=root->getRightPtr();
                if(temp!=nullptr)
                temp->setParentPtr(root->getParentPtr());

                delete root;
                return temp;
            } 
            
            else 
            if(root->getRightPtr()==nullptr)
            {
                BinaryTreeNode* temp=root->getLeftPtr();
                
                if(temp!=nullptr)
                temp->setParentPtr(root->getParentPtr());
                
                delete root;
                return temp;
            }
        

            //BinaryTreeNode* successor=nullptr;(root->right);
            BinaryTreeNode *successor=root->getRightPtr();

            while(successor->getLeftPtr()!=nullptr)
            successor=successor->getLeftPtr();

            root->setDepartureTime(successor->getDepartureTime());
            root->setRightPtr(deleteTrip(root->getRightPtr(), successor->getDepartureTime()));
        }

        return root;
    }

private:
    string name;
    BinaryTreeNode* BSThead;
};



class Vehicle {
public:
    Vehicle(string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    vector<Trip*> getTrips()
    {
        return trips;
    }

    // Setter functions
    void setVehicleNumber(string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

private:
    string vehicle_number;
    int seating_capacity;
    vector<Trip*> trips;
};

class Location {
public:
    Location(string name) : name(name) {}

    // Getter functions
    string getName() const {
        return name;
    }

    vector<Trip*> getTrips()
    {
        return trips;
    }

    TransportService* getServicePtr(string droplocation) const 
    {
        for(int i=0;i<serviceptrs.size();i++)
        {
            if(serviceptrs[i]->getName().compare(droplocation)==0)
            return serviceptrs[i];
        }
        return nullptr;
    }

    // Setter functions
    void setName(string location_name) {
        name = location_name;
    }

    void setServicePtr(TransportService* service)
    {
        serviceptrs.push_back(service);
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

private:
    string name;
    vector<TransportService* >serviceptrs;
    vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    BinaryTreeNode* getRoot()
    {
        return root;
    }

    int calcHeight(BinaryTreeNode *root) const
    {
        if(root==nullptr)
        return 0;

        int lheight=calcHeight(root->getLeftPtr());
        int rheight=calcHeight(root->getRightPtr());
        return max(lheight,rheight) + 1;
    }

    int getHeight() const 
    {
        // Implement tree height calculation
        return calcHeight(root);
    }

    int countNodes(BinaryTreeNode *root) const
    {
        if(root==nullptr)
        return 0;
        return countNodes(root->getLeftPtr()) + countNodes(root->getRightPtr()) + 1;
    }

    int getNumberOfNodes() const 
    {
        // Implement node count calculation
        return countNodes(root);
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    void setRoot(BinaryTreeNode *node)
    {
        root=node;
    }

    BinaryTreeNode* getElementWithMinimumKey() const 
    {
        BinaryTreeNode *ptr=root;
        if(ptr==nullptr)
        return nullptr;

        while(ptr->getLeftPtr()!=nullptr) 
        ptr=ptr->getLeftPtr();

        return ptr;
    }

    BinaryTreeNode* getElementWithMaximumKey() const 
    {
        // Implement getting the element with the maximum key
        BinaryTreeNode *ptr=root;
        if(ptr==nullptr)
        return nullptr;

        while(ptr->getRightPtr()!=nullptr) 
        ptr=ptr->getRightPtr();

        return ptr;
    }

    BinaryTreeNode* searchInBST(BinaryTreeNode* ptr, int key) const
    {
        if(ptr==nullptr)
        return nullptr;

        if(ptr->getDepartureTime()==key)
        return ptr;

        if(ptr->getDepartureTime()>key)
        return searchInBST(ptr->getLeftPtr(), key);

        return searchInBST(ptr->getRightPtr(), key);
    }

    BinaryTreeNode* searchNodeWithKey(int key) const 
    {
        // Implement searching for a node with the given key
        return searchInBST(root,key);
    }

    /*BinaryTreeNode* successor(BinaryTreeNode* ptr, int key)
    {
        if(ptr==nullptr)
        return nullptr;

        if(ptr->getRightPtr()!=nullptr)
        {
            ptr=ptr->getRightPtr();

            while(ptr->getLeftPtr()!=nullptr)
            ptr=ptr->getLeftPtr();

            return ptr;
        }
        else
        {
            BinaryTreeNode* parent=ptr->getParentPtr();
            while(parent!=nullptr && ptr!=parent->getRightPtr())
            {
                ptr=parent;
                parent=parent->getParentPtr();
            }

            return parent;
        }
    }*/

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const 
    {
        if(node==nullptr)
        return nullptr;

        //int key=node->getDepartureTime();

        if(node->getRightPtr()!=nullptr)
        {
            node=node->getRightPtr();

            while(node->getLeftPtr()!=nullptr)
            node=node->getLeftPtr();

            return node;
        }
        else
        {
            BinaryTreeNode* parent=node->getParentPtr();
            while(parent!=nullptr && node!=parent->getLeftPtr())
            {
                node=parent;
                parent=parent->getParentPtr();
            }

            return parent;
        }

        return nullptr;
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const 
    {
        // Implement getting the successor node by key
        BinaryTreeNode *node=searchNodeWithKey(key);
        node=getSuccessorNode(node);
        return node;
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const 
    {
        // Implement getting the predecessor node of the given node
        if(node==nullptr)
        return nullptr;

        if(node->getLeftPtr()!=nullptr)
        {
            node=node->getLeftPtr();

            while(node->getRightPtr()!=nullptr)
            node=node->getRightPtr();

            return node;
        }
        else
        {
            BinaryTreeNode *parent=node->getParentPtr();
            while(parent!=nullptr && node!=parent->getRightPtr())
            {
                node=parent;
                parent=parent->getParentPtr();
            }

            return parent;
        }

        return nullptr;
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const 
    {
        BinaryTreeNode *node=searchNodeWithKey(key);
        node=getPredecessorNode(node);
        return node;
    }

    BinaryTreeNode* inorderTraversal(BinaryTreeNode* node, int after_time)
    {
        if(node == nullptr)
        return nullptr;

        inorderTraversal(node->getLeftPtr(), after_time);

        if(node->getDepartureTime() >= after_time)
        return node;

        inorderTraversal(node->getRightPtr(), after_time);
    }
};

class TravelDesk {
public:
    void addTrip(string vehicle_number, int seating_capacity, string pick_up_location, string drop_location, int departure_time) 
    {
        // Implement this function to add a trip
        Vehicle* vehicle = nullptr;

        int f=-1;
        for(int i=0;i<vehicles.size();i++)
        {
            if(vehicles[i]->getVehicleNumber().compare(vehicle_number)==0)
            {
                f=i;
                break;
            }
        }
        
        if(f==-1)
        {
            vehicle=new Vehicle(vehicle_number,seating_capacity);
            vehicle->setVehicleNumber(vehicle_number);  //Constructor not needed?
            vehicle->setSeatingCapacity(seating_capacity);
            vehicles.push_back(vehicle);
            f=vehicles.size()-1;
        }
        // cout<<vehicles[f]->getVehicleNumber();
        
        // // Create a new trip and add it to the appropriate objects
        Trip *trip=nullptr;
        trip=new Trip(vehicles[f], pick_up_location, drop_location, departure_time);
        trip->setPickUpLocation(pick_up_location);
        trip->setDropLocation(drop_location);
        trip->setDepartureTime(departure_time);
        vehicles[f]->addTrip(trip);

        int loc=-1;
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName().compare(pick_up_location)==0)
            {
                loc=i;
                break;
            }
        }

        if(loc==-1)
        {
            Location *newloc=new Location(pick_up_location);
            newloc->setName(pick_up_location);

            //TransportService *service=new TransportService(drop_location);
            locations.push_back(newloc);
            
            loc=locations.size()-1;
        }
        // cout<<locations[loc]->getServicePtr(drop_location);
        if(locations[loc]->getServicePtr(drop_location)!=nullptr)
            locations[loc]->getServicePtr(drop_location)->addTrip(departure_time, trip);
        else
        {
            TransportService *service=new TransportService(drop_location);
            //cout<<"rrreer"<<'\n';
            service->setName(drop_location);
            service->addTrip(departure_time, trip);
            locations[loc]->setServicePtr(service);
        }
        // cout<<locations[loc]->getServicePtr(drop_location)->getName()<<'\n';

        locations[loc]->addTrip(trip);
    }

    vector<Trip*> showTrips(string pick_up_location, int after_time, int before_time) 
    {
        // Implement this function to retrieve trips within a specified time range
        if(after_time > before_time)
        {
            int t=after_time;
            after_time=before_time;
            before_time=t;
        }

        vector<Trip*> trip;
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()==pick_up_location)
            {
                trip=locations[i]->getTrips();
                break;
            }
        }
        
        for(int i=0;i<trip.size();i++)
        {
            if(trip[i]->getDepartureTime()<after_time || trip[i]->getDepartureTime() >= before_time)
            {
                trip.erase(trip.begin()+i);
                --i;
            }
        }

        return trip;
    }

    vector<Trip*> showTripsbydestination(string pick_up_location, string destination, int after_time, int before_time) 
    {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocation

        if(after_time > before_time)
        {
            int t=after_time;
            after_time=before_time;
            before_time=t;
        }

        vector<Trip*> trip;
        for(int i=0;i<locations.size();i++)
        {
            TransportService *service=nullptr;
            if(locations[i]->getName()==pick_up_location)
            {
                service=locations[i]->getServicePtr(destination);

                BinaryTreeNode *ptr=service->getBSTHead();
                BinarySearchTree obj;
                obj.setRoot(ptr);
                int prevtime=ptr->getDepartureTime();
                int time=0;
                
                if(ptr->getDepartureTime() > after_time)
                {
                    while(obj.getPredecessorNodeByKey(ptr->getDepartureTime())!=nullptr)
                    {
                        time = ptr->getDepartureTime();
                        ptr = obj.getPredecessorNodeByKey(ptr->getDepartureTime());
                        prevtime = ptr->getDepartureTime();

                        if(time >= after_time && prevtime < after_time)
                        {
                            ptr = obj.getSuccessorNodeByKey(prevtime);
                            break;
                        }
                    }
                }
                
                else
                if(ptr->getDepartureTime() < after_time)
                {
                    while(obj.getSuccessorNodeByKey(ptr->getDepartureTime())!=nullptr)
                    {
                        prevtime = ptr->getDepartureTime();
                        ptr = obj.getSuccessorNodeByKey(ptr->getDepartureTime());
                        time = ptr->getDepartureTime();

                        if(time >= after_time && prevtime < after_time)
                        break;
                    }
                }




                while(ptr->getDepartureTime()<before_time)
                {
                    trip.push_back(ptr->getTripNodePtr());
                    BinarySearchTree ob;
                    ob.setRoot(ptr);
                    ptr=ob.getSuccessorNodeByKey(ptr->getTripNodePtr()->getDepartureTime());
                }
            }
        }
        return trip;
    }

    Trip* bookTrip(string pick_up_location, string drop_location, string vehicle_number, int departure_time) 
    {
        // Implement this function to book a trip
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()==pick_up_location)
            {
                if(!locations[i]->getServicePtr(drop_location))
                return nullptr;


                BinaryTreeNode *root=locations[i]->getServicePtr(drop_location)->getBSTHead();
                BinarySearchTree ob;
                ob.setRoot(root);
                BinaryTreeNode* ptr=ob.searchNodeWithKey(root->getDepartureTime());

                if(ptr!=nullptr)
                {
                    int booked=ptr->getTripNodePtr()->getBookedSeats();
                    ptr->getTripNodePtr()->setBookedSeats(++booked);

                    //inorderPrint(root);

                    if(ptr->getTripNodePtr()->getBookedSeats() == ptr->getTripNodePtr()->getVehicle()->getSeatingCapacity())
                    {
                        root=locations[i]->getServicePtr(drop_location)->deleteTrip(root, ptr->getDepartureTime());
                    }

                    return ptr->getTripNodePtr();
                }
            }
        }

        return nullptr;
    }

    Location* getLocation(string location)
    {
        for(int i=0;i<locations.size();i++)
        {
            if(locations[i]->getName()==location) 
            return locations[i];
        }
        return nullptr;
    }

public:
    vector<Vehicle*> vehicles;
    vector<Location*> locations;
};
