#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <utility>
#define PI (atan(1)*4)
using namespace std;

const int daba= 4908;
const int maxn= 23;
const long double eps= 0.0000000001;

inline long double square(long double a);
struct star{
	char id[10];
	long double x;
	long double y;
	long double z;
	star()= default;
	star(char *i, long double xx, long double yy, long double zz) : x(xx), y(yy), z(zz)
	{
		memcpy(id, i, 9);
	}
	long double operator*(const star neib) const
	{
		return x*neib.x+y*neib.y+z*neib.z;
	}
	void Unit()
	{
		long double r= sqrt(x*x+y*y+z*z);
		x= x/r;
		y= y/r;
		z= z/r;
	}
};
struct EigenVector{
	long double x1, x2, x3, x4, x5, x6;
	EigenVector()= default;
	EigenVector(long double i1, long double i2, long double i3, long double i4, long double i5, long double i6) :
	x1(i1), x2(i2), x3(i3), x4(i4), x5(i5), x6(i6){}
	long double Differ(EigenVector data) const
	{
		return square(x1-data.x1)+square(x2-data.x2)+square(x3-data.x3)
			+square(x4-data.x4)+square(x5-data.x5)+square(x6-data.x6);
	}
};
star stars[maxn];
EigenVector exam[maxn];
EigenVector database[daba];
pair<int, long double> frstar[maxn][4];

inline long double square(long double a)
{
	return a*a;
}
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
long double Getf(long double alp, long double d)
{
	return d/(2*tan(alp/2));
}

int main()
{
	FILE *fp;
	int n;
	char id[10];
	long double xx, yy, zz, d, alp;
	long double ad;
	d= 512;
	alp= Transfer(12);
	zz= Getf(alp, d);

	char test[10];
	int tn;
	scanf("%d", &tn);
	sprintf(test, "%d.txt", tn);

	fp= fopen(test, "r");

	fscanf(fp, "%d", &n);
	for (int i= 0; i< n; ++i){
		fscanf(fp, "%s %Lf %Lf", id, &xx, &yy);
		stars[i]= star(id, xx, yy, zz);
		stars[i].Unit();
	}
	fclose(fp);

	for (int i= 0; i< n; ++i){
		for (int g= 0; g< 4; ++g){
			frstar[i][g].first= 0;
			frstar[i][g].second= 2*PI;
		}
		for (int j= 0; j< n; ++j){
			if (j!= i){
				ad= AngleDistance(stars[i], stars[j]);
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

	for (int i= 0; i< n; ++i){
		int tmp[3];
		for (int j= 0; j< 3; ++j){
			tmp[j]= frstar[i][j].first;
		}
		exam[i]= EigenVector(stars[i]*stars[tmp[0]],
			stars[i]*stars[tmp[1]], stars[i]*stars[tmp[2]], 
			stars[tmp[0]]*stars[tmp[1]], stars[tmp[0]]*stars[tmp[2]],
			stars[tmp[1]]*stars[tmp[2]]);
	}
	fp= fopen("database.txt", "r");
	for (int i= 0; i< daba; ++i){
		long double store[6];
		for (int j= 0; j< 6; ++j){
			fscanf(fp, "%Lf", store+j);
		}
		database[i]= EigenVector(store[0], store[1], store[2],
			store[3], store[4], store[5]);
	}
	fclose(fp);
	char result[10];
	sprintf(result, "result%d.txt", tn);
	fp= fopen(result, "w");
	for (int i= 0; i< n; ++i){
		pair<int, long double> ans(0, 7.0);
		long double dif;
		for (int j= 0; j< daba; ++j){
			dif= exam[i].Differ(database[j]);
			if (ans.second- dif> eps){
				ans= pair<int, long double>(j, dif);
			}
		}
		fprintf(fp, "%s %d %.10Lf\n", stars[i].id, ans.first+1, ans.second);
	}
	fclose(fp);

	
	return 0;
}