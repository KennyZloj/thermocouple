#include <stdio.h>
#include <math.h>

const long double polinom0 [9] = {0.00L, 2.5173462e1L, -1.1662878L, -1.0833638L, -8.9773540e-1L, -3.7342377e-1L, -8.6632643e-2L, -1.0450598e-2L, -5.1920577e-4L};
const long double polinom1 [10] = {0.00L, 2.508355e1L, 7.860106e-2L, -2.503131e-1L, 8.315270e-2L, -1.228034e-2L, 9.804036e-4L, -4.413030e-5L, 1.057734e-6L, -1.052755e-8L};
const long double polinom2 [7] = {-1.318058e2L, 4.830222e1L, -1.646031L, 5.464731e-2L, -9.650715e-4L, 8.802193e-6L, -3.110810e-8L};
long double mV;
unsigned char f = 1, mode;

long double thermo_pol (void);

int main (void)
{
while (f)
{

printf ("\nВведи измеренное значение ТЭДС, в mV, 0 для выхода\n\n");
scanf ("%Lf", &mV);

if (mV >= -5.891L && mV <= 54.886L) mode = 0;
if (mV < -5.891L || mV > 54.886L) mode = 1;
if (mV == 0) mode = 2;

switch (mode)
{
	case 0:
	printf ("\nТемпература= %5.2Lf °С\n\n", thermo_pol ());
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

long double thermo_pol (void)
{
unsigned char i;
long double t, h;

t = 0;
h = 0;

if (mV >= -5.891L && mV < 0)
{
	for (i=0;i<9;i++)
	{
		h = polinom0[i] * pow (mV, i);
		t = t + h;
	}
}		
if (mV > 0 && mV < 20.644L)
{
	for (i=0;i<10;i++)
        {
        	h = polinom1[i] * pow (mV, i);
        	t = t + h;
        }
}
if (mV >= 20.644L && mV <= 54.886L)
{
	for (i=0;i<7;i++)
        {
        	h = polinom2[i] * pow (mV, i);
        	t = t + h;
        }
}
return t;
}
