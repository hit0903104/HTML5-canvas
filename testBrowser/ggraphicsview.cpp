#include "ggraphicsview.h"
#include <QTime>
#include <QtOpenGL>
#include <QtWebKit>
#include <QTextCodec>

GGraphicsView::GGraphicsView(QGraphicsScene *scene, QWidget *parent, QGraphicsWebView *content) :
    QGraphicsView(scene, parent),
    parent(parent),
    frameCount(0),
    content(content)
{
    // 设置标题
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    // 设置视口使用OpenGL渲染
    setViewport(new QGLWidget(this));

    // 开启一个计时器进行计时，用来计算每秒帧数
    ticker = new QTime;
    ticker->start();
}

void GGraphicsView::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);

    frameCount++;
    if (frameCount >= 80) {
        int elapsed = ticker->elapsed();
        ticker->start();
        int fps = frameCount * 1000 / (1 + elapsed);
        bool composited = content->page()->settings()->testAttribute(QWebSettings::AcceleratedCompositingEnabled);
        QString mode = composited ? tr("加速合成模式") : tr("立即渲染模式");
        parent->setWindowTitle(tr("测试浏览器   Mode: %1      %2 帧/秒").arg(mode).arg(fps));
        frameCount = 0;
    }
}

void GGraphicsView::toggle() {
    QWebSettings *settings = content->page()->settings();
    bool composited = settings->testAttribute(QWebSettings::AcceleratedCompositingEnabled);
    settings->setAttribute(QWebSettings::AcceleratedCompositingEnabled, !composited);
    frameCount = 0;
    ticker->start();
    parent->setWindowTitle(tr("请稍后..."));
    content->setUrl(QUrl("qrc:/index.html"));
}
