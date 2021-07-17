#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(unsigned long long);
unsigned long long sigma(int *pa, int N);
void print_array_reverse_recursion(int *pa, int N);
void print_array_recursion(int *pa, int index, int size);
void array_reverse_in_place_recursion(int *pa, int start_index, int end_index);
void insertion_sort(int *pa, int size);

int main(void)
{
    unsigned long long n = 15;
    unsigned long long summation = 0;
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int b[15] = {
        414543, 5234, 1234, 123415, 431324,
        448512, 7987513216, 6846, 7592, 5484,
        68121, 7815, 78796551, 87845, 925441
    };
    int i;
    int max_element;
    int index;

    printf("fact(%llu): %llu\n", n, fact(n));
    summation = sigma(a, 10);
    printf("sigma(a, 10): %llu\n", summation);
    print_array_reverse_recursion(a, 10);
    print_array_recursion(a, 0, 10);
    puts("array before inplace reversal: ");
    for(i=0; i<10; i++)
    {
        printf("a[%d]: %d\n", i, a[i]);
    }
    array_reverse_in_place_recursion(a, 0, 9);
    puts("Array after inplace reversal: ");
    for(i=0; i<10; i++)
    {
        printf("a[%d]: %d\n", i, a[i]);
    }
    array_reverse_in_place_recursion(a, 2, 8);
    puts("Array after inplace reverseal A[2, 8]:");
    for(i=0; i<10; i++)
    {
        printf("a[%d]: %d\n", i, a[i]);
    }
    max_element = find_max(b, 0, 14);
    printf("max_element = %d\n", max_element);
    insertion_sort(b, 15);
    for(i=0; i<15; i++)
    {
        index = search(b, b[i], 0, 14);
        printf("Element %d is found at index %d\n", b[i], index);
    }
    return (EXIT_SUCCESS);
}

unsigned long long fact(unsigned long long n)
{
    if(n == 0)
        return (1);
    
    return (n * fact(n-1));
}

unsigned long long sigma(int *pa, int N)
{
    if (N == 0)
        return (0);
    
    return pa[N-1] + sigma(pa, N-1);
}

void print_array_r(int *pa, int index, int size)
{
    if(index == size)
    {
        puts("end");
        return ;
    }
    printf("a[%d]: %d\n", index, pa[index]);
    print_array_recursion(pa, index+1, size);
}

void array_reverse_in_place_recursion(int *pa, int start_index, int end_index)
{
    int tmp;
    if(start_index >= end_index)
        return ;
    tmp = pa[start_index];
    pa[start_index] = pa[end_index];
    pa[end_index] = tmp;
    array_reverse_in_place_recursion(pa, start_index+1, end_index-1);
}

int find_max(int *pa, int start_index, int end_index)
{
    int mid_index;
    int max_L;
    int max_R;
    if(start_index == end_index)
        return pa[start_index];
    mid_index = (start_index + end_index) / 2;
    max_L = find_max(pa, start_index, mid_index);
    max_R = find_max(pa, mid_index + 1, end_index);
    if(max_L > max_R)
        return max_L;
    return max_R;
}

int search(int *pa, int search_element, int start_index, int end_index)
{
    int mid_index;

    if(start_index <= end_index)
    {
        mic_index = (start_index + end_index) / 2;
        if(search_element == pa[mid_index])
            return (mid_index);
        else_if(search_element < pa[mid_index])
            return search(pa, search_element, start_index, mid_index-1);
        else if(search_element > pa[mid_index])
            return search(pa, search_element, mid_index+1, end_index);
    }
    return -1;
}

void insertion_sort(int *pa, int size)
{
    int i, j, key;
    for(j = 1; j < size; j++)
    {
        key = pa[j];
        i = j -1;
        while(i>-1 && pa[i] > key)
        {
            pa[i+1] = pa[i];
            i = i - 1;
        }
        pa[i+1] = key;
    }
}
