#include "CTcpClient.h"

//-lwsock32 
int CTcpClient::open(char* host, ushort port)
{
    WORD wVersionRequested;  
    WSADATA wsaData;  
    int err;  
    
    wVersionRequested = MAKEWORD(1, 1);  
    err = WSAStartup(wVersionRequested, &wsaData);  
    if (err != 0) {  
        return -1;  
    }  
    if (LOBYTE(wsaData.wVersion) !=1 || HIBYTE(wsaData.wVersion) != 1) {  
        WSACleanup();  
        return -1;  
    }  
    //�����׽���  
    m_sock = socket(AF_INET, SOCK_STREAM, 0);  
    SOCKADDR_IN addrSrv;  
    addrSrv.sin_addr.S_un.S_addr = inet_addr(host);  
    addrSrv.sin_family = AF_INET;  
    addrSrv.sin_port = htons(port);  
    err = connect(m_sock, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    
    if (err==SOCKET_ERROR) {
        return -1;
    }    
    return 0;    
}
int CTcpClient::close()
{
    if (m_sock) {
        closesocket(m_sock);
    }
}
int CTcpClient::read(char* buf, int size)
{
    FD_SET fdRead;
    int nRet = 0;//��¼���ͻ��߽��ܵ��ֽ���
    TIMEVAL tv;//���ó�ʱ�ȴ�ʱ��
    
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    FD_ZERO(&fdRead);
    FD_SET(m_sock, &fdRead); 
    nRet = select(0, &fdRead, NULL, NULL, &tv);
    if (nRet == 0) {
       //��ʱ	 
       return -1;
    }
    return recv(m_sock, buf, size, 0);
}
int CTcpClient::write(char* buf, int size)
{
    return send(m_sock, buf, size, 0);
}
