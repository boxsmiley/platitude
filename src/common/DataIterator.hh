template<class T>
class DataIterator
{

   private:
      int currIdx;
      int allocItems;
      T* storage;

   public:
      DataIterator(int currIdx, int allocItems, T* storage)
      {
         this->currIdx = currIdx;
         this->allocItems = allocItems;
         this->storage = storage;
      }

      T* next()
      {
         T* ret = &storage[currIdx];
         currIdx = (currIdx+1) % allocItems; 
         return ret;
      }

};
