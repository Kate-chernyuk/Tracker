#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main() {
	setlocale(LC_ALL, "rus");

	io_context io;
	ip::tcp::acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 1234));

	cout << "������ ������� �� ����� 1234...\n";

	while (true) {
		ip::tcp::socket socket(io);
		acceptor.accept(socket);
		cout << "���������� �����������\n";

		char data[256];
		while (true) {
			size_t len = socket.read_some(buffer(data));
			if (len == 0) break; 
		}

	}

        cout << "��� ������ ��������\n" << endl;

	return 0;
}