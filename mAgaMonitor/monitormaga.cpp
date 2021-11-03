#include "monitormaga.h"
#include "ui_monitormaga.h"

#include <QScrollBar>

mAgaMonitor::mAgaMonitor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mAgaMonitor)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts())
    {
        ui->cbxSerialPort->addItem(serialInfo.portName());
    }

    serialPort.setBaudRate(QSerialPort::Baud115200);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    QObject::connect(&serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
}

mAgaMonitor::~mAgaMonitor()
{
    delete ui;
}


void mAgaMonitor::on_cbxSerialSpeed_currentTextChanged(const QString &arg1)
{
    serialPort.setBaudRate(ui->cbxSerialSpeed->currentText().toInt());
}


void mAgaMonitor::on_cbxSerialPort_currentTextChanged(const QString &arg1)
{
    serialPort.setPortName(arg1);
}


void mAgaMonitor::on_btnOpen_clicked()
{
    if(serialPort.isOpen()) {
        serialPort.close();
        ui->btnOpen->setText("Open");
    }
    else
    {
        if(serialPort.open(QIODevice::ReadWrite))
            ui->btnOpen->setText("Close");
        else
            qDebug() << "Couldn't open serial port";
    }
}

void mAgaMonitor::on_btnSend_clicked()
{
    ui->textEdit->insertHtml(QString("<font color='blue'>%1 %2</font><br>").arg(ui->leFunc->text()).arg(ui->leArg->text()));
    if(!ui->leArg->text().isEmpty())
        serialPort.write(QString("<br>%1 %2\r").arg(ui->leFunc->text()).arg(ui->leArg->text()).toLatin1());
    else
        serialPort.write(ui->leFunc->text().toLatin1()+'\r');

}

void mAgaMonitor::readData()
{
    QByteArray data;
    while(serialPort.canReadLine())
    {
        QByteArray data = serialPort.readLine();
        data.replace(27,"<br>");
//        data.replace("\r\n","");
//        data.replace("[0m","");
        data.replace(QString("[0m").arg(27).toStdString(),"<br>");
        ui->textEdit->insertHtml(QString("<br><font color='red'>%1</font>").arg(data));

        QScrollBar *sb = ui->textEdit->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}


void mAgaMonitor::on_btnRescanSerialPorts_clicked()
{
    if(ui->cbxSerialPort->count()==0)
    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts())
    {
        ui->cbxSerialPort->addItem(serialInfo.portName());
    }
}


void mAgaMonitor::on_btnClearLogWindow_clicked()
{
    ui->textEdit->clear();
}


void mAgaMonitor::on_btnStartBLE_clicked()
{
    serialPort.clear();
    serialPort.write("bleStart\n");
}


void mAgaMonitor::on_btnStartAdvertise_clicked()
{

    serialPort.clear();
    serialPort.write("bleAdvertiseStartExample\n");
}


void mAgaMonitor::on_btnStopAdvertise_clicked()
{
    serialPort.clear();
    serialPort.write("bleAdvertiseStop\n");
}


void mAgaMonitor::on_btnStartScan_clicked()
{
    serialPort.clear();
    serialPort.write("bleScanStart\n");
}


void mAgaMonitor::on_btnStopScan_clicked()
{
    serialPort.clear();
    serialPort.write("bleScanStop\n");
}


void mAgaMonitor::on_btnGetMac_clicked()
{
    serialPort.clear();
    serialPort.write("bleGetMac\n");
}


void mAgaMonitor::on_btnListDevices_clicked()
{
    serialPort.clear();
    serialPort.write("bleListDevices\n");
}




void mAgaMonitor::on_btnGetParam_clicked()
{

    ui->textEdit->insertHtml(QString("<font color='blue'>%1 %2</font><br>").arg("param get").arg(ui->leParamName->text()).toLatin1());
    if(!ui->leArg->text().isEmpty())
        serialPort.write(QString("%1 %2\r").arg("param get").arg(ui->leParamName->text()).toLatin1());
    else
        serialPort.write(ui->leFunc->text().toLatin1()+'\r');
}


void mAgaMonitor::on_btnSetParam_clicked()
{

    ui->textEdit->insertHtml(QString("<font color='blue'>%1 %2 %3</font><br>").arg("param set").arg(ui->leParamName->text()).arg(ui->leParamValue->text()).toLatin1());
    if(!ui->leArg->text().isEmpty())
        serialPort.write(QString("%1 %2 %3\r").arg("param set").arg(ui->leParamName->text()).arg(ui->leParamName->text()).arg(ui->leParamValue->text()).toLatin1());
    else
        serialPort.write(ui->leFunc->text().toLatin1()+'\r');
}

void mAgaMonitor::on_comboBox_currentIndexChanged(int index)
{
    qDebug() << index << ui->comboBox->currentText() << CLI_BLE_STARTUP[ui->comboBox->currentIndex()];
}

