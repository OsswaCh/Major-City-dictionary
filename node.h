#pragma once
#include <iostream>
#include <string>
class node
{
private:

    //node components
    std::string cityName;
    std::string latitude;
    std::string longitude;
    std::string country;

    

public: 
	
    //left and right pointer
    node* left;
    node* right;


    node(std::string cityName, std::string latitude, std::string longitude, std::string country) : cityName(cityName), latitude(latitude), longitude(longitude), country(country), left(nullptr), right(nullptr) {}
    node() : cityName(""), latitude(""), longitude(""), country(""), left(nullptr), right(nullptr) {}


    void setLeft(node* ptr) {
        left = ptr;
    }

    void setRight(node* ptr) {
        right = ptr;
    }

    void changeCityName(std::string Name) {
        cityName = Name;
    }

    void changeLatitude(std::string lat) {
        latitude = lat;
    }

    void changeLongitude(std::string lat) {
        longitude = lat;
    }

    void changeCountry(std::string Name) {
        country = Name;
    }

    std::string getName() {
        return cityName;
    }

    std::string getCountry() {
        return country;
    }

    std::string getLongitude() {
        return longitude;
    }

    std::string getLatitude() {
        return latitude;
    }

    
};

