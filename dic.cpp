#include <iostream>
#include "dic.h"
#include <math.h>
#include<fstream>
#define _USE_MATH_DEFINES
#define R 6371.137





// different runs

//initial run
dic* dic::generate_from_file(std::string filename,node*& myroot) {

    std::ifstream inFile;

    std::string city;
    std::string country;
    std::string lat;
    std::string lon;
    inFile.open(filename);
    if (inFile.is_open()) {
        std::cout << "File has been opened" << std::endl;
    }
    else {
        std::cout << "NO FILE HAS BEEN OPENED" << std::endl;
    }

    if (!inFile.eof()) {
        getline(inFile, city, ',');
        getline(inFile, lat, ',');
        getline(inFile, lon, ',');
        inFile >> country;
        
        lat = transformString(lat);
        lon = transformString(lon);

        city = cityValid(city);
        country = cityValid(country);
        dic* citydic = new dic;

        myroot->changeCityName(city);
        myroot->changeCountry(country);
        myroot->changeLatitude(lat);
        myroot->changeLongitude(lon);

        //node* myroot = new node(city, lat, lon, country);



        citydic->setRoot(myroot);

        while (!inFile.eof()) {

            //extracting from the file

            getline(inFile, city, ',');
            getline(inFile, lat, ',');
            getline(inFile, lon, ',');
            inFile >> country;

            //because when reading from the file some characters are imported weirdly
            //the following fnctions are made to fix them to a usable format
            lat = transformString(lat);
            lon = transformString(lon);
            country = cityValid(country);
            //inserting into the tree
            citydic->insertNew(myroot, city, lat, lon, country);

        }

        saveInFile(citydic);
        return citydic;
    }
    

}

//Cumulative Run
dic* dic::CumulativeRun(std::string filename, node*& myroot) {
    std::ifstream inFile;
    inFile.open(filename);

    if (inFile.is_open()) {
        std::cout << "File has been opened" << std::endl;
    }
    else {
        std::cout << "NO FILE HAS BEEN OPENED" << std::endl;
    }

    dic* citydic = new dic;

    // Check if the file is empty
    if (inFile.peek() == std::ifstream::traits_type::eof()) {
        // File is empty, no previous dictionary to load
        std::cerr << "No previous dictionary found." << std::endl;
        return citydic;
    }

    std::string city;
    std::string country;
    std::string lat;
    std::string lon;

    while (!inFile.eof()) {
        // Extract data from the file
        getline(inFile, city, ',');
        getline(inFile, lat, ',');
        getline(inFile, lon, ',');
        inFile >> country;

        // Process and validate data
        city = cityValid(city);
        country = cityValid(country);
        lat = transformString(lat);
        lon = transformString(lon);

        // Insert into the tree
        citydic->insertNew(myroot, city, lat, lon, country);


    }
    //user input
    std::string userInput;
    std::cout << "Do you want to enter a new element (yes/no)? ";
    std::cin >> userInput;

    while (userInput == "yes" || userInput == "Yes" || userInput == "YES") {
        std::string newCity, newLat, newLon, newCountry;
        // Prompt the user for input and validate it if necessary
        std::cout << "Enter new city: ";
        std::cin >> newCity;
        std::cout << "Enter latitude: ";
        std::cin >> newLat;
        std::cout << "Enter longitude: ";
        std::cin >> newLon;
        std::cout << "Enter country: ";
        std::cin >> newCountry;

        // Process and validate the user's input
        newCity = cityValid(newCity);
        newCountry = cityValid(newCountry);
        newLat = transformString(newLat);
        newLon = transformString(newLon);

        // Insert the new data into the tree
        citydic->insertNew(myroot, newCity, newLat, newLon, newCountry);
        std::cout << "Do you want to enter a new element (yes/no)? ";
        std::cin >> userInput;
    }

    inFile.close();
    saveInFile(citydic);
    return citydic;



}


//query run
void dic::queryRun(dic* cityDictionary, node* myroot) {
    bool continueMenu = true;

    while (continueMenu) {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Search for a city" << std::endl;
        std::cout << "2. Calculate distance between two cities" << std::endl;
        std::cout << "3. List all elements" << std::endl;
        std::cout << "4. Exit" << std::endl;

        int choice;
        std::cin >> choice;

        // Clear the error flags and input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            // Search for a city
            std::string cityName;
            std::cout << "Enter the name of the city: ";
            std::getline(std::cin, cityName);

            // Perform the search operation
            node* result = cityDictionary->search(myroot, cityName);
            if (result) {
                std::cout << "City found: " << result->getName() << std::endl;
                // You can display other information here
            }
            else {
                std::cout << "City not found." << std::endl;
            }
            break;
        }
        case 2: {
            std::string city1, city2;
            std::cout << "Enter the names of the two cities (separated by a space): ";
            std::cin >> city1 >> city2;

            // Use the search function to find the nodes for comparison
            node* node1 = cityDictionary->search(myroot, city1);
            node* node2 = cityDictionary->search(myroot, city2);

            if (node1 && node2) {
                // Perform the distance calculation
                double distance = cityDictionary->computeDistance(node1, node2);
                if (distance >= 0) {
                    std::cout << "Distance between " << city1 << " and " << city2 << ": " << distance << " kilometers" << std::endl;
                }
                else {
                    std::cout << "Distance calculation failed." << std::endl;
                }
            }
            else {
                std::cout << "One or both cities not found." << std::endl;
            }

            break;
        }
        case 3:
            std::cout << "List of all elements:" << std::endl;
            cityDictionary->inOrderTraversal(myroot);
            break;
        case 4:
            // Exit the program
            continueMenu = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}



double dic:: convertToRadian(int val) {

	return val * M_PI / 180.0;
}

double dic::computeDistance(node* n1, node* n2) {

    double latitude1; double latitude2; double longitude1; double longitude2;
 
    getCoordinates(n1, latitude1, longitude1);
    getCoordinates(n2, latitude2, longitude2);

	double a = pow(sin((latitude2 - latitude1) / 2), 2) + cos(latitude1) * cos(latitude2) * pow(sin(longitude2 - longitude1) / 2, 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return R * c;

}

void dic::getCoordinates(node* n, double& lat, double& lon) {
    
    
    std::string latInput = n->getLatitude();
    std::string lonInput = n->getLongitude();

    double deg; double min; std::string dir;
    std::string sDeg; std::string sMin; 

    std::istringstream inputLat(latInput);
    std::getline(inputLat, sDeg, '-');
    std::getline(inputLat, sMin, '-');
    std::getline(inputLat, dir, '-');

    lat= convertToRadian(stoi(sDeg) + stoi(sMin) / 60.0);
    if (dir == "S")
        lat = -lat;
    

    std::istringstream inputLat2(latInput);
    std::getline(inputLat2, sDeg, '-');
    std::getline(inputLat2, sMin, '-');
    std::getline(inputLat2, dir, '-');

    lon = convertToRadian(stoi(sDeg) + stoi(sMin) / 60.0);
    if (dir == "W")
        lon = -lon;


}

void dic::saveInFile(dic* dict) {
    std::ofstream outFile("output.csv");
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the output file." << std::endl;
        return;
    }

    // Perform pre-order traversal and save the BST to the file
    node* myroot = dict->getRoot();
    dict->preOrdertraversalSave(myroot, outFile);

    // Close the output file
    outFile.close();
}
