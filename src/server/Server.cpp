#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main() {
	setlocale(LC_ALL, "rus");

	io_context io;
	ip::tcp::acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 1234));

	cout << "Сервер запущен на порту 1234...\n";

	while (true) {
		ip::tcp::socket socket(io);
		acceptor.accept(socket);
		cout << "Соединение установлено\n";

		char data[256];
		while (true) {
			size_t len = socket.read_some(buffer(data));
			if (len == 0) break; 
		}

	}

	return 0;
}
