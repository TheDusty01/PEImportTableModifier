#include <Windows.h>

extern "C" __declspec(dllexport) void SomeFunction() {};

DWORD WINAPI Init(HMODULE hModule)
{
    MessageBoxA(NULL, "General Kenobi", "Hello there", MB_OK);

    // Uninject
    //FreeLibraryAndExitThread(hModule, 0);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Do not get notified by thread attach-/detachment calls
        DisableThreadLibraryCalls(hModule);

        HANDLE threadHanle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, nullptr);
        if (threadHanle)
            CloseHandle(threadHanle);
        break;
    
    //case DLL_THREAD_ATTACH: // Ignored
    //case DLL_THREAD_DETACH: // Ignored
    //case DLL_PROCESS_DETACH:
    //    break;
    }

    return TRUE;
}

//extern "C" __declspec(dllexport) void SomeFunction() {};
//
//BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
//{
//    switch (ul_reason_for_call)
//    {
//    case DLL_PROCESS_ATTACH:
//        MessageBoxA(NULL, "Hello", "My DLL", MB_OK);
//
//    case DLL_THREAD_ATTACH: // Ignored
//    case DLL_THREAD_DETACH: // Ignored
//    case DLL_PROCESS_DETACH:
//        break;
//    }
//    return TRUE;
//}