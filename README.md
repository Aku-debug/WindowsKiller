# 🔌 AutoShutdownApp

🖥️ **AutoShutdownApp**, bilgisayarın otomatik olarak 3 saniye içinde kapatılmasını sağlayan, kendisini Windows başlangıcına ekleyen ve gerekirse yönetici izinlerini isteyen basit bir C++ uygulamasıdır.

DAHA GELISTIRILME ASAMASIN DA DOGRU CALISMAYABILIR.

---

## 🇹🇷 Türkçe Açıklama

### 🔧 Özellikler

- 🧪 **Yönetici kontrolü yapar:** Uygulama yönetici olarak çalışmıyorsa kendini yeniden yönetici yetkisiyle başlatır.
- 📝 **Kendini başlatma klasörüne ekler:** Uygulama ilk çalıştırıldığında kendini Windows başlangıcına ekler (`HKCU\\...\\Run`).
- 🔒 **Konsol penceresini gizler:** Çalışırken konsol penceresini gizler (isteğe bağlı olarak).
- 💣 **3 saniye sonra sistemi kapatır:** Komut satırı üzerinden zorla sistemi kapatma komutu gönderir (`shutdown /s /t 3 /f`).

### 📌 Uygulamanın Akışı

1. Uygulama başlatılır.
2. Eğer yönetici olarak çalışmıyorsa, kendini tekrar yönetici olarak başlatır.
3. Ardından kendisini kullanıcı düzeyinde başlangıç kayıt defterine ekler.
4. Konsol penceresini gizler.
5. 3 saniye sonra sistemi zorla kapatır.

---

## 🇬🇧 English Description

### 🔧 Features

"Still under development, may not function correctly."

- 🧪 **Admin check:** If not running as admin, the app relaunches itself with admin privileges.
- 📝 **Adds itself to startup:** On first run, adds itself to the Windows startup registry (`HKCU\\...\\Run`).
- 🔒 **Hides console window:** Hides its console window when running (optional).
- 💣 **Shuts down the PC after 3 seconds:** Executes a forced shutdown via `shutdown /s /t 3 /f`.

### 📌 Execution Flow

1. App starts.
2. If not running as admin, relaunches itself with elevation.
3. Adds itself to startup registry (user level).
4. Hides the console window.
5. Forces system shutdown after 3 seconds.

---

## ⚠️ Uyarı / Warning

> Bu uygulama bilgisayarı **zorla kapatır**. Lütfen sadece test amaçlı kullanın. Açık dosyalar kaybolabilir.

> This app performs a **forced shutdown**. Please use it for testing only. Unsaved files may be lost.

---

## 🛠️ Build (Derleme)

```bash
g++ AutoShutdownApp.cpp -o AutoShutdownApp.exe
