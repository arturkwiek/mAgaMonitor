#include "monitormaga.h"
#include "ui_monitormaga.h"

#include <QScrollBar>

mAgaMonitor::mAgaMonitor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mAgaMonitor)
    , enBranch(BLESTARTUP)
    , b_EscCodes(false)
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
    ui->textEdit->insertHtml(QString("<br>><font color='blue'>%1 %2</font>").arg(ui->leFunc->text()).arg(ui->leArg->text()));
    if(!ui->leArg->text().isEmpty())
        serialPort.write(QString("%1 %2\r").arg(ui->leFunc->text()).arg(ui->leArg->text()).toLatin1());
    else
        serialPort.write(ui->leFunc->text().toLatin1()+'\r');

}

void mAgaMonitor::readData()
{
    QByteArray data;
    while(serialPort.canReadLine())
    {
        QByteArray data = serialPort.readLine();
        //QString("<font color='red' style=\"font-weight:bold\">%1</font>")
        data.replace("\033[1;32m","<font color='green' style=font-weight:bold; color=green>");
        data.replace("\033[8D\033[J","<font color='red'>");

        data.replace("\033[1;31m","<font color='red'>");
        data.replace("\033[m","</font>");
        data.replace("\033[0m","</font>");
        if(data.toStdString().find("\033[31"))
            qDebug()<< "found";
        qDebug()<< data;
        ui->textEdit->insertHtml(QString("<br>%1").arg(data));
//        ui->textEdit->insertHtml(QString("<br><font color='red'>%1</font>").arg(data));

        QScrollBar *sb = ui->textEdit->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}


void mAgaMonitor::on_btnRescanSerialPorts_clicked()
{
    ui->cbxSerialPort->clear();
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


void mAgaMonitor::on_btnTestCommand_clicked()
{
    if(CMDS_BRANCH::BLEINITTESTS == enBranch)
    {
        qDebug() << "testing BLEINITTESTS";

        ui->textEdit->insertHtml(QString("<br>><font color='blue'>%1</font>").arg(CLI_BLE_BLEINITTESTS[ui->comboBox->currentIndex()]).toLatin1());
        serialPort.write(QString("%1\r").arg(CLI_BLE_BLEINITTESTS[ui->comboBox->currentIndex()]).toLatin1());
    }
    else
    {
        qDebug() << "testing BLESTARTUP";

        ui->textEdit->insertHtml(QString("<br>><font color='blue'>%1</font>").arg(CLI_BLE_STARTUP[ui->comboBox->currentIndex()]).toLatin1());
        serialPort.write(QString("%1\r").arg(CLI_BLE_STARTUP[ui->comboBox->currentIndex()]).toLatin1());
    }

}

void mAgaMonitor::on_rbBranchBleInitTests_toggled(bool checked)
{
    if(true == checked)
    {
        enBranch = CMDS_BRANCH::BLEINITTESTS;
    }
}


void mAgaMonitor::on_rbBleStartup_toggled(bool checked)
{

    if(true == checked)
    {
        enBranch = CMDS_BRANCH::BLESTARTUP;
    }
}


void mAgaMonitor::on_chbEscCodes_toggled(bool checked)
{
    b_EscCodes = checked;
}

