#include <string.h>
#include <vector>

template<class T>
class DataTable
{

   private:

   int allocItems;
   int numItems;
   int currItemIdx;
   T* storage;
   DataTable() {}
   std::vector<void (*)(const char*)> callbacks;


   public:
   DataTable(int allocItems)
   {
      this->currItemIdx = 0;
      this->numItems = 0;
      this->allocItems = allocItems;
      printf("Storing: %d of %ld sized items\n", allocItems,sizeof(T));
      this->storage = new T[allocItems];
   }

   int put(T* items, int newItems) 
   { 
      this->currItemIdx = (this->currItemIdx+1) % this->allocItems;

      for (int i=0;i<callbacks.size();i++)
      {
             callbacks[i]("putting stuff\n");
      }
      memcpy(&storage[currItemIdx], items, sizeof(T) * newItems);
      this->numItems++;
      return numItems;
   }

   void addListener(void (callback)(const char*))
   {
      this->callbacks.push_back(callback);
   }

   T* get(int* numItems) { *numItems = this->numItems; return storage; }
   
   int getNum() { return numItems; }

   virtual ~DataTable()
   {
      printf("Destructor called\n");
      delete [] storage;
   }

};

