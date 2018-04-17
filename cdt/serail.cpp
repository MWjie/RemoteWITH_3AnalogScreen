#include "serail.h"

int CSerail::open(char* dev, int baud, int databit, int check, int stopbit, int selail_number) 
{
    m_handle[selail_number] = CreateFile(dev,
        GENERIC_READ| GENERIC_WRITE,
        0,//��ռ 
        NULL,
        OPEN_EXISTING, // �򿪶����Ǵ���
        FILE_ATTRIBUTE_NORMAL/* | FILE_FLAG_OVERLAPPED*/, // ���ص���ʽ
        NULL
    );
    
    if (m_handle[selail_number] == INVALID_HANDLE_VALUE) {
        DWORD dwError = GetLastError(); // �������
        return 1; 
    }

    //���ô��ڲ��� 
    DCB dcb;
    GetCommState(m_handle[selail_number], &dcb); 
    
    dcb.BaudRate = (DWORD)baud;
    dcb.ByteSize = (BYTE)databit;
    dcb.Parity   = (BYTE)check;//NOPARITY,EVENPARITY
    dcb.StopBits = ONESTOPBIT;//ONESTOPBIT
    
    SetCommState(m_handle[selail_number], &dcb);    

    return 0;
}

int CSerail::close(int selail_number)
{
    if (m_handle[selail_number] != INVALID_HANDLE_VALUE) {
        CloseHandle(m_handle[selail_number]);		
    }
    return 0;	
}

int CSerail::read(char* buf, int size, int selail_number)
{
    DWORD realsize = 0; 
    
    if (m_handle[selail_number] == INVALID_HANDLE_VALUE) {
       return -1;
    }
    
    if (ReadFile(
        m_handle[selail_number],      // ָ���ʶ�ľ��
        buf,    // ָ��һ��������
        size, // ��ȡ���ֽ���
        &realsize, // ָ����øú����������ֽ���
        NULL  // һ��OVERLAPPED�Ľṹ
    )){
        return realsize;
    }
    
    return 0;		
}

int CSerail::write(char* buf, int size, int selail_number)
{
    DWORD realsize = 0; 

    if (m_handle[selail_number] == INVALID_HANDLE_VALUE) {
       return -1;
    }
    
    if (WriteFile(
        m_handle[selail_number],      // ָ���ʶ�ľ��
        buf,    // ָ��һ��������
        size, // ָ��Ҫ�򴮿��豸д����ֽ���
        &realsize, // ָ����øú�����д����ֽ���
        NULL   // һ��OVERLAPPED�Ľṹ
    )){
        return realsize;
    }
    
    return 0;				
}

int CSerail::settimeout(DWORD ReadIntervalTimeout, 
    DWORD ReadTotalTimeoutMultiplier,
        DWORD ReadTotalTimeoutConstant,
            DWORD WriteTotalTimeoutMultiplier, 
                DWORD WriteTotalTimeoutConstant,
                    int selail_number)
{
    COMMTIMEOUTS timeouts;
    GetCommTimeouts(m_handle[selail_number], &timeouts);
    
    /*��msΪ��λָ��ͨ����·�������ַ�����֮������ʱ������
    ��ReadFile()�����ڼ䣬�ӽ��յ���һ���ַ�ʱ��ʼ��ʱ��
    ������������ַ�����֮���ʱ��������������ֵ��
    ��ReadFile()������ɣ������ػ������ݡ��������Ϊ0�����ʾ��ʹ�ü����ʱ��*/
    timeouts.ReadIntervalTimeout = ReadIntervalTimeout;
    timeouts.ReadTotalTimeoutMultiplier = ReadTotalTimeoutMultiplier;//��msΪ��λָ��һ��ϵ������ϵ������������������ܳ�ʱʱ�䡣
    timeouts.ReadTotalTimeoutConstant = ReadTotalTimeoutConstant;//��msΪ��λָ��һ���������ó���Ҳ����������������ܳ�ʱʱ�䡣
    timeouts.WriteTotalTimeoutMultiplier = WriteTotalTimeoutMultiplier;//��msΪ��λָ��һ��ϵ������ϵ����������д�������ܳ�ʱʱ�䡣
    timeouts.WriteTotalTimeoutConstant = WriteTotalTimeoutConstant;//��msΪ��λָ��һ���������ó���Ҳ��������д�������ܳ�ʱʱ�䡣
    
    //ReadTotalTimeout=( ReadTotalTimeoutMultiplier*bytes_to_read )+ ReadTotalTimeoutConstant;
    //WriteTotalTimeout=( WriteTotalTimeoutMultiplier*bytes_to_write )+ WriteTotalTimeoutConstant;
    
    SetCommTimeouts(m_handle[selail_number], &timeouts);
}
