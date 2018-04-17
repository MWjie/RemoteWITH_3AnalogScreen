#ifndef SIMSCREEN_H
#define SIMSCREEN_H

#include "type.h"
#include "ModbusTCPCli.h"

#define MAX_REG_NUM ( 65535 )

typedef struct {
    char comport[512];
    int baud;
    ushort databit;
    ushort check;
    ushort stopbit;
    ushort devScanInterval;
    ushort simFlushT;
    ushort res;
} TY_SERAIL_PARAM;

//ң����ӳ��
typedef struct {
    ushort yxSeqStart;//ң������ʼ���
    ushort yxSize;//ң��������
    ushort mbRegStart;//modbus�Ĵ�����ʼ��ַ
    ushort mbRegSize;//modbus�Ĵ�������
    ushort bit_start;//��ʼλ��0��ʼ��ţ�255��ʾ��ʹ��λ
    ushort bit_move;//λƫ����
    ushort mbDevAddr;//modbus�豸��ַ
    ushort dataType;//��������
    char tag[25];//ip+port���
    ushort res;//
} TY_YX_MB_MAP;
struct TY_YX_MB_MAP_LINK;
typedef struct TY_YX_MB_MAP_LINK* pTY_YX_MB_MAP_LINK;
typedef struct TY_YX_MB_MAP_LINK {
    TY_YX_MB_MAP* pYxMbMap;
    pTY_YX_MB_MAP_LINK next;
} TY_YX_MB_MAP_LINK;

//ң����ӳ��
typedef struct {
    ushort ycSeqStart;//ң������ʼ���
    ushort ycSize;//ң��������
    ushort mbRegStart;//modbus�Ĵ�����ʼ��ַ
    ushort mbRegSize;//modbus�Ĵ�������
    ushort bit_start;//��ʼλ��0��ʼ��ţ�255��ʾ��ʹ��λ
    ushort bit_move;//λƫ����
    ushort mbDevAddr;//modbus�豸��ַ
    ushort dataType;//��������
    ushort byteorder;//�ֽ�˳��
    char tag[25];//ip+port���
    ushort res;//
} TY_YC_MB_MAP;
struct TY_YC_MB_MAP_LINK;
typedef struct TY_YC_MB_MAP_LINK* pTY_YC_MB_MAP_LINK;
typedef struct TY_YC_MB_MAP_LINK {
    TY_YC_MB_MAP* pYcMbMap;
    pTY_YC_MB_MAP_LINK next;
} TY_YC_MB_MAP_LINK;

//��������ʽ��ȡ��ң������ӳ��
typedef struct {
    ushort ycModbusAddr;//ң����MODBUS�Ĵ�����ַ
    char formula[255]; //����ʽ
} TY_YC_MB_REMAP;
struct TY_YC_MB_REMAP_LINK;
typedef struct TY_YC_MB_REMAP_LINK* pTY_YC_MB_REMAP_LINK;
typedef struct TY_YC_MB_REMAP_LINK {
    TY_YC_MB_REMAP* pYcMbREMap;
    pTY_YC_MB_REMAP_LINK next;
} TY_YC_MB_REMAP_LINK;

//modbus�Ĵ���
struct RegBlock;
typedef struct RegBlock *PRegBlock;
typedef struct RegBlock {
    uchar  func;
    uchar  res;
    ushort s_add;
    ushort size;
    PRegBlock next;
} TY_REG_BLOCK;

//modbus�豸
typedef struct {
    uchar mbAddr;//modbus��ַ
    uchar transm;//ͨ�ŷ�ʽ 0-���� 1-����
    int fd;//ͨ�ž��
    char ip[16];//ip��ַ
    ushort port;//�˿ں�
    char tag[25];//ip+port���
    TY_REG_BLOCK* pRegBlock;
    ushort regVal[MAX_REG_NUM];
} TY_MB_DEVICE;

struct TY_MBDEV_LINK;
typedef struct TY_MBDEV_LINK* pTY_MBDEV_LINK;
typedef struct TY_MBDEV_LINK {
    TY_MB_DEVICE* pdev;
    pTY_MBDEV_LINK next;
} TY_MBDEV_LINK;

//modbus tcp ʵ��
struct TY_MBTCPCLI_LINK;
typedef struct TY_MBTCPCLI_LINK* pTY_MBTCPCLI_LINK;
typedef struct TY_MBTCPCLI_LINK {
    char tag[25];//ip+port���б�ʾ
    CModbusTcpCli* pMbTcpCli;//modbus tcp cli
    pTY_MBTCPCLI_LINK next;
} TY_MBTCPCLI_LINK;

enum VAL_STATUS {
    NOT_Multi = 0,
    Multi_Val_0,
    Multi_Val_1,
};

#ifdef __cplusplus
extern "C" {
#endif

void loadCfg(char* cfgfile);
//modbusɨ���߳�
void startModbusScan(void);
//yx CDT�㲥�߳�
void startCdtBroadCast(void);
//Modbus���ڷ�������
void startModbusSerail(void);
//�����豸��ַ�ͼĴ�����ַ��ȡ�Ĵ���ֵ
int getMbRegValue(uchar mbaddr, ushort s_regaddr, int size, ushort byteorder, ushort* buf, char* tag);

#ifdef __cplusplus
}
#endif

#endif
