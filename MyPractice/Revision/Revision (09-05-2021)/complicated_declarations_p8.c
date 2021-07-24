/*
Declare an array 5 of pointers to function accepting
    1. a pointer to function taking int returning void 
    returning
        pointer to array of pointer to function
        accepting two ints
        returning int

    int (*(*(*arr[5])(void (*)(int)))[3])(int, int);
*/

#include <stdio.h>
#include <stdlib.h>

void ip_function_1(int n){
    printf("inside of ip_function_1: n = %d\n", n);
}
void ip_function_2(int n){
    printf("inside of ip_function_2: n*n = %d\n", n*n);
}
void ip_function_3(int n){
    printf("inside of ip_function_3: n*n*n = %d\n", n*n*n);
}
void ip_function_4(int n){
    printf("inside of ip_function_4: n*n*n*n = %d\n", n*n*n*n);
}
void ip_function_5(int n){
    printf("inside of ip_function_5: n*n*n*n*n = %d\n", n*n*n*n*n);
}

int add(int a, int b){
    puts("inside of function add a = %d, b = %d\n", a, b);
    return (a+b);
}

int sub(int a, int b){
    puts("inside of function sub a = %d, b = %d\n", a, b);
    return (a-b);
}

int mul(int a, int b){
    puts("inside of function mul a = %d, b = %d\n", a, b);
    return (a*b);
}

int quo(int a, int b){
    puts("inside of function div a = %d, b = %d\n", a, b);
    return (a/b);
}

int rem(int a, int b){
    puts("inside of function mod a = %d. b = %d\n", a, b);
    return (a%b);
}

int logical_and(int a, int b){
    puts("inside of function logical_and a = %d, b = %d\n", a, b);
    return (a && b);
}

int logical_or(int a, int b){
    puts("inside of function logical_or a = %d, b = %d\n", a, b);
    return (a || b);
}

int bitwise_and(int a, int b){
    puts("inside of function bitwise_and a = %d, b = %d\n", a, b);
    return (a & b);
}

int bitwise_or(int a, int b){
    puts("inside of function bitwise_or a = %d, b = %d\n", a, b);
    return (a | b);
}

int bitwise_xor(int a, int b){
    puts("inside of function bitwise_xor a = %d, b = %d\n", a, b);
    return (a ^ b);
}

int right_shift(int a, int b){
    puts("inside of function right_shift a = %d, b = %d\n", a, b);
    return (a >> b);
}

int left_shift(int a, int b){
    puts("inside of function left_shift a = %d, b = %d\n", a, b);
    return (a << b);
}

int compute_1(int a, int b){
    puts("inside of function compute_1 a = %d, b = %d\n", a, b);
    return (a*a + b*b);
}

int compute_2(int a, int b){
    puts("inside of function compute_2 a = %d, b = %d\n", a, b);
    return (a*a - b*b);
}

int compute_3(int a, int b){
    puts("inside of function compute_3 a = %d, b = %d\n", a, b);
    return (a*a + 2*a*b + b*b);
}

int (*(*level_1(void (*pfn)(int)))[3])(int, int){
	static int (*pfn_arr[3])(int, int); 
	puts("level_1: Calling raise to 1 function."); 
	pfn(2); 
	puts("level_1:Building array three of pointer to function accepting int, int and returning int"); 
	pfn_arr[0] = add; 
	pfn_arr[1] = sub; 
	pfn_arr[2] = mul; 
	puts("***************Returning from level_1***************");
	return (&pfn_arr); 
}

int (*(*level_2(void (*pfn)(int)))[3])(int, int){
	static int (*pfn_arr[3])(int, int); 
	puts("level_2: Calling raise to 2 function."); 
	pfn(2); 
	puts("level_2:Building array three of pointer to function accepting int, int and returning int"); 
	pfn_arr[0] = quo; 
	pfn_arr[1] = rem; 
	pfn_arr[2] = logical_and; 
	puts("***************Returning from level_2***************");
	return (&pfn_arr); 
}

int (*(*level_3(void (*pfn)(int)))[3])(int, int){
	static int (*pfn_arr[3])(int, int); 
	puts("level_3: Calling raise to 3 function."); 
	pfn(2); 
	puts("level_3:Building array three of pointer to function accepting int, int and returning int"); 
	pfn_arr[0] = logical_or; 
	pfn_arr[1] = bitwise_and; 
	pfn_arr[2] = bitwise_or; 
	puts("***************Returning from level_3***************");
	return (&pfn_arr); 
}

int (*(*level_4(void (*pfn)(int)))[3])(int, int){
	static int (*pfn_arr[3])(int, int); 
	puts("level_4 Calling raise to 4 function."); 
	pfn(2); 
	puts("level_4:Building array three of pointer to function accepting int, int and returning int"); 
	pfn_arr[0] = bitwise_xor; 
	pfn_arr[1] = left_shift; 
	pfn_arr[2] = right_shift; 
	puts("***************Returning from level_4***************");
	return (&pfn_arr); 
}

int (*(*level_5(void (*pfn)(int)))[3])(int, int){
	static int (*pfn_arr[3])(int, int); 
	puts("level_5: Calling raise to 5 function."); 
	pfn(2); 
	puts("level_5:Building array three of pointer to function accepting int, int and returning int"); 
	pfn_arr[0] = compute_1; 
	pfn_arr[1] = compute_2; 
	pfn_arr[2] = compute_3; 
	puts("***************Returning from level_5***************");
	return (&pfn_arr); 
}

int main(void){
	int i; 
	int j; 
	int ret;
	int (*(*pfn_ret)[3])(int, int); 
	int ap1 = 128, ap2 = 4; 

	int (*(*(*pfn_arr[5])(void(*)(int)))[3])(int, int) = 	{	level_1, 
																level_2, 
																level_3, 
																level_4, 
																level_5
															}; 
	void (*ip_arr_pfn[5])(int) = 	{	ip_function_1, 
										ip_function_2, 
										ip_function_3, 
										ip_function_4, 
										ip_function_5
									}; 

	for(i = 0; i < 5; ++i)
	{
		pfn_ret = pfn_arr[i](ip_arr_pfn[i]); 
		for(j = 0; j < 3; ++j)
		{
			ret = (*pfn_ret)[j](ap1, ap2); 
			printf("ret = %d\n", ret); 
		}
		printf("****************************************************\n"); 
	}

	return (EXIT_SUCCESS); 
}
