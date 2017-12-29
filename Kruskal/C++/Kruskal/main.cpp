//
//  main.cpp
//  Kruskal’s algorithm for finding the Minimum Spanning Tree of a giving undirected graph
//  Problem: Given an undirected graph, G = <N, E>, the task is find
//  a minimum spanning tree of G, using the Kruskal’s algorithm.
//  Created by Kevin Reinoso on 11/22/17.
//  Copyright © 2017 Kevin Reinoso. All rights reserved.

#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, const char * argv[]) {
    static fstream inFile;
    static ofstream outFile1, outFile2;
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    
    
    class graphNode {
        
    public:
        int nodeID;
        graphNode* next;
        
        graphNode(int ID){
            nodeID = ID;
            next = nullptr;
        }
        ~graphNode(){
            graphNode* temp;
            while(next!=NULL) {
                temp=next;
                next=next->next;
                delete temp;
            }
        }
    };
    
    class undirectedEdge {
        
    public:
        int Ni;
        int Nj;
        int edgeCost;
        undirectedEdge* next;
        undirectedEdge() {
            Ni = 0; Nj = 0; edgeCost = 0;
            next = NULL;
        }
        undirectedEdge(int i, int j, int e) {
            Ni = i; Nj = j; edgeCost = e;
            next = NULL;
        }
        void printEdge(){
            outFile2<<"<" <<Ni<<", " << Nj << ", " <<edgeCost<< ">";
        }
        ~undirectedEdge(){
            //  - distractor  //to free an undirectedEdge
            delete next;
        }
    };
    
    class KruskalMST {
    public:
        int numNodes, totalcost,numSet;
        int * inWhichSet;
        undirectedEdge* MSTofG;
        undirectedEdge* head;
        
        
        KruskalMST(int nodes){
            inWhichSet= new int[nodes];
            numNodes=nodes;
            numSet=nodes;
            for(int i=0; i<nodes; i++) {
                inWhichSet[i]=i;
            }
            MSTofG = new undirectedEdge();
            head = new undirectedEdge();
            printSet();
            
        }
        void insertEdge(undirectedEdge *edge){
            undirectedEdge* i = head;
            while (i->next != NULL && edge->edgeCost > i->next->edgeCost) {
                i = i->next;
            }
            edge->next = i->next;
            i->next = edge;
        }
        undirectedEdge* removeEdge() {
            undirectedEdge* temp = head;
            head = head->next;
            return temp;
        }
        void pushEdge(undirectedEdge *edge){
            edge->next = MSTofG;
            MSTofG = edge;
        }
        void merge2Sets(int node1, int node2) {
            if (node1 > node2)  {
                int temp = node1;
                node1 = node2;
                node2 = temp;
            }
            int newSet = inWhichSet[node2];
            for (int i = 1; i <= numNodes; i++) {
                if (inWhichSet[i] == newSet) {
                    inWhichSet[i] = inWhichSet[node1];
                }
            }
        }
        void printSet(){
            outFile2 << "inWhichSet: ";
            for (int i = 1; i <= numNodes; i++)
                outFile2 << inWhichSet[i] << " ";
            outFile2 << "\n";
            
        }
        void printList (undirectedEdge* listHead){
            undirectedEdge* temp = listHead;
            int i=10;
            while (temp != NULL && i > 0){
                temp->printEdge();
                outFile2<< "->";
                temp = temp->next;
                i--;
            }
            outFile2 << "NULL\n";
        }
        void printMST(){
            undirectedEdge* temp =MSTofG;
            outFile1<<"*** A Kruskal’s MST of the input graph is given below: ***"<<endl;
            outFile1<<numNodes<<endl;
            while (temp->next != NULL)
            {
                outFile1 << temp->Ni << " " << temp->Nj << " " << temp->edgeCost << endl;
                temp = temp->next;
            }
            outFile1 << "Total cost for MST is: " <<totalcost << endl;
        }
        void kruskalMSTAlgorithm(){
            int Ni, Nj, cost;
            while (inFile) {
                inFile >> Ni >> Nj >> cost;
                undirectedEdge* newEdge = new undirectedEdge(Ni, Nj, cost);
                insertEdge(newEdge);
                printList(head);
            }
            while (numSet > 1) {
                undirectedEdge* nextEdge=removeEdge();
                while (inWhichSet[nextEdge->Ni] == inWhichSet[nextEdge->Nj]) {
                    nextEdge = removeEdge();
                }
                pushEdge(nextEdge);
                totalcost += nextEdge->edgeCost;
                merge2Sets(nextEdge->Ni, nextEdge->Nj);
                numSet--;
                printSet();
                printList(MSTofG);
            }
            printMST();
        }
    };
    int numNodes;
    inFile >> numNodes;
    KruskalMST* MST= new KruskalMST(numNodes);
    MST->kruskalMSTAlgorithm();
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}

