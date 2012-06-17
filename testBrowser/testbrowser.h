#ifndef TESTBROWSER_H
#define TESTBROWSER_H

#include <QMainWindow>
#include <QGraphicsProxyWidget>

class QGraphicsScene;
class GGraphicsView;
class QToolBar;
class QLabel;
class QProgressBar;
class QGraphicsWebView;
class QAction;
class QTime;

class testBrowser : public QMainWindow
{
    Q_OBJECT
public:
    explicit testBrowser(QWidget *parent = 0);
    
signals:
    
public slots:
    void toggle();

private:
    void createWidgets();
    void createProxyWidgets();
    void createLayout();
    void createCentralWidget();
    void createActions();
    void createConnections();

    GGraphicsView *view;
    QGraphicsScene *scene;
    QToolBar *toolBar;
    QAction *quitAction;
    QAction *toggleAction;
    QLabel *progressLabel;
    QProgressBar *progressBar;
    QGraphicsWebView *webView;
    QGraphicsProxyWidget *proxyToolBar;
};

#endif // TESTBROWSER_H
