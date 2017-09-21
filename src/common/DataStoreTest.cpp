#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "DataStore.hh"
#include "stuff.hh"



int main(int argc, char** argv)
{
    DataStore ds;
   
    ds.addType<stuff>(200);
}

