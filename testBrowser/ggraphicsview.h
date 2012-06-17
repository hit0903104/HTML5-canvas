#ifndef GGRAPHICSVIEW_H
#define GGRAPHICSVIEW_H

#include <QGraphicsView>

class QTime;
class QGraphicsWebView;

class GGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GGraphicsView(QGraphicsScene *scene, QWidget *parent, QGraphicsWebView *content);

    void toggle();
    
signals:

protected:
    void paintEvent(QPaintEvent *event);
    
public slots:

private:
    QWidget *parent;
    QGraphicsWebView *content;

    int frameCount;
    QTime *ticker;
};

#endif // GGRAPHICSVIEW_H
