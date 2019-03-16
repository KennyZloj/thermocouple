#include <stdio.h>
#include <math.h>

const long double polinom0 [10] = {1.1573067e-4L, 1.5884573e1L, 4.0458554e-2L, 0.3170064L, 0.1666128L, 5.1946958e-2L, 9.5288883e-3L, 1.0301283e-3L, 6.0654431e-5L, 1.5131878e-6L};
const long double polinom1 [10] = {7.2069422e-3L, 1.5775525e1L, -0.2261183L, 9.4286756e-3L, -3.5394655e-4L, 1.0050886e-5L, -1.9323678e-7L, 2.3816891e-9L, -1.7130654e-11L, 5.4857331e-14L};
long double mV;
unsigned char f = 1, mode;

long double thermo_pol (void);

void main (void)
{
while (f)
{

printf ("\nВведи измеренное значение ТЭДС, в mV, 0 для выхода\n\n");
scanf ("%Lf", &mV);

if (mV >= -9.488L && mV <= 66.466L) mode = 0;
if (mV < -9.488L || mV > 66.466L) mode = 1;
if (mV == 0) mode = 2;

switch (mode)
{
	case 0:
	printf ("\nТемпература= %4.2Lf ºС\n\n", thermo_pol ());
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

if (mV >= -9.488L && mV < 0)
{
	for (i=0;i<10;i++)
	{
		h = polinom0[i] * pow (mV, i);
		t = t + h;
	}
}		
if (mV > 0 && mV <= 66.466L)
{
	for (i=0;i<10;i++)
        {
        	h = polinom1[i] * pow (mV, i);
        	t = t + h;
        }
}
return t;
}
