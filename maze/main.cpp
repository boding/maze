#include <stdio.h>
#include <stdlib.h>
#include <functional>

#define NUMSHADOWS 4

template<typename T> class maze
{
public:
    maze() : hash(0), index(0)
    {}

    void set(T t)
    {
        hash = (unsigned char)(rand() % 256);
        index = rand() % NUMSHADOWS;

        unsigned char* src = (unsigned char*)&t;
        unsigned char* dst = (unsigned char*)&shadows[index];

        auto size = sizeof(T);
        for (auto i=0u; i<size; ++i)
        {
            *dst++ = *src++ ^ hash;
        }
    }

    T get()
    {
        T t;

        unsigned char* src = (unsigned char*)&t;
        unsigned char* dst = (unsigned char*)&shadows[index];

        auto size = sizeof(T);
        for (auto i=0u; i<size; ++i)
        {
            *src++ = *dst++ ^ hash;
        }

        return t;
    }

protected:
    T shadows[NUMSHADOWS];
    unsigned char hash;
    unsigned int index;
};

int main()
{
    maze<bool> vb;
    vb.set(true);
    bool r = vb.get();

    maze<int> vars[3];
    for (int i=0; i<3; ++i)
    {
        vars[i].set(0);
    }

    for (int i=0; i<3; ++i)
    {
        int j = vars[i].get();
        j;
    }

    vars[0].set(111);
    int ret = vars[0].get();
    ret = vars[0].get();

    return 0;
}