#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include "node.h"
#include<regex>


class BTS
{
private: 
	void destroyTree(node*);



public:
    node* root;

    void setRoot(node* newRoot) {
        root = newRoot;
    }


    node* getRoot() {
        return root;
    }

	BTS () : root (nullptr){}
	BTS(node* root) : root(root) {}
	~BTS() {
		destroyTree(root);
	}

	node* insertNew(node* , std::string, std::string, std::string, std::string);
	
	void insert(std::string cityName, std::string latitude, std::string longitude, std::string country) {
		root = insertNew(root, cityName.substr(0,1), latitude, longitude, country);
	}


    
	
	bool empty(); 

	node* search(node*, std::string);

	void levelOrderTraversal();

	void inOrderTraversal(node* );

	void postOrderTraversal(node*);

	void preOrdertraversal(node*);

    void preOrdertraversalSave(node* N, std::ofstream& outFile) {
        if (N) {
            // Write the node's data to the output file
            outFile << N->getName() << "," << N->getLatitude() << "," << N->getLongitude() << "," << N->getCountry() << std::endl;

            // Recursively traverse the left and right subtrees
            preOrdertraversalSave(N->left, outFile);
            preOrdertraversalSave(N->right, outFile);
        }
    }


	std::string retrieve(std::string);


	void saveToFileHelper(node* , std::ofstream& );
	void saveToFile(const std::string&);



    node* deleteNode(node* root, std::string name) {
        if (!root) {
            return root;
        }

        if (name < root->getName()) {
            root->left = deleteNode(root->left, name);
        }
        else if (name > root->getName()) {
            root->right = deleteNode(root->right, name);
        }
        else {
            if (!root->left && !root->right) {
                // Node with no children
                delete root;
                root = nullptr;
            }
            else if (!root->left) {
                // Node with one child (right child)
                node* temp = root;
                root = root->right;
                delete temp;
            }
            else if (!root->right) {
                // Node with one child (left child)
                node* temp = root;
                root = root->left;
                delete temp;
            }
            else {
                // Node with two children
                node* successor = findSuccessor(root->right);
                root->changeCityName(successor->getName());
                root->right = deleteNode(root->right, successor->getName());
            }
        }

        return root;
    }

    node* findSuccessor(node* Node) {
        node* current = Node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    void listAllEntries() {
        // Perform an in-order traversal to list all entries
        inOrderTraversal(root);
    }


};

