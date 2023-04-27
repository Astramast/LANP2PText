#include <netinet/in.h>
#include <cstdint>

class SocketHandler{
	public:
		SocketHandler(std::uint16_t port);
		bool connect(const struct sockaddr* addr);

	private:
	int sockfd;
	struct sockaddr_in addr;
	
		void createSocket();
		void bindSocket(std::uint16_t& port);
};

