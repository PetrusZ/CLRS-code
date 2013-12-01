#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
	//We build the tree depending on the string(根据字符串构建二叉树)
	htTree *codeTree = buildTree("beep boop beer!");
	//We build the table depending on the Huffman tree(根据二叉树构建码字表)
	hlTable *codeTable = buildTable(codeTree);

	//We encode using the Huffman table(使用码字表编码)
	encode(codeTable,"beep boop beer!");
	//We decode using the Huffman tree(使用二叉树树解码)
	//We can decode string that only use symbols from the initial string(仅使用初始的字符串中的字符来解码)
	/* decode(codeTree,"0011111000111"); */
	decode(codeTree,"0011111010110001001010101100111110001001");
	//Output : 0011 1110 1011 0001 0010 1010 1100 1111 1000 1001
	return 0;
}
