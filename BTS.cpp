#include "BTS.h"

void BTS::destroyTree(node* Node) {
	if (Node) {
		destroyTree(Node->left);
		destroyTree(Node->right);
		delete Node;
	}



}

bool BTS::empty() {
	return root == nullptr;
}


node* BTS::insertNew(node* current, std::string cityName, std::string latitude, std::string longitude, std::string country) {
	if (current == nullptr) {
		return new node(cityName, latitude, longitude, country);
	}

	if (cityName < current->getName()) {
		current->setLeft(insertNew(current->left, cityName, latitude, longitude, country));
	}
	else if (cityName > current->getName()) {
		current->setRight(insertNew(current->right, cityName, latitude, longitude, country));
	}

	return current;
}

node* BTS::search(node* N, std::string name) {
	if (!N) {
		std::cout << "Node is NULL" << std::endl;
		return nullptr;
	}


	std::cout << "Comparing " << N->getName() << " with " << name << std::endl;

	if (N->getName() == name) {
		std::cout << "Found a match!" << std::endl;
		return N;
	}
	else if (name < N->getName()) {
		std::cout << "Going left" << std::endl;
		return search(N->right, name);
	}
	else {
		std::cout << "Going right" << std::endl;
		return search(N->left, name);
	}
}

void BTS:: inOrderTraversal(node* N) {
	if (N) {
		inOrderTraversal(N->left);
		std::cout << N->getName()<<"  ";
		inOrderTraversal(N->right);
	}
}

void BTS::postOrderTraversal(node* N) {
	if (N) {
		postOrderTraversal(N->left);
		postOrderTraversal(N->right);
		std::cout << N->getName() << "  ";
	}
}

void BTS::preOrdertraversal(node* N) {
	if (N) {
		std::cout << N->getName() << "," << N->getLatitude() << "," << N->getLongitude() << "," << N->getCountry() << std::endl;
		preOrdertraversal(N->left);
		preOrdertraversal(N->right);
	}
}

std::string BTS::retrieve(std::string name) {
	node* foundnode = search(root, name);
	std::string lat = foundnode->getLatitude();
	std::string lon = foundnode->getLongitude();
	if (foundnode) {
		std::string lastname = foundnode->getName() + " (" + foundnode->getCountry() + ", latitude= " + lat + ", longitude= " + lon + ")";
	}
	else {
		return "City not found!";
	}
}

void BTS:: levelOrderTraversal() {
	
	//if the tree is empty
	if (!root) {
		return;
	}

	//creating a queue with the root node as the first element
	std::queue<node*> nodeQ;
	nodeQ.push(root);

	//do this as long as we have not traversed the whole tree
	while (!nodeQ.empty()) {

		//print the current node in the front of the que
		node* current = nodeQ.front();
		std::cout << current->getName();


		//pushing the left and right in the queue
		if (current->left)
			nodeQ.push(current->left);
		if (current->right)
			nodeQ.push(current->right);

		//popping the printed element 
		nodeQ.pop();
	}

}



void BTS:: saveToFileHelper(node* node, std::ofstream& file) {
	if (!node) {
		return;
	}

	saveToFileHelper(node->left, file);
	file << node->getName() << " " << node->getLatitude() << " " << node->getLongitude() << " " << node->getCountry() << "\n";
	saveToFileHelper(node->right, file);
}

void BTS:: saveToFile(const std::string& filename) {
	std::ofstream file(filename);
	saveToFileHelper(root, file);
	file.close();
}







