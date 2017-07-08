#include <event.h>
#include <evhttp.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

using namespace std;

namespace servers {
namespace util {

class HTTPServer {
public:
  HTTPServer() {}
  ~HTTPServer() {}
  int serv(int port, int nthreads);
protected:
  static void* Dispatch(void *arg);
  static void GenericHandler(struct evhttp_request *req, void *arg);
  void ProcessRequest(struct evhttp_request *request);
  int BindSocket(int port);
};

int HTTPServer::BindSocket(int port) {
  int r;
  int nfd;
  nfd = socket(AF_INET, SOCK_STREAM, 0);
  if (nfd < 0) return -1;

  int one = 1;
  r = setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  r = bind(nfd, (struct sockaddr*)&addr, sizeof(addr));
  if (r < 0) return -1;
  r = listen(nfd, 10240);
  if (r < 0) return -1;

  int flags;
  if ((flags = fcntl(nfd, F_GETFL, 0)) < 0
      || fcntl(nfd, F_SETFL, flags | O_NONBLOCK) < 0)
    return -1;

  return nfd;
}

int HTTPServer::serv(int port, int nthreads) {
  int r;
  int nfd = BindSocket(port);
  if (nfd < 0) return -1;
  pthread_t ths[nthreads];
  for (int i = 0; i < nthreads; i++) {
    struct event_base *base = event_init();
    if (base == NULL) return -1;
    struct evhttp *httpd = evhttp_new(base);
    if (httpd == NULL) return -1;
    r = evhttp_accept_socket(httpd, nfd);
    if (r != 0) return -1;
    evhttp_set_gencb(httpd, HTTPServer::GenericHandler, this);
    r = pthread_create(&ths[i], NULL, HTTPServer::Dispatch, base);
    if (r != 0) return -1;
  }
  for (int i = 0; i < nthreads; i++) {
    pthread_join(ths[i], NULL);
  }
}

void* HTTPServer::Dispatch(void *arg) {
  event_base_dispatch((struct event_base*)arg);
  return NULL;
}

void HTTPServer::GenericHandler(struct evhttp_request *req, void *arg) {
  ((HTTPServer*)arg)->ProcessRequest(req);
}

void HTTPServer::ProcessRequest(struct evhttp_request *req) {
  struct evbuffer *buf = evbuffer_new();
  if (buf == NULL) return;

printf("I got herre: %s\n", evhttp_request_uri(req));

  int fd;
  std::string file = ".";
  file+=evhttp_request_uri(req);
  if ((fd = open(file.c_str(), O_RDONLY)) > 0) {

printf("I got herre 2\n");

      struct stat st;
      if (fstat(fd, &st)>=0) {
          evhttp_add_header(evhttp_request_get_output_headers(req),
		    "Content-Type", "text/html");
          evbuffer_add_file(buf, fd, 0, st.st_size);
     }
  }
  else
  {
printf("I got herre 3\n");

      evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));
  }
printf("I got herre 4\n");
  evhttp_send_reply(req, HTTP_OK, "OK", buf);
}
}
}

int main() {
  servers::util::HTTPServer s;
  s.serv(19850, 10);
}
