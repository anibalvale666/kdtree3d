#ifndef KDTREE_H
#define KDTREE_H

#include "kdtnode.h"
#include "kdtnode.cpp"


template<class T,int K>
class KDTree
{
	public:
		vector<Point<T>> kdt_vect_limits;
		KDTNode<T> *kdt_root;
		unsigned kdt_limit;

		KDTree(vector <Point<T>>, vector <Point<T>>, unsigned);

		bool find(Point<T>);
		bool insert(Point<T>);
		int g_dim;

		//bool compare(Point<T> a, Point<T> b);

		void build(KDTNode<T> * &, vector<Point<T>>, int);
		
		void print();
		void draw(KDTNode<T> *, vector<Point<T>>,int);
		void draw3d(KDTNode<T> *, vector<Point<T>>, int);

		void findByRegion(KDTNode<T> *, vector< Point<T> >, int , vector<Point<T>> &);

};
#endif