#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include <iostream>
#include <QString>
#include <iostream>
#include <QPainter>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QFile file("init.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for(int i = 0; i < 3; ++i)
        names.push_back(in.readLine());
    in.readLine();
    for(int i = 0; i < 36 ; ++i){
        questions.push_back(in.readLine());
        answers.push_back(in.readLine());
        in.readLine();
    }

    connect(timer1, SIGNAL(timeout()), this, SLOT(timer()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(animation()));

    ui->setupUi(this);
    ui->pushButton_13->hide();
    ui->label_2->setText(names[0]);
    ui->label_3->setText(names[1]);
    ui->label_4->setText(names[2]);
    font1.setPixelSize(50);
    font1.setFamily("Century Schoolbook");
    font2.setPixelSize(50);
    font3.setPixelSize(100);
    int count = 1;
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 5; ++j){
            auto b = new QPushButton("button" , this);
            b->setGeometry(QRect(QPoint(200 + 200*j, 100 + 75*i), QSize(100, 50)));
            b->setText(QString::number(count));
            b->setFont(font1);
            b->setStyleSheet(("QPushButton{"
                              " color: white;"
                              "  background-color: black;"
                              "border-style: solid;"
                              "border-radius:50px;"
                             "border-style: solid;"
                             "border-width:2px;"
                             "border-radius:25px;"
                             "border-color: red;"
                             "max-width:100px;"
                             "max-height:50px;"
                             "min-width:100px;"
                             "min-height:50px;"
                              "}"));
            buttons->addButton(b, count);
            count++;
        }
    connect(buttons, SIGNAL(buttonClicked(int)), this, SLOT(f(int)));

    lab = new QLabel(this);

    gif.setFileName(":/gif/tenor.gif");
    jok.setFileName(":/gif/joker.gif");
    que.setFileName(":/gif/q.gif");
    sab.setFileName(":/gif/sab.gif");
    lab->setMovie(&gif);
    lab->setGeometry(1000, 1000, 700, 700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(font2);
    painter.setPen(Qt::white);
    if(count_question < 5)
        painter.drawImage(QRect(0,0,width(), height()), background1);
    else if (count_question < 9)
        painter.drawImage(QRect(0,0,width(), height()), background2);
    else if (count_question < 14)
        painter.drawImage(QRect(0,0,width(), height()), background3);
    else if (count_question < 19)
        painter.drawImage(QRect(0,0,width(), height()), background4);
    else if (count_question < 24)
        painter.drawImage(QRect(0,0,width(), height()), background5);
    else
        painter.drawImage(QRect(0,0,width(), height()), background6);


    if(status == -1)
    {
        painter.drawImage(QRect(180,85, 950, 465), table);
    }
    if(status != -1)
    {
        show_question(question, &painter);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W)
        time+=10;
    if (event->key() == Qt::Key_S)
        time-=10;
    if (event->key() == Qt::Key_R)
        is_correct = true;
    if (event->key() == Qt::Key_F)
        is_correct = false;
    if (event->key() == Qt::Key_F1)
        ui->label_2->setStyleSheet("color : black;"
                                             "background-color: rgb(0, 0, 0);"
                                             "border-style: solid;"
                                             "border-radius:50px;"
                                             "border-style: solid;"
                                             "border-width:2px;"
                                             "border-radius:15px;"
                                             "border-color: #72a8ba;"
                                             "max-width:250px;"
                                             "max-height:30px;"
                                             "min-width:250px;"
                                             "min-height:30px;");
    if (event->key() == Qt::Key_F2)
        ui->label_3->setStyleSheet("color : black;"
                                             "background-color: rgb(0, 0, 0);"
                                             "border-style: solid;"
                                             "border-radius:50px;"
                                             "border-style: solid;"
                                             "border-width:2px;"
                                             "border-radius:15px;"
                                             "border-color: #72a8ba;"
                                             "max-width:250px;"
                                             "max-height:30px;"
                                             "min-width:250px;"
                                             "min-height:30px;");
    if (event->key() == Qt::Key_F3)
        ui->label_4->setStyleSheet("color : black;"
                                             "background-color: rgb(0, 0, 0);"
                                             "border-style: solid;"
                                             "border-radius:50px;"
                                             "border-style: solid;"
                                             "border-width:2px;"
                                             "border-radius:15px;"
                                             "border-color: #72a8ba;"
                                             "max-width:250px;"
                                             "max-height:30px;"
                                             "min-width:250px;"
                                             "min-height:30px;");
    if(event->key() == Qt::Key_F5)
    {
        if(skirmish < 6)
            skirmish++;
        hide_game();
        status = 1;
        question = 30 + skirmish;
        ui->pushButton_13->show();
        setFocus();
    }
    repaint();
}

void MainWindow::hide_game()
{
    auto b = buttons->buttons();
    for(auto &i : b)
        i->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_4->hide();
}

void MainWindow::show_game()
{
    auto b = buttons->buttons();
    for(auto &i : b)
        i->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->lineEdit_4->show();
}

void MainWindow::show_question(int q, QPainter *paint)
{
    auto v = splitting_string(questions[q-1]);
    auto a = splitting_string("Ответ: " + answers[q-1]);
    int h = 0;
    if(status == 1)
    {
        for(auto i : v)
        {
            paint->drawText(50, 200 + 50*h, i);
            h++;
        }
    }
    if(status == 2)
    {
        for(auto i : v)
        {
            paint->drawText(50, 200 + 50*h, i);
            h++;
        }
        paint->setBrush(QBrush(Qt::black));
        paint->drawEllipse(0, 500, 249,249);
        paint->setFont(font3);
        paint->drawText(70,660, QString::number(time));
    }
    if(status == 3)
    {
        h = 0;
        if(is_correct)
            paint->drawImage(QRect(0,0,width(), height()), green);       
        else
            paint->drawImage(QRect(0,0,width(), height()), red);
        for(auto i : a)
        {
            paint->drawText(50, 200 + 50*h, i);
            h++;
        }
        return;
    }
}

void MainWindow::hide_queston()
{
    ui->pushButton_13->hide();
}

void MainWindow::change_button(QPushButton *b)
{
    b->setEnabled(false);
    b->setStyleSheet("QPushButton{"
                                      "color: #1e0eb0;"
                                      "background-color: #ab2c2c;"
                                      "border-style: solid;"
                                     "border-radius:50px;"
                                     "border-style: solid;"
                                     "border-width:2px;"
                                     "border-radius:20px;"
                                     "border-color: #72a8ba;"
                                     "max-width:70px;"
                                     "max-height:70px;"
                                     "min-width:70px;"
                                     "min-height:70px;"
                                     " }");
}

QVector<QString> MainWindow::splitting_string(QString str)
{
    QVector <QString> v;
    int start = 0;
    int end = 0;
    for(int i = 0; i < str.size(); ++i)
    {
        if(str[i] == ' ' || i == str.size() - 1)
        {
            if(i - start < 47)
                end = i;
            else
            {
                v.append(str.mid(start, end - start));
                start = end + 1;
            }
        }
    }
    v.append(str.mid(start, str.size() - start));
    return v;
}

void MainWindow::joker(QPushButton *b)
{
    change_button(b);
    lab->setMovie(&jok);
    jok.start();
    timer2->start(1000/60);
    QSound::play(":/sound/joker.wav");
}

void MainWindow::sabotage(QPushButton *b)
{
    change_button(b);
    lab->setMovie(&sab);
    sab.start();
    timer2->start(1000/60);
    QSound::play(":/sound/sab.wav");
}

void MainWindow::queue(QPushButton *b)
{
    change_button(b);
    lab->setMovie(&que);
    que.start();
    timer2->start(1000/60);
    QSound::play(":/sound/que.wav");
}

void MainWindow::f(int i)
{
    if(press_button == -1)
    {
        QSound::play(":/sound/choice.wav");
        buttons->button(i)->setStyleSheet("QPushButton{"
                                                  " color: black;"
                                                  "  background-color: orange;"
                                                  "border-style: solid;"
                                                  "border-radius:50px;"
                                                 "border-style: solid;"
                                                 "border-width:2px;"
                                                 "border-radius:25px;"
                                                 "border-color: red;"
                                                 "max-width:100px;"
                                                 "max-height:50px;"
                                                 "min-width:100px;"
                                                 "min-height:50px;"
                                                  "}");
        press_button = question = i;
    }
    else if(press_button == i)
    {
        hide_game();
        status = 1;
        press_button = -1;
        ui->pushButton_13->show();
        repaint();
        setFocus();
    }
}

void MainWindow::animation()
{
    repaint();
    if(x < 460){
        x+=20;
        lab->setGeometry(x, y, 500,500);
        return;
    }
    if(pause > 0)
        pause--;
    if (pause == 0){
        x+=20;
        lab->setGeometry(x, y, 500,500);
    }
    if(x > 1500){
        pause = 300;
        x = -500;
        timer2->stop();
    }
}


void MainWindow::on_pushButton_clicked()
{
    sabotage(ui->pushButton);
}


void MainWindow::on_pushButton_2_clicked()
{
    joker(ui->pushButton_2);
}


void MainWindow::on_pushButton_3_clicked()
{
    queue(ui->pushButton_3);
}


void MainWindow::on_pushButton_4_clicked()
{
    sabotage(ui->pushButton_4);
}


void MainWindow::on_pushButton_5_clicked()
{
    joker(ui->pushButton_5);
}


void MainWindow::on_pushButton_6_clicked()
{
    queue(ui->pushButton_6);
}


void MainWindow::on_pushButton_7_clicked()
{
    sabotage(ui->pushButton_7);
}


void MainWindow::on_pushButton_8_clicked()
{
    joker(ui->pushButton_8);
}


void MainWindow::on_pushButton_9_clicked()
{
    queue(ui->pushButton_9);
}


void MainWindow::timer()
{
    if(time > 0)
        time--;
    repaint();
}

void MainWindow::on_pushButton_13_clicked()
{
    status++;
    if(status == 2){
        timer1->start(1000);
        if(time == 20)
            _20s->play();
        else if(time == 30)
            _30s->play();
        else if(time == 40)
            _40s->play();
        else if(time == 50)
            _50s->play();
    }
    if(status == 3){
        timer1->stop();
        _20s->stop();
        _30s->stop();
        _40s->stop();
        _50s->stop();
        if(is_correct)
            QSound::play(":/sound/correct.wav");
        else
            QSound::play(":/sound/lose.wav");
    }
    if(status == 4)
    {
        count_question++;
        status = -1;
        time = 20;
        hide_queston();
        show_game();
    }
    repaint();
}

