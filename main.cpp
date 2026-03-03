/* Simple HTTP server for CI/CD testing */
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 8080;
const std::string VERSION = "2.0";

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // 建立 socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }
    
    // 設定 socket 選項，允許重複使用
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cerr << "Setsockopt failed" << std::endl;
        return 1;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // 綁定到 port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }
    
    // 開始監聽
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return 1;
    }
    
    std::cout << "🚀 Server started on port " << PORT << std::endl;
    std::cout << "📦 Version: " << VERSION << std::endl;
    std::cout << "✅ Ready to accept connections..." << std::endl;
    
    // 無限迴圈接受請求
    while (true) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }
        
        // 讀取請求（簡單處理，不解析）
        char buffer[1024] = {0};
        read(client_fd, buffer, 1024);
        
        // 建立 HTTP 回應
        std::string response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<!DOCTYPE html>"
            "<html>"
            "<head><title>DevOps Test Service</title></head>"
            "<body style='font-family: Arial; text-align: center; padding: 50px;'>" 
            "<h1>🎉 Hello, DevOps World!</h1>"
            "<p style='font-size: 24px;'>✅ Service is running!</p>"
            "<p style='color: #666;'>Version: " + VERSION + "</p>"
            "<p style='color: #999; font-size: 14px;'>Powered by C++ & Kubernetes</p>"
            "</body>"
            "</html>";
        
        // 送出回應
        write(client_fd, response.c_str(), response.length());
        close(client_fd);
        
        std::cout << "📨 Request handled" << std::endl;
    }
    
    close(server_fd);
    return 0;
}
