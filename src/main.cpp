#include <iostream>
#include <cpr/cpr.h>

bool responseOk(cpr::Response res);

int main(int argc, char **argv)
{
    auto res = cpr::Get(cpr::Url{"https://api.neko-chxn.xyz/v1/blush/img"});

    if (responseOk(res))
    {
        std::cout << res.text << '\n';
    }
    else
    {
        std::cout << "Response failed.\n"
                  << res.status_code << ": " << res.error.message << '\n';
    }

    return 0;
}

bool responseOk(cpr::Response res)
{
    return res.status_code < 300 && res.status_code > 199;
}
