#include <drogon/drogon.h>

#include "store/MenuStore.h"

int main()
{
    MenuStore::instance().loadFromFile("seed/menu_seed.json");

    drogon::app().registerPreRoutingAdvice(
        [](const drogon::HttpRequestPtr &req,
           drogon::AdviceCallback &&callback,
           drogon::AdviceChainCallback &&chainCallback) {
            if (req->method() == drogon::Options)
            {
                auto resp = drogon::HttpResponse::newHttpResponse();
                resp->addHeader("Access-Control-Allow-Origin", "*");
                resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
                resp->addHeader("Access-Control-Allow-Methods", "GET,POST,PATCH,DELETE,OPTIONS");
                callback(resp);
                return;
            }
            chainCallback();
        });

    drogon::app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
            resp->addHeader("Access-Control-Allow-Methods", "GET,POST,PATCH,DELETE,OPTIONS");
        });

    drogon::app().loadConfigFile("config.json");
    drogon::app().run();
    return 0;
}
