#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include "simscreen.h"
#include "cdt.h"
#include "ModbusTCPCli.h"

extern CRITICAL_SECTION CriticalSection;

int main(int argc, char **argv)
{
    //��ʼ���ٽ������� 
    InitializeCriticalSection(&CriticalSection);
    //�������� 
    loadCfg("setting.cfg");
    //�����߳� 
    startCdtBroadCast();//Start cdt broadcast  
    startModbusScan();	//Start modbus scan 
    startModbusSerail();//start modbus serail send 
}
