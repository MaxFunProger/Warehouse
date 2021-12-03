#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEventLoop>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Modeller();
    void set_defaults(int, int);
    ~MainWindow();

signals:
    void quitloop();

private slots:

    void on_start_button_clicked();

    void on_add_prod_clicked();

    void on_next_day_but_clicked();

    void on_all_days_but_clicked();

    void on_start_gen_clicked();

    void on_next_days_but2_clicked();

    void on_gen_all_but2_clicked();

    void on_next_day_but3_clicked();

    void on_gen_all_but3_clicked();

private:

    void loop();
    Ui::MainWindow *ui;
    bool flag = false;
    QEventLoop loop_;
    int ROWS = 3;
    int COLUMS = 9;
    int days_left = 100;
    bool FLAG_ALL = false;
};
#endif // MAINWINDOW_H
