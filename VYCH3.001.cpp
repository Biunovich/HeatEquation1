//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//class Teplo1
//{
//private:
//	double ** arr;
//public:
//	int jt, kt;
//	double sttau, sth, kurt, *a, *b, *c,*uk,*x;
//	double A = 0.033;
//	double f(double x, double t)
//	{
//		return(x + 2 * t - exp(x) + A*(12 * pow(x, 2) - 2 + t*exp(x)));
//	}
//	double nu(double x)
//	{
//		return(-pow(x, 4) + pow(x, 2));
//	}
//	double nu1(double t)
//	{
//		return(pow(t, 2) - t);
//	}
//	double nu2(double t)
//	{
//		return(t + pow(t, 2) - t*exp(1.0));
//	}
//	double u(double x, double t)
//	{
//		return(-pow(x, 4) + pow(x, 2) + t*x + pow(t, 2) - t*exp(x));
//	}
//	void write()
//	{
//		for (int i = 0; i < jt + 1; i++) {
//			for (int j = 0; j < kt + 1; j++)
//				printf("%lf ", arr[i][j]);
//			printf("\n");
//		}
//	}
//	void writetri()
//	{
//		for (int i = 0; i < kt - 1; i++)
//		{
//			printf("%lf %lf %lf", b[i],c[i],a[i]);
//			printf("\n");
//		}
//	}
//	Teplo1()
//	{
//		printf("VVEDITE KOLLICHESTVO VREMENNYH SLOEV ");
//		scanf("%d", &jt);
//		printf("VVEDITE KOLLICHESTVO DELENIY STERZHNYA ");
//		scanf("%d", &kt);
//		printf("\n");
//		sttau = 1.0 / jt;
//		sth = 1.0 / kt;
//		kurt = (A * sttau) / pow(sth, 2);
//		arr = (double**)calloc(sizeof(double*), jt + 1);
//		for (int i = 0; i < jt + 1; i++)
//			arr[i] = (double*)calloc(sizeof(double), kt + 1);
//		for (int i = 0; i <= kt; i++)
//		{
//			arr[0][i] = nu(i*sth);
//		}
//		for (int i = 1; i < jt + 1; i++) {
//			arr[i][0] = nu1(i*sttau);
//			arr[i][kt] = nu2(i*sttau);
//		}
//		a = (double*)calloc(sizeof(double), kt);
//		b = (double*)calloc(sizeof(double), kt);
//		c = (double*)calloc(sizeof(double), kt);
//		uk = (double*)calloc(sizeof(double), kt);
//		x = (double*)calloc(sizeof(double), kt);
//		for (int i = 0; i < kt - 1; i++)
//		{
//			b[i] = kurt;
//			c[i] = -(1 + 2 * kurt);
//			a[i] = kurt;
//		}
//		a[0] = 0; b[kt - 2] = 0;
//	}
//	double * progon()
//	{
//		double m;
//		for (int i = 1; i < kt-1; i++)
//		{
//			m = a[i] / c[i - 1];
//			c[i] = c[i] - m*b[i - 1];
//			uk[i] = uk[i] - m*uk[i - 1];
//		}
//
//		x[kt - 2] = uk[kt - 2] / c[kt - 2];
//
//		for (int i = kt - 3; i >= 0; i--)
//			x[i] = (uk[i] - b[i] * x[i + 1]) / c[i];
//		return x;
//	}
//	void vychsloy(int n)
//	{
//		double *otv;
//		for (int i = 0; i < kt - 1; i++)
//		{
//			if (i == 0)
//				uk[i] = -(arr[n - 1][i + 1] + sttau*f(i*sth + sth, n*sttau) + kurt*arr[n][0]);
//			if (i == kt - 2)
//				uk[i] = -(arr[n - 1][i + 1] + sttau*f(i*sth + sth, n*sttau) + kurt*arr[n][kt]);
//			uk[i] = -(arr[n - 1][i + 1] + sttau*f(i*sth + sth, n*sttau));
//		}
//		otv = progon();
//		for (int i = 0; i < kt - 1; i++)
//			arr[n][i + 1] = otv[i];
//		for (int i = 0; i < kt - 1; i++)
//		{
//			b[i] = kurt;
//			c[i] = -(1 + 2 * kurt);
//			a[i] = kurt;
//		}
//		a[0] = 0; b[kt - 2] = 0;
//	}
//};
//void main()
//{
//	Teplo1 *teplo = new Teplo1();
//	teplo->write();
//	teplo->writetri();
//	for (int i = 1; i < teplo->jt + 1; i++)
//		teplo->vychsloy(i);
//	teplo->write();
//}