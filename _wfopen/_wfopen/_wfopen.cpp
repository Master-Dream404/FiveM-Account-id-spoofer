#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <string_view>

#define FatalError(str) std::cout << str << std::endl
#define FatalInfo(str) std::cout << str << std::endl

using hex32 = uint32_t;
using hex64 = uint64_t;
using string = std::string;

const char* path_t = "C:\\Users\\username\\AppData\\Roaming\\CitizenFX\\";
#define cls() system("cls")


void __getaccountdata(std::string* out_data)
{
    FILE* stream;
    std::string path = path_t;
    path.append("ros_auth.dat");


    fopen_s(&stream, path.c_str(), "r+");


    fseek(stream, 0, SEEK_END);
    int length = ftell(stream);
    fseek(stream, 0, SEEK_SET);

    std::vector<char> data(length + 1);
    fread(&data[0], 1, length, stream);

    fclose(stream);

    *out_data = &data[0];

}

bool __getaccount(hex32* out)
{
    cls();
    static std::once_flag gotAccountId;
    static hex32 accountId;


    FILE* stream;
    std::string path = path_t;
    if (path.find("username") != std::string::npos)
    {
        MessageBoxA(0, "Set your path", "C!@?#", 0);
        exit(0x0);
    }
    path.append("ros_id.dat");
    fopen_s(&stream, path.c_str(), "r+");
    fseek(stream, 0, SEEK_SET);

    fread(&accountId, 1, sizeof(accountId), stream);

    fclose(stream);

    *out = accountId;
    if (accountId != NULL)
    {
        return true;
    }
    else
        return false;
}

hex32 __spoof()
{
    cls();
    FILE* stream;
    hex32 accountId;

    accountId &= 0x7FFFFFFF;

    HCRYPTPROV provider;
    if (!CryptAcquireContext(&provider, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        FatalError("CryptAcquireContext failed (ros:five ID generation)");
    }
    if (!CryptGenRandom(provider, sizeof(accountId), reinterpret_cast<BYTE*>(&accountId)))
    {
        FatalError("CryptGenRandom failed (ros:five ID generation)");
    }

    // release
    CryptReleaseContext(provider, 0);

    if (accountId == 0)
    {
        FatalError("ros:five ID generation generated a null ID!");
        Sleep(5000);
    }
    else
    {
        std::string path = path_t;
        path.append("ros_id.dat");
        fopen_s(&stream, path.c_str(), "r+");
        fseek(stream, 0, SEEK_SET);

        fwrite(&accountId, 1, sizeof(accountId), stream);

        fclose(stream);
    }
}
hex32 __block()
{
    cls();
    FILE* stream;
    hex32 accountId = 0;

    std::string path = path_t;
    path.append("ros_id.dat");
    fopen_s(&stream, path.c_str(), "r+");
    fseek(stream, 0, SEEK_SET);

    fwrite(&accountId, 1, sizeof(accountId), stream);

    fclose(stream);
}

hex32 __fastcall_block()
{
    cls();
    FILE* stream;
    hex32 accountId = 0;

    std::string path = path_t;
    path.append("ros_id.dat");
    fopen_s(&stream, path.c_str(), "r+");
    fseek(stream, 0, SEEK_SET);

    fwrite(&accountId, 1, sizeof(accountId), stream);

    fclose(stream);
}


void __getmachineguid(std::string* out)
{
    string data;
    DWORD size = 128;

    if (RegGetValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Cryptography", L"MachineGuid", RRF_RT_REG_SZ, nullptr, &data[0], &size) == 0)
    {

        *out = data.c_str();
    }
    else
    {
        *out = "none";
    }
}

void __load_cidia_work()
{
    hex32 account;
    bool auto_t = false;
    __getaccount(&account);
    while (true && !auto_t)
    {
        std::string command;
        FatalInfo("Hello World cidia was here!\n[Account] -> " << account << "\n[Spoof]\n[Block]\n[Auto]");
        std::getline(std::cin, command);
        if (command == "spoof" || command == "Spoof")
        {
            __spoof();
            Sleep(1000);
            __getaccount(&account);
            FatalInfo("new account id -> " << account);
            Sleep(2000);
            cls();
        }
        if (command == "block" || command == "Block")
        {
            __block();
            Sleep(1000);
            __getaccount(&account);
            FatalInfo("new account id -> " << account);
            Sleep(2000);
            cls();
        }
        if (command == "auto")
        {
            auto_t = true;
        }
        if (command.find("block") == std::string::npos && command.find("spoof") == std::string::npos && command.find("auto") == std::string::npos)
        {
            cls();
        }
    }

    if (auto_t)
    {
        FatalInfo("[Account] -> " << account << std::endl);
        while (true)
        {
            __fastcall_block();
            __getaccount(&account);
            if (GetAsyncKeyState(VK_INSERT) & 1)
            {
                auto_t = false;
            }
        }
    }
}

int main()
{
    while (true)
    {
        __load_cidia_work();
    }
}
