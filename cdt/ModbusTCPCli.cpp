#include "ModbusTCPCli.h"

extern CRITICAL_SECTION CriticalSection;
void switchBytes(uchar* buf, int size); 
 
CModbusTcpCli::CModbusTcpCli(char* host, ushort port)
{
    m_host = host;
    m_port = port;
    sprintf(tag, "%s:%d", host, port);
} 

int CModbusTcpCli::open()
{
    if (CTcpClient::open(m_host, m_port) != 0) {
        linkStatus = 0;
        printf("CTcpClient open faile %s:%d\n", m_host, m_port); 
        return -1;	
    } 
    linkStatus = 1; 
    return 0; 
}
int CModbusTcpCli::close()
{
    linkStatus = 0;
    commonErrorCnt = 0;
    CTcpClient::close();
}
int CModbusTcpCli::readReg(uchar mbaddr, uchar func, ushort regaddr, uchar num, char* buf)
{
    uchar sbuf[255];
    uchar len; 
    sbuf[0]  = 0xEB;
    sbuf[1]  = 0x90;
    sbuf[2]  = 0x00;
    sbuf[3]  = 0x00;
    sbuf[4]  = 0x00;
    sbuf[5]  = 0x06;
    sbuf[6]  = mbaddr; 
    sbuf[7]  = func;
    sbuf[8]  = regaddr>>8;
    sbuf[9]  = regaddr&0xFF;
    sbuf[10] = 0x00;
    sbuf[11] = num;
    write((char*)sbuf, 12);	
    
    //�ȴ�����	
    memset(sbuf, 0, sizeof(sbuf));
    //�ȶ�ͷ 
    if (read((char*)sbuf, 6) == -1) {
        return -1;//����ͨ����·���� 
    }
    
    //�������ֽ�
    len = sbuf[5];
    memset(sbuf, 0, sizeof(sbuf));
    if (read((char*)sbuf, len) == -1) {
        return -1;//����ͨ����·���� 
    }
    
    //���ж�ͨ�ű��� 
    if (sbuf[0]!=mbaddr || sbuf[1]!=func) {
        //ͨ�ű��Ĵ���
        return -2; 
    }
    //�˴����� 
    EnterCriticalSection(&CriticalSection);
    //������Ч���� 
    memcpy(buf, sbuf+3, sbuf[2]);
    //�����ֽ�˳��
    switchBytes((uchar*)buf, sbuf[2]);
    //�˴�����
    LeaveCriticalSection(&CriticalSection); 
    return 0; 
}
int CModbusTcpCli::writeReg(uchar mbaddr, uchar func, ushort regaddr, uchar num, char* buf)
{
    
}

//�����ߵ��ֽ� 
void switchBytes(uchar* buf, int size)
{
    int i = 0;
    size /= 2;
    uchar temp;
    
    for (; i<size; i++) {
        temp = *buf;
        *buf = *(buf+1);
        *(buf+1) = temp;
        buf += 2;
    }
} 

//�����ߵͼĴ���
void switchReg(ushort* buf, int size)
{
    int i = 0;
    size /= 2;
    ushort temp;
    
    for (; i<size; i++) {
        temp = *buf;
        *buf = *(buf+1);
        *(buf+1) = temp;
        buf += 2;
    } 
} 

//����λ
void reverseBit(uchar* buf, int size)
{
    int i = 0;
    uchar* pbuf = buf;
    
    for (; i<size; i++) {
        *pbuf = (*pbuf & 0xaa) >> 1 | (*pbuf & 0x55) << 1;
        *pbuf = (*pbuf & 0xcc) >> 2 | (*pbuf & 0x33) << 2;
        *pbuf = (*pbuf & 0xf0) >> 4 | (*pbuf & 0x0f) << 4;
        pbuf++;
    }
    switchBytes(buf, size); 
} 
