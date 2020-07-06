#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void serialPort_readyRead();

    void on_openComBt_clicked();

    void on_searchComBt_clicked();

    void on_sendtextBt_clicked();

    void on_clearSendtextBt_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
};

#endif // MAINWINDOW_H
