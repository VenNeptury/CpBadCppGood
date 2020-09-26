#ifndef _API_RESPONSE_H_
#define _API_RESPONSE_H_

#include <nlohmann/json.hpp>
#include <string>

namespace nekochxn
{
    class ApiResponse
    {
    public:
        std::string url;
        std::string errorMessage;
        int32_t statusCode;
        bool ok = true;
        ApiResponse(cpr::Response res)
        {
            statusCode = res.status_code;
            errorMessage = res.error.message;

            if (statusCode > 299 || statusCode < 200)
                ok = false;
            try
            {
                auto json = nlohmann::json::parse(res.text);
                if (json.contains("url"))
                    url = json["url"].get<std::string>();
                else if (ok)
                    ok = false;
            }
            catch (nlohmann::detail::parse_error error)
            {
                if (ok)
                    ok = false;
            }
        }
    };
} // namespace nekochxn

#endif