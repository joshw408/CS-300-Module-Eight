//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Joshua Williamson
// Version     : 1.0
// Description : Lab 7-1 Project Two
//============================================================================



#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

//Define a structure to hold course information
struct Courses {
    string courseId;
    string courseName;
    vector <string> prerequisites;
};

//Internal structure for tree node
struct Node {
    Courses course;
    Node* left;
    Node* right;

    //Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //Initialize with a course
    Node(Courses aCourse) :Node() {
        course = aCourse;
    }
};

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Courses course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Courses course);
    void InOrder();
    Courses Search(string courseId);

};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}
//Destructor
BinarySearchTree::~BinarySearchTree() {
}


/**
 * Insert course
 */
void BinarySearchTree::Insert(Courses course) {
    //Adds a new root if root is empty
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        //Add Node root and course
        this->addNode(root, course);
    }
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Courses to be added
 */

void BinarySearchTree::addNode(Node* node, Courses course) {
    //If node > course, add to left subtree
    if (node->course.courseId.compare(course.courseId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        //If left node exists, keep traversing down left subtree
        else {
            this->addNode(node->left, course);
        }
    }
    //If node < course, add to right subtree
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        //If right node exists, keep traversing down right subtree
        else {
            this->addNode(node->right, course);
        }
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
    //If node is not equal to null ptr
    if (node != nullptr) {

        //InOrder node left
        inOrder(node->left);

        //Output the courseID, courseName, prerequsite
        cout << node->course.courseId << ", " << node->course.courseName << endl;


        //InOder right
        inOrder(node->right);
    }
}

/**
 * Search for a course
 */
Courses BinarySearchTree::Search(string courseId) {

    //Set current node equal to root
    Node* current = root;

    //Keep looping downward until the bottom is reached or a matching bidid is found

    while (current != nullptr) {
        if (current->course.courseId.compare(courseId) == 0) {
            return current->course;
        }
        if (courseId.compare(current->course.courseId) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    Courses course;
    return course;
}

//Method for displaying course information
void displayCourse(Courses course) {
    cout << course.courseId << ", " << course.courseName << endl;
    cout << "Prerequisites: ";

    //If prereuqiaite vector is zero 
    if (course.prerequisites.size() == 0) {
        cout << "None";
    }
    else {
        //Prints prerequisite at index zero
        cout << course.prerequisites.at(0);

        //Starts at index 1 and prints remaining prerequisites; prevents an out of range error
        for (unsigned int i = 1; i < course.prerequisites.size(); ++i) {
            cout << ", " << course.prerequisites.at(i);
        }
    }
    return;
}

/*
* Opens the file and parses the lines at the comma splitting into tokens
* @parm fileName, BinarySearchTree bst
*/
void courseLoader(string fileName, BinarySearchTree* bst) {
    //Instantiated variables
    string token;
    string line;

    int nCount = 0;

    //Reads data from a file and displays
    ifstream myFile;

    //Opens file
    myFile.open(fileName, ios::in);

    //If file is open get a line and split at the comma
    if (myFile.is_open()) {
        cout << "File is open" << endl;
        while (getline(myFile, line)) {
            vector <string> prerequsites;
            stringstream ss(line);

            //Scope and object to set structure variables
            Courses course;
            nCount = 1;

            //First pass splits the line by commas  
            //Retrieves the first element, increments the count, then retrieves the second, and so on  
            //When the end of the line is reached, the count resets to 1 and processing moves to the next line  

            while (getline(ss, token, ',')) {
                if (nCount == 1) {

                    //Stores token at position 1 into course structure
                    course.courseId = token;
                }
                //Stores token at position 2 into course structure
                if (nCount == 2) {
                    course.courseName = token;
                }
                //Pushes elements in a line at position > 2 to a vector
                if (nCount > 2) {
                    prerequsites.push_back(token);
                }
                ++nCount;
            }

            //Iterates over the vector to push the elements to the structure vector
            for (unsigned int i = 0; i < prerequsites.size(); ++i) {
                course.prerequisites.push_back(prerequsites.at(i));
            }
            //Inserts structure variable elements to the Binary Search tree
            bst->Insert(course);
        }
    }
    else {
        cout << "File could not be opened" << endl;
    }
};

int main() {
    //Instantiated variables
    int menuSelection;
    string fileName;
    string courseSearch;

    //Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Courses course;

    do {
        //Do while loop and display the menu selection
        cout << endl;
        cout << "Welcome to the course planner." << endl;
        //cout << "-----------------------------" << endl;
        cout << " " << endl;
        cout << " 1.  Load Data Structure.  " << endl;
        cout << " 2.  Print Course List.    " << endl;
        cout << " 3.  Print Course.         " << endl;
        cout << " 9.  Exit                  " << endl;
        cout << " " << endl;
        //cout << "-----------------------------" << endl;
        cout << endl;

        do { //Do while loop for the user input

            cin >> menuSelection;
            if (cin.fail()) {
                cin.clear(); //Clears cin buffer
                cin.ignore(80, '\n');
            }
        } while (cin.fail()); //Loops while cin.fail is true

        //Passes user menu selection to switch case
        switch (menuSelection) {
        case 1:
            cout << "Enter the file name:" << endl;
            //Holds user input
            cin >> fileName;
            //Calls course loader method and passes the file name and bst method
            courseLoader(fileName, bst);
            cout << endl;
            break; //prevents fall through
        case 2:
            cout << "Here is a sample schedule:" << endl;
            cout << endl;
            //Calls the inOrder Methodd of the BST, which automatically sorts by Alphabetical 
            bst->InOrder();
            break;
        case 3:
            cout << "What course do you want to know about?" << endl;
            cin >> courseSearch;

            //Converts the lowercase user input to upper case for the search method.
           
            for (int i = 0; courseSearch[i] != '\0'; i++) {
                if (courseSearch[i] >= 'a' && courseSearch[i] <= 'z')
                    courseSearch[i] = courseSearch[i] - 32;
            }
            cout << endl;
            //Passes the searched course into the search method
            course = bst->Search(courseSearch);

            if (!course.courseId.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course " << courseSearch << " not found.";
            }
            cout << endl;
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            cout << endl;
            break;
        default:
            cout << menuSelection << " is not a valid option." << endl;
            cout << endl;
            break;
        }
        //Menu Exit Selection
    } while (menuSelection != 9);
    return 0;
}