//
//  main.cpp
//  bucketsort
//  Created by Kevin Reinoso on 12/2/17.
//  Copyright © 2017 Kevin Reinoso. All rights reserved.
//
//  @arvg[1] is input
//  @argv[2] is output

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {

    static fstream inFile;
    static ofstream outFile;
    try{
        inFile.open(argv[1]);
        outFile.open(argv[2]);
    }catch(exception e){
        cout<<&e;
    }
    class bucketSort{
    private:
        int* buckets;
        int size;
        
    public:
        bucketSort(int d){
            size=d+1;
            buckets=new int [size];
            for(int i=0;i<size;i++){
                buckets[i]=0;
            }
        }
        void sort(){
            while(inFile){
                int data;
                inFile>>data;
                buckets[data]++;
            }
        }
        void print(){
            for(int i=0;i<size;i++){
                while(buckets[i]>0){
                    outFile<< i<<" , ";
                    buckets[i]--;
                }
            }
        }
    };
    int max=-1;
    while(inFile){
        int data;
        inFile>>data;
        if(max<data){
            max=data;
        }
    }
    
    inFile.close();
    inFile.open(argv[1]);
    bucketSort *sort=new bucketSort(max);
    sort->sort();
    sort->print();
    inFile.close();
    outFile.close();
    return 0;
}
