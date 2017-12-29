//
//  main.cpp
//  Project 4: Heap Sort:
//      Based on 1D implementation of Partial Order Binary Trees/Priority Q
//       taught in class.
//
//  Created by Kevin Reinoso on 10/8/17.
//  Copyright © 2017 Kevin Reinoso. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, const char * argv[]) {
    static fstream inFile;
    static fstream outFile1, outFile2;
    outFile1.close();
    outFile2.close();
    class heapSort {
    private:
        int rootIndex;
        int fatherIndex;
        int leftKidIndex;
        int rightKidIndex;
        int minKidIndex;
        int size;
        int* heapAry;
    public:
        heapSort(int amount){
            heapAry = new int[amount+1];
            heapAry[0]=0;
            rootIndex=1;
            size=amount;
            
            
        }
        
        void buildHeap()    {
            int data;
            
            while(inFile >> data) {
                int kidIndex;
                insertOneDataItem(data);
                kidIndex=heapAry[0];
                bubbleUp(kidIndex);
                outFile1<<heapAry[0]<<"\t";
                for(int i=1;i<=heapAry[0];i++){
                    outFile1<<heapAry[i]<<" ";
                }
                outFile1<<endl;
            }
            
        }
        
        void deleteHeap()   {
            while(heapAry[0]>0){
                int data= getRoot();
                outFile2<<data<<" ";
                fatherIndex=1;
                deleteRoot();
              
                bubbleDown(fatherIndex);
                outFile1<<heapAry[0]<<"\t";
                for(int i=1;i<=heapAry[0];i++){
                    outFile1<<heapAry[i]<<" ";
                }
                outFile1<<endl;
            }
        }
        void insertOneDataItem(int data){
            if(!isHeapFull()){
                int kidIndex=++heapAry[0];
                heapAry[kidIndex]=data;
            }
        }
        int getRoot(){
            return heapAry[1];
        }
        void deleteRoot(){
            int index=heapAry[0];
            heapAry[1]=heapAry[index];
            --heapAry[0];
        }
        void bubbleUp(int kIndex){
            if( isRoot(kIndex)) {
                return;
            }
            fatherIndex=kIndex/2;
            if(heapAry[kIndex]<heapAry[fatherIndex]) {
                int temp = heapAry[kIndex];
                heapAry[kIndex] = heapAry[fatherIndex];
                heapAry[fatherIndex] = temp;
                bubbleUp(fatherIndex);
            }
            
            
        }
        //  **********************************************
        void bubbleDown(int fIndex){
            if( isLeaf(fIndex)) {
                return;
            }
        
            leftKidIndex = fIndex*2;
            rightKidIndex= fIndex*2+1;
            minKidIndex=findMinKidIndex(fIndex);
            if(heapAry[minKidIndex]<heapAry[fIndex]) {
                int temp = heapAry[fIndex];
                heapAry[fIndex] = heapAry[minKidIndex];
                heapAry[minKidIndex] = temp;
                bubbleDown(minKidIndex);
            }
            
            
        }
        
        bool isLeaf(int index){
            if(index*2>heapAry[0]&&index*2+1>heapAry[0]) {
                return true;
            }
            else
                return false;
        }
        
        bool isRoot(int index){
            return index==1;
        }
        int findMinKidIndex(int fIndex){
            int left=fIndex*2;
            int right=(fIndex*2+1<heapAry[0]) ? fIndex*2+1 : -1;
            if(heapAry[left]<heapAry[right] || right<0)  {
                return left;
            }
            else{
                return right;
            }
        }
        
        bool isHeapEmpty(){
            return heapAry[0]==0;
        }
        bool isHeapFull(){
            return heapAry[0]>=size+1;
        }
        
    };
    
    
    
    heapSort *hSort;
    try{
        outFile1.open(argv[2]);
        outFile2.open(argv[3]);
        inFile.open(argv[1]);
        if(inFile.is_open()) {
            int amount=0;
            int data;
            while(inFile >> data){
                amount++;
            }
            inFile.close();
            
            hSort= new heapSort(amount);
            inFile.open(argv[1]);
            hSort->buildHeap();
            hSort->deleteHeap();
            inFile.close();
          
        }
        else
            cout<<"File is not open"<<endl;
    }
    catch(exception e) {
        cout<<&e;
    }
    outFile1.close();
    outFile2.close();
    return 0;
}

