#include "Comms.hh"

template <class T>
class ZeromqComms : Comms<T>
{
   public:
   void post(const T* val)
   {
      printf("Sending...\n");
   }

   void subscribe(void (*)(const char*, const T*))
   {
       
   }
};
