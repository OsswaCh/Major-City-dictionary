#pragma once
#include "BTS.h"
#include <math.h>
#include <regex>
#include <fstream>
#include <sstream>
#include <string>
#define _USE_MATH_DEFINES
#define R 6371.137


class dic : public BTS
{
private: 
	
	struct coord {
		int deg;
		int min;
		char dir;
	};

	double convertToRadian(int);
	//std::string transformString(const std::string& );
	


public: 

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

	std::string transformString(const std::string& input) {

		std::regex degree_minute_regex("[°′]+");

		// Use regex_replace to replace degree and minute symbols with a hyphen (-)
		std::string transformedString = std::regex_replace(input, degree_minute_regex, "-");

		transformedString = std::regex_replace(transformedString, std::regex("-+"), "-");

		return transformedString;
	}


	//save into a file
	void saveInFile(dic*);

	//initial run
	dic* generate_from_file(std::string, node*&);

	//Cumulative Run
	dic* CumulativeRun(std::string , node*& );

	//query run
	void queryRun(dic*,node*);

	
	double computeDistance(node*, node*);

	void getCoordinates(node*, double& , double& );

};

