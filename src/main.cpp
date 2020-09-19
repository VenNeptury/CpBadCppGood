#include <iostream>
#include <fstream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

bool responseOk(cpr::Response res);

class ApiResponse
{
public:
    std::string url;
    std::string errorMessage;
    int statusCode;
    bool ok = true;
    ApiResponse(cpr::Response res)
    {
        statusCode = res.status_code;
        errorMessage = res.error.message;

        if (statusCode > 299 || statusCode < 200)
            ok = false;

        auto json = nlohmann::json::parse(res.text);
        if (json.contains("url"))
            url = json["url"].get<std::string>();
        else
            ok = false;
    }
};

int main(int argc, char **argv)
{
    auto resRaw = cpr::Get(cpr::Url{"https://api.neko-chxn.xyz/v1/blush/img"});
    auto res = *new ApiResponse(resRaw);

    std::cout << (res.ok ? "OK! " : "RIP! ") << res.statusCode << ": " << (res.ok ? res.url : res.errorMessage) << '\n';

    return 0;
}

bool responseOk(cpr::Response res)
{
    return res.status_code < 300 && res.status_code > 199;
}
