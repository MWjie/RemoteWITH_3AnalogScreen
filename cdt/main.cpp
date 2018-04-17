#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include "simscreen.h"
#include "cdt.h"
#include "ModbusTCPCli.h"

extern CRITICAL_SECTION CriticalSection;

int main(int argc, char **argv)
{
    //初始化临界区对象 
    InitializeCriticalSection(&CriticalSection);
    //加载配置 
    loadCfg("setting.cfg");
    //开启线程 
    startCdtBroadCast();//Start cdt broadcast  
    startModbusScan();	//Start modbus scan 
    startModbusSerail();//start modbus serail send 
}
