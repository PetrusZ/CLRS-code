#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "huffman.h"
#include "pQueue.h"

void traverseTree(htNode *treeNode, hlTable **table, int k, char code[256])
{
	//If we reach the end we introduce the code in the table
    /* 如果抵达了树的叶结点，将码字引入到表中 */
	if(treeNode->left == NULL && treeNode->right == NULL)
	{
		code[k] = '\0';
		hlNode *aux = (hlNode *)malloc(sizeof(hlNode));
		aux->code = (char *)malloc(sizeof(char)*(strlen(code)+1));
		strcpy(aux->code,code);
		aux->symbol = treeNode->symbol;
		aux->next = NULL;
		if((*table)->first == NULL)
		{
			(*table)->first = aux;
			(*table)->last = aux;
		}
		else
		{
			(*table)->last->next = aux;
			(*table)->last = aux;
		}

	}

	//We concatenate a 0 for each step to the left
    /* 每一步转向左孩子的递归都连接一个0到码字中 */
	if(treeNode->left!=NULL)
	{
		code[k]='0';
		traverseTree(treeNode->left,table,k+1,code);

	}
	//We concatenate a 1 for each step to the right
    /* 每一步转向右孩子的递归都连接一个1到码字中 */
	if(treeNode->right!=NULL)
	{
		code[k]='1';
		traverseTree(treeNode->right,table,k+1,code);

	}
}

hlTable * buildTable(htTree * huffmanTree)
{
	//We initialize the table
    /* 初始化表 */
	hlTable *table = (hlTable *)malloc(sizeof(hlTable));
	table->first = NULL;
	table->last = NULL;

	//Auxiliary variables
    /* 辅助变量 */
	char code[256];
	//k will memories the level on which the traversal is
    /* 用k记住便利到了哪一层 */
	int k=0;

	//We traverse the tree and calculate the codes
    /* 遍历树并计算码字 */
	traverseTree(huffmanTree->root,&table,k,code);
	return table;
}

htTree * buildTree(char *inputString)
{
	//The array in which we calculate the frequency of the symbols
	//Knowing that there are only 256 posibilities of combining 8 bits
	//(256 ASCII characters)
    /*
     * probability数组用来计算字符的频率，
     * 一个8位的字符编码只有256种可能性。
     */
	int * probability = (int *)malloc(sizeof(int)*256);

	//We initialize the array
    /* 初始化数组 */
	for(int i=0; i<256; i++)
		probability[i]=0;

	//We consider the symbol as an array index and we calculate how many times each symbol appears
    /* 将字符当作数组的索引并计算每一个字符出现的频率 */
	for(int i=0; inputString[i]!='\0'; i++)
		probability[(unsigned char) inputString[i]]++;

	//The queue which will hold the tree nodes
    /* 队列将持有树的结点 */
	pQueue * huffmanQueue;
	initPQueue(&huffmanQueue);

	//We create nodes for each symbol in the string
    /* 为字符串中的每一个字符都创建一个结点 */
	for(int i=0; i<256; i++)
		if(probability[i]!=0)
		{
			htNode *aux = (htNode *)malloc(sizeof(htNode));
			aux->left = NULL;
			aux->right = NULL;
			aux->symbol = (char) i;

			addPQueue(&huffmanQueue,aux,probability[i]);
		}

	//We free the array because we don't need it anymore
    /* 释放probability数组，因为已经用不到它了 */
	free(probability);

	//We apply the steps described in the article to build the tree
    /* 使用文章中描述的步骤构建二叉数 */
	while(huffmanQueue->size!=1)
	{
		int priority = huffmanQueue->first->priority;
		priority+=huffmanQueue->first->next->priority;

		htNode *left = getPQueue(&huffmanQueue);
		htNode *right = getPQueue(&huffmanQueue);

		htNode *newNode = (htNode *)malloc(sizeof(htNode));
		newNode->left = left;
		newNode->right = right;

		addPQueue(&huffmanQueue,newNode,priority);
	}

	//We create the tree
    /* 创建树 */
	htTree *tree = (htTree *) malloc(sizeof(htTree));

	tree->root = getPQueue(&huffmanQueue);

	return tree;
}

void encode(hlTable *table, char *stringToEncode)
{
	hlNode *traversal;

	printf("\nEncoding\nInput string : %s\nEncoded string : \n",stringToEncode);

	//For each element of the string traverse the table
	//and once we find the symbol we output the code for it
    /*
     * 遍历字符串中的每一个元素(字符)，
     * 一旦在表中找到该字符就输出其码字。
     */
	for(int i=0; stringToEncode[i]!='\0'; i++)
	{
		traversal = table->first;
		while(traversal->symbol != stringToEncode[i])
			traversal = traversal->next;
		printf("%s",traversal->code);
	}

	printf("\n");
}

void decode(htTree *tree, char *stringToDecode)
{
	htNode *traversal = tree->root;

	printf("\nDecoding\nInput string : %s\nDecoded string : \n",stringToDecode);

	//For each "bit" of the string to decode
	//we take a step to the left for 0
	//or ont to the right for 1
    /*
     * 解码字符串中的每一位，
     * 如果这一位是0就转向左孩子，
     * 如果是1就转向右孩子。
     */
	for(int i=0; stringToDecode[i]!='\0'; i++)
	{
		if(traversal->left == NULL && traversal->right == NULL)
		{
			printf("%c",traversal->symbol);
			traversal = tree->root;
		}

		if(stringToDecode[i] == '0')
			traversal = traversal->left;

		if(stringToDecode[i] == '1')
			traversal = traversal->right;

		if(stringToDecode[i]!='0'&&stringToDecode[i]!='1')
		{
			printf("The input string is not coded correctly!\n");
			return;
		}
	}

	if(traversal->left == NULL && traversal->right == NULL)
	{
		printf("%c",traversal->symbol);
		traversal = tree->root;
	}

	printf("\n");
}
