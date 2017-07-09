#include <stdio.h>
#include "DataTable.hh"



struct stuff
{
   int a;
   int b;
   int c;
   unsigned char filler[3];
   unsigned char name[245];
};

void listener(const char* update)
{
   printf("listener 1: %s\n", update);
}
void listener2(const char* update)
{
   printf("listener 2: %s\n", update);
}

int main(int argc, char** argv)
{
   DataTable<stuff> d(10);
   d.addListener(listener);
   d.addListener(listener2);


   int put = 0;
   for(int i=0;i<20;i++)
   {
      stuff curr;
      curr.a = i;
      put = d.put(&curr, 1);

      printf("Stored now contains: %d items\n", put);

   }

   int numItems;
   stuff* retrieved = d.get(&numItems);

   for (int i=0;i<numItems;i++)
   {
      printf("query: %d\n", retrieved[i].a);
   }

}



