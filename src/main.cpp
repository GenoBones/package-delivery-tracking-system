#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

struct Package
{
    string trackingNumber;
    string recipient;
    string destination;
    double weight;
    string status;
};

// Function to load test packages into the system (below main)
void loadTestPackages(vector<Package>& packages,
                      queue<int>& processingQueue,
                      unordered_map<string, int>& trackingLookup);

/*
||||||||||||||||||||||||||||||||||||||
 
         HELPER FUNCTIONS

||||||||||||||||||||||||||||||||||||||
*/

// Qol function to pause the program until the user presses Enter
void pressEnterToContinue(bool clearLeftoverNewline = false)
{
    string input;

    if (clearLeftoverNewline)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << endl;
    cout << "Press Enter to continue...";
    getline(cin, input);
}

bool trackingNumberIsValid(const string& trackingNumber)
{
    if (trackingNumber.length() < 4 || trackingNumber.length() > 20)
    {
        return false;
    }

    if (trackingNumber.find(' ') != string::npos)
    {
        return false;
    }

    return true;
}

// Function to print error messages in red
void printError(const string& message)
{
    cout << endl;
    cout << "\033[31m" << message << "\033[0m" << endl;
    cout << endl;
}


/*
||||||||||||||||||||||||||||||||||||||
 
             ADD PACKAGE

||||||||||||||||||||||||||||||||||||||
*/
void addPackage(vector<Package>& packages,
                queue<int>& processingQueue,
                unordered_map<string, int>& trackingLookup)
{
    Package newPackage;

    cout << "--- ADD NEW PACKAGE ---" << endl;

    // Clears the leftover newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true)
    {
        cout << "Tracking number: ";
        getline(cin, newPackage.trackingNumber);

        if (newPackage.trackingNumber.empty())
        {
            printError("Tracking number cannot be empty. Please enter a valid tracking number.");
        }

        // Accounts for the case where the tracking number is just spaces or too short/long
        else if (!trackingNumberIsValid(newPackage.trackingNumber))
        {
            printError("Invalid tracking number. Please enter a valid tracking number.");
        }
        else if (trackingLookup.count(newPackage.trackingNumber) > 0)
        {
            printError("That tracking number is already in use. Please enter a different tracking number.");
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Recipient: ";
        getline(cin, newPackage.recipient);

        if (newPackage.recipient.empty())
        {
            printError("Recipient cannot be empty. Please enter a valid recipient.");
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Destination: ";
        getline(cin, newPackage.destination);

        if (newPackage.destination.empty())
        {
            printError("Destination cannot be empty. Please enter a valid destination.");
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Weight (lbs): ";
        cin >> newPackage.weight;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // This was added after I tried typing "yo momma" for weight and it crashed the program. This is a better way to handle that case.
            printError("Weight must be a number. Please enter a valid weight (lbs).");
        }
        else if (newPackage.weight <= 0)
        {
            printError("Weight must be greater than 0. Please enter a valid weight (lbs).");
        }
        else
        {
            break;
        }
    }

    newPackage.status = "Waiting";

    // Add the new package to end of the packages vector
    packages.push_back(newPackage);

    // New index is the last index in the packages vector, which is the index of the newly added package
    int newIndex = packages.size() - 1;

    // Add the new index to the processing queue
    processingQueue.push(newIndex);

    // Tracking number is the key, and the index of the package is the value
    trackingLookup[newPackage.trackingNumber] = newIndex;

    cout << endl;
    cout << "Package " << newPackage.trackingNumber
         << " added successfully." << endl;
    cout << "Current status: " << newPackage.status << endl;

    pressEnterToContinue(true);
}

/*
||||||||||||||||||||||||||||||||||||||
 
        PROCESS NEXT PACKAGE

||||||||||||||||||||||||||||||||||||||
*/

void processNextPackage(vector<Package>& packages,
                        queue<int>& processingQueue)
{
    cout << "--- PROCESS NEXT PACKAGE ---" << endl;

    if (processingQueue.empty())
    {
        printError("There are no packages waiting to be processed.");
        pressEnterToContinue(true);
        return;
    }

    int packageIndex = processingQueue.front();

    processingQueue.pop();

    packages[packageIndex].status = "Processed";

    cout << endl;
    cout << "Package " << packages[packageIndex].trackingNumber
         << " processed successfully." << endl;
    cout << "Recipient: " << packages[packageIndex].recipient << endl;
    cout << "Destination: " << packages[packageIndex].destination << endl;
    cout << "Weight: " << packages[packageIndex].weight << " lbs" << endl;
    cout << "Current status: " << packages[packageIndex].status << endl;

    pressEnterToContinue(true);
}

/*
||||||||||||||||||||||||||||||||||||||
 
      FIND PACKAGE HASH SEARCH

||||||||||||||||||||||||||||||||||||||
*/
void findPackage(const vector<Package>& packages,
                 const unordered_map<string, int>& trackingLookup)
{
    string trackingNumber;

    cout << "--- FIND PACKAGE ---" << endl;

    // Clears the leftover newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // More validation - may be worth making a helper if time allows.
    while (true)
    {
        cout << "Enter tracking number: ";
        getline(cin, trackingNumber);

        if (trackingNumber.empty())
        {
            printError("Tracking number cannot be empty. Please enter a valid tracking number.");
        }
        else if (!trackingNumberIsValid(trackingNumber))
        {
            printError("Invalid tracking number. Please enter a valid tracking number.");
        }
        else
        {
            break;
        }
    }

    if (trackingLookup.count(trackingNumber) == 0)
    {
        printError("Package not found. Please check the tracking number.");
        pressEnterToContinue();
        return;
    }

    int packageIndex = trackingLookup.at(trackingNumber);

    cout << endl;
    cout << "Tracking number: " << packages[packageIndex].trackingNumber << endl;
    cout << "Recipient: " << packages[packageIndex].recipient << endl;
    cout << "Destination: " << packages[packageIndex].destination << endl;
    cout << "Weight: " << packages[packageIndex].weight << " lbs" << endl;
    cout << "Status: " << packages[packageIndex].status << endl;

    pressEnterToContinue();
}

/*
||||||||||||||||||||||||||||||||||||

      FIND PACKAGE LINEAR SEARCH

||||||||||||||||||||||||||||||||||||
*/
int linearSearch(const vector<Package>& packages,
                 const string& trackingNumber)
{
    for (int i = 0; i < packages.size(); i++)
    {
        if (packages[i].trackingNumber == trackingNumber)
        {
            return i;
        }
    }

    return -1;
}

/*
||||||||||||||||||||||||||||||||||||||
 
       UPDATE PACKAGE STATUS

||||||||||||||||||||||||||||||||||||||
*/
void updatePackageStatus(vector<Package>& packages,
                         const unordered_map<string, int>& trackingLookup)
{
    string trackingNumber;

    cout << "--- UPDATE PACKAGE STATUS ---" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true)
    {
        cout << "Enter tracking number: ";
        getline(cin, trackingNumber);

        if (trackingNumber.empty())
        {
            printError("Tracking number cannot be empty. Please enter a valid tracking number.");
        }
        else if (!trackingNumberIsValid(trackingNumber))
        {
            printError("Invalid tracking number. Please enter a valid tracking number.");
        }
        else
        {
            break;
        }
    }

    if (trackingLookup.count(trackingNumber) == 0)
    {
        printError("Package not found. Please check the tracking number.");
        pressEnterToContinue();
        return;
    }

    int packageIndex = trackingLookup.at(trackingNumber);

    if (packages[packageIndex].status == "Waiting")
    {
        printError("Package is still waiting. Use Process Next Package before updating its status.");
        pressEnterToContinue();
        return;
    }
    else if (packages[packageIndex].status == "Processed")
    {
        packages[packageIndex].status = "In Transit";
    }
    else if (packages[packageIndex].status == "In Transit")
    {
        packages[packageIndex].status = "Delivered";
    }
    else if (packages[packageIndex].status == "Delivered")
    {
        printError("Package has already been delivered.");
        pressEnterToContinue();
        return;
    }

    cout << endl;
    cout << "Package " << packages[packageIndex].trackingNumber
         << " status updated successfully." << endl;
    cout << "Current status: " << packages[packageIndex].status << endl;

    pressEnterToContinue();
}

/*
||||||||||||||||||||||||||||||||||||||
 
      DISPLAY WAITING PACKAGES

||||||||||||||||||||||||||||||||||||||
*/

void displayWaitingPackages(const vector<Package>& packages,
                            const queue<int>& processingQueue)
{
    cout << "--- WAITING PACKAGES ---" << endl;

    if (processingQueue.empty())
    {
        printError("There are no packages waiting to be processed.");
        pressEnterToContinue(true);
        return;
    }

    queue<int> waitingQueue = processingQueue;

    int packageNumber = 1;

    while (!waitingQueue.empty())
    {
        int packageIndex = waitingQueue.front();

        cout << endl;
        cout << "Package " << packageNumber << endl;
        cout << "Tracking number: " << packages[packageIndex].trackingNumber << endl;
        cout << "Recipient: " << packages[packageIndex].recipient << endl;
        cout << "Destination: " << packages[packageIndex].destination << endl;
        cout << "Weight: " << packages[packageIndex].weight << " lbs" << endl;
        cout << "Status: " << packages[packageIndex].status << endl;

        waitingQueue.pop();
        packageNumber++;
    }

    pressEnterToContinue(true);
}

/*
||||||||||||||||||||||||||||||||||||||
 
       DISPLAY ALL PACKAGES

||||||||||||||||||||||||||||||||||||||
*/

void displayAllPackages(const vector<Package>& packages)
{
    cout << "--- ALL PACKAGES ---" << endl;

    if (packages.empty())
    {
        printError("There are no packages in the system.");
        pressEnterToContinue(true);
        return;
    }

    for (int i = 0; i < packages.size(); i++)
    {
        cout << endl;
        cout << "Package " << i + 1 << endl;
        cout << "Tracking number: " << packages[i].trackingNumber << endl;
        cout << "Recipient: " << packages[i].recipient << endl;
        cout << "Destination: " << packages[i].destination << endl;
        cout << "Weight: " << packages[i].weight << " lbs" << endl;
        cout << "Status: " << packages[i].status << endl;
    }
    pressEnterToContinue(true);
}

/*
||||||||||||||||||||||||||||||||||||||
 
                MAIN

||||||||||||||||||||||||||||||||||||||
*/
int main()
{
    //creates a vector of packages, a queue for processing, and an unordered map for tracking lookup
    vector<Package> packages;
    queue<int> processingQueue;
    unordered_map<string, int> trackingLookup;

    loadTestPackages(packages, processingQueue, trackingLookup);

    int choice = 0;

    while (choice != 9)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << " PACKAGE DELIVERY TRACKING SYSTEM (PDTS)" << endl;
        cout << "========================================" << endl;
        cout << "Packages in system: " << packages.size() << endl;
        cout << "Waiting to process: " << processingQueue.size() << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Add Package" << endl;
        cout << "2. Process Next Package" << endl;
        cout << "3. Find Package by Tracking Number" << endl;
        cout << "4. Update Package Status" << endl;
        cout << "5. Display Waiting Packages" << endl;
        cout << "6. Display All Packages" << endl;
        cout << "7. Display Sorted Package Report" << endl;
        cout << "8. Display System Summary" << endl;
        cout << "9. Exit" << endl;
        cout << "----------------------------------------" << endl;

        cout << "Selection -> ";
        cin >> choice;

        cout << endl;

        switch (choice)
        {
        case 1:
            addPackage(packages, processingQueue, trackingLookup);
            break;

        case 2:
            processNextPackage(packages, processingQueue);
            break;

        case 3:
            findPackage(packages, trackingLookup);
            break;

        case 4:
            updatePackageStatus(packages, trackingLookup);
            break;

        case 5:
            displayWaitingPackages(packages, processingQueue);
            break;

        case 6:
            displayAllPackages(packages);
            break;

        case 7:
            cout << "Display Sorted Package Report selected." << endl;
            break;

        case 8:
            cout << "Display System Summary selected." << endl;
            break;

        case 9:
            cout << "Closing PDTS..." << endl;
            break;

        default:
            cout << "That isn't a valid menu option. Enter 1 through 9." << endl;
        }
    }

    return 0;
}

/*
||||||||||||||||||||||||||||||||||||||
 
            TEST DATA

||||||||||||||||||||||||||||||||||||||
*/
void loadTestPackages(vector<Package>& packages,
                      queue<int>& processingQueue,
                      unordered_map<string, int>& trackingLookup)
{
    Package package1;
    package1.trackingNumber = "PDTS1001";
    package1.recipient = "John Smith";
    package1.destination = "Sacramento, CA";
    package1.weight = 12.5;
    package1.status = "Waiting";

    packages.push_back(package1);
    processingQueue.push(0);
    trackingLookup[package1.trackingNumber] = 0;


    Package package2;
    package2.trackingNumber = "PDTS1002";
    package2.recipient = "Maria Lopez";
    package2.destination = "San Francisco, CA";
    package2.weight = 7.25;
    package2.status = "Waiting";

    packages.push_back(package2);
    processingQueue.push(1);
    trackingLookup[package2.trackingNumber] = 1;


    Package package3;
    package3.trackingNumber = "PDTS1003";
    package3.recipient = "Tony Russo";
    package3.destination = "Los Angeles, CA";
    package3.weight = 22.8;
    package3.status = "Waiting";

    packages.push_back(package3);
    processingQueue.push(2);
    trackingLookup[package3.trackingNumber] = 2;


    Package package4;
    package4.trackingNumber = "PDTS1004";
    package4.recipient = "Sarah Johnson";
    package4.destination = "Reno, NV";
    package4.weight = 4.75;
    package4.status = "Waiting";

    packages.push_back(package4);
    processingQueue.push(3);
    trackingLookup[package4.trackingNumber] = 3;
}