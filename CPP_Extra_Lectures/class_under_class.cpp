#include <iostream>
#include <cstdlib>

class Outer
{
    private:
        int m, n;

    public:
        Outer(int init_m, int init_n)
        {
            m = init_m;
            n = init_n;
        }
        int get_m()
        {
            return m;
        }

        int get_n()
        {
            return n;
        }

        void set_m(int new_m)
        {
            m = new_m;
        }
        
        void set_n(int new_n)
        {
            n = new_n;
        }

        void show(const char *msg)
        {
            if(msg)
                puts(msg);
            printf("n = %d, m = %d\n", n, m);
        }

        class Inner
        {
            private:
                int a, b;
            
            public:
                Inner (int init_a, int init_b)
                {
                    a = init_a;
                    b = init_b;
                }

                int get_a()
                {
                    return a;
                }

                int get_b()
                {
                    return b;
                }

                void set_a(int new_a)
                {
                    a = new_a;
                }

                void set_b(int new_b)
                {
                    b = new_b;
                }
                
                void show(const char *msg)
                {
                    if(msg)
                        puts(msg);
                    printf("a = %d, b = %d\n", a, b);        
                }
        };
};

int main(void)
{
    Outer :: Inner ObjInner(100, 200);
    Outer  ObjOuter(10, 20);

    ObjInner.show("ObjInner: ");
    ObjOuter.show("ObjOuter: ");

    ObjInner.set_a(1000);
    ObjInner.set_b(2000);

    ObjOuter.set_n(10000);
    ObjOuter.set_m(20000);

    printf("a = %d, b = %d\n", ObjInner.get_a(), ObjInner.get_b());
    printf("m = %d, n = %d\n", ObjOuter.get_n(), ObjOuter.get_m());

    return 0;
}