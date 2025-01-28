#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

void evaluateTheQualityOfDataTransmission(io_context& io, const string& address, int port, int packetSize, int packetCount) {
    ip::tcp::socket socket(io);

    try {
        socket.connect(ip::tcp::endpoint(ip::make_address(address), port));
    }
    catch (const boost::system::system_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return;
    }

    vector<char> buffer(packetSize);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < packetCount; i++) {
        socket.send(boost::asio::buffer(buffer.data(), buffer.size()));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    double throughput = (packetSize * packetCount) / duration.count() / (1024 * 1024);
    double latency = duration.count() / packetCount * 1000; 

    ofstream resultFile("testResults.txt", ios::app);
    resultFile << "Пропускная способность: " << throughput << " MB/s, Задержка: " << latency << " ms" << endl;
    resultFile.close();
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    io_context io; 
    string address;
    int port, packetSize, packetCount;

    if (argc != 5) {
        cout << "Автоматически присваиваемые значения:\n - ip: 127.0.0.1\n - port: 1234\n - размер пакетов: 256\n - Число пакетов: 128\n" << endl;
        cout << "Оставить? Y/N\n";
        string ans;
        cin >> ans;
        if (ans == "Y") {
            address = "127.0.0.1";
            port = 1234;
            packetSize = 256;
            packetCount = 128;
        }
        else {
            
            cout << "Введите ip\n";
            cin >> address;
            cout << "Введите порт\n";
            cin >> port;
            cout << "Введите размер пакетов\n";
            cin >> packetSize;
            cout << "Введите число пакетов\n";
            cin >> packetCount;
        }
    }
    else {
        string address = argv[1];
        int port = atoi(argv[2]);
        int packetSize = atoi(argv[3]);
        int packetCount = atoi(argv[4]);
    }


    evaluateTheQualityOfDataTransmission(io, address, port, packetSize, packetCount);

    return 0;
}
