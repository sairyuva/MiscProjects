#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QRubberBand>
#include <QMouseEvent>
#include <QLabel>
#include <QGraphicsScene>
class myGraphicsView : public QGraphicsView{
public:
    myGraphicsView(QWidget *parent = NULL);
    QRect getRubberRect();
    QGraphicsScene *scene;
protected:
    QRubberBand *rubberBand;
    QPoint origin;
    bool rubberBandActive;
    QPoint rubberBandOrigin;
    QLabel *mTL;    //top left coordinates
    QLabel *mBR;    //botton right coordinates
    QRect imageSlice;

private:

  QPoint mouseLoc;
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYGRAPHICSVIEW_H
