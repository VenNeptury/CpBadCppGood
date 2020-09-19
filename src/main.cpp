#include <iostream>
#include <fstream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

bool responseOk(cpr::Response res);

int main(int argc, char **argv)
{
    auto res = cpr::Get(cpr::Url{"https://api.neko-chxn.xyz/v1/blush/img"});

    if (responseOk(res))
    {
        auto json = nlohmann::json::parse(res.text);

        auto img = cpr::Get(cpr::Url{json["url"].get<std::string>()});

        std::ofstream file;

        file.open("output.gif");
        file << img.text;
        file.close();

        std::cout << "Done!\n";
    }
    else
    {
        std::cout << "Request failed.\n"
                  << res.status_code << ": " << res.error.message << '\n';
    }

    return 0;
}

bool responseOk(cpr::Response res)
{
    return res.status_code < 300 && res.status_code > 199;
}
