import java.io.*;
import java.util.Scanner;

//huffman.java
//Project 3: Huffman Coding. You are to implement the Huffman coding algorithm
//Created by Kevin Reinoso on 12/14/17.
//Copyright © 2017 Kevin Reinoso. All rights reserved.
public class huffman {
	static Scanner inFile;
	static PrintWriter outFile1, outFile2, outFile3, outFile4, outFile5;
	public static class HuffmanLinkedList {
		ListBinTreeNode listHead;
		ListBinTreeNode oldListHead;
		public HuffmanLinkedList() {
			this.listHead = new ListBinTreeNode("dummy", -1);
		}
		public void constructHuffmanLList() {
			String chStr;
			int prob;
			ListBinTreeNode afterMe;
			ListBinTreeNode newNode;
			while (inFile.hasNext()) {
				chStr = inFile.next();
				prob = inFile.nextInt();
				afterMe = findSpot(prob);
				newNode = new ListBinTreeNode(chStr, prob);
				listInsert(afterMe, newNode);
				printList();
			}
			inFile.close();
		}

		public ListBinTreeNode findSpot(int prob) {
			ListBinTreeNode walker = this.listHead;
			if (isEmpty() == true) {
				return walker;
			}
			while (walker.next != null) {
				if (prob > walker.next.prob) {
					walker = walker.next;
				} else {
					break;
				}
			}

			return walker;
		}

		public void listInsert(ListBinTreeNode afterMe, ListBinTreeNode newNode) {
			ListBinTreeNode temp = afterMe.next;
			afterMe.next = newNode;
			newNode.next = temp;
		}

		public boolean isEmpty() {
			if (this.listHead.next == null) {
				return true;
			} else {
				return false;
			}
		}

		public void printList() {
			ListBinTreeNode walker = listHead.next;
			while (walker != null) {
				outFile5.print(walker.chStr + " " + walker.prob + " -> ");
				walker = walker.next;
			}
			outFile5.println();
		}
		ListBinTreeNode getListHead() {
			return listHead;
		}
		public void setOldListHead() {
			this.oldListHead = new ListBinTreeNode("binDummy", -1);
			oldListHead.next = this.listHead.next;
		}
	}
	public static class ListBinTreeNode {
		String chStr;
		int prob;
		ListBinTreeNode next;
		ListBinTreeNode left;
		ListBinTreeNode right;

		public ListBinTreeNode(String chStr, int prob) {
			this.chStr = chStr;
			this.prob = prob;
			this.next = null;
			this.left = null;
			this.right = null;
		}

		public String printNode() {
			return (this.chStr + " " + this.prob + " " + left.chStr + " " + this.right.chStr + " ");
		}
	}
	public static class HuffmanBinaryTree {
		ListBinTreeNode root;

		public HuffmanBinaryTree() {
			root = null;
		}

		public ListBinTreeNode constructHuffmanBinTree(HuffmanLinkedList myList) {
			myList.setOldListHead();
			ListBinTreeNode tree = myList.getListHead();
			ListBinTreeNode newNode;

			while (tree.next.next != null) {
				newNode = new ListBinTreeNode(tree.next.chStr + tree.next.next.chStr,
						tree.next.prob + tree.next.next.prob);

				newNode.left = tree.next;
				newNode.right = tree.next.next;

				tree.next = tree.next.next.next;

				outFile5.println(newNode.printNode());

				ListBinTreeNode afterMe = myList.findSpot(newNode.prob);
				myList.listInsert(afterMe, newNode);

				this.root = newNode;
			}
			return root;
		}

		public void preOrderTraversal(ListBinTreeNode node) {
			if (node == null) {
				return;
			} else {
				outFile2.print(node.chStr + " " + node.prob + " -> ");
				preOrderTraversal(node.left);
				preOrderTraversal(node.right);
			}
		}

		public void inOrderTraversal(ListBinTreeNode node) {
			if (node == null) {
				return;
			} else {
				inOrderTraversal(node.left);
				outFile3.print(node.chStr + " " + node.prob + " -> ");
				inOrderTraversal(node.right);
			}
		}

		public void postOrderTraversal(ListBinTreeNode node) {
			if (node == null) {
				return;
			} else {
				postOrderTraversal(node.left);
				postOrderTraversal(node.right);
				outFile4.print(node.chStr + " " + node.prob + " -> ");
			}
		}

		public boolean isLeaf(ListBinTreeNode node) {
			if ((node.left == null) && (node.right == null)) {
				return true;
			}
			return false;
		}

		public void constructCharCode(ListBinTreeNode node, String code) {
			if (node == null) {
				System.out.println("This is an empty tree.");
				System.exit(0);
			} else if (isLeaf(node) == true) {
				outFile1.print(node.chStr + " ");
				outFile1.println(code);
			} else {
				constructCharCode(node.left, code + "0");
				constructCharCode(node.right, code + "1");
			}
		}
	}
	public static void main(String[] args) {
		try {
			inFile = new Scanner(new FileReader(args[0]));
			outFile1 = new PrintWriter(args[1]);
			outFile2 = new PrintWriter(args[2]);
			outFile3 = new PrintWriter(args[3]);
			outFile4 = new PrintWriter(args[4]);
			outFile5 = new PrintWriter(args[5]);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		HuffmanLinkedList huffman = new HuffmanLinkedList();
		huffman.constructHuffmanLList();
		HuffmanBinaryTree tree = new HuffmanBinaryTree();
		ListBinTreeNode root = tree.constructHuffmanBinTree(huffman);
		tree.constructCharCode(root, "");
		tree.preOrderTraversal(root);
		tree.inOrderTraversal(root);
		tree.postOrderTraversal(root);

		inFile.close();
		outFile1.close();
		outFile2.close();
		outFile3.close();
		outFile4.close();
		outFile5.close();
	}
}
