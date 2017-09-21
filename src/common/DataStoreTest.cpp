#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "DataStore.hh"
#include "stuff.hh"



int main(int argc, char** argv)
{
    DataStore ds;
   
    ds.addType<stuff>(10);

    int put = 0;
    //for(int i=0;i<13;i++)
    for(int i=0;i<1;i++)
    {
      stuff curr;
      curr.a = i;
      put = ds.put(&curr, 1);

      printf("Stored now contains: %d items\n", put);
    }


   int numItems;
   DataIterator<stuff> retrieved = ds.get<stuff>(&numItems);

   for (int i=0;i<numItems;i++)
   {
      printf("query: %d\n", retrieved.next()->a);
   }


}

