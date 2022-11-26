#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1600,900);
    textFile1=new QTextEdit(this);
    textFile2=new QTextEdit(this);
    lineFile1=new QLineEdit(this);
    lineFile2=new QLineEdit(this);
    button1=new QPushButton(this);
    button2=new QPushButton(this);
    button3=new QPushButton(this);
    textFile1->setGeometry(0,100,800,800);
    textFile2->setGeometry(800,100,800,800);
    lineFile1->setGeometry(0,70,380,30);
    lineFile2->setGeometry(800,70,380,30);
    button1->setGeometry(1200,50,100,30);
    button1->setText("Equal");
    button2->setGeometry(1350,50,100,30);
    button2->setText("Inequal");
    button3->setGeometry(1500,50,100,30);
    button3->setText("Doubt");
    textFile1->setReadOnly(true);
    textFile2->setReadOnly(true);
    lineFile1->setReadOnly(true);
    lineFile2->setReadOnly(true);


    LoadFile();
    DealFile();



}

MainWindow::~MainWindow()
{
    QFile file("../SoftwareEngineering/save.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
            qDebug()<<"file open failed!";
        }
    QTextStream out(&file);
    out<<nowLineNumber;
    file.close();
    delete ui;
}

void MainWindow::ShowNextFile()
{
    QString str;
    QString file1Road="";
    QString file2Road="";    
    if(nowLineNumber>myMap.size())
    {
        QMessageBox::information(this,"WOOO!!!","You have done!");
        this->close();
    }
    str=myMap[nowLineNumber];
    int tempi=0;
    for(;str[tempi]!=",";tempi++)
    {
        file1Road+=str[tempi];
    }
    for(tempi++;tempi!=str.length();tempi++)
    {
        file2Road+=str[tempi];
    }
    QString temp="../SoftwareEngineering/";

    file1Road=temp+file1Road;
    file2Road=temp+file2Road;
    QFile file1(file1Road);
    QFile file2(file2Road);
    if(!file1.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<file1Road<<"文件打开失败";
        }
    if(!file2.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<file2Road<<"文件打开失败";
        }
    /*QString text1=file1.readAll();
    QString text2=file2.readAll();
    textFile1->setFont(QFont(tr("Consolas"), 14));
    textFile2->setFont(QFont(tr("Consolas"), 14));
    textFile1->setText(text1);
    textFile2->setText(text2);*/
    QTextStream in1(&file1);
    QTextStream in2(&file2);
    QString code1;
    QString code2;
    int num1=1;
    int num2=1;
    bool tag1=true;
    bool tag2=true;
    textFile1->clear();
    textFile2->clear();
    textFile1->setFont(QFont(tr("Consolas"), 14));
    textFile2->setFont(QFont(tr("Consolas"), 14));
    while(!in1.atEnd()&&!in2.atEnd())
    {
        if(!in1.atEnd()&&tag1)
        {
            code1=in1.readLine();
        }
        if(!in2.atEnd()&&tag2)
        {
            code2=in2.readLine();
        }
//        qDebug()<<code1;
//        qDebug()<<code2<<endl;
        if(code1==code2)
        {

            textFile1->append(QString::number(num1++)+"     "+code1);
            textFile2->append(QString::number(num2++)+"     "+code2);
            tag1=true;
            tag2=true;
        }
        else
        {
            textFile1->append(QString::number(num1++)+"      "+code1);
            textFile2->append("//////////////////////////////////////////////////");
            tag1=true;
            tag2=false;
        }
    }
    if(!tag2)
    {
        textFile2->append(QString::number(num2++)+"      "+code2);
    }
    while(!in1.atEnd())
    {
        code1=in1.readLine();
        textFile1->append(QString::number(num1++)+"      "+code1);
    }
    while(!in2.atEnd())
    {
        code2=in2.readLine();
        textFile2->append(QString::number(num2++)+"      "+code2);
    }
    lineFile1->setText(file1Road);
    lineFile2->setText(file2Road);
    file1.close();
    file2.close();
}

void MainWindow::DealFile()
{
    ShowNextFile();
    QFile equal("../SoftwareEngineering/myequal.csv");
    QFile inequal("../SoftwareEngineering/myinequal.csv");
    QFile doubt("../SoftwareEngineering/mydoubt.csv");
    if(!equal.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"file not exist,now create it";
            equal.close();
            equal.open(QIODevice::ReadWrite|QIODevice::Append);
            QTextStream out(&equal);
            out<<"file1,file2"<<endl;
            equal.close();
        }
    if(!inequal.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"file not exist,now create it";
            inequal.close();
            inequal.open(QIODevice::ReadWrite|QIODevice::Append);
            QTextStream out(&inequal);
            out<<"file1,file2"<<endl;
            inequal.close();
        }
    if(!doubt.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"file not exist,now create it";
            doubt.close();
            doubt.open(QIODevice::ReadWrite|QIODevice::Append);
            QTextStream out(&doubt);
            out<<"file1,file2"<<endl;
            doubt.close();
        }
    connect(button1,&QPushButton::clicked,[=]()
        {
            QFile equal("../SoftwareEngineering/myequal.csv");
            equal.open(QIODevice::ReadWrite|QIODevice::Append);
            QTextStream out(&equal);
            out<<myMap[nowLineNumber]<<endl;
            equal.close();
            nowLineNumber++;
            ShowNextFile();
        });
    connect(button2,&QPushButton::clicked,[=]()
        {
            QFile inequal("../SoftwareEngineering/myinequal.csv");
            inequal.open(QIODevice::ReadWrite|QIODevice::Append);
            QTextStream out(&inequal);
            out<<myMap[nowLineNumber]<<endl;
            inequal.close();
            nowLineNumber++;
            ShowNextFile();
        });
    connect(button3,&QPushButton::clicked,[=]()
        {
            QFile doubt("../SoftwareEngineering/mydoubt.csv");
            doubt.open(QIODevice::ReadWrite|QIODevice::Append);
            QTextStream out(&doubt);
            out<<myMap[nowLineNumber]<<endl;
            doubt.close();
            nowLineNumber++;
            ShowNextFile();
        });
}

void MainWindow::LoadFile()
{
    QFile file("../SoftwareEngineering/save.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"file not exist,now create it";
            file.close();
            file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out<<"1";
            file.close();
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
                    qDebug()<<"file open failed";
                }
        }
    QTextStream in(&file);
    QString str;
    str=in.readLine();
    nowLineNumber=str.toInt();
    file.close();

    QFile file1("../SoftwareEngineering/equal.csv");
    if(!file1.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"equal.csv文件打开失败";
        }
    QTextStream in1(&file1);
    QString strr;
    int tempNumber=1;
    while(!in1.atEnd())
    {
        strr=in1.readLine();
        //qDebug()<<"strr";
        if(strr=="file1,file2")
        {
            continue;
        }
        myMap[tempNumber++]=strr;
    }
    file1.close();

    /*QFile file2("../SoftwareEngineering/inequal.csv");
    if(!file2.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"inequal.csv文件打开失败";
        }
    QTextStream in2(&file2);
    QString strrr;
    while(!in2.atEnd())
    {
        strrr=in2.readLine();
        if(strrr=="file1,file2")
        {
            continue;
        }
        myMap[tempNumber++]=strrr;
    }
    file2.close();*/
}
