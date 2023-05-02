#include <netinet/in.h>
#include <cstdint>
#include <string>
using std::string;

class SocketHandler{
	public:
		SocketHandler();
		void connect(const string& ip, const std::uint16_t& port);
		void bindSocket(const std::uint16_t& port);
		int accept();

	private:
	int sockfd;
	struct sockaddr_in addr;
	
		void createSocket();
};

