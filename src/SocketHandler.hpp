#include <netinet/in.h>
#include <cstdint>
#include <string>
using std::string;

class SocketHandler{
	public:
		SocketHandler(const std::uint16_t& local_port, const std::uint16_t& remote_port, const string& remote_ip);
		bool sockread(char buffer[1024]);
		void sockwrite(const char buffer[1024]);
		bool isopen();
		void close();

	private:
	int sockfd;
	bool is_open = true;
	struct sockaddr_in addr_there;
	struct sockaddr_in addr_here;
	
		void createSocket();
		bool connect();
		void bind();
		void accept();
};

