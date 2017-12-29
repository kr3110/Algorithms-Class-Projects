import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Scanner;

//  prims.java
//  Prims algorithm for finding the Minimum Spanning Tree of a giving undirected graph
//  Problem: Given an undirected graph, G = <N, E>, the task is find
//  a minimum spanning tree of G, using the Prims algorithm.
//  Created by Kevin Reinoso on 11/28/17.
//  Copyright © 2017 Kevin Reinoso. All rights reserved.

class prims{
	class graphNode{
		public int nodeId;
		public graphNode next;
		
		public graphNode(int id){
			nodeId=id;
			next=null;
		}
	}
	class undirectedEdge{
		public int Ni,Nj,edgeCost;
		undirectedEdge next;
		
		public undirectedEdge() {
			Ni=0;Nj=0;edgeCost=0;
			next = null;
		}
		public undirectedEdge(int i,int j,int e) {
			Ni=i;Nj=j;edgeCost=e;
			next=null;
		}
		void printEdge() {
			outfile2.print("<"+Ni+", "+Nj + ", " +edgeCost+ ">");
		}
	}
	PrintWriter outfile1,outfile2;
	int numNodes,totalcost,numSet;
	int []inWhichSet;
	undirectedEdge MSTofG;
	undirectedEdge head;
	public prims(int nodes) {
		 numNodes=nodes;
		 numSet=nodes;
		 inWhichSet= new int [nodes+1];
		 for(int i=0;i<=nodes;i++) {
			 inWhichSet[i]=2;
			 if(i==1) {
				 inWhichSet[i]=1;
			 }
		 }
		 MSTofG=new undirectedEdge();
		 head = new undirectedEdge();
	}
	public void insertedEdge(undirectedEdge edge) {
		undirectedEdge i = head;
		while( i.next !=null && edge.edgeCost>i.next.edgeCost) {
			i=i.next;
		}
		edge.next = i.next;
		i.next = edge;
	}
	public undirectedEdge removeEdge() {
		undirectedEdge temp = head;
		head = head.next;
		return temp;
	}
	public void pushEdge(undirectedEdge edge) {
		edge.next = MSTofG;
		MSTofG=edge;
	}
	void move2Sets(int node, int set){
		this.inWhichSet[node]=set;
	}
	void printSet() {
		outfile2.print("InWhichSet: ");
		for(int i=1;i<numNodes+1;i++) {
			outfile2.print(inWhichSet[i] + " ");
		}
		outfile2.println();
	} 
	void printList (undirectedEdge listHead){
        undirectedEdge temp = listHead;
        int i=10;
        while (temp != null && i > 0){
            temp.printEdge();
            outfile2.print("->");
            temp = temp.next;
            i--;
        }
        outfile2.println( "NULL");
    }
	 void printMST(){
         undirectedEdge temp =MSTofG;
         outfile1.println("*** A Prims MST of the input graph is given below: ***") ;
         outfile1.println(numNodes);
         while (temp.next != null)	{
             outfile1.println(temp.Ni + " " + temp.Nj + " " +temp.edgeCost); 
             temp = temp.next;
         }
         outfile1.println("Total cost for MST is: " +totalcost );
     }
	 public boolean checksets() {
		 for(int i=1;i<=numNodes;i++) {
			 if(inWhichSet[i]==2)
				 return true;
		 }
		 return false;
	 }

	 void PrimsMSTAlgorithm(Scanner infile,PrintWriter file1,PrintWriter file2){
		 outfile1=file1;
		 outfile2=file2;
		 int Ni, Nj, cost;
		printSet();
		 
         while (infile.hasNext()) {
             Ni=infile.nextInt();
             Nj=infile.nextInt();
             cost= infile.nextInt();
             undirectedEdge newEdge = new undirectedEdge(Ni, Nj, cost);
             insertedEdge(newEdge);
         	printList(head);
         }
       
         while (checksets()) {
             undirectedEdge nextEdge=head;
             
             while (inWhichSet[nextEdge.Ni] == inWhichSet[nextEdge.Nj]) {
            	 	nextEdge = nextEdge.next;
             }
             undirectedEdge newEdge= new undirectedEdge(nextEdge.Ni,nextEdge.Nj,nextEdge.edgeCost);
             pushEdge(newEdge);
             
             totalcost += nextEdge.edgeCost;
            if(inWhichSet[nextEdge.Ni]==1) {
            	move2Sets(nextEdge.Nj,1);
            }else {
               	move2Sets(nextEdge.Ni,1);
            }
             printSet();
             printList(MSTofG);
         }
         printMST();
     }
	public static void main(String []argv) {
		try	{
			FileReader file=new FileReader(argv[0]);
			Scanner infile =new Scanner(file);
			PrintWriter outFile1 = new PrintWriter(new FileWriter(argv[1]));
			PrintWriter outFile2 = new PrintWriter(new FileWriter(argv[2]));

			int nodes=infile.nextInt();
			prims MST = new prims(nodes);
			MST.PrimsMSTAlgorithm(infile,outFile1,outFile2);
			
			
			infile.close();
			file.close();
			outFile1.close();
			outFile2.close();
		}	catch(Exception e)	{
			System.out.println(e );
		}
	}
}