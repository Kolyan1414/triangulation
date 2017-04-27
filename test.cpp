#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <malloc.h>

using namespace std;
FILE* input=fopen("input.txt","r");

class line{
public:
	double k;
	double b;
};

class point{	//структура, которая хранит данные о точке
public:
	double x;
	double y;
	int number;
};

point mass_of_points[100]; //глобальный массив точек (изначательно подается на вход)
int vector_pointer = 0; //глобальный счетчик позиции структуры в векторе

class triangle{
public:
	point* uzel[3];
	triangle* trian[3];
};

class point_group{
public:

	int amount;
	point** mass;

	
	point_group(int k){       //конструктор структуры точек
	this->amount = k;
	this->mass = new point*[k];
	}

	void del(){		//метод освобождения памяти 
	delete [] mass;
	}

};

int compare_x(const void* x1, const void* x2)    //сортировка структуры по x
{
double t;
t = ((**(point**)x1).x - (**(point**)x2).x);

if (t > 0) return 1;
else if (t==0) return 0;
else return -1;
}

int compare_y(const void* x1, const void* x2)     //сортировка структуры по y
{
double t;
t = ((**(point**)x1).y - (**(point**)x2).y);

if (t > 0) return 1;
else if (t==0) return 0;
else return -1;
}

line line_by_points(point* t_1, point* t_2)  //строит линию по двум точкам
{
line line_t;
line_t.k = (((*t_2).y)-((*t_1).y))/(((*t_2).x)-((*t_1).x));
line_t.b = (*t_1).y - (line_t.k)*((*t_1).x);
return(line_t);
}

int diagonal(point* p0, point* p1, point* p2, point* p3){
line line_t;
line_t = line_by_points(p0, p1);

if ((((*p2).y-line_t.k*(*p2).x-line_t.b)*((*p3).y-line_t.k*(*p3).x-line_t.b))<0) return(1);
else return(0); 
}

int is_it_type_1(point* p0, point* p1, point* p2, point* p3){ //пока не учитывается то, что точка может попасть четко на сторону (бред)
int tx, ty, i;                                                //проверяет есть ли это триангуляция первого типа (бьется на 3 треугльника)
int x0 = (*p0).x;
int x1 = (*p1).x;
int x2 = (*p2).x;
int x3 = (*p3).x;
int y0 = (*p0).y;
int y1 = (*p1).y;
int y2 = (*p2).y;
int y3 = (*p3).y;

for (i=0; i<4; i++){

if (i==1) {tx=x0; ty=y0; x0=x1; y0=y1; x1=tx; y1=ty;}
else if (i==2) {tx=x0; ty=y0; x0=x2; y0=y2; x2=tx; y2=ty;}
else {tx=x0; ty=y0; x0=x3; y0=y3; x3=tx; y3=ty;} 

if ( ( (((x1-x0)*(y2-y1)-(x2-x1)*(y1-y0))>0) and (((x2-x0)*(y3-y2)-(x3-x2)*(y2-y0))>0) and (((x3-x0)*(y1-y3)-(x1-x3)*(y3-y0)))>0 ) or
     ( (((x1-x0)*(y2-y1)-(x2-x1)*(y1-y0))<0) and (((x2-x0)*(y3-y2)-(x3-x2)*(y2-y0))<0) and (((x3-x0)*(y1-y3)-(x1-x3)*(y3-y0)))<0 ) )
{return(i);}

}

return(4);
}

int delanau(point* p1, point* p2, point* p3, point* p4){
double x1 = (*p1).x, y1 = (*p1).y;
double x2 = (*p1).x, y2 = (*p2).y;
double x3 = (*p1).x, y3 = (*p3).y;
double x = (*p1).x, y = (*p4).y;
double a = x1*(y2-y3) - y1*(x2-x3) + (x2*y3-x3*y2);
double b = (x1*x1+y1*y1)*(y2-y3) - y1*(x2*x2+y2*y2-x3*x3-y2*y2) + (x2*x2+y2*y2)*y3 - y2*(x3*x3+y3*y3);
double c = (x1*x1+y1*y1)*(x2-x3) - x1*(x2*x2+y2*y2-x3*x3-y2*y2) + (x2*x2+y2*y2)*x3 - x2*(x3*x3+y3*y3);
double d = (x1*x1+y1*y1)*(x2*y3-x3*y2) - x1*((x2*x2+y2*y2)*y3 - y2*(x3*x3+y3*y3)) + y1*((x2*x2+y2*y2)*x3-x2*(x3*x3+y3*y3));
double ans = (a*(x*x+y*y)-b*x+c*y-d)*a;

if (ans>=0) return(1);
else return(0);
}


void starting_triangulate(vector <triangle>* p_tr, vector <point_group>* p_vect, int num){
int kolvo = (*p_vect)[num].amount;
triangle triangle_t;
int i;
line line_t[5];

if (kolvo == 3) {
for (i=0; i<3; i++) triangle_t.uzel[i] = (*p_vect)[num].mass[i];
for (i=0; i<3; i++) triangle_t.trian[i] = NULL;
(*p_tr).push_back(triangle_t);
}

else if (kolvo == 4) { //тут не надо елсе короче, потом уберу, когда придумаю алгоритм
//cout << "ITS NE 3" << endl;
int k=is_it_type_1((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3]);
cout << "triangulation type =" << k << endl;;
if (k==0) { //нулевая точка в центре
triangle_t.uzel[0]=(*p_vect)[num].mass[0];
triangle_t.uzel[1]=(*p_vect)[num].mass[1];
triangle_t.uzel[2]=(*p_vect)[num].mass[2];
for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
(*p_tr).push_back(triangle_t); //кидаем 1
triangle_t.uzel[2]=(*p_vect)[num].mass[3];
(*p_tr).push_back(triangle_t); //кидаем 2
triangle_t.uzel[1]=(*p_vect)[num].mass[2];
(*p_tr).push_back(triangle_t); //кидаем 3
}

else if (k==1) {
triangle_t.uzel[0]=(*p_vect)[num].mass[1];
triangle_t.uzel[1]=(*p_vect)[num].mass[0];
triangle_t.uzel[2]=(*p_vect)[num].mass[2];
for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
(*p_tr).push_back(triangle_t); //кидаем 1
triangle_t.uzel[2]=(*p_vect)[num].mass[3];
(*p_tr).push_back(triangle_t); //кидаем 2
triangle_t.uzel[1]=(*p_vect)[num].mass[2];
(*p_tr).push_back(triangle_t); //кидаем 3
}

else if (k==2) {
triangle_t.uzel[0]=(*p_vect)[num].mass[2];
triangle_t.uzel[1]=(*p_vect)[num].mass[0];
triangle_t.uzel[2]=(*p_vect)[num].mass[1];
for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
(*p_tr).push_back(triangle_t); //кидаем 1
triangle_t.uzel[2]=(*p_vect)[num].mass[3];
(*p_tr).push_back(triangle_t); //кидаем 2
triangle_t.uzel[1]=(*p_vect)[num].mass[1];
(*p_tr).push_back(triangle_t); //кидаем 3
}

else if (k==3){
triangle_t.uzel[0]=(*p_vect)[num].mass[3];
triangle_t.uzel[1]=(*p_vect)[num].mass[0];
triangle_t.uzel[2]=(*p_vect)[num].mass[1];
for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
(*p_tr).push_back(triangle_t); //кидаем 1
triangle_t.uzel[2]=(*p_vect)[num].mass[2];
(*p_tr).push_back(triangle_t); //кидаем 2
triangle_t.uzel[1]=(*p_vect)[num].mass[1];
(*p_tr).push_back(triangle_t); //кидаем 3
}

else if (k==4){
if (diagonal((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3])==1) {
	if ((delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3])==1) and
	    (delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[3], (*p_vect)[num].mass[2])==1)){
	triangle_t.uzel[0]=(*p_vect)[num].mass[0];
	triangle_t.uzel[1]=(*p_vect)[num].mass[2];
	triangle_t.uzel[2]=(*p_vect)[num].mass[1];
	for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
	(*p_tr).push_back(triangle_t);
	triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
	}

	else{
	triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        triangle_t.uzel[0]=(*p_vect)[num].mass[2];
        triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
	}
}

else if (diagonal((*p_vect)[num].mass[0], (*p_vect)[num].mass[2], (*p_vect)[num].mass[1], (*p_vect)[num].mass[3])==1)
{
 if ((delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3], (*p_vect)[num].mass[1])==1) and
            (delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[2], (*p_vect)[num].mass[1], (*p_vect)[num].mass[3])==1)){
        triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        }

        else{
        triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[1];
        triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        triangle_t.uzel[0]=(*p_vect)[num].mass[2];
        triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        }

}

else if (diagonal((*p_vect)[num].mass[0], (*p_vect)[num].mass[3], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2])==1)
{
 if ((delanau((*p_vect)[num].mass[0], (*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3])==1) and
            (delanau((*p_vect)[num].mass[1], (*p_vect)[num].mass[2], (*p_vect)[num].mass[3], (*p_vect)[num].mass[0])==1)){
        triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[1];
        triangle_t.uzel[2]=(*p_vect)[num].mass[2];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        triangle_t.uzel[0]=(*p_vect)[num].mass[1];
        triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        }

        else{
        triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[2];
        triangle_t.uzel[2]=(*p_vect)[num].mass[3];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        triangle_t.uzel[0]=(*p_vect)[num].mass[0];
        triangle_t.uzel[1]=(*p_vect)[num].mass[3];
        triangle_t.uzel[2]=(*p_vect)[num].mass[1];
        for (i=0; i<2; i++) triangle_t.trian[i] = NULL;
        (*p_tr).push_back(triangle_t);
        }

}


}
}
}

void razdel(vector <point_group>* p_vect, int num, int type_of_sort){  //рекурсивная функция, реализующая первичное разбиение
int num_of_p = (*p_vect)[num].amount;
int i, new_num;
int new_type_of_sort = (type_of_sort+1)%2;

if (type_of_sort == 0) qsort((*p_vect)[num].mass, (*p_vect)[num].amount, sizeof(point*), compare_x);  //сортируем структуру
else qsort((*p_vect)[num].mass, (*p_vect)[num].amount, sizeof(point*), compare_y); 


if (num_of_p == 3);

else if (num_of_p == 4);

else if (num_of_p == 8){

vector_pointer +=2;
new_num = vector_pointer;

(*p_vect).push_back(point_group(4));       //создем две новых структуры и кладем их в вектор
(*p_vect).push_back(point_group(4));

	for (i=0; i<4; i++){
	(*p_vect)[vector_pointer-1].mass[i] = (*p_vect)[num].mass[i];     //заполняем новые структуры указателями на нужны точки 
	(*p_vect)[vector_pointer].mass[i] = (*p_vect)[num].mass[i+4];
	}

razdel(p_vect, new_num-1, new_type_of_sort);
razdel(p_vect, new_num, new_type_of_sort);
}

else if (num_of_p < 12) {
vector_pointer +=2;
new_num = vector_pointer;

(*p_vect).push_back(point_group(3));      
(*p_vect).push_back(point_group(num_of_p-3));

	for (i=0; i<3; i++) (*p_vect)[vector_pointer-1].mass[i] = (*p_vect)[num].mass[i]; 
	for (i=0; i<num_of_p-3; i++) (*p_vect)[vector_pointer].mass[i] = (*p_vect)[num].mass[i+3];

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

razdel(p_vect, new_num-1, new_type_of_sort);
razdel(p_vect, new_num, new_type_of_sort);

}

}
     
int main ()
{
int i,N,j;
vector <point_group> vect;
vector <point_group>::iterator p;
vector <point_group>* p_vect = &vect;
vector <triangle> triangles;
vector <triangle>* p_tr = &triangles;
cin >> N;

for (i=0; i<(2*N); i++)
{
	if (i<N) fscanf(input,"%lf",&mass_of_points[i].x);
	else fscanf(input,"%lf",&mass_of_points[i-N].y);
}

vect.push_back(point_group(N)); //с помощью конструктора выделяем память под первую структуру и сразу кладем ее в вектор
p = vect.begin();

for (i=0; i<N; i++){
(*p).mass[i] = &(mass_of_points[i]); //заполняем структуру
}

qsort((*p).mass, (*p).amount, sizeof(point*), compare_x); //сортируем структуру по х

razdel(p_vect, 0, 0);
for (i=0; i<=vector_pointer; i++){
starting_triangulate(p_tr, p_vect, i);
}

for (i=0; i<triangles.size(); i++){
cout << i <<" ";
for (j=0; j<3; j++){
cout << (triangles[i].uzel[j]->x) << " " << (triangles[i].uzel[j]->y) << endl;
}
}

//(*p).del();
//vect.erase(p);

return 0;
}







