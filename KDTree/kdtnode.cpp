#include "kdtnode.h"

template<class T>
KDTNode<T>::KDTNode()
{
	kdtn_is_leaf = true;
	kdtn_sons[0] = kdtn_sons[1] = NULL;

}