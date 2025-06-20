#ifndef Node_type
#define Node_type

#include "BTNode.hpp"

using type2 = BTNode *;

struct Node {
	
		type2		item;
		Node	*next;
		Node(type2);
};


#endif