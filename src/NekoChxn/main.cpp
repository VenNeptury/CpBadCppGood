#include <iostream>
#include <cpr/cpr.h>
#include "ApiResponse.hpp"

int main(int argc, char **argv)
{
    auto resRaw = cpr::Get(cpr::Url{"https://api.neko-chxn.xyz/v1/blush/img"});

    auto res = *new ApiResponse(resRaw);

    std::cout << (res.ok ? "OK! " : "RIP! ") << res.statusCode << ": " << (res.ok ? res.url : res.errorMessage) << '\n';

    return 0;
}
