# Package Delivery Tracking System — Pseudocode

## Main Program

Create package vector

Create processing queue

Create tracking number hash table

Set menu choice to 0

While choice is not 9:

    Display menu

    Get choice from user

    If choice is 1:
        Add package

    Else if choice is 2:
        Process next package

    Else if choice is 3:
        Find package by tracking number

    Else if choice is 4:
        Update package status

    Else if choice is 5:
        Display waiting packages

    Else if choice is 6:
        Display all packages

    Else if choice is 7:
        Display sorted package report

    Else if choice is 8:
        Display system summary

    Else if choice is 9:
        Exit program

    Otherwise:
        Display invalid choice message


## Add Package

Ask user for tracking number

If tracking number is empty:
    Reject package
    Return to menu

Check tracking number in hash table

If tracking number already exists:
    Reject package as duplicate
    Return to menu

Ask user for recipient

If recipient is empty:
    Reject package
    Return to menu

Ask user for destination

If destination is empty:
    Reject package
    Return to menu

Ask user for weight

If weight is less than or equal to 0:
    Reject package
    Return to menu

Create new package

Set package status to Waiting

Add package to end of package vector

Get the new package's vector index

Add the index to the processing queue

Add tracking number and vector index to the hash table

Display confirmation that package was added


## Duplicate Tracking Number Check

Search the hash table using the entered tracking number

If the tracking number is found:
    Tracking number is already being used

Otherwise:
    Tracking number can be used


## Process Next Package

If processing queue is empty:
    Display message that there are no waiting packages
    Return to menu

Get the package index from the front of the queue

Remove the front index from the queue

Use the index to find the package in the package vector

Change status from Waiting to Processed

Display the processed package information


## Hash Table Lookup

Ask user for tracking number

Search tracking hash table using tracking number as the key

If tracking number is found:
    Get the package's vector index
    Use index to access the package in the vector
    Display package information

Otherwise:
    Display package not found message


## Linear Search

Get tracking number to search for

For each package in the package vector:

    Compare package tracking number to requested tracking number

    If they match:
        Return the package index

If the entire vector has been searched without a match:
    Return -1


## Update Package Status

Ask user for tracking number

Look up tracking number in the hash table

If package is not found:
    Display package not found message
    Return to menu

Use the stored index to access the package

If current status is Waiting:
    Reject manual status update
    Package must be processed through Process Next Package

Else if current status is Processed:
    Change status to In Transit

Else if current status is In Transit:
    Change status to Delivered

Else if current status is Delivered:
    Display message that package is already delivered


## Display Waiting Packages

If processing queue is empty:
    Display message that there are no waiting packages
    Return to menu

Make a copy of the processing queue

While copied queue is not empty:

    Get index from front of copied queue

    Use index to access package in vector

    Display package information

    Remove index from copied queue

Leave the original processing queue unchanged


## Display All Packages

If package vector is empty:
    Display message that there are no packages
    Return to menu

For each package in the package vector:
    Display package information


## Display Sorted Package Report

If package vector is empty:
    Display message that there are no packages
    Return to menu

Ask user which field they want to sort by

Create a copy of the package vector

If user selects tracking number:
    Sort the copied vector by tracking number

Else if user selects weight:
    Sort the copied vector by weight using insertion sort

Otherwise:
    Display invalid choice message

Display packages from sorted copy

Do not change the original package vector


## Insertion Sort by Weight

Start with the second package in the copied vector

For each package:

    Save the current package

    Compare its weight to packages before it

    While previous package has a greater weight:
        Move previous package one position to the right

    Insert saved package into the correct position

Continue until all packages are sorted


## Display System Summary

If package vector is empty:
    Display zero packages
    Display zero total weight
    Display zero average weight
    Return to menu

Set waiting count to 0

Set processed count to 0

Set in-transit count to 0

Set delivered count to 0

Set total weight to 0

Set heaviest package to first package

For each package in package vector:

    Add package weight to total weight

    If package status is Waiting:
        Increase waiting count

    Else if package status is Processed:
        Increase processed count

    Else if package status is In Transit:
        Increase in-transit count

    Else if package status is Delivered:
        Increase delivered count

    If package weight is greater than current heaviest package:
        Set heaviest package to current package

Calculate average weight:
    total weight divided by number of packages

Display:
    Total packages
    Waiting packages
    Processed packages
    In-transit packages
    Delivered packages
    Total weight
    Average weight
    Heaviest package