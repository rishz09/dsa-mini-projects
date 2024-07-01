//RED LINE'S Inder Lok changed to Inderlok
// #include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const 
{
    int s=0;
    MetroStop* stop=node;
    while(stop!=nullptr)
    {
        ++s;
        stop=stop->getNextStop();
    }

    return s;
}

void MetroLine::populateLine(std::string filename) 
{
    // Read the file and populate the line
    fstream fp;
    fp.open(filename,ios::in); 

    if(fp.is_open())  
    {
        string temp;
        while(getline(fp, temp))  
        {
            int l=temp.length();
            int last_space=temp.rfind(' ');
            string name=temp.substr(0, last_space);
            string price=temp.substr(last_space + 1, l);

            if(price.at(price.length()-1) == ',')
            price=price.substr(0,price.length()-1);

            int fare=stoi(price);

            MetroStop *ob=new MetroStop(name, this, fare);

            if(getNode()==nullptr)
            setNode(ob);
            else
            {
                MetroStop *ptr=getNode();
                //MetroStop *temp=nullptr;
                while(ptr->getNextStop()!=nullptr)
                {   
                    //temp=ptr;
                    ptr=ptr->getNextStop();
                }

                ob->setPrevStop(ptr);
                ptr->setNextStop(ob);
            }
        }
    }
}

// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent=nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root=nullptr;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchInAVL(AVLNode* node, string stopName);
    AVLNode* searchStop(string stopName);
    //bool isBalanced(AVLNode *root);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) 
{
    if(node == nullptr)
    return 0;

    int l_height=height(node->getLeft());
    int r_height=height(node->getRight());

    return max(l_height,r_height) + 1;
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node)
{
    if(node == nullptr)
    return 0;

    return height(node->getLeft()) - height(node->getRight());
}

void AVLTree::rotateLeft(AVLNode* node) 
{
    AVLNode* temp=node->getRight();
    node->setRight(temp->getLeft());

    if(temp->getLeft()!=nullptr)
    temp->getLeft()->setParent(node);

    temp->setParent(node->getParent());

    if(node->getParent()==nullptr)
    setRoot(temp);

    else
    if(node==node->getParent()->getLeft())
    node->getParent()->setLeft(temp);

    else
    node->getParent()->setRight(temp);

    temp->setLeft(node);
    node->setParent(temp);
}

void AVLTree::rotateRight(AVLNode* node) 
{
    AVLNode* temp=node->getLeft();
    node->setLeft(temp->getRight());

    if(temp->getRight()!=nullptr)
    temp->getRight()->setParent(node);

    temp->setParent(node->getParent());

    if(node->getParent()==nullptr)
    setRoot(temp);

    else
    if(node==node->getParent()->getLeft())
    node->getParent()->setLeft(temp);

    else
    node->getParent()->setRight(temp);

    temp->setRight(node);
    node->setParent(temp);
}

void AVLTree::balance(AVLNode* node) 
{   
    int balance=0;
    while(node!=nullptr)
    {
        balance=balanceFactor(node);

        if(balance>1)
        {
            if(balanceFactor(node->getLeft())<0)
            rotateLeft(node->getLeft());

            rotateRight(node);
        }
        
        else
        if(balance<-1)
        {
            if(balanceFactor(node->getRight())>0)
            rotateRight(node->getRight());

            rotateLeft(node);
        }

        node=node->getParent();
    }
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) 
{   
    if(getRoot()==nullptr)
    {
        AVLNode* ptr=new AVLNode(metroStop->getStopName());
        ptr->addMetroStop(metroStop);
        setRoot(ptr);
        return;
    }

    if(stringCompare(metroStop->getStopName(), node->getStopName())==0)
    {
        node->addMetroStop(metroStop);
        return;
    }

    else
    if(stringCompare(metroStop->getStopName(), node->getStopName()) < 0)
    {   
        if(node->getLeft()==nullptr)
        {
            AVLNode* ptr=new AVLNode(metroStop->getStopName());
            ptr->addMetroStop(metroStop);
            node->setLeft(ptr);
            node->getLeft()->setParent(node);
            balance(ptr);
        }

        else
        insert(node->getLeft(), metroStop);  //traversing until node == nullptr obtained
    }

    else
    {
        if(node->getRight()==nullptr)
        {
            AVLNode* ptr=new AVLNode(metroStop->getStopName());
            ptr->addMetroStop(metroStop);
            node->setRight(ptr);
            node->getRight()->setParent(node);
            balance(ptr);
        }

        else
        insert(node->getRight(), metroStop);
    }
}

void AVLTree::populateTree(MetroLine* metroLine) 
{
    MetroStop* ptr=metroLine->getNode();
    while(ptr!=nullptr)
    {
        insert(getRoot(), ptr);
        ptr=ptr->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) 
    return;

    inOrderTraversal(node->getLeft());
    if(node->getStops().size()>1)
    {
        vector<MetroStop*> stops=node->getStops();
        for(int i=0;i<stops.size();i++)
        cout << node->getStopName() <<' ' << stops[i]->getLine()->getLineName() << endl;

        cout << endl;
    }
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr)
    return 0;
    
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchInAVL(AVLNode* ptr, string stopName)
{
    //ptr=getRoot();

    if(ptr==nullptr)
    return nullptr;

    if(ptr->getStopName()==stopName)
    return ptr;

    if(stringCompare(stopName, ptr->getStopName()) < 0)
    return searchInAVL(ptr->getLeft(), stopName);
    
    return searchInAVL(ptr->getRight(), stopName);
}

AVLNode* AVLTree::searchStop(string stopName)
{
    return searchInAVL(getRoot(), stopName);
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    //cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {

    for(auto stop:stops) 
    {
        //cout << stop->getStopName() << " - " << stop->getLine()->getLineName() << endl;
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;
    queue<int> countStops;
    Path* shortestPath=nullptr;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);
    void createMultipleTrips(AVLNode* node, Exploration& ob, Trip* prevTrip, int count);
    void givePath(Trip* trip);
    //Path* giveShortestPath();
    bool isLoop(Trip *trip);
    int lengthOfPath(Path *path);
    int findFare(Path* path);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() 
{
    for(int i=0;i<lines.size();i++)
    getTree()->populateTree(lines[i]);
}

void PathFinder::createMultipleTrips(AVLNode *node, Exploration& ob, Trip* prevTrip, int count)
{
    if(prevTrip==nullptr)
    {
        for(int i=0;i<node->getStops().size();i++)
        {
            vector<MetroStop*> station=node->getStops();
            Trip* newTrip1=new Trip(station[i], nullptr);
            Trip* newTrip2=new Trip(station[i], nullptr);
            ob.enqueue(newTrip1);
            countStops.push(count);
            ob.enqueue(newTrip2);
            countStops.push(count);
            
        }
    }

    else
    {
        for(int i=0;i<node->getStops().size();i++)
        {
            vector<MetroStop*> station=node->getStops();
            if(station[i]->getLine() == prevTrip->getNode()->getLine())
            {
                Trip* newTrip=new Trip(station[i], prevTrip);
                ob.enqueue(newTrip);
                countStops.push(count);
            }

            else
            {
                Trip* newTrip1=new Trip(station[i], prevTrip);
                Trip* newTrip2=new Trip(station[i], prevTrip);
                ob.enqueue(newTrip1);
                countStops.push(count);
                ob.enqueue(newTrip2);
                countStops.push(count);
            }

            
        }
    }
}

void PathFinder::givePath(Trip* trip)
{   
    Path *ob=new Path();
    Trip *ptr=trip;

    while(ptr!=nullptr)
    {
        ob->addStop(ptr->getNode());
        ptr=ptr->getPrev();
    }

    ob->setTotalFare(0);
    shortestPath=ob;
}

int PathFinder::lengthOfPath(Path* path)
{
    vector<MetroStop*> pathStops=path->getStops();
    return pathStops.size();
}

bool PathFinder::isLoop(Trip *trip)
{   
    Trip *ptr=trip->getPrev();
    while(ptr!=nullptr)
    {
        if((ptr->getNode()->getStopName() == trip->getNode()->getStopName()))
        return true;

        ptr=ptr->getPrev();
    }
    return false;
}

int PathFinder::findFare(Path* path)
{
    int fare=0;
    vector<MetroStop*> pathStops=path->getStops();
    int l=pathStops.size();

    string linename=pathStops[l-1]->getLine()->getLineName();
    int prev=pathStops[l-1]->getFare();

    for(int i=l-1;i>=0;i--)
    {
        if(pathStops[i]->getLine()->getLineName() != linename)
        {
            string stopName=pathStops[i]->getStopName();
            vector<MetroStop*> temp=tree->searchStop(stopName)->getStops();

            for(int j=0;j<temp.size();j++)
            {
                if(temp[j]->getLine()->getLineName()==linename)
                {
                    int lineFare=temp[j]->getFare();
                    fare+=abs(lineFare-prev);
                    prev=pathStops[i]->getFare();
                    linename=pathStops[i]->getLine()->getLineName();
                    break;
                }
            }
        }

        else
        {
            fare+=abs(pathStops[i]->getFare()-prev);
            prev=pathStops[i]->getFare();
            linename=pathStops[i]->getLine()->getLineName();
        }
    }

    return fare;
}

Path* PathFinder::findPath(std::string origin, std::string destination) 
{
    AVLNode *start=tree->searchStop(origin);
    if(start==nullptr)
    return nullptr;

    Exploration explore;

    createMultipleTrips(start, explore, nullptr, 0);

    int f=0,c;
    while(!explore.isEmpty())
    {
        Trip* ptr=explore.dequeue();
        c=countStops.front();
        countStops.pop();

        if(isLoop(ptr))  //checks if a junction is visited again. It means that path is not possible
        {
            //cout << "Loop happened" << endl;
            continue;
        }

        if(origin==destination)
        {
            Path *same=new Path();
            vector<MetroStop*> stops=tree->searchStop(origin)->getStops();
            same->addStop(stops[0]);
            same->setTotalFare(0);

            return same;
        }
        
        if(ptr->getPrev()==nullptr && f==0)
        {
            f=1;
            MetroStop* metrostop=ptr->getNode();

            while(metrostop->getNextStop()!=nullptr)
            {
                metrostop=metrostop->getNextStop();
                Trip* temp=ptr;
                ptr=new Trip(metrostop, ptr);
                ++c;

                if(shortestPath!=nullptr && c>=shortestPath->getStops().size())
                break;

                if(metrostop->getStopName() == destination)
                givePath(ptr);
                
                if(tree->searchStop(metrostop->getStopName())->getStops().size()>1)
                {
                    createMultipleTrips(tree->searchStop(metrostop->getStopName()), explore, temp, c);
                    break;
                }
            }   
        }

        else
        if(ptr->getPrev()==nullptr && f==1)
        {
            f=0;
            MetroStop* metrostop=ptr->getNode();

            while(metrostop->getPrevStop()!=nullptr)
            {
                metrostop=metrostop->getPrevStop();
                Trip* temp=ptr;
                ptr=new Trip(metrostop, ptr);
                ++c;
                if((shortestPath!=nullptr) && (c>=shortestPath->getStops().size()))
                break;

                if(metrostop->getStopName() == destination)
                givePath(ptr);

                if(tree->searchStop(metrostop->getStopName())->getStops().size()>1)
                {
                    createMultipleTrips(tree->searchStop(metrostop->getStopName()), explore, temp, c);
                    break;
                }
            }
        }

        else
        if((ptr->getPrev()->getNode() == ptr->getNode()->getNextStop()) && (ptr->getPrev()->getNode()->getLine()->getLineName() == ptr->getNode()->getNextStop()->getLine()->getLineName()))
        {
            
            MetroStop* metrostop=ptr->getNode();

            while(metrostop->getPrevStop()!=nullptr)
            {
                metrostop=metrostop->getPrevStop();
                Trip* temp=ptr;
                ptr=new Trip(metrostop, ptr);
                ++c;

                if((shortestPath!=nullptr) && (c>=shortestPath->getStops().size()))
                break;

                if(metrostop->getStopName() == destination)
                givePath(ptr);

                if(tree->searchStop(metrostop->getStopName())->getStops().size()>1)
                {
                    createMultipleTrips(tree->searchStop(metrostop->getStopName()), explore, temp, c);
                    break;
                }
            }
        }

        else
        if((ptr->getPrev()->getNode() == ptr->getNode()->getPrevStop()) && (ptr->getPrev()->getNode()->getLine()->getLineName() == ptr->getNode()->getPrevStop()->getLine()->getLineName()))
        {
            MetroStop* metrostop=ptr->getNode();

            while(metrostop->getNextStop()!=nullptr)
            {
                metrostop=metrostop->getNextStop();
                Trip* temp=ptr;
                ptr=new Trip(metrostop, ptr);
                ++c;

                if((shortestPath!=nullptr) && (c>=shortestPath->getStops().size()))
                break;

                if(metrostop->getStopName() == destination)
                givePath(ptr);

                if(tree->searchStop(metrostop->getStopName())->getStops().size()>1)
                {
                    createMultipleTrips(tree->searchStop(metrostop->getStopName()), explore, temp, c);
                    break;
                }
            } 
        }

        else
        if(f==0)
        {
            f=1;
            MetroStop* metrostop=ptr->getNode();

            while(metrostop->getNextStop()!=nullptr)
            {
                metrostop=metrostop->getNextStop();
                Trip* temp=ptr;
                ptr=new Trip(metrostop, ptr);
                ++c;

                if((shortestPath!=nullptr) && (c>=shortestPath->getStops().size()))
                break;

                if(metrostop->getStopName() == destination)
                givePath(ptr);

                if(tree->searchStop(metrostop->getStopName())->getStops().size()>1)
                {
                    createMultipleTrips(tree->searchStop(metrostop->getStopName()), explore, temp, c);
                }

                
            }
        }

        else
        if(f==1)
        {
            f=0;
            MetroStop* metrostop=ptr->getNode();

            while(metrostop->getPrevStop()!=nullptr)
            {
                metrostop=metrostop->getPrevStop();
                Trip* temp=ptr;
                ptr=new Trip(metrostop, ptr);
                ++c;

                if((shortestPath!=nullptr) && (c>=shortestPath->getStops().size()))
                break;

                if(metrostop->getStopName() == destination)
                givePath(ptr);
                
                if(tree->searchStop(metrostop->getStopName())->getStops().size()>1)
                {
                    createMultipleTrips(tree->searchStop(metrostop->getStopName()), explore, temp, c);
                    break;
                }
            }
        }
    }

    if(shortestPath!=nullptr)
    shortestPath->setTotalFare(findFare(shortestPath));

    return shortestPath;
}
vector<MetroLine*> lines;

// int main()
// {
//     vector<MetroLine*> metrolines;

//     string filenames[]={"blue.txt", "green.txt", "magenta.txt", "orange.txt", "red.txt", "violet.txt", "yellow.txt"};

//     for(int i=0;i<7;i++)
//     {
//         string lineName = filenames[i].substr(0, filenames[i].length() - 4);
//         MetroLine *ob=new MetroLine(lineName);
//         ob->populateLine(filenames[i]);

//         metrolines.push_back(ob);
//     }
    
//     AVLTree *tree=new AVLTree();
//     PathFinder ob(tree,metrolines);

//     ob.createAVLTree();

//     AVLNode *root=tree->getRoot();
//     //cout << tree->height(root) << '\n' << tree->getTotalNodes(root) << endl;
//     //ob.findPath("Technology Park", "Dwarka")->printPath();  //Important test case
//     // vector<MetroStop*> stop=tree->searchStop("Pitampura")->getStops();
//     // cout << stop[0]->getLine()->getLineName();
//     //tree->inOrderTraversal(root);

//     string origin="Shivaji Park"; 
//     string stop="Inderlok";   
//     if(ob.findPath(origin, stop)==nullptr)
//     cout << "Path not possible" << endl;
    
//     else
//     {
//         ob.findPath(origin, stop)->printPath();
//         cout << "\nTotal Fare : " << ob.findPath(origin,stop)->getTotalFare() << endl; 
//         cout << ob.findPath(origin, stop)->getStops().size() << endl;
//     }

//     // fstream fp;
//     // fp.open("green.txt",ios::in); 

//     // if(fp.is_open())  
//     // {
//     //     string temp;
//     //     while(getline(fp, temp))  
//     //     {
//     //         int last=temp.rfind(' ');
//     //         string name=temp.substr(0,last);
//     //         cout << tree->searchStop(name)->getStops().size() << endl;
//     //     }
//     //     fp.close();
//     // }

//     return 0;
// }