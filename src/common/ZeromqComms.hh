#include "Comms.hh"
#include <string>
#include <zmq.hpp>
#include <unistd.h>

template <class T>
class ZeromqComms : Comms<T>
{
   private:
     std::string hostname = "localhost";
     int port = 5555;
     zmq::message_t update;
     zmq::context_t* context;
     zmq::socket_t* sock;


   public:
   ZeromqComms(int pubOrSub)
   {
       context = new zmq::context_t(1);
       sock = new zmq::socket_t(*context, pubOrSub);

       if (pubOrSub == ZMQ_PUB)
       {
          std::string addy = "tcp://*:";
          addy+=std::to_string(port);
          sock->bind(addy);
          sleep(2);
       }
       else
       {
          std::string addy = "tcp://";
          addy+=hostname + ":";
          addy+=std::to_string(port);
          printf("addy: %s\n", addy.c_str());
          sock->connect(addy);
          sock->setsockopt(ZMQ_SUBSCRIBE, "", 0);

       }
   }
   

   void post(const T* val)
   {
      printf("Sending...\n");
      //while (1)
      {
         zmq::message_t msg(sizeof(T)); 
         memcpy((char*)msg.data(), val, sizeof(T));
         sock->send(msg);
      }
   }

   void subscribe(void (f)(const char* topic, const T* val))
   {

      while (1)
      {
         printf("waiting for some stuff\n");
         sock->recv(&update);          
         printf("got some stuff\n");
         f("wee", (T*)update.data());
      } 
   }
};
