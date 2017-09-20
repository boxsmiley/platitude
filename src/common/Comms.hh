template <class T>
class Comms
{
   public:
   virtual void post(const T*) = 0;
   virtual void subscribe(void (*)(const char*, const T*)) = 0;

};
