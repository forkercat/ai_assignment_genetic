#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

class QTextEdit;
class QLabel;
class QLineEdit;

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    virtual ~MyDialog() {};

private:

    QLineEdit *popsizeEdit;
    QLineEdit *precisionEdit;
    QLineEdit *p_crossEdit;
    QLineEdit *p_mutableEdit;

    

// private slots:

};

#endif // MYDIALOG_H
