#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //连接信号预槽
    QObject::connect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialPort_readyRead);
    //发送键失能
     ui->sendtextBt->setEnabled(false);
     on_searchComBt_clicked();
    //波特率默认选项1 115200
    ui->BAUDCB->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialPort_readyRead()
{

    //从接收缓冲区中读取数据
    QByteArray buffer = serial.readAll();
    //从界面中读取以前收到的数据
    QString recv = ui->receiveTb->toPlainText();
    recv += QString(buffer);
    //清空以前的显示
    ui->receiveTb->clear();
    //重新显示
    ui->receiveTb->append(recv);


}

void MainWindow::on_openComBt_clicked()
{
    //打开串口
    if(ui->openComBt->text() ==QString("打开串口"))
    {
         qDebug()<<"打开串口成功\r\n";
        //设置串口名
        serial.setPortName(ui->COMCB->currentText());

        //设置波特率
        serial.setBaudRate(ui->BAUDCB->currentText().toInt());
        switch (ui->DatabitsCB->currentIndex()) {
        case 8:
            serial.setDataBits(QSerialPort::Data8);
            break;
        default:
            break;
        }
        //设置数据位
        switch(ui->DatabitsCB->currentIndex())
        {
            case 8: serial.setDataBits(QSerialPort::Data8);
                    break;
            default: break;
        }

        //设置校验位
        switch (ui->ParityCB->currentIndex()) {
        case 0:
            serial.setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch (ui->StopbitsCB->currentIndex()) {
        case 1:
            serial.setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial.setStopBits(QSerialPort::OneStop);
            break;
        default:
            break;
        }
        //设置流控

        serial.setFlowControl(QSerialPort::NoFlowControl);
        if(!serial.open(QIODevice::ReadWrite))
        {
            QMessageBox::about(nullptr, "提示", "无法打开串口");
        }

        //下拉菜单控件失能
        ui->COMCB->setEnabled(false);
        ui->BAUDCB->setEnabled(false);
        ui->DatabitsCB->setEnabled(false);
        ui->ParityCB->setEnabled(false);
        ui->StopbitsCB->setEnabled(false);
        ui->FlowCtrCB->setEnabled(false);

        ui->openComBt->setText(QString("关闭串口"));
        //发送键使能
        ui->sendtextBt->setEnabled(true);

    }
    else {
        qDebug()<<"打开串口失败\r\n";
        //下拉菜单控件使能
        ui->COMCB->setEnabled(true);
        ui->BAUDCB->setEnabled(true);
        ui->DatabitsCB->setEnabled(true);
        ui->ParityCB->setEnabled(true);
        ui->StopbitsCB->setEnabled(true);
        ui->FlowCtrCB->setEnabled(true);

        ui->openComBt->setText(QString("打开串口"));
        //发送按键失能
        ui->sendtextBt->setEnabled(false);


    }
}

void MainWindow::on_searchComBt_clicked()
{
    ui->COMCB->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->COMCB->addItem((info.portName()));
    }
}

void MainWindow::on_sendtextBt_clicked()
{
    //获取界面上的数据并转换成utf8格式的字节流
        QByteArray data = ui->SendTe->toPlainText().toUtf8();
        serial.write(data);
}

void MainWindow::on_clearSendtextBt_clicked()
{
     ui->receiveTb->clear();
}
