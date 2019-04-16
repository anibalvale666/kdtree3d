#include "kdtree.h"
#include<GL/glut.h>
#include <algorithm>


template<class T,int K>
KDTree<T, K>::KDTree(vector <Point<T>> arr_points, vector<Point<T>> limits, unsigned l)
{
	kdt_root = NULL;
	kdt_limit = l;
	kdt_vect_limits = limits;
	// llamo a insertar
	build(kdt_root, arr_points,0);
}



template<class T,int K>
 void KDTree<T,K>::build(KDTNode<T> * &act, vector <Point<T>> arr_points,int dim)
{
	act = new KDTNode<T>();
	if (arr_points.size() <= kdt_limit)
	{
		act->kdtn_points = arr_points;
		return;
	}
	g_dim = dim;
	sort(arr_points.begin(), arr_points.end(),  [dim](Point<T> a, Point<T> b) {return (a.p_coords[dim] < b.p_coords[dim]);});
	
	act->kdtn_is_leaf = false;
	int mid = arr_points.size() / 2;
	act->kdtn_split_dim = arr_points[mid].p_coords[dim];
	
	if (dim == K - 1)
		dim = 0;
	else
		dim++;

	build(act->kdtn_sons[0], vector<Point<T>>(arr_points.begin(), arr_points.begin() + mid),dim);
	build(act->kdtn_sons[1], vector<Point<T>>(arr_points.begin() + mid + 1, arr_points.end()),dim);

}

template<class T,int K>
void KDTree<T,K>::draw(KDTNode<T> *act, vector<Point<T>> limits,int dim)
{
	if (!act)
	{
		return;
	}
	if (act->kdtn_is_leaf)
	{
		for (unsigned i = 0; i < act->kdtn_points.size(); i++)
		{
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glColor3f(0, 0, 255);
			glVertex2d(act->kdtn_points[i].p_coords[0], act->kdtn_points[i].p_coords[1]);
			glEnd();
		}
		
		return;
	}

	vector<Point<T>> vl;
	vector<Point<T>> vr;

	if (dim == 0)
	{
		dim = 1;
		glBegin(GL_LINES);
		glColor3d(255, 0, 0);
		glVertex2d(act->kdtn_split_dim, limits[1].p_coords[0]);
		glVertex2d(act->kdtn_split_dim, limits[1].p_coords[1]);
		glEnd();

		vl.push_back(Point<T>(act->kdtn_split_dim, limits[0].p_coords[1]));
		vr.push_back(Point<T>(limits[0].p_coords[0], act->kdtn_split_dim));

		vl.push_back(limits[1]);
		vr.push_back(limits[1]);
	}
	else
	{
		dim = 0;
		glBegin(GL_LINES);
		glColor3d(255, 0, 0);
		glVertex2d(limits[0].p_coords[0], act->kdtn_split_dim);
		glVertex2d(limits[0].p_coords[1], act->kdtn_split_dim);
		glEnd();

		vl.push_back(limits[0]);
		vr.push_back(limits[0]);
		vl.push_back(Point<T>(act->kdtn_split_dim, limits[1].p_coords[1]));
		vr.push_back(Point<T>(limits[1].p_coords[0], act->kdtn_split_dim));
	}
	

		 

	draw(act->kdtn_sons[0],vl,dim);
	draw(act->kdtn_sons[1],vr,dim);

}


template<class T, int K>
void KDTree<T, K>::draw3d(KDTNode<T> *act, vector<Point<T>> limits, int dim)
{
	if (!act)
	{
		return;
	}
	if (act->kdtn_is_leaf)
	{
		for (unsigned i = 0; i < act->kdtn_points.size(); i++)
		{
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glColor3f(0, 0, 255);
			glVertex3d(act->kdtn_points[i].p_coords[0], act->kdtn_points[i].p_coords[1],act->kdtn_points[i].p_coords[2]);
			glEnd();
		}

		return;
	}

	vector<Point<T>> vl;
	vector<Point<T>> vr;

	if (dim == 0)
	{
		dim = 1;
		glBegin(GL_LINES);
		glColor3d(255, 0, 0);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[0], limits[2].p_coords[0]);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[1], limits[2].p_coords[0]);

		glColor3d(255, 0, 0);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[0], limits[2].p_coords[1]);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[1], limits[2].p_coords[1]);

		glColor3d(255, 0, 0);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[0], limits[2].p_coords[0]);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[0], limits[2].p_coords[1]);

		glColor3d(255, 0, 0);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[1], limits[2].p_coords[0]);
		glVertex3d(act->kdtn_split_dim, limits[1].p_coords[1], limits[2].p_coords[1]);

		glEnd();

		vl.push_back(Point<T>(act->kdtn_split_dim, limits[0].p_coords[1]));
		vr.push_back(Point<T>(limits[0].p_coords[0], act->kdtn_split_dim));

		vl.push_back(limits[1]);
		vr.push_back(limits[1]);

		vl.push_back(limits[2]);
		vr.push_back(limits[2]);

	}
	else if(dim == 1)
	{
		dim = 2;
		glBegin(GL_LINES);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[0], act->kdtn_split_dim, limits[2].p_coords[0]);
		glVertex3d(limits[0].p_coords[1], act->kdtn_split_dim, limits[2].p_coords[0]);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[0], act->kdtn_split_dim, limits[2].p_coords[1]);
		glVertex3d(limits[0].p_coords[1], act->kdtn_split_dim, limits[2].p_coords[1]);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[0], act->kdtn_split_dim, limits[2].p_coords[0]);
		glVertex3d(limits[0].p_coords[0], act->kdtn_split_dim, limits[2].p_coords[1]);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[1], act->kdtn_split_dim, limits[2].p_coords[0]);
		glVertex3d(limits[0].p_coords[1], act->kdtn_split_dim, limits[2].p_coords[1]);
		glEnd();

		vl.push_back(limits[0]);
		vr.push_back(limits[0]);
		vl.push_back(Point<T>(act->kdtn_split_dim, limits[1].p_coords[1]));
		vr.push_back(Point<T>(limits[1].p_coords[0], act->kdtn_split_dim));
		vl.push_back(limits[2]);
		vr.push_back(limits[2]);
	}
	else
	{
		dim = 0;
		glBegin(GL_LINES);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[0], limits[1].p_coords[0], act->kdtn_split_dim);
		glVertex3d(limits[0].p_coords[1], limits[1].p_coords[0], act->kdtn_split_dim);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[0], limits[1].p_coords[1], act->kdtn_split_dim);
		glVertex3d(limits[0].p_coords[1], limits[1].p_coords[1], act->kdtn_split_dim);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[0], limits[1].p_coords[0], act->kdtn_split_dim);
		glVertex3d(limits[0].p_coords[0], limits[1].p_coords[1], act->kdtn_split_dim);
		glColor3d(255, 0, 0);
		glVertex3d(limits[0].p_coords[1], limits[1].p_coords[0], act->kdtn_split_dim);
		glVertex3d(limits[0].p_coords[1], limits[1].p_coords[1], act->kdtn_split_dim);
		glEnd();

		vl.push_back(limits[0]);
		vr.push_back(limits[0]);
		vl.push_back(limits[1]);
		vr.push_back(limits[1]);
		vl.push_back(Point<T>(act->kdtn_split_dim, limits[2].p_coords[1]));
		vr.push_back(Point<T>(limits[2].p_coords[0], act->kdtn_split_dim));
	}




	draw3d(act->kdtn_sons[0], vl, dim);
	draw3d(act->kdtn_sons[1], vr, dim);

}

template<class T, int K>
bool KDTree<T, K>::find(Point<T> x)
{
	KDTNode<T> *p;
	int dim = 0;
	for (p = kdt_root; !p->kdtn_is_leaf; p = p->kdtn_sons[x.p_coords[dim] > p->kdtn_split_dim]);

	for (int i = 0; i < p->kdtn_points.size(); i++)
		if (x.p_coords[0] == p->kdtn_points[i].p_coords[0] and x.p_coords[1] == p->kdtn_points[i].p_coords[1] and x.p_coords[2] == p->kdtn_points[i].p_coords[2]) return true;
	
	return false;
}

template<class T, int K>
void KDTree<T, K>::findByRegion(KDTNode<T> *act, vector< Point<T> >limits, int dim, vector<Point<T>> &vect_points)
{
	/*
	if (!act)
	{
		return;
	}
	if (act->kdtn_is_leaf)
	{
		for (unsigned i = 0; i < act->kdtn_points.size(); i++)
		{
			if (p->kdtn_points[i].p_coords[0] <= limits[0].p_coords[0] and p->kdtn_points[i].p_coords[0] >= limits[0].p_coords[1] and
				p->kdtn_points[i].p_coords[1] <= limits[1].p_coords[0] and p->kdtn_points[i].p_coords[1] >= limits[1].p_coords[1] and
				p->kdtn_points[i].p_coords[2] <= limits[2].p_coords[0] and p->kdtn_points[i].p_coords[2] >= limits[2].p_coords[1] )
				vect_points.push_back(act->kdtn_points[i]);
		}

		return;
	}

	vector<Point<T>> vl;
	vector<Point<T>> vr;

	if (dim == 0)
	{
		dim = 1;


		vl.push_back(Point<T>(act->kdtn_split_dim, limits[0].p_coords[1]));
		vr.push_back(Point<T>(limits[0].p_coords[0], act->kdtn_split_dim));

		vl.push_back(limits[1]);
		vr.push_back(limits[1]);

		vl.push_back(limits[2]);
		vr.push_back(limits[2]);

	}
	else if (dim == 1)
	{
		dim = 2;

		vl.push_back(limits[0]);
		vr.push_back(limits[0]);
		vl.push_back(Point<T>(act->kdtn_split_dim, limits[1].p_coords[1]));
		vr.push_back(Point<T>(limits[1].p_coords[0], act->kdtn_split_dim));
		vl.push_back(limits[2]);
		vr.push_back(limits[2]);
	}
	else
	{
		dim = 0;


		vl.push_back(limits[0]);
		vr.push_back(limits[0]);
		vl.push_back(limits[1]);
		vr.push_back(limits[1]);
		vl.push_back(Point<T>(act->kdtn_split_dim, limits[2].p_coords[1]));
		vr.push_back(Point<T>(limits[2].p_coords[0], act->kdtn_split_dim));
	}




	findByRegion(act->kdtn_sons[0], vl, dim, vect_points);
	findByRegion(act->kdtn_sons[1], vr, dim,v ect_points);*/
}