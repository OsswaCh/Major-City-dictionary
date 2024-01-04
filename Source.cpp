#include <iostream>
#include <fstream>
#include <fstream>
#include<string>
#include <cmath>
#include "node.h"
#include "BTS.h"
#include "dic.h"
using namespace std;


std::string transformString(const std::string& input) {

    std::regex degree_minute_regex("[Â°â€²]+");

    // Use regex_replace to replace degree and minute symbols with a hyphen (-)
    std::string transformedString = std::regex_replace(input, degree_minute_regex, "-");

    transformedString = std::regex_replace(transformedString, std::regex("-+"), "-");

    return transformedString;
}

std::string cityValid(const std::string& input) {
    std::regex pattern("[A-Za-z\\s]+");
    std::smatch match;
    std::string result = "";

    // Use std::regex_iterator to find and append matches to the result string
    for (std::sregex_iterator it(input.begin(), input.end(), pattern); it != std::sregex_iterator(); ++it) {
        result += it->str() + " ";
    }

    return result;
}


int main() {
    

    
    std::string filename = "MCity List.csv"; // Replace with the actual filename

    dic* citydic = new dic;
    dic* citydic2 = new dic;


    node* myroot = new node;
    node* myroot2 = new node;

    //this is for the initial run; you can comment it if you are not in need of it
    citydic = citydic->generate_from_file(filename, myroot);

    

    //this tests out the generated tree:

    std::cout << "In order traveral of the tree: " << std::endl;
    citydic->inOrderTraversal(myroot);

    std::cout<<std::endl << std::endl;

    std::cout << "In order traveral of the tree: " << std::endl;
    citydic->preOrdertraversal(myroot);

    std::cout << std::endl << std::endl;

    //this function is to save the tree, however you do not need to specifically call it as it is already imprelemented in teh implimentation functions
    citydic->saveInFile(citydic);
    

    //this lets you test the cummulative run where you can load a tree, modify it and save it again
    citydic2 = citydic2->CumulativeRun("output.csv", myroot2);


    //this is the query run, you might encounter some problems and it is because of the following
    //all function used in it are independantly functional
    //however I am experiencing an unexplanable problem with the search function
    //the implimentation is correct but for some reason it does not work as intended
    //the other functions might rely on it 
    citydic->queryRun(citydic, myroot);
    

    //this is an example that might show you how the compute distance works

    std::cout << "this is an exmaple that shows how the computation of distance work!"<<std::endl<<"here is the distance between the root node and the one to its left";
    double dis = citydic->computeDistance(myroot, myroot->left);
    std::cout << dis;

    return 0;
}


