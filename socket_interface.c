/**
 * @file socket_interface.c
 * @author your name (you@domain.com)
 * @brief get the socket's corresponding interface
 * @version 0.1
 * @date 2022-06-12
 *
 * @copyright Copyright (c) 2022
 * usage:
❯ clang -std=gnu11 socket_interface.c -o socket_interface

❯ ./socket_interface 93.184.216.34
interface index   : 15
interface name    : utun4
interface address : 10.14.0.2
remote    address : 93.184.216.34
 * references:
 * - [linux - How to get interface index from interface ip address - Stack
 * Overflow](https://stackoverflow.com/questions/2396081/how-to-get-interface-index-from-interface-ip-addres)
 */
#include <arpa/inet.h>
#include <assert.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 80

void connect2(int* sock_fd, const char* const dst) {

    *sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(*sock_fd >= 3);

    struct sockaddr_in sin = { .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr = {} };
    // Convert IPv4 and IPv6 addresses from text to binary
    assert(1 == inet_pton(AF_INET, dst, &(sin.sin_addr)) && "\nInvalid address/ Address not supported \n");

    assert(0 == connect(*sock_fd, (struct sockaddr*)(&sin), sizeof(struct sockaddr_in)) && "\nConnect to dst failed \n");
}

void disconnect(int* sock_fd) {
    close(*sock_fd);
    *sock_fd = -1;
}

int main(int argc, const char* argv[]) {

    assert(argc == 2);
    assert(argv[1] && strlen(argv[1]));
    const char* const remoteaddr_s = argv[1];
    int sock_fd;
    // const char *const remoteaddr_s = "93.184.216.34"; // example.org

    connect2(&sock_fd, remoteaddr_s);

    struct sockaddr_in addr;
    struct ifaddrs* ifaddr;
    struct ifaddrs* ifa;
    socklen_t addr_len;

    addr_len = sizeof(addr);
    getsockname(sock_fd, (struct sockaddr*)&addr, &addr_len);
    getifaddrs(&ifaddr);

    // look which interface contains the wanted IP.
    // When found, ifa->ifa_name contains the name of the interface (eth0, eth1,
    // ppp0...)
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr) {
            if (AF_INET == ifa->ifa_addr->sa_family) {
                struct sockaddr_in* inaddr = (struct sockaddr_in*)ifa->ifa_addr;

                if (inaddr->sin_addr.s_addr == addr.sin_addr.s_addr) {
                    if (ifa->ifa_name) {
                        // Found it
                        char ifaddr_s[INET_ADDRSTRLEN] = {};
                        assert(ifaddr_s == inet_ntop(AF_INET, &(inaddr->sin_addr), ifaddr_s, INET_ADDRSTRLEN));

                        printf("interface index   : %d\n", if_nametoindex(ifa->ifa_name));
                        printf("interface name    : %s\n", ifa->ifa_name);
                        printf("interface address : %s\n", ifaddr_s);
                        printf("remote    address : %s\n", remoteaddr_s);
                    }
                }
            }
        }
    }
    freeifaddrs(ifaddr);
    disconnect(&sock_fd);
    return 0;
}