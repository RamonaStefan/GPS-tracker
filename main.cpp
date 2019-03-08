#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <limits.h>
using namespace std;

struct noduri{
    char nod[30];
    double x = INT_MAX;
    double y = INT_MAX;
};
double rotunjire(double d)
{
  return floor(d+0.5);
}

double cost(double x1, double y1, double x2, double y2){
    double cost;
    cost = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return cost;
}

double char_double(char m[10]){
    int i, L;
    double nr = 0;

    L = strlen(m);
    for (i = 0; i < L; i++) {
       	nr = nr*10 + m[i] - '0';		//determinarea numarului de operatii
    }
    return nr;
}

void coord_inter (double x1, double y1, double r1, double x2, double y2, double r2, double x3, double y3, double r3, double *x, double *y)
{
    double c1, c2, c3, c4, c5;
    double x01, x02, y01, y02;
    double ver1,ver2;
    if (y1 != y2){
    	c1 = (x1-x2)/(y2-y1);
    	c2 = ((pow(r1,2) - pow(r2,2)) - (pow(x1,2)- pow(x2,2))-(pow(y1,2) - pow(y2,2)))/(2.0*(y2-y1));
    	c3 = pow(c1,2) + 1;
    	c4 = 2*c1*c2 - 2*c1*y1 - 2*x1;
    	c5 = pow(x1, 2) + pow(c2,2) + pow(y1,2) - 2*c2*y1 - pow(r1,2);
    	x01 = (-c4 - sqrt(fabs(pow(c4,2)-4*c3*c5)))/(2*c3);
   		x02 = (-c4 + sqrt(fabs(pow(c4,2)-4*c3*c5)))/(2*c3);
    	y01 = c1*x01 + c2;
    	y02 = c1*x02 + c2;
    	ver2 = fabs(pow(x3 - x02, 2)+ pow(y3 - y02, 2) - pow(r3,2));
    	ver1 = fabs(pow(x3 - x01, 2)+ pow(y3 - y01, 2) - pow(r3,2));
    	if (ver2 <= 0.0001){
        	if (fabs(x02) <0.0000001)
        			*x = 0;
        	else
        			*x = x02;
        	if (fabs(y02) <0.0000001)
        			*y = 0;
        		else
        			*y = y02;
    	}
    	if (ver1 <= 0.0001){
        	if (fabs(x01) <0.0000001)
        			*x = 0;
        	else
        			*x = x01;
        	if (fabs(y01) <0.0000001)
        			*y = 0;
        		else
        			*y = y01;
    	}
    }
    else {
    	c1 = (x1+x2)/2;
    	c2 = (pow(r2,2)-pow(r1,2))/(2*(x1-x2));
    	x01 = c1+c2;
    	y01 = y1-sqrt(fabs(pow(r1,2)-pow(x1-x01,2)));
    	y02 = y1+sqrt(fabs(pow(r1,2)-pow(x1-x01,2)));
    	ver2 = fabs(pow(x3 - x01, 2)+ pow(y3 - y02, 2) - pow(r3,2));
    	ver1 = fabs(pow(x3 - x01, 2)+ pow(y3 - y01, 2) - pow(r3,2));
    	if (ver2 <= 0.0001){
        	if (fabs(x01) <0.0000001)
        			*x = 0;
        	else
        			*x = x01;
        	if (fabs(y02) <0.0000001)
        			*y = 0;
        		else
        			*y = y02;
    	}
    	if (ver1 <= 0.0001){
        	if (fabs(x01) <0.0000001)
        		*x = 0;
        	else
        			*x = x01;
        	if (fabs(y01) <0.0000001)
        			*y = 0;
        	else
        			*y = y01;
    	}
    }

}


int minDistance(double dist[], int noduri_vizitate[], int n)
{

   double min = INT_MAX;
   int min_index;
    int v;
   for ( v = 0; v < n; v++)
     if (noduri_vizitate[v] == 0 && dist[v] <= min){
         min = dist[v];
         min_index = v;
     }
   return min_index;
}



void dijkstra(double graph[30][30], int sursa, int n, double dist[30])
{
     double cost;
     int noduri_vizitate[n];
     int i, count, u, v;
     for (i = 0; i < n; i++){
        dist[i] = INT_MAX;
        noduri_vizitate[i] = 0;
     }
     dist[sursa] = 0;


     for(count = 0; count < n-1; count++)
     {

       u = minDistance(dist, noduri_vizitate,n);
       noduri_vizitate[u] = 1;


       for (v = 0; v < n; v++){
       	cost = dist[u] + graph[u][v];
     	 if (noduri_vizitate[v] == 0 && graph[u][v] != 0){
          if (dist[u] != INT_MAX && cost < dist[v])
      		{
           	dist[v] = cost;

     		}
     	 }
 		}
 }
 	/*if (fabs(dist[pozitie]-ceil(dist[pozitie]))< 0.001)
 		return ceil(dist[pozitie]);
 	else
     	return floor(dist[pozitie]); */

 //return dist[pozitie];
     //afisare(dist, n, pozitie);
}

int main(int argc, char *argv[])
{
    double x = INT_MAX, y = INT_MAX, dist[30];
    int L, i, nr, j, k, q, pozitie;
    double x1, x2, x3, y1, y2, y3, r1, r2, r3;
    double a[30][30], costminim;
    char linie[100], *s, *cuv[20];
    struct noduri *graf;
    ifstream f("coordonate.in");
    ifstream g("avarii.in");
    ofstream r("coord_finale.out");
    ofstream h("rezultat.out");
    if (!f) {
        cout << "Deschidere nereusita coordonate.in" << endl;
        exit(1);
    }
   if (!g) {
        cout << "Deschidere nereusita avarii.in" << endl;
        exit(1);
    }
    if (!r) {
        cout << "Deschidere nereusita coord_finale.out" << endl;
        exit(1);
    }
    if (!h) {
        cout << "Deschidere nereusita rezultat.out" << endl;
        exit(1);
    }
    nr = 0;
    f.getline(linie, 80);
    L = strlen(linie);
    for (i = 0; i < L; i++) {
       	nr = nr*10+linie[i]-'0';		//determinarea numarului de locatii
    }
    graf = new noduri [nr];
    /**a = new double[nr];
    for (i = 0; i < nr; i++)
        a[i] = new double [nr]; */
    for (i = 0; i < nr; i++) {
       	x = INT_MAX;
       	y = INT_MAX;
       	f.getline(linie, 80);
       	s = strtok(linie, " ");    //citirea linie cu linie si imparitrea in cuvinte cu ajutorul strtok
       	k = 0;
       	while (s != NULL) {
            cuv[k] = s;
            k++;
            s = strtok(NULL, " ");
        }
        strcpy(graf[i].nod, cuv[0]);
        f.getline(linie, 80);
        k = 0;
       	s = strtok(linie, " ");
       	while (s != NULL) {
            cuv[k] = s;
            k++;
            s = strtok(NULL, " ");
        }
        x1 = char_double(cuv[1]);
        y1 = char_double(cuv[2]);
        r1 = char_double(cuv[3]);
        f.getline(linie, 80);
        k = 0;
       	s = strtok(linie, " ");
       	while (s != NULL) {
            cuv[k] = s;
            k++;
            s = strtok(NULL, " ");
        }
        x2 = char_double(cuv[1]);
        y2 = char_double(cuv[2]);
        r2 = char_double(cuv[3]);
        f.getline(linie, 80);
        k = 0;
       	s = strtok(linie, " ");
       	while (s != NULL) {
            cuv[k] = s;
            k++;
            s = strtok(NULL, " ");
        }
        x3 = char_double(cuv[1]);
        y3 = char_double(cuv[2]);
        r3 = char_double(cuv[3]);
        coord_inter(x1, y1, r1, x2, y2, r2, x3, y3,r3, &x, &y);
        graf[i].x = x;
        graf[i].y = y;
        r<<graf[i].x<<' '<<graf[i].y<<'\n';
        f.getline(linie, 80);

    }
    for (i = 0; i < nr; i++)
        for (j = 0; j < nr; j++)
            a[i][j] = cost(graf[i].x,graf[i].y, graf[j].x, graf[j].y);
     while (g.eof() == 0) {
        g.getline(linie, 80);
        k = 0;
       	s = strtok(linie, " ");
       	while (s != NULL) {
            cuv[k] = s;
            k++;
            s = strtok(NULL, " ");
        }
        for (q = 0; q < nr; q++) {
            if (strcmp (cuv[0], graf[q].nod) == 0)
                i = q;
            if (strcmp (cuv[1], graf[q].nod) == 0)
                j = q;
        }
        a[i][j] = 0;
        a[j][i] = 0;
    }
    pozitie = 2;

    dijkstra(a, 0, nr, dist);
    /*for (i = 0; i < nr; i++)
        if (strcmp(argv[3], graf[i].nod) == 0)
            pozitie = i;
*/
    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nr; j++)
            cout<<a[i][j]<<"    ";
        cout<<'\n';
    }
    /*for (i = 0; i < nr; i++)
    {
        cout<<graf[i].nod<<'*'<<graf[i].x<<'*'<<graf[i].y<<'\n';
    }*/
    cout<<dist[pozitie];
    h<<dist[pozitie]<<'\n';
    return 0;
}
