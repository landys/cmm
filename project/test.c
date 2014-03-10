/************* test.c *****************/
/**************************************/
int main(void)
{	/* comment */
	int i;
	int j;	/* comment */
	int d;
	int t;
	
	/* testing
	comment */
	output(62);	/* output letter > */	
	
	t = input(); /* Input a letter as ASCII code */
	t = t - 48; /* the 0's ASCII code is 48 */
	i = t + 1 - t / 2;
	j = 2+3*4-6;	/* comment */
	/***a/*a/****/
	d = (i=2*2) + j * 2 / 4 + t + 97;	/* 97 is the ASCII code of a */
	
	output(10);	/* output letter \n */
	output(32); /* output letter black */
	output(100); /* output letter d */
	output(61); /* output letter = */
	output(39);	/* output letter ' */
	output(d); /* output letter as ASCII code */
	output(39);	/* output letter ' */
	output(32); /* output letter black */
	output(58);	/* output letter : */
	output(41);	/* output letter ) */
	
	return 0;
}
