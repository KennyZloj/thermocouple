#include <stdio.h>
#include <math.h>

const long double polinom0 [15] = {0.00L, 3.8748106364e-2L, 4.4194434347e-5L, 1.1844323105e-7L, 2.0032973554e-8L, 9.0138019559e-10L, 2.2651156593e-11L, 3.6071154205e-13L, 3.8493939883e-15L, 2.8213521925e-17L, 1.4251594779e-19L, 4.8768662286e-22L, 1.0795539270e-24L, 1.3945027062e-27L, 7.9795153927e-31L};
const long double polinom1 [9] = {0.00L, 3.8748106364e-2L, 3.3292227880e-5L, 2.0618243404e-7L, -2.1882256846e-9L, 1.0996880928e-11L, -3.0815758772e-14L, 4.5479135290e-17L, -2.7512901673e-20L};
long double t;
unsigned char f = 1, mode;

long double thermo_rpol (void);

void main (void)
{
while (f)
{

printf ("\nВведи измеренное значение температуры, в °С, 0 для выхода\n\n");
scanf ("%Lf", &t);

if (t >= -270.00L && t <= 400.00L) mode = 0;
if (t < -270.00L || t > 400.00L) mode = 1;
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
	for (i=0;i<15;i++)
	{
		h = polinom0[i] * pow (t, i);
		mV = mV + h;
	}
}		
if (t > 0 && t <= 400.00L)
{
	for (i=0;i<9;i++)
        {
		h = polinom1[i] * pow (t, i);
		mV = mV + h;
	}
}
return mV;
}
