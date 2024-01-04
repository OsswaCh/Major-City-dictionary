# City Dictionary and Tree Implementation

This C++ code implements a city dictionary using a Binary Search Tree (BST) data structure. It reads city data from a CSV file, creates a BST of cities, performs various operations like traversal, search, modification, and computes distances between cities based on latitude and longitude coordinates.

## Prerequisites
- C++ compiler
- Standard Template Library (STL)

## File Structure
- `node.h`: Header file containing the structure of a node in the BST.
- `BTS.h`: Header file containing the definition of the Binary Search Tree class.
- `dic.h`: Header file containing the dictionary class with various functionalities.
- `main.cpp`: Main C++ file with implementation and demonstration of functionalities.

## Functionality Overview
- `transformString`: Method to transform strings by replacing degree and minute symbols with a hyphen.
- `cityValid`: Method to validate city names by removing non-alphabetic characters.
- `generate_from_file`: Reads city data from a CSV file and generates a BST.
- `inOrderTraversal`, `preOrderTraversal`: Traverses the BST in-order and pre-order respectively.
- `saveInFile`: Saves the BST structure in a file.
- `CumulativeRun`: Loads a tree, allows modifications, and saves it back.
- `queryRun`: Function to perform queries on the BST (currently experiencing issues with search function).
- `computeDistance`: Computes the distance between two cities using their coordinates.

## Usage
1. Modify `MCity List.csv` with the desired city data in the required format.
2. Compile the code using a C++ compiler: `g++ main.cpp -o city_dictionary`.
3. Run the executable: `./city_dictionary`.

Note: Certain functionalities might require adjustments or debugging, especially the `queryRun` due to search issues.

## Additional Notes
- The code contains comments and instructions for various operations and functionalities.
- Some functions might require additional testing and debugging for optimal performance.
- Feel free to modify and adapt the code according to your specific requirements.
