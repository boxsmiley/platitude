#include <stdio.h>
#include "DataTable.hh"
#include "ZeromqComms.hh"
#include "stuff.hh"
#include <stdlib.h>



ZeromqComms<stuff> comms(ZMQ_PUB);

void listener(const char* update, const stuff* newVal)
{
   printf("listener 1: %s %d\n", update, newVal->a);
   comms.post(newVal); 
}
void listener2(const char* update, const stuff* newVal)
{
   printf("listener 2: %s %d\n", update, newVal->a);
}

int main(int argc, char** argv)
{

   DataTable<stuff> d(10);


   d.addListener(listener);
   d.addListener(listener2);


   int put = 0;
   for(int i=0;i<13;i++)
   //for(int i=0;i<1000000;i++)
   {
      stuff curr;
      curr.a = i;
      put = d.put(&curr, 1);

      printf("Stored now contains: %d items\n", put);

   }


   int numItems;
   DataIterator<stuff> retrieved = d.get(&numItems);

   for (int i=0;i<numItems;i++)
   {
      printf("query: %d\n", retrieved.next()->a);
   }

}



