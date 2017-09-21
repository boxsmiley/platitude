#ifndef DATA_STORE
#define DATA_STORE

#include <string.h>
#include <typeinfo>
#include <stdio.h>
#include <map>
#include "DataTable.hh"

class DataStore
{

   private:
   std::map<const std::type_info, void*> tables;

   public:
   
   DataStore() 
   {
   }

   template<typename T> 
   void addType(int numItems)
   {
      tables.insert(std::make_pair<std::type_info, void*>(typeid(T), new DataTable<T>(numItems)));
   }

   template<typename T> 
   DataTable<T>* get()
   {
      return tables[typeid(T)];
   }
 

   virtual ~DataStore()
   {
      printf("Destructor called\n");
   }

};

#endif
