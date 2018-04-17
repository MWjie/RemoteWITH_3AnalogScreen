#include "cdt.h"

char Buffer[255];//ͨ�Ż���

//����У�� 
uchar getcheck(char* buf, int len) 
{
    uchar check=0;
    int i;
    for (i=0; i<len; i++) {
        check ^= buf[i];
        check =~ check; 
    }
    return check;
}

//����YX
void sendBatchYX(ushort startSeq, uchar* yxs, int size, uint Serail_NUM)
{
    uchar len = size/4+3;
    uchar packageSize = len+3; 
    Buffer[0] = 0xF2;//��ͷ 
    Buffer[1] = 0x01;//���� 
    Buffer[2] = len;//�ֽڳ��� 
    Buffer[3] = startSeq>>8; 
    Buffer[4] = startSeq&0xFF;
    Buffer[5] = size;
    memcpy(Buffer+6, yxs, size/4);
    Buffer[packageSize] = getcheck(Buffer, packageSize);
    io_write(Buffer, packageSize+1, Serail_NUM);
    screenAllYxUpdate(Serail_NUM);
}
//����YC ����YCһ�οɷ�120�����������120���ɷֶ��Ρ���һ����Ŵ�0001��ʼ���ڶ�����Ŵ�0079��121YC����ʼ 
void sendBatchYC(ushort startSeq, uchar* ycs, int size, uint Serail_NUM)
{
    uchar len = size*2+3;
    uchar packageSize = len+3;
    Buffer[0] = 0xF2;//��ͷ 
    Buffer[1] = 0x09;//���� 
    Buffer[2] = len;//�ֽڳ��� 
    Buffer[3] = startSeq>>8; 
    Buffer[4] = startSeq&0xFF;
    Buffer[5] = size;
    memcpy(Buffer+6, ycs, size*2);
    Buffer[packageSize] = getcheck(Buffer,packageSize);
    io_write(Buffer, packageSize+1, Serail_NUM);
    screenAllYxUpdate(Serail_NUM);
} 

void sendBatchYXNoLimit(ushort startSeq, uchar* yxs, int size, uint Serail_NUM)
{
    int i=0, curSize=0;
    size /= 4; 
    while (size > 0) {
        curSize = (size>MAX_YX_SIZE_ONE_PACKAGE?MAX_YX_SIZE_ONE_PACKAGE:size);
        sendBatchYX(startSeq, yxs, curSize, Serail_NUM);
        size -= curSize;
        yxs += curSize;
        startSeq += curSize;
    }
}

//����YX
void sendSingleYX(ushort seq, uchar yx, uint Serail_NUM)
{ 
    Buffer[0] = 0xF2;//��ͷ 
    Buffer[1] = 0x02;//���� 
    Buffer[2] = 0x03;//�ֽڳ��� 
    Buffer[3] = seq>>8; 
    Buffer[4] = seq&0xFF;
    Buffer[5] = yx; 
    Buffer[6] = getcheck(Buffer,6);
    io_write(Buffer, 7, Serail_NUM);
} 

//ȫ������ 
void allScreenOpreate(char cmd, uint Serail_NUM)
{
    Buffer[0] = 0xF2;
    Buffer[1] = 0x04;
    Buffer[2] = 0x01;
    Buffer[3] = cmd;
    uchar check = getcheck(Buffer, 4);
    switch (cmd) {
        case SCREEN_ALL_CLOSE:
                Buffer[4] = 0xF4;
                break; 
        case SCREEN_ALL_OPEN:
                Buffer[4] = 0xF3;
                break;
        case SCREEN_ALL_BLUCK:
                Buffer[4] = 0xF0;
                break;
        case SCREEN_ALL_NIGHT:
                Buffer[4] = 0xF1;
                break;
        case SCREEN_ALL_YX_UPDATE:
                Buffer[4] = 0xFD;
                break;
        case SCREEN_ALL_RECOVERY:
                Buffer[4] = 0xF6;
                break;
   }
   io_write(Buffer, 5, Serail_NUM);
} 
void screenAllClose(uint Serail_NUM)
{
    allScreenOpreate(SCREEN_ALL_CLOSE, Serail_NUM);
    screenAllRecovery(Serail_NUM);
} 
void screenAllOpen(uint Serail_NUM)
{
    allScreenOpreate(SCREEN_ALL_OPEN, Serail_NUM);
    screenAllRecovery(Serail_NUM);
} 
void screenAllBluck(uint Serail_NUM)
{
    allScreenOpreate(SCREEN_ALL_BLUCK, Serail_NUM);
} 
void screenAllLight(uint Serail_NUM)
{
    allScreenOpreate(SCREEN_ALL_NIGHT, Serail_NUM);
} 
void screenAllYxUpdate(uint Serail_NUM)
{
    allScreenOpreate(SCREEN_ALL_YX_UPDATE, Serail_NUM);
} 
void screenAllRecovery(uint Serail_NUM)
{
    allScreenOpreate(SCREEN_ALL_RECOVERY, Serail_NUM);
} 

//ʱ�䱨��
void sendTime(ushort year, uchar month, uchar day, uchar week, uchar hour, uchar min, uchar sec, ushort safedays, uint Serail_NUM)
{    
    Buffer[0]  = 0xF2;//��ͷ 
    Buffer[1]  = 0x0C;//���� 
    Buffer[2]  = 0x0A;//�ֽڳ��� 
    Buffer[3]  = (year/1000)*10 + year%1000/100;//��H
    Buffer[4]  = year%100/10 + year%10;//��L
    Buffer[5]  = month;
    Buffer[6]  = day;
    Buffer[7]  = week;
    Buffer[8]  = hour;
    Buffer[9]  = min;
    Buffer[10] = sec;
    Buffer[11] = safedays;
    Buffer[12] = getcheck(Buffer, 12);
    io_write(Buffer, 13, Serail_NUM); 
}
