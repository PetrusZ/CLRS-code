#pragma once
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

//The Huffman tree node definition
/* 赫夫曼树结点定义 */
typedef struct _htNode {
	char symbol;
	struct _htNode *left, *right;
}htNode;

/*
	We "encapsulate(封装)" the entire tree in a structure
	because in the future we might add fields like "size"
	if we need to. This way we don't have to modify the entire
	source code.
    封装整棵树，以便在未来需要扩展的时候，不必修改整个原代码
*/
typedef struct _htTree {
	htNode *root;
}htTree;

//The Huffman table nodes (linked list implementation)
/* 赫夫曼码字表结点(链表实现) */
typedef struct _hlNode {
	char symbol;
	char *code;
	struct _hlNode *next;
}hlNode;

//Incapsularea listei
/* 罗马尼亚语？！封装列表 */
typedef struct _hlTable {
	hlNode *first;
	hlNode *last;
}hlTable;

htTree * buildTree(char *inputString);
hlTable * buildTable(htTree *huffmanTree);
void encode(hlTable *table, char *stringToEncode);
void decode(htTree *tree, char *stringToDecode);

#endif
