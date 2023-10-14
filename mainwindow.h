#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "QPushButton"
#include "QButtonGroup"
#include <QVector>
#include <QString>
#include <QFont>
#include <QTimer>
#include <QMovie>
#include <QLabel>
#include <QSound>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);
    void hide_game();
    void show_game();
    void show_question(int q, QPainter* paint);
    void hide_queston();
    void change_button(QPushButton* b);
    QVector <QString> splitting_string(QString str);
    void joker(QPushButton* b);
    void sabotage(QPushButton* b);
    void queue(QPushButton* b);
private slots:
    void f(int i);
    void animation();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void timer();
    void on_pushButton_13_clicked();

private:
    int press_button = -1;
    int question = 0;
    int count_question = 0;
    bool is_press = false;
    bool is_correct = false;
    int status = -1;
    int time = 20;
    int skirmish = 0;

    int x = -500;
    int y = 100;
    int pause = 300;

    Ui::MainWindow *ui;
    QButtonGroup* buttons = new QButtonGroup();

    QImage background1 = QImage(":/images/background1.jpg");
    QImage background2 = QImage(":/images/background2.jpg");
    QImage background3 = QImage(":/images/background3.jpg");
    QImage background4 = QImage(":/images/background4.jpg");
    QImage background5 = QImage(":/images/background5.jpg");
    QImage background6 = QImage(":/images/background6.jpg");
    QImage red = QImage(":/images/red.jpeg");
    QImage green = QImage(":/images/green.jpeg");
    QImage table = QImage(":/images/table.jpg");

    QVector <QString> names;
    QVector <QString> questions;
    QVector <QString> answers;

    QFont font1;
    QFont font2;
    QFont font3;

    QSound* _20s = new QSound(":/sound/20_.wav");
    QSound* _30s = new QSound(":/sound/30_.wav");
    QSound* _40s = new QSound(":/sound/40_.wav");
    QSound* _50s = new QSound(":/sound/50_.wav");

    QTimer* timer1 = new QTimer();
    QTimer* timer2 = new QTimer();

    QMovie gif;
    QMovie jok;
    QMovie sab;
    QMovie que;

    QLabel* lab;
};
#endif // MAINWINDOW_H
