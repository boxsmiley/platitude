#ifndef DATA_STORE
#define DATA_STORE

#include <string.h>
#include <typeinfo>
#include <typeindex>
#include <stdio.h>
#include <map>
#include "DataTable.hh"
#include "stuff.hh"

class DataStore
{

   private:
   std::map<std::type_index, void*> tables;

   template<typename T> 
   DataTable<T>* get()
   {
      return (DataTable<T>*)tables[typeid(T)];
   }

   public:
   
   DataStore() 
   {
   }

   template<typename T> 
   void addType(int numItems)
   {
      void* val = new DataTable<T>(numItems);
      tables[typeid(T)] = val;
   }

   template<typename T> 
   int put(T* items, int numItems)
   {
       DataTable<T>* table = get<T>();
       return table->put(items, numItems); 
   }


   template<typename T> 
   DataIterator<T> get(int* retItems) {
       DataTable<T>* table = get<T>();
       return table->get(retItems);
   }

   virtual ~DataStore()
   {
      printf("Destructor called\n");
   }

};

#endif
