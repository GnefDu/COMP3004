#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connectElevatorButtons();
    void connectDoorButtons();
    std::string extractNums(std::string);
    void consoleOut(int);

private:
    Ui::MainWindow *ui;

private slots:
    void callElevator();
    void moveElevatorA();
    void moveElevatorB();
    void helpA();
    void helpB();
    void doorObsA();
    void doorObsB();
    void fire();
    void overLoadA();
    void overLoadB();
    void powerout();
    void allocation1();
    void allocation2();
};
#endif // MAINWINDOW_H
