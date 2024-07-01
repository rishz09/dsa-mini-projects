#include <iostream>
#include <cassert>
#include "code.cpp" // Include the header file for your PhoneBook class

int failed_tests = 0;

void assertWithMessage(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void testLoadContactsFromFile() {
    try {
        // Create a PhoneBook and load contacts from "Details.txt"
        PhoneBook phoneBook;
        phoneBook.readRecordsFromFile("Details.txt"); // Assuming the file is in the same directory

        // Fetch contacts and check if they are loaded correctly
        vector<PhoneRecord*> fetchedContacts = phoneBook.fetchContacts(new std::string("Rahul Kumar Mishra"));
        assertWithMessage(!fetchedContacts.empty(), "No contacts loaded from file");
        assertWithMessage(fetchedContacts[0]->getName() == "Rahul Kumar Mishra", "Contact not loaded from file");

        fetchedContacts = phoneBook.fetchContacts(new std::string("Vikram Rana"));
        assertWithMessage(!fetchedContacts.empty(), "No contacts loaded from file");
        // Either keyword Vikram or Rana should be present in the contact's name
        assertWithMessage(
            fetchedContacts[0]->getName().find("Vikram") != std::string::npos ||
            fetchedContacts[0]->getName().find("Rana") != std::string::npos,
            "Contact not loaded from file"
        );

        // Add more checks for other contacts as needed...
    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testLoadContactsFromFile' failed: " << e.what() << std::endl;
    }
}

void testAddContact() {
    try {
        // Create a PhoneBook
        PhoneBook phoneBook;

        // Create some PhoneRecord objects
        vector<string> phoneNumbers1 = {"1234567890", "4567891230"};
        PhoneRecord record1("John Doe", "Company A", phoneNumbers1);

        // Add a contact to the PhoneBook
        phoneBook.addContact(&record1);

        // Fetch the contact and assert its name
        vector<PhoneRecord*> fetchedContacts = phoneBook.fetchContacts(new std::string("John Doe"));
        assertWithMessage(!fetchedContacts.empty(), "Contact not found");
        assertWithMessage(fetchedContacts[0]->getName() == "John Doe", "Contact not found");
    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testAddContact' failed: " << e.what() << std::endl;
    }
}

void testDeleteContact() {
    try {
        // Create a PhoneBook
        PhoneBook phoneBook;

        // Create and add some PhoneRecord objects
        vector<string> phoneNumbers2 = {"9998887777"};
        PhoneRecord record2("Dwayne Johnson", "Company A", phoneNumbers2);
        phoneBook.addContact(&record2);

        // Delete the contact and check if it's removed
        bool deleteResult = phoneBook.deleteContact(new std::string("Dwayne Johnson"));
        assertWithMessage(deleteResult, "Contact deletion failed");

        // Try to fetch the deleted contact
        vector<PhoneRecord*> fetchedContacts = phoneBook.fetchContacts(new std::string("Dwayne Johnson"));
        assertWithMessage(fetchedContacts.empty(), "Deleted contact still exists");
    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testDeleteContact' failed: " << e.what() << std::endl;
    }
}

void testAddAndFetchContacts() {
    try {
        PhoneBook phoneBook;

        // Create and add multiple PhoneRecord objects
        vector<string> phoneNumbers1 = {"1234567890", "4567891230"};
        PhoneRecord record1("John Doe", "Company A", phoneNumbers1);
        phoneBook.addContact(&record1);

        vector<string> phoneNumbers2 = {"9998887777"};
        PhoneRecord record2("Dwayne Johnson", "Company B", phoneNumbers2);
        phoneBook.addContact(&record2);

        vector<string> phoneNumbers3 = {"5555555555"};
        PhoneRecord record3("Dwayne John", "Company A", phoneNumbers3);
        phoneBook.addContact(&record3);

        vector<string> phoneNumbers4 = {"1111222233"};
        PhoneRecord record4("Charlie Dwayne", "Company C", phoneNumbers4);
        phoneBook.addContact(&record4);

        // Fetch contacts by organization
        vector<PhoneRecord*> Contacts = phoneBook.fetchContacts(new std::string("John"));
        assertWithMessage(Contacts.size() == 2, "Incorrect number of John contacts");

        vector<PhoneRecord*> Contacts2 = phoneBook.fetchContacts(new std::string("Dwayne"));
        assertWithMessage(Contacts2.size() == 3, "Incorrect number of Dwayne contacts");

    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testAddAndFetchContacts' failed: " << e.what() << std::endl;
    }
}

void testDeleteMultipleContacts() {
    try {
        PhoneBook phoneBook;

        // Create and add multiple PhoneRecord objects
        vector<string> phoneNumbers1 = {"1234567890", "4567891230"};
        PhoneRecord record1("John Doe", "Company A", phoneNumbers1);
        phoneBook.addContact(&record1);

        vector<string> phoneNumbers2 = {"9998887777"};
        PhoneRecord record2("Dwayne Johnson", "Company A", phoneNumbers2);
        phoneBook.addContact(&record2);

        vector<string> phoneNumbers3 = {"5555555555"};
        PhoneRecord record3("Bob Smith", "Company A", phoneNumbers3);
        phoneBook.addContact(&record3);

        vector<string> phoneNumbers4 = {"1111222233"};
        PhoneRecord record4("Charlie Brown", "Company C", phoneNumbers4);
        phoneBook.addContact(&record4);


        bool deleteResult = phoneBook.deleteContact(new std::string("Brown"));
        assertWithMessage(deleteResult, "Contact deletion failed");

      
        vector<PhoneRecord*> BrownContacts = phoneBook.fetchContacts(new std::string("Brown"));
        assertWithMessage(BrownContacts.empty(), "Brown contact not deleted");

        
        vector<PhoneRecord*> BobContacts = phoneBook.fetchContacts(new std::string("Bob"));
        assertWithMessage(BobContacts.size() == 1, "Bob contact is deleted, where as it should not be deleted");
    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testDeleteMultipleContacts' failed: " << e.what() << std::endl;
    }
}

void testFetchContactsByPartialQuery() {
    try {
        PhoneBook phoneBook;

        // Create and add multiple PhoneRecord objects
        vector<string> phoneNumbers1 = {"1234567890", "4567891230"};
        PhoneRecord record1("John Doe", "Company A", phoneNumbers1);
        phoneBook.addContact(&record1);

        vector<string> phoneNumbers2 = {"9998887777"};
        PhoneRecord record2("Dwayne Johnson", "Company B", phoneNumbers2);
        phoneBook.addContact(&record2);

        vector<string> phoneNumbers3 = {"5555555555"};
        PhoneRecord record3("Bob Smith", "Company A", phoneNumbers3);
        phoneBook.addContact(&record3);

        // Fetch contacts by a partial query "John" (should match John Doe)
        vector<PhoneRecord*> johnContacts = phoneBook.fetchContacts(new std::string("John"));
        assertWithMessage(johnContacts.size() == 1, "Incorrect number of contacts for query 'John'");

    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testFetchContactsByPartialQuery' failed: " << e.what() << std::endl;
    }
}

void testSearchByMiddleName() {
    try {
        PhoneBook phoneBook;

        // Create and add multiple PhoneRecord objects
        vector<string> phoneNumbers1 = {"1234567890", "4567891230"};
        PhoneRecord record1("John Doe", "Company A", phoneNumbers1);
        phoneBook.addContact(&record1);

        vector<string> phoneNumbers2 = {"9998887777"};
        PhoneRecord record2("Dwayne Johnson", "Company B", phoneNumbers2);
        phoneBook.addContact(&record2);

        vector<string> phoneNumbers3 = {"5555555555"};
        PhoneRecord record3("Bob Smith", "Company A", phoneNumbers3);
        phoneBook.addContact(&record3);

        vector<string> phoneNumbers4 = {"1111222233"};
        PhoneRecord record4("Charlie Dwayne Brown", "Company C", phoneNumbers4); // Added middle name
        phoneBook.addContact(&record4);

        // Search for contacts using middle names
        vector<PhoneRecord*> middleNameContacts = phoneBook.fetchContacts(new std::string("Dwayne"));
        assertWithMessage(middleNameContacts.size() == 2, "Incorrect number of contacts with middle name 'Dwayne'");

    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testSearchByMiddleName' failed: " << e.what() << std::endl;
    }
}


void testObjectValues() {
    try {
        PhoneBook phoneBook;

        // Create and add a PhoneRecord object
        vector<string> phoneNumbers1 = {"1234567890", "4567891230"};
        PhoneRecord record1("John Doe", "Company A", phoneNumbers1);
        phoneBook.addContact(&record1);

        // Fetch the contact
        vector<PhoneRecord*> fetchedContacts = phoneBook.fetchContacts(new std::string("John Doe"));
        assertWithMessage(!fetchedContacts.empty(), "Contact not found");

        // Check if the fetched contact has the correct values
        PhoneRecord* fetchedRecord = fetchedContacts[0];
        assertWithMessage(fetchedRecord->getName() == "John Doe", "Incorrect name");
        assertWithMessage(fetchedRecord->getOrganisation() == "Company A", "Incorrect organization");

        vector<string> fetchedPhoneNumbers = fetchedRecord->getPhoneNumbers();
        assertWithMessage(fetchedPhoneNumbers.size() == 2, "Incorrect number of phone numbers");
        assertWithMessage(fetchedPhoneNumbers[0] == "1234567890", "Incorrect phone number");
        assertWithMessage(fetchedPhoneNumbers[1] == "4567891230", "Incorrect phone number");
    } catch (const std::exception& e) {
        failed_tests++;
        std::cout << "Unit test 'testObjectValues' failed: " << e.what() << std::endl;
    }
}

int main() {
    std::vector<void (*)()> unit_tests_list = {
        testLoadContactsFromFile,
        testAddContact,
        testDeleteContact,
        testAddAndFetchContacts,
        testDeleteMultipleContacts,
        testFetchContactsByPartialQuery,
        testObjectValues,
        testSearchByMiddleName
    };
    int total = unit_tests_list.size();

    for (int i = 0; i < total; ++i) {
        try {
            unit_tests_list[i]();
        } catch (const std::exception& e) {
            failed_tests++;
            std::cout << "Unit test #" << i + 1 << " failure: " << e.what() << std::endl;
        }
    }

    if (failed_tests == 0) {
        std::cout << "All tests have passed successfully!" << std::endl;
    } else {
        std::cout << failed_tests << " tests failed!" << std::endl;
    }

    std::cout << "Number of failed test cases are: " << failed_tests << std::endl;
    return 0;
}
