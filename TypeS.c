#include <stdio.h>
#include <math.h>

const long double polinom0 [10] = {0.00L, 1.84949460e2L, -8.00504062e1L, 1.02237430e2L, -1.52248592e2L, 1.88821343e2L, -1.59085941e2L, 8.23027880e1L, -2.34181944e1L, 2.79786260L};
const long double polinom1 [10] = {1.291507177e1L, 1.466298863e2L, -1.534713402e1L, 3.145945973L, -4.163257839e-1L, 3.187963771e-2L, -1.291637500e-3L, 2.183475087e-5L, -1.447379511e-7L, 8.211272125e-9L};
const long double polinom2 [6] = {-8.087801117e1L, 1.621573104e2L, -8.536869453L, 4.719686976e-1L, -1.441693666e-2L, 2.081618890e-4L};
const long double polinom3 [5] = {5.333875126e4L, -1.235892298e4L, 1.092657613e3L, -4.265693686e1L, 6.247205420e-1L};
long double mV;
unsigned char f = 1, mode;

long double thermo_pol (void);

void main (void)
{
while (f)
{

printf ("\nВведи измеренное значение ТЭДС, в mV, 0 для выхода\n\n");
scanf ("%Lf", &mV);

if (mV >= -0.235L && mV <= 18.694L) mode = 0;
if (mV < -0.235L || mV > 18.694L) mode = 1;
if (mV == 0) mode = 2;

switch (mode)
{
	case 0:
	printf ("\nТемпература= %5.2Lf ºС\n\n", thermo_pol ());
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

if (mV >= -0.235L && mV < 1.874L)
{
	for (i=0;i<10;i++)
	{
		h = polinom0[i] * pow (mV, i);
		t = t + h;
	}
}		
if (mV >= 1.874L && mV < 10.332L)
{
	for (i=0;i<10;i++)
        {
        	h = polinom1[i] * pow (mV, i);
        	t = t + h;
        }
}
if (mV >= 10.332L && mV < 17.536L)
{
	for (i=0;i<6;i++)
        {
        	h = polinom2[i] * pow (mV, i);
        	t = t + h;
        }
}
if (mV >= 17.536L && mV <= 18.694L)
{
	for (i=0;i<5;i++)
        {
        	h = polinom3[i] * pow (mV, i);
        	t = t + h;
        }
}
return t;
}
