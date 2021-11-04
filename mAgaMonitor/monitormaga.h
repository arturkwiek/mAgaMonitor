#ifndef MONITORMAGA_H
#define MONITORMAGA_H
#include <QDialog>
#include <QSerialPortInfo>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class mAgaMonitor; }
QT_END_NAMESPACE

typedef enum CLI_CMNDS
{
    START, //!< start smth
    STOP, //!< stop smth
    SET, //!< set smth
    GET, //!< get smth
    BLE, //!< Bluetooth Low Energy
    BIST, //!< Built In Self Test
    DUT, //!< Device Under Test
    ADVERTISE, //!< Advertising
    SCAN, //!< Scanning
    CUSTOM, //!< Custom functionality
    START_BLE, //!< start BLE
    STOP_BLE, // not implemented
    START_ADVERTISE, //!< start Advertising
    STOP_ADVERTISE, //!< stop Advertising
    START_SCAN, //!< start Scanning
    STOP_SCAN, //!< stop Scanning
    LIST_DEVICES, //!< list scanned devices
    START_CUSTOM, //!< start Custom
    STOP_CUSTOM, //!< stop Custom
    GET_MAC, //!< get device Mac address
    GET_DEVICE_NAME, //!< get bluetooth device name
    SET_PARAMETER, //!< get parameter
    GET_PARAMETER //!< set parameter
}en_cli_cmd_t;



static const char *CLI_BLE_STARTUP[] = {
    "start",
    "stop",
    "set",
    "get",
    "ble",
    "bist",
    "dut",
    "advertise",
    "scan",
    "custom",
    "ble start",
    "ble stop",
    "advertise start",
    "advertise stop",
    "scan start",
    "scan stop",
    "scan list_devices",
    "custom start",
    "custom stop",
    "get_mac",
    "get_devname",
    "parameter set",
    "parameter get",

};

static const char *CLI_BLE_BLEINITTESTS[] = {
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "bleStart",
    "unknown",
    "bleAdvertiseStartExample",
    "bleAdvertiseStop",
    "bleScanStart",
    "bleScanStop",
    "bleListDevices",
    "unknown",
    "unknown",
    "bleGetMac",
    "unknown",
    "unknown",
    "unknown",

};

class mAgaMonitor : public QDialog
{
    Q_OBJECT

public:
    mAgaMonitor(QWidget *parent = nullptr);
    ~mAgaMonitor();
    QSerialPort serialPort;

    enum CMDS_BRANCH
    {
        BLESTARTUP,
        BLEINITTESTS
    } enBranch;

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

    void on_btnGetParam_clicked();

    void on_btnSetParam_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_btnTestCommand_clicked();

    void on_rbBranchBleInitTests_toggled(bool checked);

    void on_rbBleStartup_toggled(bool checked);

private:
    Ui::mAgaMonitor *ui;
    QSerialPortInfo serialInfo;
};
#endif // MONITORMAGA_H
