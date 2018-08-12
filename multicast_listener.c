#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmd_package.h"

#define PORT 1589
#define GROUP "225.0.0.55"

int main(int argc, char *argv[]) {
	struct sockaddr_in addr;
	int fd, nbytes, addrlen;
	struct ip_mreq mreq;
	struct Command *cmd = malloc(sizeof(struct Command));
	u_int yes = 1;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
		perror("Reusing ADDR failed");
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(1);
	}

	mreq.imr_multiaddr.s_addr = inet_addr(GROUP);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))
			< 0) {
		perror("setsockopt");
		exit(1);
	}

	while (1) {
		addrlen = sizeof(addr);
		if ((nbytes = recvfrom(fd, cmd, sizeof(*cmd), 0,
				(struct sockaddr *) &addr, &addrlen)) < 0) {
			perror("recvfrom");
			exit(1);
		}

		printf("type:%x\n", cmd->type);
		printf("to:%#lx\n", cmd->to);
		printf("who:%#lx\n", cmd->who);
		printf("cmd1:%#lx\n", cmd->cmd1);
		printf("cmd1_param1:%#lx\n", cmd->cmd1_param[0]);
		printf("cmd1_param2:%#lx\n", cmd->cmd1_param[1]);
		printf("cmd2:%#lx\n", cmd->cmd2);
		printf("cmd2_param1:%#lx\n", cmd->cmd2_param[0]);
		printf("cmd2_param2:%#lx\n", cmd->cmd2_param[1]);
		printf("cmd3:%#lx\n", cmd->cmd2);
		printf("cmd3_param1:%#lx\n", cmd->cmd3_param[0]);
		printf("cmd3_param2:%#lx\n", cmd->cmd3_param[1]);
		printf("execute:%#lx\n", cmd->execute);


	}
}
