#include "ModbusSend.h"

/*  
CRC�㷨����	    ����ʽ��ʽ	���	����ʽ	��ʼֵ	������ֵ	����ֵ��ת	���ֵ��ת
CRC-16/MODBUS	16+x15+x2+1	16	    8005	FFFF	0000	    true	    true
*/
ushort CRC16(uchar *Msg, ushort DataLen)
{
    uchar uchCRCH = 0xFF; /* ��λCRC�ֽڳ�ʼ�� */
    uchar uchCRCL = 0xFF; /* ��λCRC�ֽڳ�ʼ�� */
    uint uIndex; /* CRCѭ���е����� */

    while (DataLen--) { /* ������Ϣ������ */
        uIndex  = uchCRCH ^ *Msg++; /* ����CRC */
        uchCRCH = uchCRCL ^ CRCH[uIndex];
        uchCRCL = CRCL[uIndex];
    }

    return (uchCRCH<<8 | uchCRCL);
}

/* �жϴ��ڽ��� */
int CheckSerailMsg(uchar *sbuf) 
{
    ushort crcData;
    crcData = CRC16(sbuf, 6);
    if (crcData == (sbuf[7]+(sbuf[6]<<8))) {//У����ȷ
        if(sbuf[1] == 0x03) {
            return 1;
        } else {
            return -1;//��������� 
        }
    } else {
        return -2;//CRCУ����� 
    }
}
