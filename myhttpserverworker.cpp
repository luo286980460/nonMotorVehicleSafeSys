#include "myhttpserverworker.h"
#include "include/libhv/hthread.h"    // import hv_gettid
#include "include/libhv/hasync.h"     // import hv::async
#include <QDebug>

#define TEST_HTTPS 0

MyHttpServerWorker::MyHttpServerWorker(QObject *parent)
    : QObject{parent}
{

}

MyHttpServerWorker::~MyHttpServerWorker()
{
    hv::async::cleanup();
}

void MyHttpServerWorker::slotStart()
{
    HV_MEMCHECK;

    /* Static file service */
    // curl -v http://ip:port/
    m_router.Static("/", "./html");

    /* Forward proxy service */
    m_router.EnableForwardProxy();
    // curl -v http://httpbin.org/get --proxy http://127.0.0.1:8080
    m_router.AddTrustProxy("*httpbin.org");

    /* Reverse proxy service */
    // curl -v http://ip:port/httpbin/get
    m_router.Proxy("/httpbin/", "http://httpbin.org/");

    /*          POST            */

    // curl -v http://ip:port/echo -d "hello,world!"
    m_router.POST("/echo", [](const HttpContextPtr& ctx) {
        return ctx->send(ctx->body(), ctx->type());
    });

    /*          GET            */
    /* API handlers */
    // curl -v http://ip:port/ping
    m_router.GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
        Q_UNUSED(req);
        hv::Json ex3 = {
                    {"happy", true},
                    {"pi", 3.141},
                    };
        return resp->Json(ex3);
        //return resp->String("connected............");
    });

    // curl -v http://ip:port/data
    m_router.GET("/data", [](HttpRequest* req, HttpResponse* resp) {Q_UNUSED(req);
        static char data[] = "0123456789";
        return resp->Data(data, 10 /*, false */);
    });

    // curl -v http://ip:port/paths
    m_router.GET("/paths", [this](HttpRequest* req, HttpResponse* resp) {Q_UNUSED(req);
        return resp->Json(m_router.Paths());
    });

    // curl -v http://ip:port/get?env=1
    m_router.GET("/get", [](const HttpContextPtr& ctx) {
        hv::Json resp;
        resp["origin"] = ctx->ip();
        resp["url"] = ctx->url();
        resp["args"] = ctx->params();
        resp["headers"] = ctx->headers();
        return ctx->send(resp.dump(2));
    });

    // curl -v http://ip:port/user/123
    m_router.GET("/user/{id}", [](const HttpContextPtr& ctx) {
        hv::Json resp;
        resp["id"] = ctx->param("id");
        return ctx->send(resp.dump(2));
    });

    // curl -v http://ip:port/async
    m_router.GET("/async", [](const HttpRequestPtr& req, const HttpResponseWriterPtr& writer) {Q_UNUSED(req);
        writer->Begin();
        writer->WriteHeader("X-Response-tid", hv_gettid());
        writer->WriteHeader("Content-Type", "text/plain");
        writer->WriteBody("This is an async response.\n");
        writer->End();
    });

    // middleware
    m_router.AllowCORS();
    m_router.Use([](HttpRequest* req, HttpResponse* resp) {Q_UNUSED(req);
        resp->SetHeader("X-Request-tid", hv::to_string(hv_gettid()));
        return HTTP_STATUS_NEXT;
    });

    m_server.service = &m_router;
    m_server.port = m_port;
#if TEST_HTTPS
    server.https_port = 8443;
    hssl_ctx_opt_t param;
    memset(&param, 0, sizeof(param));
    param.crt_file = "cert/server.crt";
    param.key_file = "cert/server.key";
    param.endpoint = HSSL_SERVER;
    if (server.newSslCtx(&param) != 0) {
        fprintf(stderr, "new SSL_CTX failed!\n");
        return -20;
    }
#endif

    // uncomment to test multi-processes
    // server.setProcessNum(4);
    // uncomment to test multi-threads
    // server.setThreadNum(4);

    m_server.start();

    // press Enter to stop
    //while (getchar() != '\n');
}
