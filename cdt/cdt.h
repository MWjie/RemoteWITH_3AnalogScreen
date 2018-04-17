#ifndef CDT_H
#define CDT_H

#include "type.h"

#define YX_RED    ( 0x01 )//��� ��-1 
#define YX_GREEN  ( 0x02 )//�̵� ��-0 
#define YX_CLOSE  ( 0x00 )//���
#define YX_YELLOW ( 0x03 )//�Ƶ�	

#define SCREEN_ALL_CLOSE      ( 0x03 )//(ȫ����)
#define SCREEN_ALL_OPEN       ( 0x04 )//(ȫ����)
#define SCREEN_ALL_BLUCK      ( 0x07 )//(ȫ������)
#define SCREEN_ALL_NIGHT      ( 0x06 )//(ȫ������)
#define SCREEN_ALL_YX_UPDATE  ( 0x0A )//(YX����)
#define SCREEN_ALL_RECOVERY   ( 0x01 )//01(�����ָ�)

#define MAX_YX_SIZE_ONE_PACKAGE ( 249*4 )//��֡�������YX������ 

extern char Buffer[];//ͨ�Ż���

/*typedef int(*IO_CallBack)(char* buf, int size);
extern IO_CallBack ioWriteCallBack;
extern IO_CallBack ioReadCallBack;*/

#ifdef __cplusplus  
extern "C" {  
#endif 

void io_read(char* buf, int size, int selail_number);//��Э��ʹ����ʵ�� 
void io_write(char* buf, int size, int selail_number);//��Э��ʹ����ʵ��

//ע��ص�����
//void registerIoCallBack(IO_CallBack read,IO_CallBack write);

//����У�� 
uchar getcheck(char* buf, int len);
//����YX
void sendBatchYX(ushort startSeq, uchar* yxs, int size, uint Serail_NUM);
void sendBatchYXNoLimit(ushort startSeq, uchar* yxs, int size, uint Serail_NUM);
//����YX
void sendSingleYX(ushort seq, uchar yx, uint Serail_NUM);
//����YC 
void sendBatchYC(ushort startSeq, uchar* ycs, int size, uint Serail_NUM);

//ȫ������ 
void screenAllClose(uint Serail_NUM);
void screenAllOpen(uint Serail_NUM);
void screenAllBluck(uint Serail_NUM);
void screenAllLight(uint Serail_NUM);
void screenAllYxUpdate(uint Serail_NUM);
void screenAllRecovery(uint Serail_NUM);

//ʱ�䱨��
void sendTime(ushort year, uchar month, uchar day, uchar week, uchar hour, uchar min, uchar sec, ushort safedays, uint Serail_NUM);

#ifdef __cplusplus  
}  
#endif 

#endif

