//Source: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
#pragma once
#include <iostream>
#include <queue>
using namespace std;

class HuffmanCoding 
{
	struct MinHeapNode {

		// One of the input characters 
		unsigned char data;

		// Frequency of the character 
		unsigned freq;

		// Left and right child 
		MinHeapNode* left, * right;

		MinHeapNode(unsigned char data, unsigned freq)

		{

			left = right = NULL;
			this->data = data;
			this->freq = freq;
		}
	};

	// For comparison of 
	// two heap nodes (needed in min heap) 
	struct compare {

		bool operator()(MinHeapNode* l, MinHeapNode* r)

		{
			return (l->freq > r->freq);
		}
	};

public:
	static void printCodes(struct MinHeapNode* root, string str);
	static void HuffmanCodes(unsigned char data[], int freq[], int size);
};