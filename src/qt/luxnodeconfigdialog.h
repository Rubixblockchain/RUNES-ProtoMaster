#ifndef RÜNESNODECONFIGDIALOG_H
#define RÜNESNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class RÜNESNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class RÜNESNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RÜNESNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:28666", QString privkey="MASTERNODEPRIVKEY");
    ~RÜNESNodeConfigDialog();

private:
    Ui::RÜNESNodeConfigDialog *ui;
};

#endif // RÜNESNODECONFIGDIALOG_H
