#include<stdio.h>

int bitAnd(int x, int y) { 
	return ~(~x|~y);
}

int divpwr2(int x, int n) {
	int bias = (1<<n)-1;
	int sign = x>>31;
	bias = bias & (~sign+1);
	return (x+bias)>>n;
}

int addOK(int x, int y) {
	int x_sign = x>>31;
	int y_sign = y>>31;
	int	 r = x+y;
	int r_sign = r>>31;
	int temp = ((x_sign ^ y_sign)|(~(x_sign ^ r_sign)));
	//printf ("%d\n",   x_sign ^ y_sign);	
	//printf ("%d\n",   x_sign ^ r_sign);	
	//printf ("%d\n",~(x_sign ^ r_sign));
	return temp&1;
}

int conditional(int x, int y, int z) {
	printf ("%d\n",(!x)&z);
	printf ("%d\n",(!!x));
	return ((!x)&z) + ((!!x)&y);
}

/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *
 *   Argument is passed as unsigned int, but it is to be
 *   interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *
 *   Fractional portion of value should be truncated.
 *   Anything out of range (including NaN and infinity)
 *   should return 0x80000000u.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&, <, >, etc.
 *   Also allowed: if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
	unsigned sign 	  = uf >> 31;		
	unsigned exponent = (uf>>23) & 0xFF;	// exponent is in lower 8 bits 
	unsigned frac     = uf & 0x7FFFFF;	// frac     is in lower 23 bits
	printf ("sign: %x\n", sign);
	printf ("exponent: %d\n", exponent);
	printf ("frac: %x\n", frac);
	printf ("=================================\n");

	int M;
	int result;
	int E = exponent - 127;			// -126 ... 127
			
	// Nan or infinity
	if (exponent == 255) {
		printf ("NaN\n");
		return 0x80000000u;	
	}
	// denormalized, the integer is zero
	if (exponent == 0) {
		printf ("Denormalized\n");
		return 0;
	}
	
	// Following is the normalized situations
	printf ("Normalized\n");
	printf ("E: %d\n",E);
	printf ("frac: %x\n",frac);

	if (E < 0 ) {
		result = 0;
	}
	
	else if (E == 0) {
		result = 1;	
	}
	
	else if ( (E > 0) && (E < 31) ) {
		M = (frac|0x800000);
		printf ("M: %x\n",M);
		M = (M << E);
		printf ("M: %x\n",M);
		M = (M >> 23);
		result = M;
	}

	else {
		printf ("Out of Range\n");
		result = 0x80000000u;	
	}

	if (sign == 1) {
		result = (~result + 1);
	}
	return result; 
}



int main (int argc, char** argv) {
	int a = 255;
	int b =  23;
	int c =  11;
	//int result =   bitAnd(a,b);
	//int f = conditional(a,b,c);
	//int f =     divpwr2(-33,4);
	//int f = addOK(0x80000000,0x70000000);
	//int f = conditional(2, 4, 5);
		
	unsigned t = 130;
	t = t << 23;
	
	unsigned sign 	  = 1;
	unsigned exponent = 129;
	unsigned frac     = 0x700000;
	unsigned M;
	t = (sign << 31) | (exponent << 23) | (frac);
	
	
	int f = float_f2i(t);
	printf("%d\n",f);

	return 0;
}










