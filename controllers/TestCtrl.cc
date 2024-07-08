#include "TestCtrl.h"

void TestCtrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
	auto resp=HttpResponse::newHttpResponse();
	resp->setStatusCode(k200OK);
	resp->setContentTypeCode(CT_TEXT_HTML);
	resp->setBody("Hello World!");
	auto clientPtr = drogon::app().getDbClient();
	auto f = clientPtr->execSqlAsyncFuture("select * from test");
	auto r = f.get(); // Block until we get the result or catch the exception;
	std::cout << r.size() << " rows selected!" << std::endl;
	int i = 0;
		for (auto row : r)
	{
			std::cout << i++ << ": user name is " << row["id"].as<std::string>() << std::endl;
	}
	callback(resp);
}
