#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QRubberBand>
#include <QMouseEvent>
#include <QTextStream>
#include <QDir>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QMessageBox>
QString filename;
QPoint origin ;
QString coord;
QString mark;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphicsView = new myGraphicsView(this);
    file = new QFile("text.txt");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    graphicsView->setGeometry(QRect(12, 50, 700, 360));
    saveIndex = 0;
    curIndex = -1;
}

MainWindow::~MainWindow()
{
    file->close();
    delete ui;


}

void MainWindow::on_loadImgBtn_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Find positive images' directory"), QDir::currentPath());
    if(!dirPath.isEmpty()){
        ui->dirName->setText(dirPath);

    }

    dir = QDir(dirPath);
    QStringList filters;
    filters<<"*.pgm"<<"*.jpg"<<"*.bmp"<<"*.png";
    dir.setNameFilters(filters);
    fileList = dir.entryList(filters, QDir::Files | QDir::NoSymLinks);

    if(fileList.empty())
    {
        graphicsView->setDisabled(true);
        graphicsView->scene->addText("No Images found. Select another directory.");}
    else{

         graphicsView->setDisabled(false);
        curIndex = 0;
        QString filePath = dirPath + QString("/") + fileList.at(0);
        setPixScene(filePath);

        ui->fileNo->setText(QString::number(curIndex +1)+"/"+QString::number(fileList.size()));

        ui->progressBar->setMaximum(fileList.size() - 1);
        ui->progressBar->setValue(curIndex);
    }

}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
//press E berfore you S

    if(e->key() == Qt::Key_E)
    {

        QRect rubberbandSize = graphicsView->getRubberRect();
        ui->xVal->setText(QString::number(rubberbandSize.x()));
        ui->yVal->setText(QString::number(rubberbandSize.y()));
        ui->width->setText(QString::number(rubberbandSize.height()));
        ui->length->setText(QString::number(rubberbandSize.width()));

        if(saveIndex == 0)
        {
            saveIndex = 1;
            coord.clear();
            mark.clear();
        }
        else
            saveIndex++;
        QString dirN = ui->dirName->text();
        int delLen = 0;
        for(int i = 0; i<dirN.length(); ++i)
        {
            if(dirN.at(i) == '/' )
            {
                delLen = i;
            }
        }
        dirN.remove(0,delLen+1);

        mark = dirN +  QString("/") + (fileList.at(curIndex))
                +" "+ QString::number(saveIndex);

        coord.append(" "+ui->xVal->text() +" " + ui->yVal->text() +" "
                     + ui->width->text() +" " + ui->length->text());

        mark.append(coord);
        if(saveIndex > 1)
        {
            ui->outLine->clearFocus();
            ui->outLine->setFocus();
            QTextCursor storeCursorPos = ui->outLine->textCursor();
            ui->outLine->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
            ui->outLine->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
            ui->outLine->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
            ui->outLine->textCursor().removeSelectedText();
            ui->outLine->textCursor().deletePreviousChar();
            ui->outLine->setTextCursor(storeCursorPos);

            ui->outLine->append(mark);

        }
        else
          ui->outLine->append(mark);
        ui->outLine->clearFocus();

    }

    if(e->key() == Qt::Key_S)
    {

        ui->outLine->append("\n");
        ui->outLine->clearFocus();

        QMessageBox msg;
        msg.setWindowTitle("Save?");
        msg.setText("Are you sure you want to save?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        msg.setDefaultButton(QMessageBox::No);
        if(msg.exec() == QMessageBox::Yes)
        {
            QTextStream out(file);
            out<<(ui->outLine->toPlainText());

        }

    }

    if(e->key() == Qt::Key_C)
    {
        ui->outLine->setFocus();
        QTextCursor storeCursorPos = ui->outLine->textCursor();
        ui->outLine->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->outLine->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        ui->outLine->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
        ui->outLine->textCursor().removeSelectedText();
        ui->outLine->textCursor().deletePreviousChar();
        ui->outLine->setTextCursor(storeCursorPos);
        ui->outLine->clearFocus();
        saveIndex = 0;
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->outLine->clearMask();

    if(curIndex < 0 || curIndex >= fileList.size())
        return;
    else
    {
        curIndex++;
        if(curIndex < fileList.size())
        {
            QString filename = dir.path() + "/" + fileList.at(curIndex);
            setPixScene(filename);
            ui->fileNo->setText(QString::number(curIndex +1)+"/"+QString::number(fileList.size()));
            ui->progressBar->setValue(curIndex);

        }
        else
        {
            curIndex--;
            return;
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    ui->outLine->clearMask();

    if(curIndex <= 0 || curIndex > fileList.size()-1)
        return;
    else
    {
        --curIndex;
        if(curIndex >= 0)
        {
            QString filename = dir.path() + "/" + fileList.at(curIndex);
            setPixScene(filename);
            ui->fileNo->setText(QString::number(curIndex +1)+"/"+QString::number(fileList.size()));
            ui->progressBar->setValue(curIndex);

        }
        else
            return;
    }

}

void MainWindow::setPixScene(QString fileName)
{
    image.load(fileName);
    graphicsView->scene->clear();
    graphicsView->scene->addPixmap(image);
    graphicsView->setScene(graphicsView->scene);

    saveIndex = 0;
}

void MainWindow::on_actionOpen_triggered()
{
    this->on_loadImgBtn_clicked();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox about;
    about.setWindowTitle("About this software");
    about.setText(QString("Author:Sandeep Manandhar\nVersion:1.02b\nThis software has been prepared for the use \n")+
                  ("of marking images before haar training."));
    about.setStandardButtons(QMessageBox::Ok);
    about.exec();
}

void MainWindow::on_actionUsage_triggered()
{
    QMessageBox usage;
    usage.setWindowTitle("How to use this software");
    usage.setText(QString("Load folder containg Images(only jpg, pgm and bmp).\nMark the image by clicking left mouse button ")+
                          QString("and dragging it.\nMark it by pressing E on your keyboard.\nClick on next and mark until you are done.\n")+
                  QString("Press S on keyboard to save details to a text file.\n")+QString("Clicking right mouse button will clear selection area."));
    usage.setStandardButtons(QMessageBox::Ok);
    usage.exec();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}
