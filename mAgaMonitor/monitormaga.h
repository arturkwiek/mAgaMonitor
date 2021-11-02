#ifndef MONITORMAGA_H
#define MONITORMAGA_H
#include <QDialog>
#include <QSerialPortInfo>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class mAgaMonitor; }
QT_END_NAMESPACE

class mAgaMonitor : public QDialog
{
    Q_OBJECT

public:
    mAgaMonitor(QWidget *parent = nullptr);
    ~mAgaMonitor();
    QSerialPort serialPort;

public slots:
    void readData();

private slots:
    void on_cbxSerialSpeed_currentTextChanged(const QString &arg1);

    void on_cbxSerialPort_currentTextChanged(const QString &arg1);

    void on_btnOpen_clicked();

    void on_btnSend_clicked();

    void on_btnRescanSerialPorts_clicked();

    void on_btnClearLogWindow_clicked();

    void on_btnStartBLE_clicked();

    void on_btnStartAdvertise_clicked();

    void on_btnStopAdvertise_clicked();

    void on_btnStartScan_clicked();

    void on_btnStopScan_clicked();

    void on_btnGetMac_clicked();

    void on_btnListDevices_clicked();

private:
    Ui::mAgaMonitor *ui;
    QSerialPortInfo serialInfo;
};
#endif // MONITORMAGA_H
