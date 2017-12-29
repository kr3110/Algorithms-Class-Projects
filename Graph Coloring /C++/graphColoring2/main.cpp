//
//  main.cpp
//  graphColoring2
//  Project 9.2:  Graph coloring problem:  given a undirected graph, G = <N, E>,
//  the graph coloring problem is to find the minumum number of colors to color all nodes in N,
//  such that two adjacent nodes, ni, nj, can not be colored with the same color.
//  Created by Kevin Reinoso on 12/10/17.
//  Copyright © 2017 Kevin Reinoso. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, const char * argv[]) {
    
    static fstream inFile;
    static ofstream outFile1;
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    class node{
    public:
        int colorID;
        node* next;
        node(int k){
            colorID=k;
            next=nullptr;
        }
    };
    class graphColoring2{
        
    private:
        int** adjacencyMatrix;
        node* usedColorTop;
        int newColor;
        int numNode;
        int currentNode;
    public:
        graphColoring2(int n){
            numNode=n;
            adjacencyMatrix= new int*[numNode+1];
            for(int i=0; i<=numNode; i++) {
                adjacencyMatrix[i]=new int [numNode+1];
                for(int j=0; j<=numNode; j++) {
                        adjacencyMatrix[i][j]=0;
                }
            }
            usedColorTop=nullptr;
            newColor=0;
            currentNode=0;
            
        }
        void loadMatrix(){
            int n1,n2;
            while (inFile) {
                inFile>>n1>>n2;
                adjacencyMatrix[n1][n2] = 1;
                adjacencyMatrix[n2][n1] = 1;
            }
        }
        int checkAdjacent(int nodeID, int color){
            for (int i = 1; i <= numNode; i++) {
                if (adjacencyMatrix[nodeID][i] == 1) {
                    if (adjacencyMatrix[i][i] == color)
                        return 1;
                }
            }
            return 0;
        }
        bool isThereUncolorNode() {
            for (int i = 1; i <= numNode; i++){
                if (adjacencyMatrix[i][i] == 0)
                    return true;
            }
            return false;
        }
        void pushUsedColor(int color){
            node* newNode=new node(color);
            if(usedColorTop==nullptr){
                usedColorTop=newNode;
            }else{
                newNode->next=usedColorTop;
                usedColorTop=newNode;
            }
        }
        int  findUsedColor(int cNode){
            node* trav = usedColorTop;
            while(trav != nullptr)
            {
                if (checkAdjacent(cNode, trav->colorID) == 0)
                    return trav->colorID;
                trav = trav->next;
            }
            return 0;
        }
        void colorGraph(){
            while(isThereUncolorNode()){
            currentNode++;
            printAdjacencyMatrix();
            int usedColor;
            usedColor=findUsedColor(currentNode);
            if(usedColor>0){
                adjacencyMatrix[currentNode][currentNode]=usedColor;
            }else{
                newColor++;
                adjacencyMatrix[currentNode][currentNode]=newColor;
                pushUsedColor(newColor);
            }
            }
            finalPrint();
        }
        void finalPrint(){
            outFile1<<"\n\n****************Final Print******************\n";
            outFile1<<"The total number of colors used were "<< newColor<<"\n";
            printAdjacencyMatrix();
            outFile1<<"Node\tColor\n";
            for(int i=1;i<=numNode;i++)
                outFile1<<i<<"\t\t"<<adjacencyMatrix[i][i]<<"\n";
        }
        void printAdjacencyMatrix() {
            outFile1<<"Printing Adjacency Matrix \n";
            for (int i = 1; i <= numNode; i++) {
                for (int j = 1; j <= numNode; j++)
                    outFile1<<adjacencyMatrix[i][j] <<"  ";
                outFile1<<"\n";
            }
        }

    };
 
    int numNode;
    inFile>>numNode;
    graphColoring2 *coloring=new graphColoring2(numNode);
    coloring->loadMatrix();
    coloring->colorGraph();
    
    inFile.close();
    outFile1.close();
    return 0;
}
