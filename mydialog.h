#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <vector>
#include <string>

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

    QLabel *imageLabel;

    QLineEdit *popsizeEdit;
    QLineEdit *precisionEdit;
    QLineEdit *p_crossEdit;
    QLineEdit *p_mutateEdit;
    QLineEdit *iterationEdit;
    QLineEdit *jEdit;
    QLineEdit *leftValEdit;
    QLineEdit *rightValEdit;
    QLineEdit *nEdit;
    QLineEdit *tournamentEdit;

    QPushButton *functionBtn;

    int current_problem_type;
    void SwitchFunction();

    std::vector<QString> functionNameData;
    std::vector<QPixmap> imageData;
    

private slots:
    void TrainBtnClicked();
    void FunctionBtnClicked();
    void ResetBtnClicked();

};

#endif // MYDIALOG_H
