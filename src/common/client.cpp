#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "DataTable.hh"
#include "ZeromqComms.hh"
#include "stuff.hh"


ZeromqComms<stuff> comms(ZMQ_SUB);

void listener(const char* update, const stuff* newVal)
{
   printf("listener 1: %s %d\n", update, newVal->a);
}

int main(int argc, char** argv)
{
   comms.subscribe(listener);

   //while (1)
      //sleep(10000);
}

