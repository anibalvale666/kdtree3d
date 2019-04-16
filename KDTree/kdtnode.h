#ifndef KDTNODE_H
#define KDTNODE_H

#include <vector>
#include "point.h"
#include "point.cpp"

template<class T>
class KDTNode
{
public:
	vector<Point<T>> kdtn_points;
	double kdtn_split_dim;
	bool kdtn_is_leaf;
	KDTNode<T> *kdtn_sons[2];
	
	KDTNode( );
};


#endif
