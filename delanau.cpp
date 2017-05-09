#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <malloc.h>
#include "functions.h"
#include <algorithm>

using namespace std;

int compare_x(const void* x1, const void* x2)	//сomparison function for a function qsort that sorts the structure pointgroup along the x axis
{	
	double t;
	t = ((**(point**)x1).x - (**(point**)x2).x);
	if (t > 0) return 1;
	else if (t==0) return 0;
	else return -1;
}

int compare_y(const void* x1, const void* x2)	//сomparison function for a function qsort that sorts the structure pointgroup along the x axis
{
	double t;
	t = ((**(point**)x1).y - (**(point**)x2).y);
	if (t > 0) return 1;
	else if (t==0) return 0;
	else return -1;
}

line line_by_points(point* t_1, point* t_2)	//builds a line on two points
{
	line line_t;
	line_t.k = (((*t_2).y)-((*t_1).y))/(((*t_2).x)-((*t_1).x));
	line_t.b = (*t_1).y - (line_t.k)*((*t_1).x);
	return(line_t);
}

int diagonal(point* p0, point* p1, point* p2, point* p3)	//checks whether the line is diagonal
{	
	line line_t;
	line_t = line_by_points(p0, p1);
	if ((((*p2).y-line_t.k*(*p2).x-line_t.b)*((*p3).y-line_t.k*(*p3).x-line_t.b))<0) return(1);
	else return(0); 
}

int is_it_type_1(point* p0, point* p1, point* p2, point* p3)	//сhecks whether this triangulation consists of 3 triangles
{
	int tx, ty, i;                                                
	int x0 = (*p0).x;
	int x1 = (*p1).x;
	int x2 = (*p2).x;
	int x3 = (*p3).x;
	int y0 = (*p0).y;
	int y1 = (*p1).y;
	int y2 = (*p2).y;
	int y3 = (*p3).y;

	for (i=0; i<4; i++)
	{

		if (i==1) {tx=x0; ty=y0; x0=x1; y0=y1; x1=tx; y1=ty;}
		else if (i==2) {tx=x0; ty=y0; x0=x2; y0=y2; x2=tx; y2=ty;}
		else {tx=x0; ty=y0; x0=x3; y0=y3; x3=tx; y3=ty;} 

		if 
		( 
		     ( (((x1-x0)*(y2-y1)-(x2-x1)*(y1-y0))>0) and 
		       (((x2-x0)*(y3-y2)-(x3-x2)*(y2-y0))>0) and 
		       (((x3-x0)*(y1-y3)-(x1-x3)*(y3-y0))>0) 
		     ) or

		     ( (((x1-x0)*(y2-y1)-(x2-x1)*(y1-y0))<0) and 
		       (((x2-x0)*(y3-y2)-(x3-x2)*(y2-y0))<0) and 
		       (((x3-x0)*(y1-y3)-(x1-x3)*(y3-y0))<0) 
		     ) 
		)
		return(i);

	}

	return(4);
}

int delanau(point* p1, point* p2, point* p3, point* p4)		//checks whether triangulation of 3 triangles is a Delaunay triangulation
{
	double x1 = (*p1).x, y1 = (*p1).y;
	double x2 = (*p2).x, y2 = (*p2).y;
	double x3 = (*p3).x, y3 = (*p3).y;
	double x = (*p4).x, y = (*p4).y;
	double a = x1*(y2-y3) - y1*(x2-x3) + (x2*y3-x3*y2);
	double b = (x1*x1+y1*y1)*(y2-y3) - y1*(x2*x2+y2*y2-x3*x3-y3*y3) + (x2*x2+y2*y2)*y3 - y2*(x3*x3+y3*y3);
	double c = (x1*x1+y1*y1)*(x2-x3) - x1*(x2*x2+y2*y2-x3*x3-y3*y3) + (x2*x2+y2*y2)*x3 - x2*(x3*x3+y3*y3);
	double d = (x1*x1+y1*y1)*(x2*y3-x3*y2) - x1*((x2*x2+y2*y2)*y3 - y2*(x3*x3+y3*y3)) + y1*((x2*x2+y2*y2)*x3-x2*(x3*x3+y3*y3));
	double ans = (a*(x*x+y*y)-b*x+c*y-d)*a;

	if (ans>=0) return(1);
	else return(0);
}


void starting_triangulate(vector <triangle>* p_tr, vector <point_group>* p_vect, int num)	//Performs a triangulation of a 
												//group of points of 3 or 4 points
{
	int kolvo = (*p_vect)[num].amount;
	triangle triangle_t;
	int i;
	line line_t[5];

	if (kolvo == 3) 
	{
		cout << "triangulation type =-1" << endl;
		for (i=0; i<3; i++) triangle_t.uzel[i] = (*p_vect)[num].mass[i]; 
		triangle_t.trian[i] = NULL;
		(*p_tr).push_back(triangle_t);
		tr_pointer++;
		(*p_vect)[num].triang[0] = tr_pointer-1;
		(*p_vect)[num].tr_amount = 1;
	}

	else if (kolvo == 4) 	//ТУТ НАДО ИСПРАВИТЬ
	{	
		int k=is_it_type_1((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3]);
		cout << "triangulation type =" << k << endl;
		if (k==0) 
		{ 
			triangle_t.uzel[0]=(*p_vect)[num].mass[0];
			triangle_t.uzel[1]=(*p_vect)[num].mass[1];
			triangle_t.uzel[2]=(*p_vect)[num].mass[2];
			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
			(*p_tr).push_back(triangle_t);
			tr_pointer+=3;
			(*p_vect)[num].triang[0] = tr_pointer-3;
			(*p_vect)[num].tr_amount = 3;
			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
			(*p_tr).push_back(triangle_t);
			(*p_vect)[num].triang[1] = tr_pointer-2;
			triangle_t.uzel[1]=(*p_vect)[num].mass[2];
			(*p_tr).push_back(triangle_t); 
			(*p_vect)[num].triang[2] = tr_pointer-3;
		}

		else if (k==1) 
		{
			triangle_t.uzel[0]=(*p_vect)[num].mass[1];
			triangle_t.uzel[1]=(*p_vect)[num].mass[0];
			triangle_t.uzel[2]=(*p_vect)[num].mass[2];
			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
			(*p_tr).push_back(triangle_t); 
			tr_pointer+=3;
			(*p_vect)[num].triang[0] = tr_pointer-3;
			(*p_vect)[num].tr_amount = 3;
			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
			(*p_tr).push_back(triangle_t); 
			(*p_vect)[num].triang[1] = tr_pointer-2;
			triangle_t.uzel[1]=(*p_vect)[num].mass[2];
			(*p_tr).push_back(triangle_t); 
			(*p_vect)[num].triang[2] = tr_pointer-3;
		}

		else if (k==2) 
		{
			triangle_t.uzel[0]=(*p_vect)[num].mass[2];
			triangle_t.uzel[1]=(*p_vect)[num].mass[0];
			triangle_t.uzel[2]=(*p_vect)[num].mass[1];
			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
			(*p_tr).push_back(triangle_t); 
			tr_pointer+=3;
			(*p_vect)[num].triang[0] = tr_pointer-3;
			(*p_vect)[num].tr_amount = 3;
			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
			(*p_tr).push_back(triangle_t); 
			(*p_vect)[num].triang[1] = tr_pointer-2;
			triangle_t.uzel[1]=(*p_vect)[num].mass[1];
			(*p_tr).push_back(triangle_t); 
			(*p_vect)[num].triang[2] = tr_pointer-1;
		}

		else if (k==3)
		{
			triangle_t.uzel[0]=(*p_vect)[num].mass[3];
			triangle_t.uzel[1]=(*p_vect)[num].mass[0];
			triangle_t.uzel[2]=(*p_vect)[num].mass[1];
			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
			(*p_tr).push_back(triangle_t); 
			tr_pointer+=3;
			(*p_vect)[num].triang[0] = tr_pointer-3;
			(*p_vect)[num].tr_amount = 3;
			triangle_t.uzel[2]=(*p_vect)[num].mass[2];
			(*p_tr).push_back(triangle_t); 
			(*p_vect)[num].triang[1] = tr_pointer-2;
			triangle_t.uzel[1]=(*p_vect)[num].mass[1];
			(*p_tr).push_back(triangle_t); 
			(*p_vect)[num].triang[2] = tr_pointer-1;
		}

		else if (k==4){
		   if (diagonal((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3])==1) 
		   {
		
			if ((delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3])==1) and
	    	    	(delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[3], (*p_vect)[num].mass[2])==1))
			{
				cout << "___1___" << endl;
				triangle_t.uzel[0]=(*p_vect)[num].mass[0];
				triangle_t.uzel[1]=(*p_vect)[num].mass[2];
				triangle_t.uzel[2]=(*p_vect)[num].mass[1];
				for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
				(*p_tr).push_back(triangle_t);
				tr_pointer+=2;
				(*p_vect)[num].triang[0] = tr_pointer-2;
				(*p_vect)[num].tr_amount = 2;
				triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[1];
				for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				(*p_vect)[num].triang[1] = tr_pointer-1;
			}	

			else
			{
				cout << "___2___" << endl;
				triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				tr_pointer+=2;
        			(*p_vect)[num].triang[0] = tr_pointer-2;
        			(*p_vect)[num].tr_amount = 2;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[2];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				(*p_vect)[num].triang[1] = tr_pointer-1;
			}
		   }

		   else if (diagonal((*p_vect)[num].mass[0], (*p_vect)[num].mass[2], (*p_vect)[num].mass[1], (*p_vect)[num].mass[3])==1)
		   {
 			if ((delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3], (*p_vect)[num].mass[1])==1) and
            	    	    (delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[2], (*p_vect)[num].mass[1], (*p_vect)[num].mass[3])==1))
			{
				cout << "___3___" << endl;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				tr_pointer+=2;
        			(*p_vect)[num].triang[0] = tr_pointer-2;
        			(*p_vect)[num].tr_amount = 2;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				(*p_vect)[num].triang[1] = tr_pointer-1;
			}

        		else
			{
				cout << "___4___" << endl;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[1];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				tr_pointer+=2;
        			(*p_vect)[num].triang[0] = tr_pointer-2;
        			(*p_vect)[num].tr_amount = 2;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[2];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				(*p_vect)[num].triang[1] = tr_pointer-1;
        		}

		   }

		   else if (diagonal((*p_vect)[num].mass[0], (*p_vect)[num].mass[3], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2])==1)
		   {
			 if ((delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3])==1) and
            		     (delanau((*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3], (*p_vect)[num].mass[0])==1))
			{
				cout << "___5___" << endl;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[1];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[2];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
        			tr_pointer+=2;
        			(*p_vect)[num].triang[0] = tr_pointer-2;
        			(*p_vect)[num].tr_amount = 2;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[1];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				(*p_vect)[num].triang[1] = tr_pointer-1;
        		}


        		else
			{
				cout << "___6___" << endl;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				tr_pointer+=2;
        			(*p_vect)[num].triang[0] = tr_pointer-2;
        			(*p_vect)[num].tr_amount = 2;
        			triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        			triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        			triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        			for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        			(*p_tr).push_back(triangle_t);
				(*p_vect)[num].triang[1] = tr_pointer-1;
        		}

		   }


		}
	}
}

void razdel(vector <point_group>* p_vect, int num, int type_of_sort)  //recursive function realizing the primary partition
{
	int num_of_p = (*p_vect)[num].amount;
	int i, new_num;
	int new_type_of_sort = (type_of_sort+1)%2;

	if (type_of_sort == 0) qsort((*p_vect)[num].mass, (*p_vect)[num].amount, sizeof(point*), compare_x);  
	else qsort((*p_vect)[num].mass, (*p_vect)[num].amount, sizeof(point*), compare_y); 


	if (num_of_p == 3);

	else if (num_of_p == 4);

	else if (num_of_p == 8){

		vector_pointer +=2;
		new_num = vector_pointer;

		(*p_vect).push_back(point_group(4));      
		(*p_vect).push_back(point_group(4));

		for (i=0; i<4; i++){
			(*p_vect)[vector_pointer-1].mass[i] = (*p_vect)[num].mass[i];   
			(*p_vect)[vector_pointer].mass[i] = (*p_vect)[num].mass[i+4];
		}
		(*p_vect)[new_num-1].father = num;
		(*p_vect)[new_num].father = num;
		razdel(p_vect, new_num-1, new_type_of_sort);
		razdel(p_vect, new_num, new_type_of_sort);
	}

	else if (num_of_p < 12) 
	{
		vector_pointer +=2;
		new_num = vector_pointer;

		(*p_vect).push_back(point_group(3));      
		(*p_vect).push_back(point_group(num_of_p-3));

		for (i=0; i<3; i++) (*p_vect)[vector_pointer-1].mass[i] = (*p_vect)[num].mass[i]; 
		for (i=0; i<num_of_p-3; i++) (*p_vect)[vector_pointer].mass[i] = (*p_vect)[num].mass[i+3];

		(*p_vect)[new_num-1].father = num;
                (*p_vect)[new_num].father = num;

		razdel(p_vect, new_num-1, new_type_of_sort);
		razdel(p_vect, new_num, new_type_of_sort);

	}

	else if (num_of_p >=12) {
		vector_pointer +=2;
		new_num = vector_pointer;

		(*p_vect).push_back(point_group(num_of_p/2));      
		(*p_vect).push_back(point_group(num_of_p - num_of_p/2));

		for (i=0; i<num_of_p/2; i++) (*p_vect)[vector_pointer-1].mass[i] = (*p_vect)[num].mass[i];
        	for (i=0; i<(num_of_p - num_of_p/2); i++) (*p_vect)[vector_pointer].mass[i] = (*p_vect)[num].mass[i+num_of_p/2];

		(*p_vect)[new_num-1].father = num;
                (*p_vect)[new_num].father = num;

		razdel(p_vect, new_num-1, new_type_of_sort);
		razdel(p_vect, new_num, new_type_of_sort);

	}

}


bool cmp (point* a, point* b) {
	return a->x < b->x || a->x == b->x && a->y < b->y;
}

bool cw (point* a, point* b, point* c) {
	return a->x*(b->y-c->y)+b->x*(c->y-a->y)+c->x*(a->y-b->y) <= 0;
}

bool ccw (point* a, point* b, point* c) {
	return a->x*(b->y-c->y)+b->x*(c->y-a->y)+c->x*(a->y-b->y) >= 0;
}

void convex_hull(vector <point*> & a) {
	if (a.size() == 1)  return;
	sort (a.begin(), a.end(), &cmp);
	point* p1 = a[0];  
	point* p2 = a.back();
	vector<point*> up, down;
	up.push_back (p1);
	down.push_back (p1);
	for (size_t i=1; i<a.size(); ++i) {
		if (i==a.size()-1 || cw (p1, a[i], p2)) {
			while (up.size()>=2 && !cw (up[up.size()-2], up[up.size()-1], a[i]))
				up.pop_back();
			up.push_back (a[i]);
		}
		if (i==a.size()-1 || ccw (p1, a[i], p2)) {
			while (down.size()>=2 && !ccw (down[down.size()-2], down[down.size()-1], a[i]))
				down.pop_back();
			down.push_back (a[i]);
		}
	}
	a.clear();
	for (size_t i=0; i<up.size(); ++i)
		a.push_back (up[i]);
	for (size_t i=down.size()-2; i>0; --i)
		a.push_back (down[i]);
}



void do_shell(vector <point_group>* p_vect, int num)
{
	for (int i=0; i<(*p_vect)[num].amount; i++)
	{
		(*p_vect)[num].shell.push_back((*p_vect)[num].mass[i]);
	}

convex_hull((*p_vect)[num].shell);
}

void find_bridges(vector <point_group>* p_vect, int num)
{
	int i,k = 0;
	int papa = (*p_vect)[num].father;  
	for (i=0; i<(*p_vect)[num].shell.size(); i++) {
		(*p_vect)[num].shell[i]->type = 0;
		(*p_vect)[papa].shell.push_back(((*p_vect)[num].shell[i]));
	}

	for (i=0; i<(*p_vect)[num-1].shell.size(); i++) {
		(*p_vect)[num-1].shell[i]->type = 1;
		(*p_vect)[papa].shell.push_back(((*p_vect)[num-1].shell[i]));
	}

	convex_hull((*p_vect)[papa].shell);

	for (i=1; i<(*p_vect)[papa].shell.size(); i++)
	{
		if (((*p_vect)[papa].shell[i-1]->type + (*p_vect)[papa].shell[i]->type) == 1)
		{
			if (k==0){
				(*p_vect)[papa].bridge[0] = (*p_vect)[papa].shell[i-1];
				(*p_vect)[papa].bridge[1] = (*p_vect)[papa].shell[i];
				k = 1;
			}
			
			else {
				(*p_vect)[papa].bridge[2] = (*p_vect)[papa].shell[i-1];
                                (*p_vect)[papa].bridge[3] = (*p_vect)[papa].shell[i];
                        }
		}
	}
}




