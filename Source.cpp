//Name: Zachary Abbe
//Date: 10/18/2024
//Desc: This is the Project 3 for Corner Grocer
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>  // For transform
using namespace std;

class itemSearch {
	// this houses private member variables, and creates variables to store file names
private:
	map<string, int> itemFrequency;
	string inputFileName = "CS210_Project_Three_Input_File.txt";
	string outputFileName = "frequency.dat";

public:
	//this reads the input file and stores the frequency in item frequency
	void readInputFile() {
		ifstream inputFile(inputFileName);
		string item;
		while (inputFile >> item) {
			itemFrequency[item]++;
		}
		inputFile.close();
	}
	//this writes an output file and writes the contents of itemFrequency to it
	void writeOutputFile() {

		ofstream outputFile(outputFileName);
		for (auto item : itemFrequency) {
			outputFile << item.first << " " << item.second << endl;
		}
		outputFile.close();
	}

	// Helper function to convert a string to lowercase
	string toLowerCase(const string& str) {
		string lowerStr = str;
		transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
		return lowerStr;
	}

	// Modify the searchItem function to handle missing items gracefully
	void searchItem() {
		string item;
		cout << "Enter the item to search for: ";
		cin >> item;

		// Convert the search term to lowercase
		string searchItemLower = toLowerCase(item);

		// Search for the item by iterating through the map and checking the lowercase version
		bool found = false;
		for (const auto& entry : itemFrequency) {
			if (toLowerCase(entry.first) == searchItemLower) {
				cout << "Frequency of " << entry.first << " is " << entry.second << endl;
				found = true;
				break;
			}
		}

		// If no match was found, display a message
		if (!found) {
			cout << item << " not found in the list." << endl;
		}
	}

	// this is the list print function, and it prints the item frequency in list format
	void printList() {
		const int alignDistance = 15; //sets the distance to keep it all lined up
		cout << "Item Frequency List: " << endl;
		for (auto item : itemFrequency) {
			cout << item.first;
			// Calculate the number of spaces to add after the item name
			int spacesToAdd = alignDistance - item.first.length();
			if (spacesToAdd < 0) {
				spacesToAdd = 1; // Ensure there's at least one space between the item and asterisks
			}

			// Add the spaces
			for (int i = 0; i < spacesToAdd; i++) {
				cout << " ";
			}
			cout << item.second << endl;
		}
	}

	//this will print the histogram using asteriks
	void printHistogram() {
		const int alignDistance = 15;  // Set the distance where the asterisks begin
		cout << "Item Frequency Histogram:" << endl;
		for (auto item : itemFrequency) {
			cout << item.first;

			// Calculate the number of spaces to add after the item name
			int spacesToAdd = alignDistance - item.first.length();
			if (spacesToAdd < 0) {
				spacesToAdd = 1; // Ensure there's at least one space between the item and asterisks
			}

			// Add the spaces
			for (int i = 0; i < spacesToAdd; i++) {
				cout << " ";
			}

			// Print the asterisks corresponding to the frequency
			for (int i = 0; i < item.second; i++) {
				cout << "*";
			}
			cout << endl;
		}
	}
};

// now we begin the main function which houses our menu
int main() {
	// we need to create an instance of Grocer
	itemSearch itemsearch;
	itemsearch.readInputFile();

	//begin to display the menu and make the appropriate function call based on number choice
	int choice;
	do {
		cout << endl <<"Menu:" <<endl;
		cout << "1. Search for an item" << endl;
		cout << "2. Print item frequency list" << endl;
		cout << "3. Print item frequency histogram" << endl;
		cout << "4. Exit Program" << endl;
		cout << "Enter your choice from the menu above: ";
		
		if (!(cin >> choice)) {
			// If input is not a valid number (e.g., letters or special characters)
			cin.clear();  // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
			cout << "Invalid input. Please enter a valid number." << endl;
		}
		else {
			switch (choice) {
			case 1:
				itemsearch.searchItem();
				break;
			case 2:
				itemsearch.printList();
				break;
			case 3:
				itemsearch.printHistogram();
				break;
			case 4:
				cout << "Exiting Program... " << endl << "Thank you for choosing Grocer Corner!!!" << endl;
				break;
			default:
				cout << "INVALID CHOICE" << endl;
			}
		}
	} while (choice != 4);
	itemsearch.writeOutputFile();
	return 0;
}