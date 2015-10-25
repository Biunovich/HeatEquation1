#include <stdio.h>
#include <stdlib.h>
#include <math.h>
class Teplo
{
public:
	double **arr;
	int jt, kt;
	double sttau, sth, kurt, **tridiag, *uk, *x;
	double A = 0.033;
	double f(double x, double t)
	{
		return (x + 2.0 * t - exp(x) + A*(12.0 * pow(x, 2) - 2.0 + t*exp(x)));
	}
	double nu(double x)
	{
		return (-pow(x, 4) + pow(x, 2));
	}
	double u(double x, double t)
	{
		return(-pow(x, 4) + pow(x, 2) + t*x + pow(t, 2) - t* exp(x));
	}
	double nu1(double t)
	{
		return (pow(t, 2) - t);
	}
	void printtridiag()
	{
		for (int i = 0; i < kt - 1; i++)
		{
			printf("\n");
			for (int j = 0; j < kt - 1; j++)
				printf("%lf ", tridiag[i][j]);
		}
		printf("\n");
	}
	void write()
	{
		for (int i = 0; i < jt + 1; i++) {
			printf("\n");
			for (int j = 0; j < kt + 1; j++)
				printf("%lf ", arr[i][j]);
		}
		printf("\n");
	}
	double nu2(double t)
	{
		return (t + pow(t, 2) - t*exp(1.0));
	}
	Teplo()
	{
		printf("VVEDITE KOLLICHESTVO VREMENNYH SLOEV ");
		scanf("%d", &jt);
		printf("VVEDITE KOLLICHESTVO DELENIY STERZHNYA ");
		scanf("%d", &kt);
		printf("\n");
		sttau = 1.0 / jt;
		sth = 1.0 / kt;
		kurt = (A * sttau) / pow(sth, 2);
		arr = (double**)calloc(sizeof(double*), jt + 1);
		for (int i = 0; i < jt + 1; i++)
			arr[i] = (double*)calloc(sizeof(double), kt + 1);
		for (int i = 0; i <= kt; i++)
		{
			arr[0][i] = nu(i*sth);
		}
		for (int i = 1; i < jt + 1; i++) {
			arr[i][0] = nu1(i*sttau);
			arr[i][kt] = nu2(i*sttau);
		}
		tridiag = (double**)calloc(sizeof(double*), kt);
		for (int i = 0; i < kt; i++)
		{
			tridiag[i] = (double*)calloc(sizeof(double), kt);

		}
		uk = (double*)calloc(sizeof(double), kt);
		x = (double*)calloc(sizeof(double), kt);
		for (int j = 0; j < kt - 1; j++)
		{
			if (j == 0)
			{
				tridiag[j][j] = -(1.0 + 2 * kurt);
				tridiag[j][j + 1] = kurt;
			}
			if (j > 0 && j < kt - 1)
			{
				tridiag[j][j - 1] = kurt;
				tridiag[j][j] = -(1.0 + 2 * kurt);
				tridiag[j][j + 1] = kurt;
			}
			if (j == kt - 2)
			{
				tridiag[j][j - 1] = kurt;
				tridiag[j][j] = -(1.0 + 2 * kurt);
			}
		}
	}
	double * progon(double * uk)
	{
		double m;
		for (int i = 1; i < kt - 1; i++)
		{
			m = tridiag[i][i-1] / tridiag[i-1][i-1];
			tridiag[i][i] -= m*tridiag[i-1][i];
			uk[i] -= m*uk[i-1];
		}
		x[kt - 2] = uk[kt - 2] / tridiag[kt - 2][kt - 2];
		for (int i = kt - 3; i >= 0; i--)
			x[i] = (uk[i] - tridiag[i][i + 1] * x[i + 1]) / tridiag[i][i];
		return x;
	}
	void vychsloy(int n)
	{
		double *otv;
		for (int i = 0; i < kt - 1; i++) {
			if (i == 0) {
				uk[i] = -(arr[n - 1][i + 1] + sttau*f(i*sth + sth, n*sttau) + kurt* arr[n][0]);
				continue;
			}
			if (i == kt - 2) {
				uk[i] = -(arr[n - 1][i + 1] + sttau*f(i*sth + sth, n*sttau) + kurt* arr[n][kt]);
				continue;
			}
			uk[i] = -(arr[n - 1][i + 1] + sttau*f(i*sth + sth, n*sttau));
		}
		otv = progon(uk);
		for (int i = 0; i < kt - 1; i++)
			arr[n][i + 1] = otv[i];
		for (int j = 0; j < kt - 1; j++)
		{
			if (j == 0)
			{ 
				tridiag[j][j] = -(1.0 + 2 * kurt);
				tridiag[j][j + 1] = kurt;
			}
			if (j > 0 && j < kt - 1)
			{
				tridiag[j][j - 1] = kurt;
				tridiag[j][j] = -(1.0 + 2 * kurt);
				tridiag[j][j + 1] = kurt;
			}
			if (j == kt - 2)
			{
				tridiag[j][j - 1] = kurt;
				tridiag[j][j] = -(1.0 + 2 * kurt);
			}
			//tridiag[0][1] = 0; tridiag[1][0] = 0;
		}
	}
};
void main()
{
	Teplo * teplo = new Teplo();
	//teplo->write();
	//teplo->printtridiag();
	for (int i = 1; i < teplo->jt+1;i++)
		teplo->vychsloy(i);
	//teplo->write();
	//for (int j = 0; j < teplo->jt +1; j++) {
	//	printf("\n");
	//	for (int i = 0; i < teplo->kt + 1; i++)
	//		printf("%lf ", teplo->u(i*teplo->sth, j*teplo->sttau));
	//}
	printf("\n");
	FILE * f = fopen("output.txt", "w");
	for (int i = 0; i < teplo->jt+1; i++) {
		for (int j = 0; j < teplo->kt+1; j++)
			fprintf(f, "%lf %lf %lf\n",j*teplo->sth,teplo->arr[i][j], teplo->u(j*teplo->sth, i*teplo->sttau));
		fprintf(f, "\n");
	}
}