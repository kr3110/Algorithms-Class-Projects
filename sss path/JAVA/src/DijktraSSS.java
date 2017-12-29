//
//  DijktraSSS.Java
//  sss path
//  Dijkstra’s algorithm for the Single-Source-Shortest Paths problem
//  Created by Kevin Reinoso on 11/8/17.
//  Copyright © 2017 Kevin Reinoso. All rights reserved.
//

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class DijktraSSS {

	int numNodes; // number of nodes in G
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;

	int[][] costMatrix;
	int[] fatherAry;
	int[] toDoAry;
	int[] bestCostAry;

	public DijktraSSS(int num, int source) {
		this.numNodes = num;
		this.sourceNode = source;
		costMatrix = new int[numNodes + 1][numNodes + 1];
		for (int i = 0; i <= numNodes; i++) {
			for (int j = 0; j <= numNodes; j++) {
				if (i == j)
					costMatrix[i][i] = 0;
				else
					costMatrix[i][j] = 99999;
			}
		}
		fatherAry = new int[numNodes + 1];
		for (int i = 0; i <= numNodes; i++) {
			fatherAry[i] = i;
		}
		toDoAry = new int[numNodes + 1];
		for (int i = 0; i <= numNodes; i++) {
			toDoAry[i] = 1;
		}
		bestCostAry = new int[numNodes + 1];
		for (int i = 0; i <= numNodes; i++) {
			bestCostAry[i] = i;
		}
	}

	void loadCostMatrix(Scanner inFile) {
		int from, dest, cost;
		while (inFile.hasNext()) {
			from = inFile.nextInt();
			dest = inFile.nextInt();
			cost = inFile.nextInt();
			costMatrix[from][dest] = cost;
		}

	}

	void setBestCostAry(int sourceNode) {
		for (int i = 1; i <= numNodes; i++)
			bestCostAry[i] = costMatrix[sourceNode][i];
	}

	void setFatherAry(int sourceNode) {
		for (int i = 0; i <= numNodes; i++)
			fatherAry[i] = sourceNode;
	}

	void setToDoAry(int sourceNode) {
		for (int i = 0; i <= numNodes; i++)
			toDoAry[i] = 1;
		toDoAry[sourceNode] = 0;
	}

	int findMinNode() {
		int cost = 99999, minNode = -1;
		for (int i = 0; i <= numNodes; i++) {
			if (toDoAry[i] == 1) {
				if (bestCostAry[i] < cost) {
					cost = bestCostAry[i];
					minNode = i;
				}
			}
		}
		return minNode;
	}

	int computeCost(int minNode, int currentNode) {
		return bestCostAry[minNode] + costMatrix[minNode][currentNode];
	}

	void markMinNode(int minNode) {
		toDoAry[minNode] = 0;
	}

	void changeFather(int node, int minNode) {
		fatherAry[node] = minNode;
	}

	void changeCost(int node, int newCost) {
		bestCostAry[node] = newCost;
	}

	void debugPrint(PrintWriter outFile2) {
		outFile2.println("The sourceNode is: " + sourceNode + "\n");
		outFile2.println("The father Array is: ");
		for (int i = 0; i <= numNodes; i++) {
			outFile2.print(" | " + fatherAry[i]);
		}
		outFile2.println("The best Cost Array is: ");
		for (int i = 0; i <= numNodes; i++) {
			outFile2.print(" | " + bestCostAry[i]);
		}
		outFile2.println("The To do Ary is: ");
		for (int i = 0; i <= numNodes; i++) {
			outFile2.print(" | " + toDoAry[i]);
		}
		outFile2.println();
	}

	void printShortestPaths(int current, PrintWriter outFile1) {
		int index = 1;
		int counter = 1;
		int[] temp = new int[numNodes];
		temp[0] = current;
		while (fatherAry[current] != sourceNode) {
			temp[index] = fatherAry[current];
			current = fatherAry[current];
			counter++;
			index++;
		}
		temp[index] = sourceNode;
		counter++;
		
		outFile1.print("The path from " + sourceNode + " to " + temp[0] + " is: " + temp[0]);
		for (int i = 1; i < counter; i++) {
			outFile1.print("<-" + temp[i]);
		}
		if (counter < 3) {
			outFile1.print("\t");
		}
		outFile1.print("\tcost:" + bestCostAry[temp[0]] + "\n");
	}

	boolean isDone() {
		for (int i = 0; i <= numNodes; i++)
			if (toDoAry[i] == 1)
				return false;
		return true;
	}

	void Dijkstras(PrintWriter outFile1, PrintWriter outFile2) {
		// step 2
		setBestCostAry(sourceNode);
		setFatherAry(sourceNode);
		setToDoAry(sourceNode);
		while (!isDone()) {
			minNode = findMinNode();
			markMinNode(minNode);
			debugPrint(outFile2);
			currentNode = 1;

			while (currentNode <= numNodes) {
				if (toDoAry[currentNode] == 1) {
					newCost = computeCost(minNode, currentNode);
					if (newCost < bestCostAry[currentNode]) {
						changeCost(currentNode, newCost);
						changeFather(currentNode, minNode);
						debugPrint(outFile2);
					}
				}
				currentNode++;
			}
		}
		currentNode = 1;
		outFile1.println("The sourceNode is: " + sourceNode);
		while (currentNode <= numNodes) {
			printShortestPaths(currentNode, outFile1);
			currentNode++;
		}

	}

	public static void main(String argv[]) throws IOException {

		Scanner inFile;
		inFile = new Scanner(new FileReader(argv[0]));
		PrintWriter outFile1 = new PrintWriter(new FileWriter(argv[1]));
		PrintWriter outFile2 = new PrintWriter(new FileWriter(argv[2]));
		
		int numNodes, sourceNode;
		numNodes = inFile.nextInt();
		sourceNode = inFile.nextInt();
		DijktraSSS sss = new DijktraSSS(numNodes, sourceNode);
		sss.loadCostMatrix(inFile);
		sss.Dijkstras(outFile1, outFile2);
		inFile.close();
		outFile1.close();
		outFile2.close();

	}

}
