/**------------------------------------------
    Program 6: Graphs

    Course: CS 141, Spring 2023.
    System: Linux x86_64 and G++
    Author: Gerard W. Wilbert
 ---------------------------------------------**/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;
/* struct created to create the nodes for the link list 
  */
struct Node {
  Node* next; // pointer to the next node
  int id; // the data for the node
  Node(int theid) { // creates Nodes using the data
    id = theid;
    this->next = NULL;
  }
};
/* 
  Function created to add nodes to a NULL linked list or add nodes to the front of a linked list
  The head is a pass by refrence since it is a index in the adjaceny list vector that accepts head pointers.
  the id is the data
  */
void Prepend(Node * &head, int theid) {
  if (head == NULL) {
    head = new Node(theid);
  }

  else {
    Node* newNode = new Node(theid); // Delcares a node pointer called newNode that creates a new node for the linked list
    newNode->next = head; // Makes newNode the first Node in the linked list
    head = newNode;
  }
}
/* This function handles inserting nodes into the linked list

*/
void insert(Node* &head, int theid) {
  if(head == NULL || head->id > theid) {
    Prepend(head, theid); // Call the previous function if head is NULL or the data you are trying to input is smaller than the first node in the linked list
  }
  else { // if the data you are inputing is bigger the first node
    Node * newNode = new Node(theid); // Creates new Node
    Node * curr = head; // create a pointer that helps traverse the linked list so we can insert the new node
    while(curr->next != NULL) { // until the curr value pointers to NULL
      if(curr->next->id > theid) { // Handles when the newNode's data is the not the bigger than all the other data in the linked list. WHich breaks the loop and adds it in the middle of the linked list.
        break;
      }
      curr = curr->next;
    }
    newNode->next = curr->next; // make newNode next NULL
    curr->next = newNode; // then makes the curr node point to the new node adding it into the linked list
  }
}
/*
Loads the inputted file and adds its contents to the empty adjanceny list
  */
void loadFile(vector<Node*>& adList, string file) {
  string node; // takes in the first value of the line in the file
  string edge; // takes in the second value of the line in the file
  int headNode; // converts the node to a integer to help make the code cleaner
  int edgeNode; // converts the edge to a integer to help make the code cleaner
  ifstream GraphData{file}; // opens the file 
  while(!GraphData.eof()) { // until there are no other lines to read in
  GraphData >> node; 
  GraphData >> edge;
  headNode = stoi(node);
  edgeNode = stoi(edge);
  if(headNode >= edgeNode) { 
    if(headNode > adList.size()) { 
      while(adList.size() <= headNode) {
        adList.push_back(NULL); // increases the size of the adjency list 
      }
    }
  }
  else if(edgeNode > headNode){
    if(edgeNode >= adList.size()) {
      while(adList.size() <= edgeNode) {
        adList.push_back(NULL);
      }  
    }
    }
       insert(adList.at(headNode), edgeNode);  // After the Adjacency list has all the values in needs inserts new node into linked list at the index at the value of the node
       insert(adList.at(edgeNode), headNode); // Does the reverse of last line using the index at the edge's value and insert the value of the node.
  }

}
/* Helps run each file instead of having to do the same for each file
*/
void run(const string& src_path, const string& dst_path) {
  vector<Node*> AdjList; // creates empty adjanceny list
  int numOfNodes = 0;
  int numOfEdges = 0;
  int degree = 0;
  int maxDegree = 0;
  loadFile(AdjList, src_path);
  
  ofstream filestr{dst_path}; // writes a file
  if(!filestr) {
    cout << "Error: file could not be opened" << endl;
  }
  for(int f = 0; f < AdjList.size(); f++) {
    Node * curr = AdjList[f];
    if(curr == NULL) { // Makes sure indexs that don't have linked are not put into the written file
    }
  
    else {
      filestr << f << ": ";
      numOfNodes += 1;
      while(curr != NULL) {  
      if(curr->next != NULL) { // Make sure curr does not point to NULL
       if(curr->id != curr->next->id) { // Makes duplicate not written into the file
         filestr << curr->id << " ";
         numOfEdges += 1;
         degree += 1;
       }
      }

      else { // if current points to NULL don't add a space
        filestr << curr->id;
        numOfEdges += 1;
        degree += 1;
      }
       
       curr = curr->next;
      }
    filestr << endl; // add endline at the end of each linklist
    if(degree > maxDegree) { // Help calculate the maxDegree for the whole file
    maxDegree = degree;
    }
    degree = 0; // redeclares degree as 0 for the following linked list
    }
    
  }
  filestr.close();
  cout <<  "Number of nodes: "<< numOfNodes << endl;
  cout << "Number of edges: " << numOfEdges/2 << endl;
  cout << "Maximum degree: " << maxDegree << endl;
}

int main() {
  run("roadNet-CA.txt", "blue.txt");
}

