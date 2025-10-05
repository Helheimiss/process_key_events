#pragma once
#include "pch.h"


class process
{
private:
    static DWORD targetPID;
    static HHOOK keyboardHook;
    static void *lw_info;
    static void *cb_time;
    static void *cb_save;

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
public:
    process() = default;
    ~process() = default;

    static QStringList GetAllProcess();

    static void SetHook(DWORD pid, void *lwi);
    static void RemoveKeyboardHook();
};

