#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct Package
{
    string trackingNumber;
    string recipient;
    string destination;
    double weight;
    string status;
};

int main()
{
    vector<Package> packages;
    queue<int> processingQueue;
    unordered_map<string, int> trackingLookup;

    int choice = 0;

    while (choice != 9)
    {
        cout << endl;
        cout << "PACKAGE DELIVERY TRACKING SYSTEM" << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Add Package" << endl;
        cout << "2. Process Next Package" << endl;
        cout << "3. Find Package by Tracking Number" << endl;
        cout << "4. Update Package Status" << endl;
        cout << "5. Display Waiting Packages" << endl;
        cout << "6. Display All Packages" << endl;
        cout << "7. Display Sorted Package Report" << endl;
        cout << "8. Display System Summary" << endl;
        cout << "9. Exit" << endl;
        cout << endl;

        cout << "Enter choice: ";
        cin >> choice;

        cout << endl;

        switch (choice)
        {
        case 1:
            cout << "Add Package selected." << endl;
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
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number from 1 to 9." << endl;
        }
    }

    return 0;
}