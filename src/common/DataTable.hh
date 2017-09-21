#ifndef DATA_TABLE
#define DATA_TABLE

#include <string.h>
#include <vector>
#include "DataIterator.hh"

template<class T>
class DataTable
{

   private:

   int allocItems;
   int currIdx;
   int numItems;
   T* storage;
   DataTable() {}
   std::vector<void (*)(const char*, const T*)> callbacks;


   public:
   DataTable(int allocItems)
   {
      this->currIdx = 0;
      this->numItems = 0;
      this->allocItems = allocItems;
      printf("Storing: %d of %ld sized items\n", allocItems,sizeof(T));
      this->storage = new T[allocItems];
   }

   int put(T* items, int newItems) 
   { 
      for (int i=0;i<callbacks.size();i++)
      {
             callbacks[i]("putting stuff\n", items);
      }
      memcpy(&storage[currIdx], items, sizeof(T) * newItems);
      this->currIdx = (this->currIdx+newItems) % this->allocItems;
      this->numItems+=newItems;
      return numItems;
   }

   void addListener(void (callback)(const char*, const T*))
   {
      this->callbacks.push_back(callback);
   }

   DataIterator<T> get(int* retItems) { 

         *retItems = this->numItems < allocItems ? this->numItems : allocItems; 
 
         int getIdx = this->numItems < allocItems ? 0 : currIdx;

         return DataIterator<T>(getIdx, allocItems, storage); 
   }
   
   int getNum() { return numItems; }

   virtual ~DataTable()
   {
      printf("Destructor called\n");
      delete [] storage;
   }

};


#endif
