#include <iostream>
#include <cpr/cpr.h>
#include "ApiResponse.hpp"

const nekochxn::ApiResponse fetch(const char *url);

int main(int argc, char **argv)
{
    nekochxn::ApiResponse res = fetch("https://api.neko-chxn.xyz/v1/blush/img");

    std::cout << (res.ok ? "OK! " : "RIP! ") << res.statusCode << ": " << (res.ok ? res.url : res.errorMessage) << '\n';

    return 0;
}

const nekochxn::ApiResponse fetch(const char *url)
{
    cpr::Response resRaw = cpr::Get(cpr::Url{url});
    return nekochxn::ApiResponse{resRaw};
}