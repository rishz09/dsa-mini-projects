// #include<bits/stdc++.h>
#include<assert.h>
#include<iostream>
#include "code.cpp"
//#include"b22cs067.cpp"

int failed_tests = 0;

void test1() {
    std::string entity_name = "Commerce";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    StudentRecord* student;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == "EthanMartinez") {
            student = ite->get_element();
            break;
        }
        ite = ite->get_next();
    }
    assert(student->get_studentName() == "EthanMartinez" && "Student EthanMartinez is not present in the Commerce Entity");
}

void test2() {
    std::string entity_name = "MBA";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    StudentRecord* student;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == "MichaelWilson") {
            student = ite->get_element();
            break;
        }
        ite = ite->get_next();
    }
    assert(student->get_studentName() == "MichaelWilson"&& "Student MichaelWilson is not present in the MBA Entity");
}

void test3() {
    std::string entity_name = "DSA";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 69 && "Incorrect count of records in DSA course");
}

void test4() {
    std::string entity_name = "Programming";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 87 && "Incorrect count of records in Programming Club");
}

void test5() {
    std::string entity_name = "Networking";
    LinkedList entity;
    std::string studentname = "NoahHernandez";

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.delete_student(studentname);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 0 && "Record still exists, Delete function not working!");
}

void test6() {
    std::string entity_name = "Econometrics";
    LinkedList entity;
    std::string studentname = "ShaheenClark";
    std::string studentroll = "B22ECON1721";
    StudentRecord student;
    student.set_studentName(studentname) ;
    student.set_rollNumber(studentroll) ;

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.add_student(student);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 1 && "Record is not added, Add Student Record function not working!");
}

void test7() {
    std::string entity_name = "Commerce";
    LinkedList entity;
    std::string studentname = "WilliamJones";

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.delete_student(studentname);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 0 && "Record still exists, Delete function not working!");
}

void test8() {
    std::string entity_name = "G6";
    LinkedList entity;
    std::string studentname = "KoshimoDiago";
    std::string studentroll = "B22POLSCI1078";
    StudentRecord student;
    student.set_studentName(studentname) ;
    student.set_rollNumber(studentroll) ;

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.add_student(student);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 1 && "Record is not added, Add Student Record function not working!");
}

void test9() {
    std::string entity_name = "Thermodynamics";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 2 && "Incorrect count of records in Thermodynamics course");
}

void test10() {
    std::string entity_name = "Finance";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 13 && "Incorrect count of records in Finance course");
}

void test11() {
    std::string entity_name = "English Literature";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    int size = 0;
    while (ite != nullptr) {
        size += 1;
        ite = ite->get_next();
    }
    assert(size == 6 && "Incorrect count of records in English Literature course");
}

void test12() {
    std::string entity_name = "G1";
    LinkedList entity;
    std::string studentname = "JamesWilson";
    std::string studentroll = "B22CHEM1016";
    StudentRecord student;
    student.set_studentName(studentname) ;
    student.set_rollNumber(studentroll) ;

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.add_student(student);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 1 && "Record is not added, Add Student Record function not working!");
}

void test13() {
    std::string entity_name = "Commerce";
    LinkedList entity;
    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }
    Node* ite = entity.get_iterator();
    StudentRecord* student;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == "OliviaTaylor") {
            student = ite->get_element();
            break;
        }
        ite = ite->get_next();
    }
    assert(student->get_studentName() == "OliviaTaylor"&& "Student OliviaTaylor is not present in the MBA Entity");
}


void test14() {
    std::string entity_name = "Social Science";
    LinkedList entity;
    std::string studentname = "NoahMartin";

    for (auto i : EntityArray) {
        if (i.get_name() == entity_name) {
            entity = i;
            break;
        }
    }

    entity.delete_student(studentname);
    Node* ite = entity.get_iterator();

    int if_exists = 0;
    while (ite != nullptr) {
        if (ite->get_element()->get_studentName() == studentname) {
            if_exists = 1;
            break;
        }
        ite = ite->get_next();
    }

    assert(if_exists == 0 && "Record still exists, Delete function not working!");
}


int main() {
    int failed_tests = 0;
    int retarr[14];
    int k =0;

    std::vector<void (*)()> unit_tests_list = {
        test1, test2, test3, test4, test5, test6, test7, test8, test9, test10, test11, test12, test13, test14
    };
    int total = unit_tests_list.size();

    try {
        read_input_file("NewDetails.txt");
    } catch (const std::exception& e) {
        std::cout << "Could not read Sample Input File! Ensure that the file 'Details.txt' is in the folder and try again!" << std::endl;
        return 1;
    }

    for (int i = 0; i < total; ++i) {
        try {
            unit_tests_list[i]();
            retarr[k] = 1;
            k+=1;
        } catch (const std::exception& e) {
            retarr[k] = 0;
            k+=1;
            //failed_tests++;
            //std::cout << "Unit test #" << i+1 << " failure: " << e.what() << std::endl;
        }
    }

    // if (failed_tests == 0) {
    //     std::cout << "All tests have passed successfully!" << std::endl;
    // } else {
    //     std::cout << failed_tests << " tests failed!" << std::endl;
    // }

    // cout << "Number of failed test cases are: " << failed_tests<< endl;
    //std::ostringstream retarr_output;
    for (int j = 0; j < total; ++j) {
        std::cout << retarr[j];
        // if (j != total - 1) {
        //     std::cout << ",";
        
    }
    //std::cout << std::endl;
}