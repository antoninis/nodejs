#include <napi.h>

#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")
 
#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>

Napi::String GetUsers(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    setlocale(LC_ALL, "Rus");
    DWORD dwlevel = 0;
    DWORD dwfilter = 0;
    USER_INFO_0* theEntries = new USER_INFO_0[20];
    DWORD dwprefmaxlen = 512;
    DWORD dwentriesread;
    DWORD dwtotalentries;
    NET_API_STATUS result;

    std::wstring resultNames = L"";
    result = NetUserEnum(NULL, dwlevel, dwfilter, (LPBYTE*)&theEntries, dwprefmaxlen, &dwentriesread, &dwtotalentries, NULL);
    for (int i = 0; i < dwentriesread; i++) {
        resultNames += theEntries[i].usri0_name;
	    resultNames += L" ";
    }
    NetApiBufferFree(theEntries);

    return Napi::String::New(env, std::u16string(resultNames.begin(), resultNames.end()));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "getUsers"),
              Napi::Function::New(env, GetUsers));
  return exports;
}

NODE_API_MODULE(getUsers, Init)