#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

typedef int32_t Socket;
#define clear(S) memset(&S, 0, sizeof(S))

#define MESSAGE(N, NAME) \
	typedef struct { \
		uint8_t in[N]; \
		uint8_t out[N]; \
		ssize_t in_size; \
		ssize_t out_size; \
	} NAME;

MESSAGE(512, Message)

static inline Socket socket_stream() {
	Socket socket_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (socket_fd == -1) {
		perror("socket creation failed");
		abort();
	}
	return socket_fd;
}

static inline void socket_bind(Socket socket_fd, in_port_t port) {
	struct sockaddr_in addr;
	clear(addr);

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int bind_result = bind(socket_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	if (bind_result == -1) {
		perror("Binding failed");
		abort();
	}
}

static inline void accept_connection(Socket socket, fd_set *actice_socket) {
	struct sockaddr_in client;
	clear(client);
	socklen_t client_len = sizeof(struct sockaddr_in);
	Socket new_conn =
		accept(socket, (struct sockaddr *)&client, &client_len);
	FD_SET(new_conn, actice_socket);
}

static inline Socket server_create(in_port_t port) {
	Socket socket_fd = socket_stream();
	socket_bind(socket_fd, port);
	return socket_fd;
}

static inline bool send_message(uint32_t current_client, Message *msg) {
	int32_t result;
try_send_again:
	result = send(current_client, msg->out, msg->out_size, MSG_NOSIGNAL);
	if (result == -1) {
		switch (errno) {
			case EPIPE:
				return true;
			case EINTR:
				goto try_send_again;
			case EAGAIN:
				break;
			default:
				perror("send failed");
				abort();
		}
	}
	clear(msg->out);
	msg->out_size = 0;
	return false;
}

static inline void recv_message(uint32_t current_client, Message *msg) {
	int32_t result;
try_recv_again:
	result = recv(current_client, msg->in, sizeof(msg->in), 0);
	if (result == -1) {
		switch (errno) {
			case EINTR:
				goto try_recv_again;
			case EAGAIN:
				break;
			default:
				perror("recv failed");
				abort();

		}
	}
	msg->in_size = result;
}

void cu_server_create_and_listen(in_port_t port, bool (*handle)(Message *msg)) {
	Message message;
	clear(message);

	Socket socket = socket_stream();
	socket_bind(socket, port);

	int32_t result = listen(socket, 1);
	if (result == -1) {
		perror("listen failed");
		abort();
	}

	fd_set actice_socket, reading_socket;
	FD_ZERO(&actice_socket);
	FD_SET(socket, &actice_socket);

	for (;;) {
		reading_socket = actice_socket;

		result = select(FD_SETSIZE, &reading_socket, NULL, NULL, NULL);
		if (result < 0) {
			perror("failed to select");
			abort();
		}

		for (int32_t i = 0; i < FD_SETSIZE; i++) {
			if (FD_ISSET(i, &reading_socket)) {
				if (i == socket) {
					/* Accept a new connection */
					accept_connection(socket, &actice_socket);
				} else {
					/* Handle exisiting client */
					recv_message(i, &message);

					bool shall_close = handle(&message);
					assert((uint32_t)message.out_size < sizeof(message.out));

					if (message.out_size > 0) {
						shall_close = send_message(i, &message);
					}

					if (shall_close) {
						close(i);
						FD_CLR(i, &actice_socket);
					}
					clear(message.in);
					message.in_size = 0;
				}
			}
		}
	}
}

