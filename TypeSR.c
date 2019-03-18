#include <stdio.h>
#include <math.h>

const long double polinom0 [9] = {0.00L, 5.40313308631e-3L, 1.25934289740e-5L, -2.32477968689e-8L, 3.22028823036e-11L, -3.31465196389e-14L, 2.55744251786e-17L, -1.25068871393e-20L, 2.71443176145e-24L};
const long double polinom1 [5] = {1.32900444085L, 3.34509311344e-3L, 6.54805192818e-6L, -1.64856259209e-9L, 1.29989605174e-14L};
const long double polinom2 [5] = {1.46628232636e2L, -2.58430516752e-1L, 1.63693574641e-4L, -3.30439046987e-8L, -9.43223690612e-15L};
long double t;
unsigned char f = 1, mode;

long double thermo_rpol (void);

void main (void)
{
while (f)
{

printf ("\nВведи измеренное значение температуры, в °С, 0 для выхода\n\n");
scanf ("%Lf", &t);

if (t >= -50.00L && t <= 1768.10L) mode = 0;
if (t < -50.00L || t > 1768.10L) mode = 1;
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

if (t >= -50.00L && t < 1064.18L)
{
	for (i=0;i<9;i++)
	{
		h = polinom0[i] * pow (t, i);
		mV = mV + h;
	}
}		
if (t >= 1064.18L && t < 1664.50L)
{
	for (i=0;i<5;i++)
        {
		h = polinom1[i] * pow (t, i);
		mV = mV + h;
	}
}
if (t >= 1664.50L && t <= 1768.10L)
{
	for (i=0;i<5;i++)
        {
		h = polinom2[i] * pow (t, i);
		mV = mV + h;
	}
}
return mV;
}
