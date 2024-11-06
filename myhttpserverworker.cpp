#include "myhttpserverworker.h"
#include "include/libhv/hthread.h"    // import hv_gettid
#include "include/libhv/hasync.h"     // import hv::async

#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QImage>
#include <QApplication>
#include <QDir>
#include <QNetworkReply>
#include <QBuffer>
#include <QPainter>
#include <QDebug>

#define TEST_HTTP                   0
#define IMG_SAVE_PATH               "/Pics"

#define NOVA_PROGRAM_TEXT           "http://%1/screenOn/Text"
#define NOVA_PROGRAM_PIC            "http://%1/screenOn/TextPic"
#define NOVA_PROGRAM_TEXT_AND_PIC   "http://%1/screenOn/TextAndPic"
#define BACK_BLACK_FILE_NAME        "/backBlack.jpg"

#define KEY_FONTSIZE "FontSize"         // 字号
#define KEY_CONTENT "Content"           // 内容
#define KEY_AUDIOTIMES "AudioTimes"     // 音频次数
#define KEY_AUDIOCONTENT "AudioContent" // 音频内容
#define KEY_AUDIOSWITCH "AudioSwitch"   // 音频开关
#define KEY_AUDIOVOLUME "Audiovolume"   // 音频音量

MyHttpServerWorker::MyHttpServerWorker(int port, int novaScreen, QString face2BackUrl, QString face2BoxUrl, QString Place, QObject *parent)
    : QObject{parent}
    , m_port(port)
    , m_novaScreen(novaScreen)
    , m_face2BackUrl(face2BackUrl)
    , m_face2BoxUrl(face2BoxUrl)
    , m_place(Place)
{
    m_novaScreenIpPort = "127.0.0.1:" + QString::number(novaScreen);

    m_imgSavePath = QApplication::applicationDirPath() + IMG_SAVE_PATH;
    QDir imgPath(m_imgSavePath);
    if(!imgPath.exists()){
        imgPath.mkpath(m_imgSavePath);
    }
    connect(this, &MyHttpServerWorker::signalPost, this, &MyHttpServerWorker::post);
}

MyHttpServerWorker::~MyHttpServerWorker()
{
    hv::async::cleanup();
}

QJsonDocument MyHttpServerWorker::unpackNonMotorVehicleIllegalInfo(QJsonObject &json)
{
    qDebug() << QDateTime::currentDateTime().toString("******************************************************* ： yyyyMMdd hh:mm:ss.zzz");

    int fontSize = 30;
    QString content;
    int audioTimes = 1;
    QString voiceContent;
    int audioSwitch = 1;
    int audiovolume = 9;
    QString base64;

    QJsonObject break_rule_info = json.value("break_rule_info").toObject();
    QString b64StrBackImg = break_rule_info.value("img").toString();
    QImage imgBack = QImage::fromData(QByteArray::fromBase64(b64StrBackImg.toLocal8Bit()));
    e_illegalAct illegalAct = (e_illegalAct)break_rule_info.value("break_type").toInt();

    // 备份命令
    QFile file("/home/nonMotorVehicleSafeSys/libs/1.log");
    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(json).toJson());
    file.close();

    //qDebug() << json;

    // 抠非机动车图片
    QJsonObject detect_info = break_rule_info.value("detect_info").toObject();
    //QByteArray base64 = QByteArray::fromBase64(break_rule_info.value("img").toString().toLocal8Bit());
    int x, y, width, height;
    x = detect_info.value("x").toInt();
    y = detect_info.value("y").toInt();
    width = detect_info.value("width").toInt();
    height = detect_info.value("height").toInt();

    int leftOffset = (height - width) / 2;
    if(leftOffset > x){
        x = 0;
    }else if(imgBack.width() < x + height){
        x = imgBack.width() - height;
    }else{
        x = x - leftOffset;
    }

    QImage imgCar = imgBack.copy(x, y, height, height);

    // // 打包数据
    // QJsonObject jsonData;

    // jsonData.insert("FontSize", 32);
    // jsonData.insert("AudioTimes", 1);

    switch(illegalAct){
    case withoutHelmet:
        // jsonData.insert("Content", "请戴好头盔");
        // jsonData.insert("AudioContent", "请戴好头盔");
        content = "请戴好头盔";
        voiceContent = "请戴好头盔";
        break;
    case manned:
        // jsonData.insert("Content", "请不要违法载人");
        // jsonData.insert("AudioContent", "请不要违法载人");
        content = "请不要违法载人";
        voiceContent = "请不要违法载人";
        break;
    case retrograde:
        // jsonData.insert("Content", "请不要逆行");
        // jsonData.insert("AudioContent", "请不要逆行");
        content = "请不要逆行";
        voiceContent = "请不要逆行";
        break;
    case jiZhanFei:
        // jsonData.insert("Content", "请勿违法占道");
        // jsonData.insert("AudioContent", "请勿违法占道");
        content = "请勿违法占道";
        voiceContent = "请勿违法占道";
        break;
    default:
        // jsonData.insert("Content", "请安全驾驶");
        // jsonData.insert("AudioContent", "请安全驾驶");
        content = "请安全驾驶";
        voiceContent = "请安全驾驶";
        break;
    }

    // jsonData.insert("AudioSwitch", 1);
    // jsonData.insert("Audiovolume", 9);

    // jsonData.insert("Img", img2base64(imgCar));
    base64 = img2base64(imgCar);

    //QByteArray data = QJsonDocument(jsonData).toJson();

    // 上屏
    // emit signalPost(QString(NOVA_PROGRAM_TEXT_AND_PIC).arg(m_novaScreenIpPort), data);

    // fontSize content audioTimes voiceContent audioSwitch audiovolume base64);
    emit signalPlayProgram3(fontSize, content, audioTimes, voiceContent, audioSwitch, audiovolume, base64);

    // 上传给黄杨
    sendToBackServer(json);

    return QJsonDocument(json);
}

void MyHttpServerWorker::post(QString url, QByteArray data)
{
    // 构造请求
    QNetworkRequest request;
    /*httpbin.org 这个网站能测试 HTTP 请求和响应的各种信息，比如 cookie、ip、headers 和登录验证等，且支持 GET、POST 等多种方法，对 web 开发和测试很有帮助。*/
    request.setUrl(QUrl(url));

    //request.setUrl(QUrl("http://10.181.218.209:8080/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    //qDebug() << "post : " << data << "****************************************************************";
    //qDebug() << "url: " << url;

    // 发送请求
    //m_manager->post(request, data);
    m_manager->post(request, data);
}

void MyHttpServerWorker::postBack(QNetworkReply* reply)
{
    //qDebug()<<reply->readAll().data(); //输出所有响应内容

    // 获取响应信息
    QByteArray bytes = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << QStringLiteral("解析Json失败");
        return;
    }

    // 解析Json
    if (doucment.isObject())
    {
        QJsonObject obj = doucment.object();
        QJsonValue value;
        if (obj.contains("data"))
        {
            value = obj.take("data");
            if (value.isString())
            {
                QString data = value.toString();
                qDebug() << data;
            }
        }
    }

}

QString MyHttpServerWorker::img2base64(QImage image)
{
    // 图片转base64
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    image.save(&buf, "jpg");
    QByteArray ba2 = ba.toBase64();
    return QString::fromLatin1(ba2);
}
QJsonDocument MyHttpServerWorker::unpackPlayProgram1(QJsonObject &json)
{
    QJsonObject jsonBack;
    QString msg;
    QJsonValue FontSizeJV = json.value(KEY_FONTSIZE);         // 字号
    QJsonValue ContentJV = json.value(KEY_CONTENT);           // 内容
    QJsonValue AudioTimesJV = json.value(KEY_AUDIOTIMES);     // 音频次数
    QJsonValue AudioContentJV = json.value(KEY_AUDIOCONTENT); // 音频内容
    QJsonValue AudioSwitchJV = json.value(KEY_AUDIOSWITCH);   // 音频开关
    QJsonValue AudiovolumeJV = json.value(KEY_AUDIOVOLUME);   // 音频音量
    int FontSize = FontSizeJV.toInt();
    QString Content = ContentJV.toString();
    int AudioTimes = AudioTimesJV.toInt();
    QString AudioContent = AudioContentJV.toString();
    int AudioSwitch = AudioSwitchJV.toInt();
    int Audiovolume = AudiovolumeJV.toInt();

    jsonBack.insert("code", 0);

    // 字号 合法性
    if(!FontSizeJV.isDouble() || FontSize <= 0){
        msg += "error1 FontSize not int or FontSize <= 0;";
        jsonBack["code"] = -1;
    }

    // 内容 合法性
    if(!ContentJV.isString()){
        msg += "error2 Content not string;";
        jsonBack["code"] = -1;
    }

    // 音频次数 合法性
    if(!AudioTimesJV.isDouble() || AudioTimes <= 0){
        msg += "error3 AudioTimes not int or AudioTimes <= 0;";
        jsonBack["code"] = -1;
    }

    // 音频内容 合法性
    if(!AudioContentJV.isString()){
        msg += "error4 AudioContent not string;";
        jsonBack["code"] = -1;
    }


    // 音频开关 合法性
    if(!AudioSwitchJV.isDouble() || AudioSwitch != 0 && AudioSwitch != 1){
        msg += "error5 AudioSwitch not int or AudioSwitch != 0 && AudioSwitch != 1;";
        jsonBack["code"] = -1;
    }

    // 音频音量 合法性
    if(!AudiovolumeJV.isDouble() || Audiovolume < 1 && Audiovolume > 9){
        msg += "error5 Audiovolume not int or 1~9;";
        jsonBack["code"] = -1;
    }

    jsonBack.insert("msg", msg);
    if(jsonBack.value("code").toInt() == 0){
        emit this->signalPlayProgram1(FontSize, Content, AudioTimes, AudioContent, AudioSwitch, Audiovolume);
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

    QJsonValue FontSizeJV = json.value(KEY_FONTSIZE);         // 字号
    QJsonValue ContentJV = json.value(KEY_CONTENT);           // 内容
    QJsonValue AudioTimesJV = json.value(KEY_AUDIOTIMES);     // 音频次数
    QJsonValue AudioContentJV = json.value(KEY_AUDIOCONTENT); // 音频内容
    QJsonValue AudioSwitchJV = json.value(KEY_AUDIOSWITCH);   // 音频开关
    QJsonValue AudiovolumeJV = json.value(KEY_AUDIOVOLUME);   // 音频音量
    int FontSize = FontSizeJV.toInt();
    QString Content = ContentJV.toString();
    int AudioTimes = AudioTimesJV.toInt();
    QString AudioContent = AudioContentJV.toString();
    int AudioSwitch = AudioSwitchJV.toInt();
    int Audiovolume = AudiovolumeJV.toInt();
    QJsonValue imgJV = json.value("Img");
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

    // 音频内容 合法性
    if(!AudioContentJV.isString()){
        msg += "error6 AudioContent not string;";
        jsonBack["code"] = -1;
    }

    if(!imgJV.isString()){
        msg += "error7 Img not string;";
        jsonBack["code"] = -1;
    }

    jsonBack.insert("msg", msg);
    if(jsonBack.value("code").toInt() == 0){
        emit this->signalPlayProgram3(FontSize, Content, AudioTimes, AudioContent, AudioSwitch, Audiovolume, img);
    }

    return QJsonDocument(jsonBack);
}

void MyHttpServerWorker::sendToBackServer(QJsonObject &json)
{

}

void MyHttpServerWorker::slotStart()
{
    //qDebug() << "***********************************************";
    m_manager = new QNetworkAccessManager;

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
    m_router.POST("/YuanHong/nonMotorVehicleIllegalInfo", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();// = jsonDoc.object().value("break_rule_info").toObject();
        QJsonObject break_rule_info = jsonDoc.object().value("break_rule_info").toObject();
        QJsonObject face_info = jsonDoc.object().value("face_info").toObject();

        //qDebug() << jsonDoc;

        // AtU8aRV7yK3YbANv


        QJsonObject jsonUpWide;
        jsonUpWide.insert("key", "AtU8aRV7yK3YbANv");
        jsonUpWide.insert("method", "wfxx");

        QJsonObject jsonUp;
        jsonUp.insert("hphm", "");      // 车牌
        jsonUp.insert("xm", "");        // 姓名
        jsonUp.insert("icard", "");     // 身份证号码
        jsonUp.insert("wfsj", break_rule_info.value("time_1").toString().left(19));      // 违法时间yyyy-MM-dd hh24:mi:ss
        jsonUp.insert("wfxw", QString::number(break_rule_info.value("break_type").toInt()));      // 违法行为，编码
        jsonUp.insert("wfdd", m_place); // 违法地点，编码
        jsonUp.insert("type", "2");     // 图片传输方式1 url  2 base64
        //jsonUp.insert("photo1", face_info.value("img").toString());     // 图片1
        jsonUp.insert("photo1", "img"); // 图片1
        jsonUp.insert("photo2", "");    // 图片2
        jsonUp.insert("photo3", "");    // 特征抠图
        //jsonUp.insert("photo4", face_info.value("img").toString());     // 人脸抠图，人脸抓拍时候传输
        jsonUp.insert("photo4", "img"); // 人脸抠图，人脸抓拍时候传输
        jsonUp.insert("DevNum", m_face2BoxUrl); //


        jsonUpWide.insert("data", jsonUp);

        signalPost(this->m_face2BackUrl, QJsonDocument(jsonUpWide).toJson());     // 发送给后台
        qDebug() << "jsonUpWide : \n" << jsonUpWide;
        qDebug() << "\n";

        return ctx->send(unpackNonMotorVehicleIllegalInfo(json).toJson().toStdString(), APPLICATION_JSON);
    });

    // 屏幕显示文字
    m_router.POST("/screenOn/Text", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();

        //return ctx->send(unpackNonMotorVehicleIllegalInfo(json).toJson().toStdString(), APPLICATION_JSON);
        return ctx->send(unpackPlayProgram1(json).toJson().toStdString(), APPLICATION_JSON);
    });

    // 屏幕显示图片
    m_router.POST("/screenOn/Pic", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();

        return ctx->send(unpackPlayProgram2(json).toJson().toStdString(), APPLICATION_JSON);
    });

    // 屏幕显示文字+图片
    m_router.POST("/screenOn/TextAndPic", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();
        return ctx->send(unpackPlayProgram3(json).toJson().toStdString(), APPLICATION_JSON);
    });

    // 人脸信息上传
    m_router.POST("/face/update", [this](const HttpContextPtr& ctx) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromStdString(ctx->body()));
        QJsonObject json = jsonDoc.object();// = jsonDoc.object().value("break_rule_info").toObject();

        //qDebug() << jsonDoc;


        signalPost(this->m_face2BoxUrl, jsonDoc.toJson());     // 发送给后台

        return ctx->sendString("success");
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
                    {"time", "最后更新时间：2024年11月06日"},
                    {"Name", "非机动车安全防治一体机"},
                    {"Version", "1.10"},
                    {"Msg", "整合版,包含gps、温湿度、诺瓦屏，依赖一个STH30.py"}
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
