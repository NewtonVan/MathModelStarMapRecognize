#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define PI (atan(1)*4)
using namespace std;

const int n= 4908;
inline long double Transfer(long double j);
inline long double RTransfer(long double h);
struct star{
	int id;
	long double alp;
	long double dlt;
	long double lev;
	star() : id(0), alp(0.0), dlt(0.0), lev(0.0) {}
	star(int i, long double a, long double d, long double l) : id(i), alp(a), dlt(d), lev(l) {}
	long double operator*(const star f) const
	{
		long double rx, ry, rz;
		rx= cos(Transfer(alp))*cos(Transfer(f.alp))*cos(Transfer(dlt))*cos(Transfer(f.dlt));
		ry= cos(Transfer(dlt))*cos(Transfer(f.dlt))*sin(Transfer(alp))*sin(Transfer(f.alp));
		rz= sin(Transfer(dlt))*sin(Transfer(f.dlt));
		return rx+ry+rz;
	}
};

inline long double Transfer(long double j)
{
	return (j*PI)/180;
}
inline long double RTransfer(long double h)
{
	return (h*180)/PI;
}
long double AngleDistance(star m, star f)
{
	return fabs(acos(m*f));
}

star starmap[n];
pair<int, long double> frstar[n][4];

int main()
{
	FILE *fp;
	int id;
	long double alp, dlt, lev;
	fp= fopen("starmap.txt", "r");
	for (int i= 0; i< n; ++i){
		fscanf(fp, "%d %Lf %Lf %Lf", &id, &alp, &dlt, &lev);
		starmap[i]= star(id, alp, dlt, lev);
	}
	for (int i= 0; i< n; ++i){
		for (int g= 0; g< 4; ++g){
			frstar[i][g].first= 0;
			frstar[i][g].second= 2*PI;
		}
		for (int j= 0; j< n; ++j){
			if (i!= j){
				long double ad= AngleDistance(starmap[i], starmap[j]);
				frstar[i][3]= pair<int, long double>(j, ad);
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
	fp= fopen("database.txt", "w");
	for (int i= 0; i< n; ++i){
		// fprintf(fp, "%d Eigen Vector:\n", i+1);
		int tmp[3];
		for (int j= 0; j< 3; ++j){
			tmp[j]= frstar[i][j].first;
		}
		fprintf(fp, "%.10Lf %.10Lf %.10Lf %.10Lf %.10Lf %.10Lf\n", starmap[i]*starmap[tmp[0]],
			starmap[i]*starmap[tmp[1]], starmap[i]*starmap[tmp[2]], 
			starmap[tmp[0]]*starmap[tmp[1]], starmap[tmp[0]]*starmap[tmp[2]],
			starmap[tmp[1]]*starmap[tmp[2]]);
	}
	fclose(fp);

	
	return 0;
}  				