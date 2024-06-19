#include "tcp_socket.h"
#include <sys/ioctl.h>
#include <netinet/in.h>

bool TCPSocket::bind() {
	// int opt = 1;
	// struct sockaddr_in address;

	// if (setsockopt(fileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
	// 	close(fileDescriptor);
	// 	return false;
	// }

	// // 주소 구조체 초기화
	// address.sin_family = AF_INET;
	// address.sin_addr.s_addr = INADDR_ANY;  // 모든 인터페이스에 바인드
	// address.sin_port = htons(8080);        // 포트 8080

	// // 소켓 바인드
	// if (bind(fileDescriptor, (struct sockaddr *)&address, sizeof(address)) < 0) {
	// 		perror("bind failed");
	// 		close(server_fd);
	// 		exit(EXIT_FAILURE);
	// }
}