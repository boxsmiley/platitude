#include <string.h>
#include <vector>

template<class T>
class DataStore
{

   private:
   int numItems;
   int currItems;
   T* storage;
   DataStore() {}
   std::vector<void (*)(const char*)> callbacks;


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
         for (int i=0;i<callbacks.size();i++)
         {
             callbacks[i]("putting stuff\n");
         }
         memcpy(&storage[currItems], items, sizeof(T) * newItems);
         currItems++;
      }
      return currItems;
   }

   void addListener(void (callback)(const char*))
   {
      this->callbacks.push_back(callback);
   }

   T* get(int* numItems) { *numItems = this->numItems; return storage; }
   
   int getNum() { return numItems; }

   virtual ~DataStore()
   {
      printf("Destructor called\n");
      delete [] storage;
   }

};

