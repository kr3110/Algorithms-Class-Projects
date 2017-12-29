import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Scanner;

// graphColoring1.java
// Graph coloring problem:  given a undirected graph, G = <N, E>,  
// the graph coloring problem is to find the minumum number of colors to color all nodes in N, 
// such that two adjacent nodes, ni, nj, can not be colored with the same color. 
// Created by Kevin Reinoso on 12/6/17.
// Copyright © 2017 Kevin Reinoso. All rights reserved.

public class graphColoring1 {
	public class node {
		public int ID;
		public int color;
		public int numEdges;
		public node next;

		node(int k) {
			ID = k;
			color = k;
			numEdges = k;
		}
	}

	PrintWriter outfile1, outfile2;
	int[][] adjacencyMatrix;
	node listHead;
	int newColor;
	int numNodes;
	private node temp;

	public graphColoring1(int n, PrintWriter o1) {
		numNodes = n;
		listHead = new node(0);
		outfile1 = o1;

		adjacencyMatrix = new int[numNodes + 1][numNodes + 1];
		for (int i = 0; i <= numNodes; i++)
			for (int j = 0; j <= numNodes; j++)
				adjacencyMatrix[i][j] = 0;
		newColor = 0;
		printAdjacencyMatrix();
	}

	void loadMatrix(Scanner in) {
		while (in.hasNext()) {
			int n1 = in.nextInt();
			int n2 = in.nextInt();
			adjacencyMatrix[n1][n2] = 1;
			adjacencyMatrix[n2][n1] = 1;
		}
	}

	void printAdjacencyMatrix() {
		outfile1.println("Printing Adjacency Matrix ");
		for (int i = 1; i <= numNodes; i++) {
			for (int j = 1; j <= numNodes; j++)
				outfile1.print(adjacencyMatrix[i][j] + "  ");
			outfile1.println();
		}
	}

	void insertOneNode(node newNode) {


			node trav = listHead.next;
			node temp= listHead;
			while(trav!=null) {
				if(newNode.numEdges<=trav.numEdges) {
					newNode.next=trav;
					temp.next=newNode;
					return;
				}
				trav=trav.next;
				temp=temp.next;
			}
			temp.next=newNode;
			
		
	}

	void constructNodeList() {
		for (int i = 1; i <= numNodes; i++) {
			node temp = new node(i);
			temp.ID = i;
			temp.color = 0;
			temp.numEdges = 0;
			for (int j = 1; j <= numNodes; j++) {
				if (adjacencyMatrix[i][j] == 1)
					temp.numEdges += 1;
			}
		
			insertOneNode(temp);
		}
	}

	boolean isThereUncolorNode() {
		node temp = listHead.next;
		while (temp != null) {
			if (temp.color == 0) {
				return true;
			}
			temp = temp.next;
		}
		return false;
	}

	int checkAdjacent(int nodeID, int color) {
		for (int i = 1; i <= numNodes; i++) {
			if (adjacencyMatrix[nodeID][i] == 1) {
				if (getcolor(i) == color)
					return 1;
			}
		}
		return 0;
	}

	int getcolor(int id) {
		node temp = listHead;
		while (temp != null) {
			if (temp.ID == id) {
				return temp.color;
			}
			temp = temp.next;
		}
		return -1;
	}

	void colorGraph() {
		
	
		while (isThereUncolorNode()) {
			
			node temp = listHead;
			node currentNode = listHead.next;
			newColor++;
			while (currentNode != null) {
				if (currentNode.color == 0) {
					if (checkAdjacent(currentNode.ID, newColor) == 0) {
						adjacencyMatrix[currentNode.ID][currentNode.ID] = newColor;
						currentNode.color = newColor;
					}
				}
				currentNode = currentNode.next;
			}
			printAdjacencyMatrix();
		}
		finalPrint();
	}
	void finalPrint() {
		outfile1.println("\n\n****************Final Print******************");
		outfile1.println("The total number of colors used were " + newColor);
		printAdjacencyMatrix();
		outfile1.println("Node\tColor");
		node temp = listHead.next;
		while (temp != null) {
			outfile1.println(temp.ID + "\t" +temp.color);
			temp = temp.next;
		}
	}
	
	public static void main(String[] args) {
		try {
			FileReader file = new FileReader(args[0]);
			Scanner infile = new Scanner(file);
			PrintWriter outFile1 = new PrintWriter(new FileWriter(args[1]));
			int numNodes = infile.nextInt();
			graphColoring1 coloring = new graphColoring1(numNodes, outFile1);
			coloring.loadMatrix(infile);
			
			coloring.constructNodeList();
			coloring.colorGraph();
			infile.close();
			file.close();
			outFile1.close();
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}
