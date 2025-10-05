#include "process.h"


QStringList process::GetAllProcess()
{
    QStringList sl;
    
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);    
    if (hSnapshot == INVALID_HANDLE_VALUE) throw std::runtime_error("INVALID_HANDLE_VALUE");
    
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    
    if (Process32First(hSnapshot, &pe)) 
    {
        do 
        {
            sl.emplace_back(QString::fromWCharArray(pe.szExeFile));
            sl.back() += " (";
            sl.back() += QString::number(pe.th32ProcessID);
            sl.back() += ")";
        } 
        while (Process32Next(hSnapshot, &pe));
    }
    
    sl.pop_front();
    CloseHandle(hSnapshot);
    return sl;
}


DWORD process::targetPID = 0;
HHOOK process::keyboardHook = nullptr;
void *process::lw_info = nullptr;


LRESULT CALLBACK process::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    QListWidget *lwi = static_cast<QListWidget *>(lw_info);

    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        DWORD foregroundPID;
        GetWindowThreadProcessId(GetForegroundWindow(), &foregroundPID);
        if (foregroundPID == targetPID) 
        {
            auto key = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
            // printf("Key: %d\n", key);

            if (lwi)
            {
                lwi->addItem(QString(static_cast<char>(key)));
                lwi->scrollToBottom();
            }
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}


void process::SetHook(DWORD pid, void *lwi)
{
    targetPID = pid;
    lw_info = lwi;
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(nullptr), 0);
}


void process::RemoveKeyboardHook()
{
    if (keyboardHook) 
    {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = nullptr;
    }
}