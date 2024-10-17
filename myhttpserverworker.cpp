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

MyHttpServerWorker::MyHttpServerWorker(QObject *parent)
    : QObject{parent}
    , m_aPlayerIpPort("127.0.0.1:23334")
    , m_novaScreenIpPort("127.0.0.1:23335")
{
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
    QJsonObject break_rule_info = json.value("break_rule_info").toObject();
    QString b64StrBackImg = break_rule_info.value("img").toString();
    QImage imgBack = QImage::fromData(QByteArray::fromBase64(b64StrBackImg.toLocal8Bit()));

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
    QImage imgCar = imgBack.copy(x - (height -width )/2, y, height, height);//.scaledToHeight(160);

    // QJsonObject face_info = json.value("face_info").toObject();
    // QString base64Str = face_info.value("img").toString();

    // 生产黑底图
    // QImage back(160,160,QImage::Format_RGB888);
    // back.fill(QColor(Qt::black));

    // 图片叠加
    // QPainter painter(&back);
    // painter.drawImage(imgCar.width() < 160 ? (160 - imgCar.width()) / 2 : 0,
    //                     0, imgCar);
    // painter.end();

    // 打包数据
    QJsonObject jsonData;
    jsonData.insert("FontSize", 32);
    jsonData.insert("Content", "请安全驾驶");
    jsonData.insert("Img", img2base64(imgCar));

    QByteArray data = QJsonDocument(jsonData).toJson();

    // 上屏
    emit signalPost(QString(NOVA_PROGRAM_TEXT_AND_PIC).arg(m_novaScreenIpPort), data);

    // 语音
    // 根据违法信息来进行语音提示
    //  emit signalPost();

    return QJsonDocument(jsonData);
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

    // 发送请求
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

void MyHttpServerWorker::slotStart()
{
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

        //qDebug() << jsonDoc;

        return ctx->send(unpackNonMotorVehicleIllegalInfo(json).toJson().toStdString(), APPLICATION_JSON);
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
                    {"Name", "非机动车安全防治一体机"},
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
