#include "testbrowser.h"
#include "ggraphicsview.h"
#include <QTextCodec>
#include <QtGui>
#include <QtWebKit>
#include <QWebSettings>
#include <QWebPage>
#include <QAction>

namespace {
const int WIDTH = 1000;
const int HEIGHT = 600;
const int MARGIN = 20;
}

testBrowser::testBrowser(QWidget *parent) :
    QMainWindow(parent)
{
    // 设置标题
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    setWindowTitle(tr("测试浏览器"));

    // 创建场景
    scene = new QGraphicsScene(this);
    // 创建WebView
    webView = new QGraphicsWebView;
    webView->load(QUrl("qrc:/index.html"));
    webView->setMaximumHeight(590);

    // 创建所有部件并完成布局
    this->createActions();
    this->createWidgets();
    this->createProxyWidgets();
    this->createLayout();
    this->createCentralWidget();
    this->createConnections();

    // 调整主窗口大小
    resize(1000, 600);
}

void testBrowser::createActions() {
    quitAction = new QAction(QIcon(":images/quit.png"),
                             tr("退出"), this);
    toggleAction = new QAction(QIcon(":images/toggle.png"),
                               tr("硬件加速切换"), this);
}

void testBrowser::createWidgets() {
    // 工具栏
    progressLabel = new QLabel(tr("进度"));
    progressLabel->setMargin(5);
    progressBar = new QProgressBar;
    toolBar = new QToolBar(tr("Navigation"), this);
    toolBar->addAction(webView->pageAction(QWebPage::Back));
    toolBar->addAction(webView->pageAction(QWebPage::Forward));
    toolBar->addAction(webView->pageAction(QWebPage::Reload));
    toolBar->addAction(webView->pageAction(QWebPage::Stop));
    toolBar->addSeparator();
    toolBar->addWidget(progressLabel);
    toolBar->addWidget(progressBar);
    toolBar->addSeparator();
    toolBar->addAction(toggleAction);
    toolBar->addAction(quitAction);
    this->addToolBar(toolBar);
}

void testBrowser::createProxyWidgets() {
    // 代理部件
}

void testBrowser::createLayout() {
    // 布局设置
    webView->setMinimumWidth(1000);
    webView->setMaximumHeight(568);
    scene->addItem(webView);
}

void testBrowser::createCentralWidget() {

    view = new GGraphicsView(scene, this, webView);
    view->setFrameShape(QFrame::NoFrame);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHints(QPainter::Antialiasing|
                         QPainter::TextAntialiasing);
    view->setBackgroundBrush(QColor("bisque"));
    setCentralWidget(view);
}

void testBrowser::createConnections() {
    connect(webView, SIGNAL(loadProgress(int)),
            progressBar, SLOT(setValue(int)));
    connect(quitAction, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(toggleAction, SIGNAL(triggered()),
            this, SLOT(toggle()));
}

void testBrowser::toggle() {
    view->toggle();
}
