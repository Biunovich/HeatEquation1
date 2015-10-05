#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void inversion(double **A, int N)
{
	double temp;

	double **E = new double *[N];

	for (int i = 0; i < N; i++)
		E[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			E[i][j] = 0.0;

			if (i == j)
				E[i][j] = 1.0;
		}

	for (int k = 0; k < N; k++)
	{
		temp = A[k][k];

		for (int j = 0; j < N; j++)
		{
			A[k][j] /= temp;
			E[k][j] /= temp;
		}

		for (int i = k + 1; i < N; i++)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int k = N - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i][j] = E[i][j];

	for (int i = 0; i < N; i++)
		delete[] E[i];

	delete[] E;
}
class Teplo
{
private:
	double **arr;
public:
	int jt, kt;
	double sttau, sth,kurt,**tridiag;
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
		for (int i = 0; i < kt-1; i++)
		{
			printf("\n");
			for (int j = 0; j < kt-1; j++)
				printf("%lf ", tridiag[i][j]);
		}
		printf("\n");
	}
	void write()
	{
		for (int i = 0; i < jt+1; i++) {
			printf("\n");
			for (int j = 0; j < kt+1; j++)
				printf("%lf ", arr[i][j]);
		}
		printf("\n");
	}
	double nu2(double t)
	{
		return (t + pow(t, 2) - t*exp(1));
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
		arr = (double**)calloc(sizeof(double*), jt+1);
		for (int i = 0; i < jt+1; i++)
			arr[i] = (double*)calloc(sizeof(double), kt+1);
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
	void matrvect(double * x, double * y)
	{
		for (int i = 0; i < kt - 1; i++)
		{
			for (int j = 0; j < kt - 1;j++)
			{
				y[i] += tridiag[i][j] * x[j];
			}
		}
	}
	void vychsloy(int n)
	{
		double *otv = (double*)calloc(sizeof(double), kt);
		double *uk = (double*)calloc(sizeof(double), kt);
		for (int i = 0; i < kt - 1; i++) {
			if (i == 0)
				uk[i] = -(arr[n - 1][i + 1] + f(i*sth + sth, n*sttau) + kurt* arr[n][0]);
			if (i == kt - 2)
				uk[i] = -(arr[n - 1][i + 1] + f(i*sth + sth, n*sttau) + kurt* arr[n][kt]);
			uk[i] = -(arr[n - 1][i + 1] + f(i*sth + sth, n*sttau));
		}
		matrvect(uk,otv);
		for (int i = 0; i < kt - 1; i++)
			arr[n][i + 1] = otv[i];
		delete[] otv, uk;
	}
};
void main()
{
	Teplo *teplo = new Teplo();
	teplo->write();
	//teplo->printtridiag();
	inversion(teplo->tridiag, teplo->kt - 1);
	//teplo->printtridiag();
	for (int i = 1; i <= teplo->jt;i++)
		teplo->vychsloy(i);
	//teplo->write();
	printf("\n");
	for (int i = 0; i < teplo->kt +1; i++) {
		printf("\n");
		for (int j = 0; j < teplo->jt; j++)
			printf("%lf ", teplo->u(i*teplo->sth, j*teplo->sttau));
	}
	printf("\n");
	delete teplo;
}