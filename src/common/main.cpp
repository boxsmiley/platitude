#include <stdio.h>
#include <DataStore.hh>



struct stuff
{
   int a;
   int b;
   int c;
   unsigned char filler[3];
   unsigned char name[245];
};

int main(int argc, char** argv)
{
   DataStore<stuff> d(10);

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



