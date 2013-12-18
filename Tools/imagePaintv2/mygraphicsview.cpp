#include "mygraphicsview.h"
//#include <QDebug>
#include <QString>
myGraphicsView::myGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->installEventFilter(this);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setResizeAnchor( QGraphicsView::AnchorUnderMouse );
    origin = QPoint(0,0);
    mTL = new QLabel(this);
    scene = new QGraphicsScene(this);
    scene->addText("No Images Available. Please browse to a folder containing appropriate images.");
    setScene(scene);
    setCursor(Qt::CrossCursor);
    setDisabled(true);
    mBR = new QLabel(this);
    mTL->setStyleSheet("QLabel { background-color : white; color : black;}");
    mBR->setStyleSheet("QLabel { background-color : white; color : black;}");
    mTL->hide();
    mBR->hide();
    rubberBandActive = false;

    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    QPalette palette;
    QColor highlight(Qt::green);
    highlight.setAlpha(100);
    palette.setBrush(QPalette::Highlight, QBrush(highlight));
    palette.setBrush(QPalette::Shadow, QColor(Qt::red));
    rubberBand->setPalette(palette);
    rubberBand->setGeometry(20, 20, 200, 100);
}

void myGraphicsView::mousePressEvent(QMouseEvent *event)
{
    //  QGraphicsView::mousePressEvent(event);
    origin = event->pos();
    QPointF pos = this->mapToScene(event->pos());
    QPoint posImg((int)pos.x(), (int)pos.y());
    imageSlice.setTopLeft(posImg);
    if(event->button() == Qt::LeftButton && !rubberBandActive)
    {
        if(posImg.x() > 0 && posImg.y()>0 && posImg.x() <= scene->sceneRect().width() && posImg.y() <= scene->sceneRect().height())
        {
            setCursor(Qt::CrossCursor);




            rubberBandOrigin = event->pos();
            rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
            QPalette palette;
            QColor highlight(Qt::white);
            highlight.setAlpha(100);
            palette.setBrush(QPalette::Highlight, QBrush(highlight));
            palette.setBrush(QPalette::Shadow, QColor(Qt::red));
            rubberBand->setPalette(palette);
            rubberBand->setPalette(palette);
            QPoint p;

            rubberBand->setGeometry(event->x(), event->y(), 0, 0 );
            rubberBand->show();
            mTL->show();

            rubberBandActive = true;
            mTL->setGeometry(rubberBandOrigin.x(), rubberBandOrigin.y() - 12, 50, 12);
            mTL->setText(QString("%1, %2").arg(QString::number(posImg.x())).
                         arg(QString::number(posImg.y())));

        }
        else{
            setCursor(Qt::ForbiddenCursor);

        }
    }
    else if(event->button() == Qt::RightButton && rubberBandActive == true)
    {
        rubberBandActive = false;
        rubberBand->hide();
        mTL->hide();
        mBR->hide();
    }


}

void myGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    /*Mapping mouse coordinates to image coordinates*/
    QPointF pos = this->mapToScene(event->pos());
    QPoint posImg((int)pos.x(), (int)pos.y());
    /**********************************************/

    if(event->buttons() == Qt::LeftButton && rubberBandActive == true){
        if(posImg.x() > 0 && posImg.y()>0 && posImg.x() < this->scene->sceneRect().width() && posImg.y() < this->scene->sceneRect().height())
        {
            setCursor(Qt::CrossCursor);
            rubberBand->show();

            mBR->show();
            rubberBand->resize(event->x() - rubberBandOrigin.x(), event->y() - rubberBandOrigin.y());
            mouseLoc = event->pos();
            mBR->setGeometry(event->pos().x()+12, event->pos().y() + 5, 50, 12);
            mBR->setText(QString("%1, %2").arg(QString::number(posImg.x())).
                         arg(QString::number(posImg.y())));
        }

        else
        {
            setCursor(Qt::ForbiddenCursor);
        }
    }



}

void myGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    QPointF pos = this->mapToScene(event->pos());
    QPoint posImg((int)pos.x(), (int)pos.y());
    mouseLoc = event->pos();
}
QRect myGraphicsView::getRubberRect()
{
    imageSlice.setWidth(rubberBand->width());
    imageSlice.setHeight(rubberBand->height());
    return imageSlice;

}




