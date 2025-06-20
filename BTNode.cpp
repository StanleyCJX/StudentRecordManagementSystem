#include <iostream>
#include "BTNode.hpp"

using namespace std;

BTNode::BTNode(type newItem) {
	item = newItem;
	left = right = NULL;
}
