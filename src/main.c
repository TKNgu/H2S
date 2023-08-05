#include <stdio.h>
#include <uv.h>

#include "log/log.h"

#ifdef DEBUG
#define TCP_PORT 8080
#else
#define TCP_PORT 80
#endif

void TCPAccept(uv_stream_t *, int);

int main(void) {
  log_info("Hello H2S\n");
  uv_loop_t *loop = uv_default_loop();
  if (!loop) {
    log_fatal("Init uv default loop");
    return 1;
  }

  struct sockaddr_in addr;
  uv_ip4_addr("0.0.0.0", TCP_PORT, &addr);

  uv_tcp_t server;
  uv_tcp_init(loop, &server);
  uv_tcp_bind(&server, (const struct sockaddr *)(&addr), 0);

  int errorCode;
  if (errorCode = uv_listen((uv_stream_t *)(&server), 32, TCPAccept)) {
    log_fatal("Bind socket %d %s", TCP_PORT, uv_strerror(errorCode));
    goto EXIT_LOOP;
  }

  if (errorCode = uv_run(loop, UV_RUN_DEFAULT)) {
    log_fatal(uv_strerror(errorCode));
  }
EXIT_LOOP:
  uv_loop_close(loop);
  return 0;
}

void TCPAccept(uv_stream_t *, int) { log_info("New connection"); }
