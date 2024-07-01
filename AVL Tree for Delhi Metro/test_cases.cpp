// #include<bits/stdc++.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "code.cpp"
using namespace std;


vector<string> getFileNames() {
    vector<string> filenames;
    filenames.push_back("blue.txt");
    filenames.push_back("green.txt");
    filenames.push_back("magenta.txt");
    filenames.push_back("orange.txt");
    filenames.push_back("red.txt");
    filenames.push_back("violet.txt");
    filenames.push_back("yellow.txt");
    return filenames;
}

void testPopulateLine() {
    cout<<"Testing populateLine()"<<endl;
    vector<string> filenames = getFileNames();
    int expectedTotalStops[] = {44, 21, 25, 6, 29,38, 62};
    for (int i = 0; i < filenames.size(); i++) {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine* metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
        cout << "Line name: " << metroLine->getLineName() << endl;
        cout << "Total stops: " << metroLine->getTotalStops() << endl;
        cout << endl;
        assert(metroLine->getTotalStops() == expectedTotalStops[i]);
        metroLine->printLine();
    }
}

void testPopulateTree() {
    cout<<"Testing populateTree()"<<endl;
    vector<string> filenames = getFileNames();
    AVLTree* tree = new AVLTree();
    tree->setRoot(nullptr);
    for (auto line : lines) {
        if (tree->getRoot() == nullptr) {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
    cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    assert(tree->height(tree->getRoot()) == 9);
    assert(tree->getTotalNodes(tree->getRoot()) == 211);
}

vector<string> getExpectedPath() {
    vector<string> expectedPath;
    expectedPath.push_back("Pul Bangash");
    expectedPath.push_back("Pratap Nagar");
    expectedPath.push_back("Shastri Nagar");
    expectedPath.push_back("Inder Lok");
    expectedPath.push_back("Kanhaiya Nagar");
    expectedPath.push_back("Keshav Puram");
    expectedPath.push_back("Netaji Subhash Place");
    expectedPath.push_back("Kohat Enclave");
    expectedPath.push_back("Pitampura");

    return expectedPath;
}

void testFindPath() {
    PathFinder* pathFinder = new PathFinder(new AVLTree(), lines);
    pathFinder->createAVLTree();
    Path* path = pathFinder->findPath("Pitampura", "Pul Bangash");
    assert(path != nullptr);
    cout << "Total fare: " << path->getTotalFare() << endl;
    path->printPath();
    vector<string> expectedPath = getExpectedPath();
    for (int i = 0; i < expectedPath.size(); i++) {
        assert(path->getStops()[i]->getStopName() == expectedPath[i]);
    }
}

int main() {
    vector<void(*)()> tests;
    tests.push_back(&testPopulateLine);
    tests.push_back(&testPopulateTree);
    tests.push_back(&testFindPath);

    for (auto test : tests) {
        test();
    }

    return 0;
}
