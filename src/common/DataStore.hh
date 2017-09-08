#ifndef DATA_STORE
#define DATA_STORE

#include <string.h>
#include <stdio.h>
#include <vector>
#include "DataTable.hh"

class DataStore
{

   private:
   std::vector<void*> tables;

   public:
   
   DataStore() 
   {
   }

   template<typename T> 
   void addType(int numItems)
   {
      tables.push_back(new DataTable<T>(numItems));
   }
 

   virtual ~DataStore()
   {
      printf("Destructor called\n");
   }

};

#endif
