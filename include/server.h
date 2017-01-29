#ifndef CU_GENERIC_SERVER
#define CU_GENERIC_SERVER

#include <stdint.h>



#define MESSAGE(N, NAME) \
	typedef struct { \
		uint8_t in[N]; \
		uint8_t out[N]; \
		ssize_t in_size; \
		ssize_t out_size; \
	} NAME;

MESSAGE(512, Message)

void cu_server_create_and_listen(in_port_t port, bool (*handle)(Message *msg));

#endif
