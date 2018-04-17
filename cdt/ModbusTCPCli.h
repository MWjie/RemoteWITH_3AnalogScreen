#ifndef MODBUSTCPCLI_H
#define MODBUSTCPCLI_H

#include <iostream>
#include "CTcpClient.h"

#define MAX_COMMON_ERROR_CNT ( 3 )//���ͨ�Ŵ������ 

class CModbusTcpCli: public CTcpClient{
private:
    //CTcpClient m_tcpcli;
public:
    char tag[25];//host+port �ı�� 
    int linkStatus;//����״̬ 
    int commonErrorCnt;//ͨ�Ŵ������ 
public:
    CModbusTcpCli(char* host, ushort port); 
    int open();
    int close();
    int readReg(uchar mbaddr, uchar func, ushort regaddr, uchar num, char* buf);	
    int writeReg(uchar mbaddr, uchar func, ushort regaddr, uchar num, char* buf);
};
void switchBytes(uchar* buf, int size);
void switchReg(ushort* buf, int size);
void reverseBit(uchar* buf, int size);
#endif

