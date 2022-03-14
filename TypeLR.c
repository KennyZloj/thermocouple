#include <stdio.h>
#include <math.h>

const long double polinom0 [9] = {-5.8952244e-5L, 6.3391502e-2L, 6.7592964e-5L, 2.0672566e-7L, 5.5720884e-9L, 5.7133860e-11L, 3.2995593e-13L, 9.9232420e-16L, 1.2079584e-18L};
const long double polinom1 [9] = {-1.8656953e-5L, 6.3310975e-2L, 6.0153091e-5L, -8.0073134e-8L, 9.6946071e-11L, -3.6047289e-14L, -2.4694775e-16L, 4.2880341e-19L, -2.0725297e-22L};
long double t;
unsigned char f = 1, mode;

long double thermo_rpol (void);

int main (void)
{
while (f)
{

printf ("\nВведи измеренное значение температуры, в °С, 0 для выхода\n\n");
scanf ("%Lf", &t);

if (t >= -200.00L && t <= 800.00L) mode = 0;
if (t < -200.00L || t > 800.00L) mode = 1;
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

if (t >= -200.00L && t < 0)
{
	for (i=0;i<9;i++)
	{
		h = polinom0[i] * pow (t, i);
		mV = mV + h;
	}
}		
if (t > 0 && t <= 800.00L)
{
	for (i=0;i<9;i++)
        {
		h = polinom1[i] * pow (t, i);
		mV = mV + h;
	}
}
return mV;
}
