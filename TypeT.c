#include <stdio.h>
#include <math.h>

const long double polinom0 [8] = {0.00L, 2.5949192e1L, -2.1316967e-1L, 7.9018692e-1L, 4.2527777e-1L, 1.3304473e-1L, 2.0241446e-2L, 1.2668171e-3L};
const long double polinom1 [7] = {0.00L, 2.592800e1L, -7.602961e-1L, 4.637791e-2L, -2.165394e-3L, 6.048144e-5L, -7.293422e-7L};
long double mV;
unsigned char f = 1, mode;

long double thermo_pol (void);

int main (void)
{
while (f)
{

printf ("\nВведи измеренное значение ТЭДС, в mV, 0 для выхода\n\n");
scanf ("%Lf", &mV);

if (mV >= -5.603L && mV <= 20.872L) mode = 0;
if (mV < -5.603L || mV > 20.872L) mode = 1;
if (mV == 0) mode = 2;

switch (mode)
{
	case 0:
	printf ("\nТемпература= %4.2Lf °С\n\n", thermo_pol ());
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

if (mV >= -5.603L && mV < 0)
{
	for (i=0;i<8;i++)
	{
		h = polinom0[i] * pow (mV, i);
		t = t + h;
	}
}		
if (mV > 0 && mV <= 20.872L)
{
	for (i=0;i<7;i++)
        {
        	h = polinom1[i] * pow (mV, i);
        	t = t + h;
        }
}
return t;
}
