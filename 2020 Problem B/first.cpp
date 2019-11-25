#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define PI (atan(1)*4)
using namespace std;
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define PI (atan(1)*4)
using namespace std;

const int n= 4908;
inline double Transfer(double j);
inline double RTransfer(double h);
struct star{
	int id;
	double alp;
	double dlt;
	double lev;
	star() : id(0), alp(0.0), dlt(0.0), lev(0.0) {}
	star(int i, double a, double d, double l) : id(i), alp(a), dlt(d), lev(l) {}
	double operator*(const star f) const
	{
		double rx, ry, rz;
		rx= cos(Transfer(alp))*cos(Transfer(f.alp))*cos(Transfer(dlt))*cos(Transfer(f.dlt));
		ry= cos(Transfer(dlt))*cos(Transfer(f.dlt))*sin(Transfer(alp))*sin(Transfer(f.alp));
		rz= sin(Transfer(dlt))*sin(Transfer(f.dlt));
		return rx+ry+rz;
	}
};

inline double Transfer(double j)
{
	return (j*PI)/180;
}
inline double RTransfer(double h)
{
	return (h*180)/PI;
}
double AngleDistance(star m, star f)
{
	return fabs(acos(m*f));
}

star starmap[n];
pair<int, double> frstar[n][4];

int main()
{
	FILE *fp;
	int id;
	double alp, dlt, lev;
	fp= fopen("starmap.txt", "r");
	for (int i= 0; i< n; ++i){
		fscanf(fp, "%d %lf %lf %lf", &id, &alp, &dlt, &lev);
		starmap[i]= star(id, alp, dlt, lev);
	}
	for (int i= 0; i< n; ++i){
		for (int g= 0; g< 4; ++g){
			frstar[i][g].first= 0;
			frstar[i][g].second= 2*PI;
		}
		for (int j= 0; j< n; ++j){
			if (i!= j){
				double ad= AngleDistance(starmap[i], starmap[j]);
				frstar[i][3]= pair<int, double>(j, ad);
				for (int k= 3; k> 0; --k){
					if (frstar[i][k-1].second< ad){
						break;
					}
					else{
						swap(frstar[i][k-1], frstar[i][k]);
					}
				}
			}
		}
	}
	fp= fopen("out.txt", "w");
	for (int i= 0; i< n; ++i){
		// fprintf(fp, "%d friend:\n", i+1);
		pair<int, double> tmp;
		for (int j= 0; j< 3; ++j){
			tmp= frstar[i][j];
/*			fprintf(fp, "%d %f %f %f %f\n", tmp.first+1, tmp.second, 
				starmap[tmp.first].alp, starmap[tmp.first].dlt, 
				starmap[tmp.first].lev);*/
			fprintf(fp, "%d(%f)                               ", tmp.first+1, tmp.second);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	
	return 0;
}
