#include "myhttpserverworker.h"
#include "include/hthread.h"    // import hv_gettid
#include "include/hasync.h"     // import hv::async
#include "aplayer.h"

#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


#define TEST_HTTPS 0

MyHttpServerWorker::MyHttpServerWorker(QObject *parent)
    : QObject{parent}
{

}

MyHttpServerWorker::~MyHttpServerWorker()
{
    hv::async::cleanup();
}

void MyHttpServerWorker::initHttpServer()
{
    HV_MEMCHECK;

    m_server = new HttpServer;
    m_router = new HttpService;
    m_server->service = m_router;
    m_server->port = m_port;

    m_router->Static("/", "./html");
    m_router->EnableForwardProxy();
    m_router->AddTrustProxy("*httpbin.org");
    m_router->Proxy("/httpbin/", "http://httpbin.org/");

    /*          POST            */
    m_router->POST("/echo", [](const HttpContextPtr& ctx) {
        return ctx->send(ctx->body(), ctx->type());
    });

    /*          GET            */
    m_router->GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
        Q_UNUSED(req);
        Json ex3 = {
                    {"connected", true},
                    {"time", QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss").toStdString()},
                    };
        return resp->Json(ex3);
        //return resp->String("connected............");
    });

    m_router->POST("/play/start", [=](const HttpContextPtr& ctx) {
        QJsonObject json;
        QString error;

        emit signalPlayStart();
        json.insert("code", 0);
        json.insert("msg", "successful");

        return ctx->sendString(QJsonDocument(json).toJson().toStdString());
    });

    m_router->POST("/play/stop", [=](const HttpContextPtr& ctx) {

        QJsonObject json;
        QString error;

        emit signalPlayStop();
        json.insert("code", 0);
        json.insert("msg", "successful");

        return ctx->sendString(QJsonDocument(json).toJson().toStdString());
    });

    m_router->POST("/addAudio", [=](const HttpContextPtr& ctx) {

        QJsonObject backJson;
        QString error;
        QJsonDocument jsonObj = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject resJson = jsonObj.object();
        QJsonArray jsonArray;

        // 是否含有键值（count data） data值是否为数组
        if(!resJson.contains("data") || !resJson.value("data").isArray()){
            backJson.insert("code", 1);
            backJson.insert("msg", "json fromat error");

            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }

        // data数组里面是否为string
        jsonArray = resJson.value("data").toArray();
        foreach(QJsonValue str, jsonArray){
            if(!str.isString()){
                backJson.insert("code", 1);
                backJson.insert("msg", "file name fromat error");

                return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
            }
        }

        backJson.insert("code", 0);
        if(m_aPlayer){
            for(int i=0; i<jsonArray.size(); i++){
                m_aPlayer->addAudio(jsonArray.at(i).toString(), error);
                backJson.insert(jsonArray.at(i).toString(), error);
            }
        }else{
            backJson.value("code") = 1;
            backJson.insert("msg", "m_aPlayer is nullptr");
        }

        return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
    });

    m_router->POST("/clearPlayList", [=](const HttpContextPtr& ctx) {

        QJsonObject json;
        if(m_aPlayer){
            json.insert("code", 0);
            json.insert("msg", "successful");

            emit signalClearPlayListp();
            return ctx->sendString(QJsonDocument(json).toJson().toStdString());
        }else{
            json.insert("code", 1);
            json.insert("msg", "m_aPlayer is nullptr");

            return ctx->sendString(QJsonDocument(json).toJson().toStdString());
        }
    });

    m_router->POST("/setLoop", [=](const HttpContextPtr& ctx) {
        QJsonObject backJson;
        QString error;
        QJsonDocument jsonObj = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject resJson = jsonObj.object();
        int loop;

        // 是否含有键值loop loop值是否为整数
        if(!resJson.contains("loop") || !resJson.value("loop").isDouble()){
            backJson.insert("code", 1);
            backJson.insert("msg", "json fromat error");

            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }

        // loop值是否合法
        loop = resJson.value("loop").toInt();
        if(loop < 0 || loop > 2  ){
            backJson.insert("code", 1);
            backJson.insert("msg", "loop value error");

            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }

        if(m_aPlayer){
            m_aPlayer->setLoop(loop);
            backJson.insert("code", 0);
            backJson.insert("msg", "successful");
            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }else{
            backJson.insert("code", 1);
            backJson.insert("msg", "m_aPlayer is nullptr");

            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }

    });

    m_router->POST("/setVolume", [=](const HttpContextPtr& ctx) {
        QJsonObject backJson;
        QString error;
        QJsonDocument jsonObj = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject resJson = jsonObj.object();
        int volume;

        // 是否含有键值volume volume值是否为整数
        if(!resJson.contains("volume") || !resJson.value("volume").isDouble()){
            backJson.insert("code", 1);
            backJson.insert("msg", "json fromat error");

            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }

        // volume值是否合法
        volume = resJson.value("volume").toInt();
        if(volume < 1 || volume > 10  ){
            backJson.insert("code", 1);
            backJson.insert("msg", "volume value error");

            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }

        if(m_aPlayer){
            m_aPlayer->setVolume(volume);
            backJson.insert("code", 0);
            backJson.insert("msg", "successful");
            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }else{
            backJson.insert("code", 1);
            backJson.insert("msg", "m_aPlayer is nullptr");

            return ctx->sendString(QJsonDocument(backJson).toJson().toStdString());
        }

    });

    m_router->GET("/playList", [=](HttpRequest* req, HttpResponse* resp) {Q_UNUSED(req);
        QJsonObject json;
        QJsonArray playList;

        if(m_aPlayer){
            foreach(QString name,  m_aPlayer->getPlayList()){
                playList << name;
            }

            json.insert("code", 0);
            json.insert("msg", "success");
            json.insert("循环模式", m_aPlayer->getLoopPattern());
            json.insert("count", playList.size());
            json.insert("data", playList);

            QByteArray jsonBy = QJsonDocument(json).toJson();
            return resp->Data(jsonBy.data(), jsonBy.size());
        }else{
            json.insert("code", 1);
            json.insert("msg", "m_aPlayer is nullptr");

            QByteArray jsonBy = QJsonDocument(json).toJson();
            return resp->Data(jsonBy.data(), jsonBy.size());
        }
    });
/*
    m_router->POST("/setLoopPattern", [=](const HttpContextPtr& ctx) {

//        QJsonObject json;
//        if(m_aPlayer){
//            json.insert("code", 0);
//            json.insert("msg", "successful");

//            return ctx->sendString(QJsonDocument(json).toJson().toStdString());
//        }else{
//            json.insert("code", 1);
//            json.insert("msg", "m_aPlayer is nullptr");

//            return ctx->sendString(QJsonDocument(json).toJson().toStdString());
//        }
    });
*/
//    // curl -v http://ip:port/data
//    m_router->GET("/date", [](HttpRequest* req, HttpResponse* resp) {Q_UNUSED(req);
//        //static char data[] = "0123456789";QDateTime
//        //static char data[] = QDateTime::currentDateTime().toString("yyyyMMdd hh:mm:ss").toLocal8Bit().data();
//        QString data = QDateTime::currentDateTime().toString("yyyyMMdd hh:mm:ss").toLocal8Bit().data();
//        return resp->Data(data.toLocal8Bit().data(), data.size() /*, false */);
//    });

//    // curl -v http://ip:port/paths
//    m_router->GET("/paths", [=](HttpRequest* req, HttpResponse* resp) {Q_UNUSED(req);
//        return resp->Json(m_router->Paths());
//    });

//    // curl -v http://ip:port/get?env=1
//    m_router->GET("/get", [](const HttpContextPtr& ctx) {
//        hv::Json resp;
//        resp["origin"] = ctx->ip();
//        resp["url"] = ctx->url();
//        resp["args"] = ctx->params();
//        resp["headers"] = ctx->headers();
//        return ctx->send(resp.dump(2));
//    });

//    // curl -v http://ip:port/user/123
//    m_router->GET("/user/{id}", [](const HttpContextPtr& ctx) {
//        hv::Json resp;
//        resp["id"] = ctx->param("id");
//        return ctx->send(resp.dump(2));
//    });

//    // curl -v http://ip:port/async
//    m_router->GET("/async", [](const HttpRequestPtr& req, const HttpResponseWriterPtr& writer) {Q_UNUSED(req);
//        writer->Begin();
//        writer->WriteHeader("X-Response-tid", hv_gettid());
//        writer->WriteHeader("Content-Type", "text/plain");
//        writer->WriteBody("This is an async response.\n");
//        writer->End();
//    });

//    // middleware
//    m_router->AllowCORS();
//    m_router->Use([](HttpRequest* req, HttpResponse* resp) {Q_UNUSED(req);
//        resp->SetHeader("X-Request-tid", hv::to_string(hv_gettid()));
//        return HTTP_STATUS_NEXT;
//    });

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

    m_server->start();
}

void MyHttpServerWorker::initAPlayer()
{
    m_aPlayer = new aPlayer;
    connect(this, &MyHttpServerWorker::signalPlayStart, m_aPlayer, &aPlayer::slotPlayStart);
    connect(this, &MyHttpServerWorker::signalPlayStop, m_aPlayer, &aPlayer::slotPlayStop);
    connect(this, &MyHttpServerWorker::signalClearPlayListp, m_aPlayer, &aPlayer::slotClearPlayListp);
}

void MyHttpServerWorker::slotStart()
{
    initHttpServer();
    initAPlayer();
}
