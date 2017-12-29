//
// main.cpp
//huffman.java
//Project 3: Huffman Coding. You are to implement the Huffman coding algorithm
//Created by Kevin Reinoso on 12/14/17.
//Copyright © 2017 Kevin Reinoso. All rights reserved.
//

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
    
    static ifstream inFile;
    static ofstream outFile1, outFile2, outFile3, outFile4, outFile5;
    
    class ListBinTreeNode {
        public:
        string chStr;
        int prob;
        ListBinTreeNode* next;
        ListBinTreeNode* left;
        ListBinTreeNode* right;
        
        ListBinTreeNode(string chStr, int prob) {
            this->chStr = chStr;
            this->prob = prob;
            this->next = NULL;
            this->left = NULL;
            this->right = NULL;
        }
        
        string printNode() {
            string temp=chStr + " " + to_string(prob) + " " + left->chStr + " " +right->chStr + " ";
            return temp;
        }
    };
    
    class HuffmanLinkedList {
        public:
        ListBinTreeNode* listHead;
        ListBinTreeNode* oldListHead;
        HuffmanLinkedList() {
            this->listHead = new ListBinTreeNode("dummy", -1);
        }
        void constructHuffmanLList() {
            string chStr;
            int prob;
            ListBinTreeNode* afterMe;
            ListBinTreeNode* newNode;
            while(inFile){
                inFile>>chStr;
                inFile>>prob;
                afterMe = findSpot(prob);
                newNode = new ListBinTreeNode(chStr, prob);
                listInsert(afterMe, newNode);
                printList();
            }
            inFile.close();
        }
        
        ListBinTreeNode* findSpot(int prob) {
            ListBinTreeNode* walker = this->listHead;
            if (isEmpty() == true) {
                return walker;
            }
            while (walker->next != NULL) {
                if (prob > walker->next->prob) {
                    walker = walker->next;
                } else {
                    break;
                }
            }
            
            return walker;
        }
        
        void listInsert(ListBinTreeNode* afterMe, ListBinTreeNode* newNode) {
            ListBinTreeNode* temp = afterMe->next;
            afterMe->next = newNode;
            newNode->next = temp;
        }
        
        bool isEmpty() {
            if (this->listHead->next == NULL) {
                return true;
            } else {
                return false;
            }
        }
        
        void printList() {
            ListBinTreeNode* walker = listHead->next;
            while (walker != NULL) {
                outFile5<<walker->chStr << " " << walker->prob << " -> ";
                walker = walker->next;
            }
            outFile5<<endl;
        }
        ListBinTreeNode* getListHead() {
            return listHead;
        }
        void setOldListHead() {
            this->oldListHead = new ListBinTreeNode("binDummy", -1);
            oldListHead->next = this->listHead->next;
        }
    };
    
    class HuffmanBinaryTree {
        public:
        ListBinTreeNode* root;
        
        HuffmanBinaryTree() {
            root = NULL;
        }
        
        ListBinTreeNode* constructHuffmanBinTree(HuffmanLinkedList *myList) {
            myList->setOldListHead();
            ListBinTreeNode* tree = myList->getListHead();
            ListBinTreeNode* newNode;
            
            while (tree->next->next != NULL) {
                newNode = new ListBinTreeNode(tree->next->chStr + tree->next->next->chStr,
                                               tree->next->prob + tree->next->next->prob);
                
                newNode->left = tree->next;
                newNode->right = tree->next->next;
                
                tree->next = tree->next->next->next;
                
                outFile5<<newNode->printNode()<<endl;
                
                ListBinTreeNode* afterMe = myList->findSpot(newNode->prob);
                myList->listInsert(afterMe, newNode);
                
                this->root = newNode;
            }
            return root;
        }
        
        void preOrderTraversal(ListBinTreeNode* node) {
            if (node == NULL) {
                return;
            } else {
                outFile2<<node->chStr<< " " << node->prob << " -> ";
                preOrderTraversal(node->left);
                preOrderTraversal(node->right);
            }
            
        }
        
        void inOrderTraversal(ListBinTreeNode* node) {
            if (node == NULL) {
                return;
            } else {
                inOrderTraversal(node->left);
                outFile3<<node->chStr << " " << node->prob << " -> ";
                inOrderTraversal(node->right);
            }
        }
        
        void postOrderTraversal(ListBinTreeNode* node) {
            if (node == NULL) {
                return;
            } else {
                postOrderTraversal(node->left);
                postOrderTraversal(node->right);
                outFile4<<node->chStr << " " <<node->prob << " -> ";
            }
        }
        
        bool isLeaf(ListBinTreeNode* node) {
            if ((node->left == NULL) && (node->right == NULL)) {
                return true;
            }
            return false;
        }
        
        void constructCharCode(ListBinTreeNode* node, string code) {
            if (node == NULL) {
               cout<<"This is an empty tree.";
                return;
            } else if (isLeaf(node) == true) {
                outFile1<<node->chStr <<" ";
                outFile1<<code<<endl;
            } else {
                constructCharCode(node->left, code + "0");
                constructCharCode(node->right, code + "1");
            }
        }
    };
    
    try {
        inFile.open(argv[1]);
        outFile1.open(argv[2]);
        outFile2.open(argv[3]);
        outFile3.open(argv[4]);
        outFile4.open(argv[5]);
        outFile5.open(argv[6]);
    } catch (exception e) {
        cout<<&e<<endl;
    }
    
    HuffmanLinkedList* huffman = new HuffmanLinkedList();
    huffman->constructHuffmanLList();
    HuffmanBinaryTree *tree = new HuffmanBinaryTree();
    ListBinTreeNode* root = tree->constructHuffmanBinTree(huffman);
    
    tree->constructCharCode(root, "");
    tree->preOrderTraversal(root);
    tree->inOrderTraversal(root);
    tree->postOrderTraversal(root);
    
    inFile.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();
    outFile4.close();
    outFile5.close();
    return 0;
}
