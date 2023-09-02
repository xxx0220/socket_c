#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main() {

    //读取txt1文件
    //文件地址 "E:\my\socket\1\txt1.txt" 请修改为自己的文件地址
    std::ifstream file("E:/my/socket/1/txt1.txt");
    std::string sendData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    std::cout << "send data1 from c++ :"  << std::endl;
    std::cout << sendData << std::endl;

    // 初始化Winsock库
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    // 创建Socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Failed to create socket" << std::endl;
        WSACleanup();
        return 1;
    }

    // 设置服务器的IP地址和端口号
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr));

    // 连接到服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cout << "Failed to connect to server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // 发送数据到服务器
    if (send(clientSocket, sendData.c_str(), sendData.size(), 0) == SOCKET_ERROR) {
        std::cout << "Failed to send data to server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // 接收来自服务器的响应数据
    char buffer[1024]{};
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == SOCKET_ERROR) {
        std::cout << "Failed to receive data from server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Received data from server: " << buffer << std::endl;
    

    // 清理和关闭Socket
    closesocket(clientSocket);

    // 关闭Winsock库
    WSACleanup();
    system("Pause");
    return 0;
}