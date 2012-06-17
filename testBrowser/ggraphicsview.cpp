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
    // ���ñ���
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    // �����ӿ�ʹ��OpenGL��Ⱦ
    setViewport(new QGLWidget(this));

    // ����һ����ʱ�����м�ʱ����������ÿ��֡��
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
        QString mode = composited ? tr("���ٺϳ�ģʽ") : tr("������Ⱦģʽ");
        parent->setWindowTitle(tr("���������   Mode: %1      %2 ֡/��").arg(mode).arg(fps));
        frameCount = 0;
    }
}

void GGraphicsView::toggle() {
    QWebSettings *settings = content->page()->settings();
    bool composited = settings->testAttribute(QWebSettings::AcceleratedCompositingEnabled);
    settings->setAttribute(QWebSettings::AcceleratedCompositingEnabled, !composited);
    frameCount = 0;
    ticker->start();
    parent->setWindowTitle(tr("���Ժ�..."));
    content->setUrl(QUrl("qrc:/index.html"));
}
