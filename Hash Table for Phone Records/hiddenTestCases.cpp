#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <csignal>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>

// Import your PhoneBook and PhoneRecord classes here
#include "code.cpp"



std::mutex mtx;
std::atomic<bool> segFaulted;

void handleSegmentationFault(int signal) {
    segFaulted.store(true, std::memory_order_relaxed);
    std::cerr << "Segmentation fault occurred in the test." << std::endl;
}

class CustomTestResult {
public:
    CustomTestResult() : passedCount(0), failedCount(0) {
        resultsFile.open("results_temp.txt", std::ios::app);
    }

    void addSuccess(const std::string& testName) {
        std::lock_guard<std::mutex> lock(mtx);
        ++passedCount;
        resultsFile << "passed," << testName << "\n";
    }

    void addFailure(const std::string& testName) {
        std::lock_guard<std::mutex> lock(mtx);
        ++failedCount;
        resultsFile << "failed," << testName << "\n";
        std::cout << "Test failed: " << testName << std::endl;
    }

    int getPassedCount() const {
        return passedCount.load(std::memory_order_relaxed);
    }

    int getFailedCount() const {
        return failedCount.load(std::memory_order_relaxed);
    }

    ~CustomTestResult() {
        resultsFile.close();
    }

    std::atomic<int> passedCount;
    std::atomic<int> failedCount;
    std::ofstream resultsFile;
};

class TestPhoneBook {
public:
    void setUp() {
        phone_book = new PhoneBook();
        phone_book->readRecordsFromFile("Details_new.txt");
    }

    void tearDown() {
        delete phone_book;
    }

    void runTest(const std::function<void()>& testCase, const std::string& testName) {
        segFaulted.store(false, std::memory_order_relaxed);
        signal(SIGSEGV, handleSegmentationFault);

        std::thread testThread([&]() {
            try {
                testCase();
            } catch (const std::exception& e) {
                segFaulted.store(true, std::memory_order_relaxed);
                std::cerr << "Exception occurred in the test: " << e.what() << std::endl;
            }
        });

        testThread.join();

        if (segFaulted.load(std::memory_order_relaxed)) {
            std::cout << "Skipping test: " << testName << " due to segmentation fault or exception." << std::endl;
            result.addFailure(testName);
        } 
    }

    void runTests() {
        runTest([this]() { test_add_and_fetch_contact(); }, "test_add_and_fetch_contact");
        //runTest([this]() { test_add_and_delete_contact(); }, "test_add_and_delete_contact");
        //runTest([this]() { test_delete_nonexistent_contact(); }, "test_delete_nonexistent_contact");
        runTest([this]() { test_fetch_nonexistent_contact(); }, "test_fetch_nonexistent_contact");
        runTest([this]() { test_add_multiple_contacts(); }, "test_add_multiple_contacts");
        runTest([this]() { test_delete_multiple_contacts(); }, "test_delete_multiple_contacts");
        runTest([this]() { test_add_delete_fetch_combination(); }, "test_add_delete_fetch_combination");
        runTest([this]() { test_fetch_contacts_with_multiple_words(); }, "test_fetch_contacts_with_multiple_words");
        runTest([this]() { test_search_with_middle_name(); }, "test_search_with_middle_name");
        runTest([this]() { test_delete_by_middle_name(); }, "test_delete_by_middle_name");
    }

    CustomTestResult result;
    PhoneBook* phone_book;

private:
    

    void test_add_and_fetch_contact() {
        // Test adding a new contact and then fetching it
        // PhoneRecord new_contact("Adhir Ranjan", "Novotel", {"7889234231"});

        vector<string> phoneNumbers1 = {"7889234231"};
        PhoneRecord record1("Adhir Ranjan", "Novotel", phoneNumbers1);
        phone_book->addContact(&record1);

        vector<PhoneRecord*> contacts = phone_book->fetchContacts(new std::string("Adhir"));
        // check if the contact is present in the first position of the list
        if (contacts.size() >= 1 && contacts[0]->getName() == "Adhir Ranjan") {
            result.addSuccess("test_add_and_fetch_contact");
        } else {
            result.addFailure("test_add_and_fetch_contact");
        }
        
    }

    void test_add_and_delete_contact() {
        // Test adding a new contact and then deleting it

        vector<string> phoneNumbers1 = {"7889234231"};
        PhoneRecord record1("Adhir Ranjan", "Novotel", phoneNumbers1);
        phone_book->addContact(&record1);


        if (phone_book->deleteContact(new std::string("Adhir Ranjan"))) {
            vector<PhoneRecord*> contacts = phone_book->fetchContacts(new std::string("Adhir Ranjan"));    
        

        if (contacts.empty()) {

                result.addSuccess("test_add_and_delete_contact");
            } else {
                result.addFailure("test_add_and_delete_contact");
            }

    }
    else {
        result.addFailure("test_add_and_delete_contact");
    }
    
    }

    void test_delete_nonexistent_contact() {
        // Test deleting a contact that doesn't exist (should not delete)

        vector<PhoneRecord*> initial_contacts = phone_book->fetchContacts(new std::string("Akshay Trivedi"));

        if (!phone_book->deleteContact(new std::string("Akshay Trivedi"))) {
            vector<PhoneRecord*> contacts_after_delete = phone_book->fetchContacts(new std::string("Akshay Trivedi"));
            if (initial_contacts == contacts_after_delete) {
                result.addSuccess("test_delete_nonexistent_contact");
            } else {
                result.addFailure("test_delete_nonexistent_contact");
            }
        } else {
            result.addFailure("test_delete_nonexistent_contact");
        }
    }

    void test_fetch_nonexistent_contact() {
        // Test fetching a contact that doesn't exist (should return an empty list)
        vector<PhoneRecord*> contacts = phone_book->fetchContacts(new std::string("Akshay Trivedi"));
        if (contacts.empty()) {
            result.addSuccess("test_fetch_nonexistent_contact");
        } else {
            result.addFailure("test_fetch_nonexistent_contact");
        }
    }

    void test_add_multiple_contacts() {
        // Test adding multiple contacts with different names
        std::vector<PhoneRecord> new_contacts = {
            PhoneRecord("John", "Benz", {"1111111111"}),
            PhoneRecord("Atreya", "Tata", {"2222222222"})
        };
        for (const PhoneRecord& contact : new_contacts) {
            phone_book->addContact(&contact);
        }
        bool allAdded = true;
        for (const PhoneRecord& contact : new_contacts) {
            vector<PhoneRecord*> contacts = phone_book->fetchContacts(new std::string(contact.getName()));
            //iterate through contacts and check if the name of the added contact is present in the list
            bool found = false;
            for (PhoneRecord* record : contacts) {
                if (record->getName() == contact.getName()) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                allAdded = false;
                break;
            }

        }
        if (allAdded) {
            result.addSuccess("test_add_multiple_contacts");
        } else {
            result.addFailure("test_add_multiple_contacts");
        }


    }

    void test_delete_multiple_contacts() {
        // Test deleting multiple contacts with different names
        // Fetch contacts with the name and store the first contact in the list in a variable
        vector<PhoneRecord*> contacts_gupta = phone_book->fetchContacts(new std::string("Ankush Gupta"));
        vector<PhoneRecord*> contacts_khanna = phone_book->fetchContacts(new std::string("Aarav Khanna"));

        if (phone_book->deleteContact(new std::string("Ankush Gupta")) && phone_book->deleteContact(new std::string("Aarav Khanna"))) {
            // Get the first contact again if any contacts are returned after fetching
            vector<PhoneRecord*> contacts_gupta_after_delete = phone_book->fetchContacts(new std::string("Ankush Gupta"));
            vector<PhoneRecord*> contacts_khanna_after_delete = phone_book->fetchContacts(new std::string("Aarav Khanna"));

            if (!contacts_gupta_after_delete.empty() && contacts_khanna_after_delete.empty()) {
                // Also check that other contacts with the same names are not deleted
                vector<PhoneRecord*> contacts_sharma = phone_book->fetchContacts(new std::string("Sharma"));
                vector<PhoneRecord*> contacts_kumar = phone_book->fetchContacts(new std::string("Kumar"));

                if (contacts_sharma.size() >= 1 && contacts_kumar.size() >= 1) {
                    result.addSuccess("test_delete_multiple_contacts");
                } else {
                    result.addFailure("test_delete_multiple_contacts");
                }
            } else {
                result.addFailure("test_delete_multiple_contacts");
            }
        } else {
            result.addFailure("test_delete_multiple_contacts");
        }
    }

    void test_add_delete_fetch_combination() {
        // Test a combination of add, delete, and fetch operations
        PhoneRecord new_contact("Venkata Subramanian", "Microsoft", {"8056297058"});
        phone_book->addContact(&new_contact);
        if (phone_book->deleteContact(new std::string("Venkata Subramanian"))) {
            vector<PhoneRecord*> contacts_after_delete = phone_book->fetchContacts(new std::string("Venkata Subramanian"));
            if (contacts_after_delete.empty()) {
                result.addSuccess("test_add_delete_fetch_combination");
            } else {
                result.addFailure("test_add_delete_fetch_combination");
            }
        } else {
            result.addFailure("test_add_delete_fetch_combination");
        }
    }

    void test_fetch_contacts_with_multiple_words() {
        // Test fetching contacts with multiple words in the query
        vector<PhoneRecord*> contacts = phone_book->fetchContacts(new std::string("Kumar"));
        if (!contacts.empty()) {
            result.addSuccess("test_fetch_contacts_with_multiple_words");
        } else {
            result.addFailure("test_fetch_contacts_with_multiple_words");
        }
    }

    void test_search_with_middle_name() {
        // Test searching with a middle name
        vector<PhoneRecord*> contacts = phone_book->fetchContacts(new std::string("Shekhar"));
        if (!contacts.empty()) {
            result.addSuccess("test_search_with_middle_name");
        } else {
            result.addFailure("test_search_with_middle_name");
        }
    }

    void test_delete_by_middle_name() {
        // Test deleting by a middle name
        if (phone_book->deleteContact(new std::string("Dev"))) {
            result.addSuccess("test_delete_by_middle_name");
        } else {
            result.addFailure("test_delete_by_middle_name");
        }
    }

    // CustomTestResult result;
};

int main() {
    TestPhoneBook test;
    test.setUp();
    test.runTests();

    int passedCount = test.result.getPassedCount();
    int failedCount = test.result.getFailedCount();

    std::ofstream jsonFile("test_results.json");
    jsonFile << "{ \"passed\": " << passedCount << ", \"failed\": " << failedCount << " }";
    jsonFile.close();

    if (failedCount > 0) {
        return 1; // Exit with a non-zero status code if there were failures
    }
    return 0;
}