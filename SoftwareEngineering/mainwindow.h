#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMap>
#include <QMessageBox>
#include <QTextCharFormat>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //int fileNumber;
    int nowLineNumber;
    QMap<int,QString> myMap;


    QTextEdit* textFile1;
    QTextEdit* textFile2;
    QLineEdit* lineFile1;
    QLineEdit* lineFile2;
    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void LoadFile();
    void DealFile();
    void ShowNextFile();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
