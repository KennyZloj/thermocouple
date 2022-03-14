#include <stdio.h>
#include <math.h>

const long double polinom0 [11] = {0.00L, 3.9450128025e-2L, 2.3622373598e-5L, -3.2858906784e-7L, -4.9904828777e-9L, -6.7509059173e-11L, -5.7410327428e-13L, -3.1088872894e-15L, -1.0451609365e-17L, -1.9889266878e-20L, -1.6322697486e-23L};
const long double polinom1 [10] = {-1.7600413686e-2L, 3.8921204975e-2L, 1.8558770032e-5L, -9.9457592874e-8L, 3.1840945719e-10L, -5.6072844889e-13L, 5.6075059059e-16L, -3.2020720003e-19L, 9.7151147152e-23L, -1.2104721275e-26L};
const long double coef [2] = {1.185976e-1L, -1.183432e-4L};
long double t;
unsigned char f = 1, mode;

long double thermo_rpol (void);

int main (void)
{
while (f)
{

printf ("\nВведи измеренное значение температуры, в °С, 0 для выхода\n\n");
scanf ("%Lf", &t);

if (t >= -270.00L && t <= 1372.00L) mode = 0;
if (t < -270.00L || t > 1372.00L) mode = 1;
if (t == 0) mode = 2;

switch (mode)
{
	case 0:
	printf ("\nТЭДС= %2.3Lf mV\n\n", thermo_rpol ());
	break;

	case 1:
	printf ("\nЗначение вне диапазона\n\n");
        break;

	case 2:
	f = 0;
	printf ("\nВыход\n\n");
	break;

	default:
	break;
}

}
}

long double thermo_rpol (void)
{
unsigned char i;
long double mV, h;

mV = 0;
h = 0;

if (t >= -270.00L && t < 0)
{
	for (i=0;i<11;i++)
	{
		h = polinom0[i] * pow (t, i);
		mV = mV + h;
	}
}		
if (t > 0 && t <= 1372.00L)
{
	for (i=0;i<10;i++)
        {
		h = polinom1[i] * pow (t, i);
		mV = mV + h;
	}
	mV = mV + (coef[0] * exp (coef[1] * pow((t - 126.9686L),2)));
}
return mV;
}
