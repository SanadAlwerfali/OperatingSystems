/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


static void do_child_stuff(const struct sockaddr_un *addr, socklen_t addrlen);
static void do_parent_stuff(const struct sockaddr_un *addr, socklen_t addrlen);


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage:  %s <socket filename>\n", argv[0]);
		return 1;
	}

	const char *socket_name = argv[1];

	//
	// Both the child and parent processes will need the socket name:
	//
	struct sockaddr_un addr;
	addr.sun_family = AF_LOCAL;

	const size_t namelen = strlen(socket_name);
	if (namelen >= sizeof(addr.sun_path))
	{
		fprintf(stderr, "Name too long: '%s'\n", socket_name);
		return 1;
	}
	strncpy(addr.sun_path, socket_name, namelen);
	addr.sun_len = (unsigned char) strlen(addr.sun_path);

	socklen_t addrlen = (socklen_t) SUN_LEN(&addr);


	//
	// Create child!
	//
	pid_t child = fork();

	if (child < 0)
	{
		err(-1, "Error in fork()");
	}
	else if (child == 0)
	{
		do_child_stuff(&addr, addrlen);
	}
	else
	{
		do_parent_stuff(&addr, addrlen);
	}

	return 0;
}


static void
do_child_stuff(const struct sockaddr_un *addr, socklen_t addrlen)
{
	int sock = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (sock < 0)
	{
		err(-1, "Child unable to create socket");
	}

	printf("Child connecting to socket...\n");
	if (connect(sock, (const struct sockaddr *) addr, addrlen) != 0)
	{
		err(-1, "Child unable to connect()");
	}
}


static void
do_parent_stuff(const struct sockaddr_un *addr, socklen_t addrlen)
{
	int sock = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (sock < 0)
	{
		err(-1, "Parent unable to create socket");
	}

	if (bind(sock, (const struct sockaddr *) addr, addrlen) < 0)
	{
		err(-1, "Parent unable to bind address");
	}

	if (listen(sock, 1) < 0)
	{
		err(-1, "Parent unable to listen()");
	}

	printf("Parent listening on socket!\n");

	struct sockaddr_un client_addr;
	socklen_t client_addr_len;

	int client = accept(sock, (struct sockaddr *) &client_addr,
	                    &client_addr_len);
	if (client < 0)
	{
		err(-1, "Parent failed to accept connection");
	}

	printf("Parent accepted socket.\n");
}