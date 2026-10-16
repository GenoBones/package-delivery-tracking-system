# Package Delivery Tracking System — Analysis

## Linear Search

The linear search checks each package in the vector until the tracking number is found.

Worst case: O(N)

This is because the package could be at the end of the vector or not exist at all, meaning every package has to be checked.


## Hash Table Lookup

The normal Find Package option uses the unordered_map.

The tracking number is the key and the package's vector index is the value.

Average lookup: O(1)

Worst case: O(N)

The average lookup is much faster than linear search, but collisions can make the worst case slower.


## Processing Queue

The processing queue uses FIFO, so the first package added is the first package processed.

Adding to the queue with push(): O(1)

Removing from the queue with pop(): O(1)

Displaying all waiting packages is O(N) because each package in the copied queue has to be visited once.


## Insertion Sort

I used insertion sort for the sorted package report.

The report can sort by:

- Tracking number
- Weight

Average and worst case: O(N^2)

Best case: O(N)

Insertion sort checks the packages before the current package and shifts them until the package is in the correct position.


## Sorting a Copy

The sorted report creates a copy of the package vector before sorting it.

`vector<Package> sortedPackages = packages`

This is important because the queue and hash table store indexes that point to the original vector.

If I sorted the original vector, those indexes could point to the wrong packages.


## System Summary

The system summary loops through the package vector once.

It counts each status, adds the total weight, calculates the average, and finds the heaviest package.

Time complexity: O(N)

The program checks for an empty vector first so it does not divide by zero when calculating the average.


## Data Structure Choices

The vector stores the actual package records.

The queue keeps the packages in FIFO processing order.

The unordered map gives faster tracking-number lookup.

Each structure has a separate purpose and works with the others through the package's vector index.