#ifndef ADDEDITRÜNESNODE_H
#define ADDEDITRÜNESNODE_H

#include <QDialog>

namespace Ui {
class AddEditRÜNESNode;
}


class AddEditRÜNESNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditRÜNESNode(QWidget *parent = 0);
    ~AddEditRÜNESNode();

protected:

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

signals:

private:
    Ui::AddEditRÜNESNode *ui;
};

#endif // ADDEDITRÜNESNODE_H
