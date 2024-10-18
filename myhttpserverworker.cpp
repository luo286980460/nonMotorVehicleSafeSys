#include "myhttpserverworker.h"
#include "include/libhv/hthread.h"    // import hv_gettid
#include "include/libhv/hasync.h"     // import hv::async

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDateTime>
//#include <QImage>
//#include <QApplication>
#include <QDir>
#include <QDebug>

#define TEST_HTTPS 0
#define IMG_SAVE_PATH "/imgs"

MyHttpServerWorker::MyHttpServerWorker(QObject *parent)
    : QObject{parent}
{
    //m_imgSavePath = QApplication::applicationDirPath() + IMG_SAVE_PATH;
    QDir imgPath(m_imgSavePath);
    if(!imgPath.exists()){
        imgPath.mkpath(m_imgSavePath);
    }
}

MyHttpServerWorker::~MyHttpServerWorker()
{
    hv::async::cleanup();
}

QJsonDocument MyHttpServerWorker::unpackNonMotorVehicleIllegalInfo(QJsonObject &json)
{
    return QJsonDocument();
    // QJsonObject jsonBack;
    // QString msg;
    // QJsonValue fontSizeJV = json.value("FontSize");
    // QJsonValue contentJV = json.value("Content");
    // int fontSize = fontSizeJV.toInt();
    // QString content;

    // jsonBack.insert("code", 0);

    // if(!fontSizeJV.isDouble() || fontSize <= 0){
    //     msg += "error1 FontSize not int or fontSize <= 0;";
    //     jsonBack["code"] = -1;
    // }else{
    //     fontSize = fontSizeJV.toInt();
    // }

    // if(!contentJV.isString()){
    //     msg += "error2 Content not string;";
    //     jsonBack["code"] = -1;
    // }else{
    //     content = contentJV.toString();
    // }

    // jsonBack.insert("msg", msg);
    // if(jsonBack.value("code").toInt() == 0){
    //     emit this->signalPlayProgram1(fontSize, content);
    // }

    // return QJsonDocument(jsonBack);

    //QByteArray base64 = QByteArray::fromBase64(json.value("img").toString().toLocal8Bit());
    //QImage image;
    //image.loadFromData(base64);

    //QLabel* label = new QLabel;
    //label->resize(image.size()/4);
    //label->setPixmap(QPixmap::fromImage(image));
    //label->setScaledContents(true);
    // label->resize(500, 500);
    // label->setText("**********");
    //label->show();
    //showMsg(json.value("img").toString());

    // 保存图片并且上屏
    // if(!base64.isEmpty()){
    //     image.save(m_imgSavePath + "/1.jpg", "png");
    //     qDebug() << m_imgSavePath + "/1.jpg";
    // }

    //qDebug() << json.value("img").toString();

}

QJsonDocument MyHttpServerWorker::unpackPlayProgram1(QJsonObject &json)
{
    QJsonObject jsonBack;
    QString msg;
    QJsonValue FontSizeJV = json.value("FontSize");         // 字号
    QJsonValue AudioTimesJV = json.value("AudioTimes");     // 音频次数
    QJsonValue ContentJV = json.value("Content");           // 内容
    QJsonValue AudioSwitchJV = json.value("AudioSwitch");   // 音频开关
    QJsonValue AudiovolumeJV = json.value("Audiovolume");   // 音频音量
    int FontSize = FontSizeJV.toInt();
    int AudioTimes = AudioTimesJV.toInt();
    QString Content = ContentJV.toString();
    int AudioSwitch = AudioSwitchJV.toInt();
    int Audiovolume = AudiovolumeJV.toInt();

    jsonBack.insert("code", 0);

    // 字号 合法性
    if(!FontSizeJV.isDouble() || FontSize <= 0){
        msg += "error1 FontSize not int or FontSize <= 0;";
        jsonBack["code"] = -1;
    }

    // 音频次数 合法性
    if(!AudioTimesJV.isDouble() || AudioTimes <= 0){
        msg += "error2 AudioTimes not int or AudioTimes <= 0;";
        jsonBack["code"] = -1;
    }

    // 内容 合法性
    if(!ContentJV.isString()){
        msg += "error3 Content not string;";
        jsonBack["code"] = -1;
    }

    // 音频开关 合法性
    if(!AudioSwitchJV.isDouble() || AudioSwitch != 0 && AudioSwitch != 1){
        msg += "error4 AudioSwitch not int or AudioSwitch != 0 && AudioSwitch != 1;";
        jsonBack["code"] = -1;
    }

    // 音频音量 合法性
    if(!AudiovolumeJV.isDouble() || Audiovolume < 1 && Audiovolume > 9){
        msg += "error5 Audiovolume not int or 1~9;";
        jsonBack["code"] = -1;
    }

    jsonBack.insert("msg", msg);
    if(jsonBack.value("code").toInt() == 0){
        emit this->signalPlayProgram1(FontSize, AudioTimes, Content, AudioSwitch, Audiovolume);
    }

    return QJsonDocument(jsonBack);
}

QJsonDocument MyHttpServerWorker::unpackPlayProgram2(QJsonObject &json)
{
    QJsonObject jsonBack;
    QJsonValue imgJV = json.value("Img");
    QString img;
    QString msg;

    jsonBack.insert("code", 0);

    if(!imgJV.isString()){
        msg += "error1 Img not string;";
        jsonBack["code"] = -1;
    }else{
        img = imgJV.toString();
    }

    jsonBack.insert("msg", msg);
    if(jsonBack.value("code").toInt() == 0){
        //qDebug() << "this->signalPlayProgram2(msg);";
        emit this->signalPlayProgram2(img);
    }

    return QJsonDocument(jsonBack);
}

QJsonDocument MyHttpServerWorker::unpackPlayProgram3(QJsonObject &json)
{
    QJsonObject jsonBack;
    QString msg;
    QJsonValue FontSizeJV = json.value("FontSize");         // 字号
    QJsonValue AudioTimesJV = json.value("AudioTimes");     // 音频次数
    QJsonValue ContentJV = json.value("Content");           // 内容
    QJsonValue AudioSwitchJV = json.value("AudioSwitch");   // 音频开关
    QJsonValue AudiovolumeJV = json.value("Audiovolume");   // 音频音量
    QJsonValue imgJV = json.value("Img");                   // 图片
    int FontSize = FontSizeJV.toInt();
    int AudioTimes = AudioTimesJV.toInt();
    QString Content = ContentJV.toString();
    int AudioSwitch = AudioSwitchJV.toInt();
    int Audiovolume = AudiovolumeJV.toInt();
    QString img = imgJV.toString();

    jsonBack.insert("code", 0);

    // 字号 合法性
    if(!FontSizeJV.isDouble() || FontSize <= 0){
        msg += "error1 FontSize not int or FontSize <= 0;";
        jsonBack["code"] = -1;
    }

    // 音频次数 合法性
    if(!AudioTimesJV.isDouble() || AudioTimes <= 0){
        msg += "error2 AudioTimes not int or AudioTimes <= 0;";
        jsonBack["code"] = -1;
    }

    // 内容 合法性
    if(!ContentJV.isString()){
        msg += "error3 Content not string;";
        jsonBack["code"] = -1;
    }

    // 音频开关 合法性
    if(!AudioSwitchJV.isDouble() || AudioSwitch != 0 && AudioSwitch != 1){
        msg += "error4 AudioSwitch not int or AudioSwitch != 0 && AudioSwitch != 1;";
        jsonBack["code"] = -1;
    }

    // 音频音量 合法性
    if(!AudiovolumeJV.isDouble() || Audiovolume < 1 && Audiovolume > 9){
        msg += "error5 Audiovolume not int or 1~9;";
        jsonBack["code"] = -1;
    }

    if(!imgJV.isString()){
        msg += "error3 Img not string;";
        jsonBack["code"] = -1;
    }

    jsonBack.insert("msg", msg);
    if(jsonBack.value("code").toInt() == 0){
        emit this->signalPlayProgram3(FontSize, AudioTimes, Content, AudioSwitch, Audiovolume, img);
    }

    return QJsonDocument(jsonBack);
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
    m_router.POST("/screenOn/Text", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();

        //return ctx->send(unpackNonMotorVehicleIllegalInfo(json).toJson().toStdString(), APPLICATION_JSON);
        return ctx->send(unpackPlayProgram1(json).toJson().toStdString(), APPLICATION_JSON);
    });

    m_router.POST("/screenOn/Pic", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();

        return ctx->send(unpackPlayProgram2(json).toJson().toStdString(), APPLICATION_JSON);
    });

    m_router.POST("/screenOn/TextAndPic", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();
        return ctx->send(unpackPlayProgram3(json).toJson().toStdString(), APPLICATION_JSON);
    });

    m_router.POST("/screenOff", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();

        //return ctx->send(unpackNonMotorVehicleIllegalInfo(json).toJson().toStdString(), APPLICATION_JSON);
        return ctx->sendString("未实现");
    });

    m_router.POST("/echo", [](const HttpContextPtr& ctx) {
        return ctx->send(ctx->body(), ctx->type());
    });

    /*          GET            */
    /* API handlers */
    // curl -v http://ip:port/ping
    m_router.GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
        Q_UNUSED(req);
        hv::Json ex3 = {
                    {"time", QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss").toStdString()},
                    {"Name", "诺瓦屏幕控制服务"},
                    {"Version", "0.1"},
                    {"Msg", "测试版"}
                    };
        return resp->Json(ex3);
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
