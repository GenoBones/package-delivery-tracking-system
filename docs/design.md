# Package Delivery Tracking System — Design

## Package Record

Each package will be stored using a `Package` struct.

Each package will contain:

- `trackingNumber`
- `recipient`
- `destination`
- `weight`
- `status`

New packages will start with the status `Waiting`.

## Package Collection

The main package collection will use:

`vector<Package> packages`

The vector will store the actual package records. The original vector will not be reordered because the queue and hash table will use its indexes to locate packages.

## Processing Queue

The processing queue will use:

`queue<int> processingQueue`

The queue will store the vector index of each package that is waiting to be processed.

A queue makes sense here because packages need to be processed in FIFO order. The package that has been waiting the longest will be processed first. This also means we do not need something like a `dateCreated` just to determine processing order.

When a package is processed, its index will be removed from the front of the queue and its status will change from `Waiting` to `Processed`.

## Hash Table

The hash table will use:

`unordered_map<string, int> trackingLookup`

The tracking number will be the key and the package's vector index will be the value.

For example:

`trackingLookup["ABC123"] = 0`

means package `ABC123` can be found at index `0` in the packages vector.

This gives us a fast way to look up a package without searching through the entire vector.

## Preventing Duplicate Tracking Numbers

Before adding a package, the program will check whether the tracking number already exists in `trackingLookup`.

If it already exists, the package will not be added.

## Keeping the Data Structures Consistent

The `packages` vector will contain the actual package records.

The processing queue will contain indexes for packages that are waiting.

The hash table will connect each tracking number to its index in the vector.

The original vector will not be sorted or rearranged. Sorted reports will use a copy so the indexes stored in the queue and hash table do not change.

When a package status changes, the package in the vector will be updated.

## Major Functions

The program will use the following primary functions:

- `addPackage()` — validate and add a package.
- `processNextPackage()` — process the package at the front of the queue.
- `findPackage()` — find a package using the hash table.
- `linearSearch()` — search through the vector for a tracking number.
- `updatePackageStatus()` — update a package to a valid status.
- `displayWaitingPackages()` — display the waiting queue without changing it.
- `displayAllPackages()` — display all packages.
- `displaySortedReport()` — display a sorted copy of the package collection.
- `displaySystemSummary()` — display totals and weight information.

Additional small helper functions will also be used.

## Searching Strategy

The normal tracking-number lookup will use the hash table because `unordered_map` provides efficient lookup using the tracking number as the key.

As required by the assignment, I will also create a linear-search function that checks the vector from beginning to end. This will allow the two search methods to be compared.

## Sorting and Reporting Strategy

Sorted reports will use a copy of the `packages` vector so the original collection does not change.

The program will allow packages to be sorted by at least tracking number and weight.

Insertion sort will be used for one of the required sorting options. Its worst-case complexity is `O(N^2)`.

## Why These Data Structures Are Appropriate

The vector works well for the main collection because it keeps all of the package records together and lets us access a package by its index.

The queue works well for waiting packages because FIFO processes packages in the order they were added.

The unordered map works well for tracking-number lookup because tracking numbers are unique keys and hash-table lookup is `O(1)` on average.

Most importantly of all, these are the data structures I feel most confident using and can conceptually wrap my head around without having to extensively rely on documentation, examples, or AI explanations.