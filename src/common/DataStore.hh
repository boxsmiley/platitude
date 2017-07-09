#include <string.h>

template<class T>
class DataStore
{

   private:
   int numItems;
   int currItems;
   T* storage;
   DataStore() {}


   public:
   DataStore(int numItems)
   {
      this->currItems = 0;
      this->numItems = numItems;
      printf("Storing: %d of %ld sized items\n", numItems,sizeof(T));
      this->storage = new T[numItems];
   }

   int put(T* items, int newItems) 
   { 
      if (currItems + newItems > this->numItems)
      {
          printf("Number of put items exceeds allocation of: %d\n",
                            numItems);
      }
      else
      {
         memcpy(&storage[currItems], items, sizeof(T) * newItems);
         currItems++;
      }
      return currItems;
   }

   T* get(int* numItems) { *numItems = this->numItems; return storage; }
   
   int getNum() { return numItems; }

   virtual ~DataStore()
   {
      printf("Destructor called\n");
      delete [] storage;
   }

};

