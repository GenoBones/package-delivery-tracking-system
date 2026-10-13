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
}

int main()
{
    //creates a vector of packages, a queue for processing, and an unordered map for tracking lookup
    vector<Package> packages;
    queue<int> processingQueue;
    unordered_map<string, int> trackingLookup;

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
            cout << "Process Next Package selected." << endl;
            break;

        case 3:
            cout << "Find Package by Tracking Number selected." << endl;
            break;

        case 4:
            cout << "Update Package Status selected." << endl;
            break;

        case 5:
            cout << "Display Waiting Packages selected." << endl;
            break;

        case 6:
            cout << "Display All Packages selected." << endl;
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

