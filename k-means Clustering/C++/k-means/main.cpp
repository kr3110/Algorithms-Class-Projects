//
//  main.cpp
//  k-means
//
//  Created by Kevin Reinoso on 10/18/17.
//  Copyright © 2017 Kevin Reinoso. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
double dist(int, int, int, int);
int main(int argc, const char * argv[]) {
    static fstream inFile;
    static ofstream outFile1, outFile2;
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    
    class point {
    public:
        int x_cord;
        int y_cord;
        int label;
        double distance;
        point(int x, int y) {
            y_cord = y;
            x_cord = x;
        }
        void printPoint(){
            outFile1<<y_cord<<" "<< y_cord<< " "<<label<<endl;
        }
        
    };
    class kmean {
    private:
        int k;
        struct xyCoord {
            int x_cord=0;
            int y_cord=0;
        };
        int label;
        xyCoord *Kcentroids;
        int numpoints;
        int numRow;
        int numCol;
        int changeLabel;
        int **imageArray;
        point **pointSet;
        int* clus_average;
    public:
        //methods
        kmean(int k, int row, int col, int nump)
        {
            this->k = k;
            clus_average = new int[k];
            numRow = row;
            numCol = col;
            numpoints = nump;
            Kcentroids = new xyCoord[k];
            imageArray = new int*[row];
            for(int i = 0; i<row; i++)
            {
                imageArray[i] = new int[col];
            }
            pointSet = new point*[nump];
            
        }
        void loadPointSet(){
            // read each point from input file and store it onto
            // the struct pointSet array.
            int counter = 0;
            int row, col;
            while(inFile >> row >>col)  {
                pointSet[counter] = new point(row, col);
                counter++;
            }
        }
        void assingLabel(){
            int rando = rand();
            for(int i = 0; i<numpoints; i++)
                pointSet[i]->label = ((i+rando)%4)+1;
        }
        void kMeanClustering(){
            for(int i = 0; i< k; i++)
                clus_average[i] = 0;
            for(int i = 0; i<numpoints; i++) {
                if(pointSet[i]->label == 1) {
                    Kcentroids[0].x_cord += pointSet[i]->x_cord;
                    Kcentroids[0].y_cord += pointSet[i]->y_cord;
                    clus_average[0] += 1;
                }
                else if(pointSet[i]->label == 2) {
                    Kcentroids[1].x_cord += pointSet[i]->x_cord;
                    Kcentroids[1].y_cord += pointSet[i]->y_cord;
                    clus_average[1]+= 1;
                }
                else if(pointSet[i]->label == 3) {
                    Kcentroids[2].x_cord += pointSet[i]->x_cord;
                    Kcentroids[2].y_cord += pointSet[i]->y_cord;
                    clus_average[2]+= 1;
                }
                else  {
                    Kcentroids[3].x_cord += pointSet[i]->x_cord;
                    Kcentroids[3].y_cord += pointSet[i]->y_cord;
                    clus_average[3]+= 1;
                }
            }
            for(int i = 0; i<k; i++) {
                if(clus_average[i]!=0) {
                    Kcentroids[i].x_cord = Kcentroids[i].x_cord/clus_average[i];
                    Kcentroids[i].y_cord = Kcentroids[i].y_cord/clus_average[i];
                    
                }
            }
        }
        
        bool minDistSetter(int l)
        {
            bool changeLabel = false;
            double temp = 0;
            for(int i = 0; i<numpoints; i++)
            {
                for(int j = 0; j<k; j += 1)
                {
                    if(l==0){
                        pointSet[i]->label = 1;
                        pointSet[i]->distance = dist(pointSet[i]->x_cord,pointSet[i]->y_cord,Kcentroids[0].x_cord,Kcentroids[0].y_cord);
                    }
                    if( (j+1) != pointSet[i]->label)
                    {
                        temp = dist(pointSet[i]->x_cord, pointSet[i]->y_cord, Kcentroids[j].x_cord, Kcentroids[j].y_cord);
                        if(temp<pointSet[i]->distance)
                        {
                            pointSet[i]->label = j+1;
                            pointSet[i]->distance = temp;
                            changeLabel = true;
                        }
                    }
                }
            }
            return changeLabel;
        }
        void printPointSet(){
            outFile1<<k<<endl;
            outFile1<<numpoints<<endl;
            outFile1<<numRow<<" "<< numCol<<endl;
            for(int i = 0; i<numpoints; i++)
                pointSet[i]->printPoint();
        }
        
        void mapPoint2Image(){
            for(int i = 0; i< numpoints; i++)
                imageArray[pointSet[i]->x_cord][pointSet[i]->y_cord] = pointSet[i]->label;
        }
        void prettyPrint (){
            for(int i = 0; i<numRow; i++)
            {
                for(int j = 0; j<numCol; j++)
                {
                    if(imageArray[i][j]==0) outFile2<<" ";
                    else outFile2<<imageArray[i][j];
                }
                outFile2<<endl;
            }
        }
    };
    // insert code here...
    int k,nump,row,col,iterations = 0;
    inFile >> k;
    inFile >> nump;
    inFile >> row >> col;
    kmean clusters(k,row,col,nump);
    clusters.loadPointSet();
    clusters.assingLabel();
    clusters.mapPoint2Image();
    outFile2<<"image number: "<<++iterations<<endl;
    clusters.prettyPrint();
    clusters.kMeanClustering();
    clusters.minDistSetter(0);
    while(true) {
        clusters.mapPoint2Image();
        outFile2<<"image number: "<<++iterations<<endl;
        clusters.prettyPrint();
        clusters.kMeanClustering();
        if(!clusters.minDistSetter(iterations))
            break;
    }
    clusters.printPointSet();
    //step 9
    inFile.close();
    outFile2.close();
    outFile1.close();
    return 0;
}
double dist(int x1, int y1, int x2, int y2) {
    int a = (x1-x2)*(x1-x2);
    int b = (y1-y2)*(y1-y2);
    return sqrt((a+b));
}


