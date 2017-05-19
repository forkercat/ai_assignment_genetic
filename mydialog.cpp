#include "mydialog.h"

#include <QtGui>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

#include "genetic.h"

#include "constant.h"

using namespace std;

// 定义些常量

// 宽度
static const int LINE_EDIT_WIDTH = 195;
static const int TRAINING_LABEL_WIDTH = 560;

// 高度
static const int LINE_EDIT_HEIGHT = 30;
static const int NORMAL_BUTTON_HEIGHT = 50;
static const int LARGE_BUTTON_HEIGHT = 60;

static const int LABEL_HEIGHT = 25;
static const int MAIN_LAYOUT_MARGIN = 10;
static const int TRAINING_LABEL_HEIGHT = 250;
static const int TRAINING_LABEL_INDENT = 3;
// 字体
static const int SMALL_LABEL_FONT_SIZE = 14;
static const int LABEL_FONT_SIZE = 16;
static const int BUTTON_FONT_SIZE = 16;
static const int BUTTON_BIG_FONT_SIZE = 18;
static const int TEXT_FONT_SIZE = 14;

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{
    // 窗口
    this->setWindowTitle("俊皓的遗传算法作业");
    
    // 函数Name
    current_problem_type = 0;
    functionNameData.push_back("问题一 （n和锦标比例无关, 点我切换问题）");
    functionNameData.push_back("问题二 （j无关, 不可修改）");

    // 图片
    QPixmap introImage_1;
    introImage_1.load(":/images/genetic_1.jpg");
    QPixmap introImage_2;
    introImage_2.load(":/images/genetic_2.jpg");
    imageData.push_back(introImage_1);
    imageData.push_back(introImage_2);

    imageLabel = new QLabel;
    imageLabel->setPixmap(introImage_1);
    imageLabel->setScaledContents(true);
    imageLabel->resize(imageLabel->pixmap()->size());

    // All Labels

    QFont *labelFont = new QFont;
    labelFont->setPointSize(LABEL_FONT_SIZE);
    QFont *smallLabelFont = new QFont;
    smallLabelFont->setPointSize(SMALL_LABEL_FONT_SIZE);

    QLabel *popsizeLabel = new QLabel("规模大小:");
    popsizeLabel->setFont(*labelFont);
    popsizeLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *precisionLabel = new QLabel("小数精度:");
    precisionLabel->setFont(*labelFont);
    precisionLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *p_crossLabel = new QLabel("杂交概率:");
    p_crossLabel->setFont(*labelFont);
    p_crossLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *p_mutateLabel = new QLabel("变异概率:");
    p_mutateLabel->setFont(*labelFont);
    p_mutateLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *iterationLabel = new QLabel("迭代次数:");
    iterationLabel->setFont(*labelFont);
    iterationLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *jLabel = new QLabel("j值:          ");
    jLabel->setFont(*labelFont);
    jLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *leftValLabel = new QLabel("区间左值:");
    leftValLabel->setFont(*labelFont);
    leftValLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *rightValLabel = new QLabel("区间右值:");
    rightValLabel->setFont(*labelFont);
    rightValLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *nLabel = new QLabel("n值:         ");
    nLabel->setFont(*labelFont);
    nLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *tournamentLabel = new QLabel("锦标比例:");
    tournamentLabel->setFont(*labelFont);
    tournamentLabel->setFixedHeight(LABEL_HEIGHT);

    QLabel *endingLabel = new QLabel("ai_assignment_genetic © 2017 Junhao (2014101027)");
    endingLabel->setFont(*smallLabelFont);
    endingLabel->setFixedHeight(SMALL_LABEL_FONT_SIZE);
    endingLabel->setAlignment(Qt::AlignHCenter);

    // All LineEdits
    QFont *textFont = new QFont;
    textFont->setPointSize(TEXT_FONT_SIZE);

    popsizeEdit = new QLineEdit;
    popsizeEdit->setFixedWidth(LINE_EDIT_WIDTH);
    popsizeEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    popsizeEdit->setFont(*textFont);
    popsizeEdit->setText(QString("%1").arg(POPSIZE));

    precisionEdit = new QLineEdit;
    precisionEdit->setFixedWidth(LINE_EDIT_WIDTH);
    precisionEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    precisionEdit->setFont(*textFont);
    precisionEdit->setText(QString("%1").arg(PRECISION));

    p_crossEdit = new QLineEdit;
    p_crossEdit->setFixedWidth(LINE_EDIT_WIDTH);
    p_crossEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    p_crossEdit->setFont(*textFont);
    p_crossEdit->setText(QString("%1").arg(P_CROSS));

    p_mutateEdit = new QLineEdit;
    p_mutateEdit->setFixedWidth(LINE_EDIT_WIDTH);
    p_mutateEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    p_mutateEdit->setFont(*textFont);
    p_mutateEdit->setText(QString("%1").arg(P_MUTATE));

    iterationEdit = new QLineEdit;
    iterationEdit->setFixedWidth(LINE_EDIT_WIDTH);
    iterationEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    iterationEdit->setFont(*textFont);
    iterationEdit->setText(QString("%1").arg(ITERATION_TIME));

    jEdit = new QLineEdit;
    jEdit->setFixedWidth(LINE_EDIT_WIDTH);
    jEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    jEdit->setFont(*textFont);
    jEdit->setText(QString("%1").arg(J));

    leftValEdit = new QLineEdit;
    leftValEdit->setFixedWidth(LINE_EDIT_WIDTH);
    leftValEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    leftValEdit->setFont(*textFont);
    leftValEdit->setText(QString("%1").arg(LEFT_VAL_1));

    rightValEdit = new QLineEdit;
    rightValEdit->setFixedWidth(LINE_EDIT_WIDTH);
    rightValEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    rightValEdit->setFont(*textFont);
    rightValEdit->setText(QString("%1").arg(RIGHT_VAL_1));

    nEdit = new QLineEdit;
    nEdit->setFixedWidth(LINE_EDIT_WIDTH);
    nEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    nEdit->setFont(*textFont);
    nEdit->setText(QString("%1").arg(N_2));
    nEdit->setReadOnly(true);

    tournamentEdit = new QLineEdit;
    tournamentEdit->setFixedWidth(LINE_EDIT_WIDTH);
    tournamentEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    tournamentEdit->setFont(*textFont);
    tournamentEdit->setText(QString("%1").arg(PERCENTAGE));
    tournamentEdit->setReadOnly(true);

    // TrainingResultLabel
    QScrollArea *trainingScrollArea = new QScrollArea;
    trainingScrollArea->setFixedWidth(TRAINING_LABEL_WIDTH);
    trainingScrollArea->setFixedHeight(TRAINING_LABEL_HEIGHT);
    trainingResultLabel = new QLabel;
    trainingResultLabel->setScaledContents(true);
    trainingResultLabel->setFont(*textFont);
    trainingResultLabel->setIndent(TRAINING_LABEL_INDENT);
    trainingResultLabel->setText("<训练结果>");
    trainingScrollArea->setWidget(trainingResultLabel);

    // All Buttons
    QFont *btnFont = new QFont;
    btnFont->setPointSize(BUTTON_FONT_SIZE);
    QFont *btnBigFont = new QFont;
    btnBigFont->setPointSize(BUTTON_BIG_FONT_SIZE);

    functionBtn = new QPushButton(functionNameData[0]);
    functionBtn->setFont(*btnFont);
    functionBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *resetBtn = new QPushButton("重置数据");
    resetBtn->setFont(*btnFont);
    resetBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    QPushButton *trainBtn = new QPushButton("训练");
    trainBtn->setFont(*btnBigFont);
    trainBtn->setFixedHeight(LARGE_BUTTON_HEIGHT);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subFunctionLayout = new QHBoxLayout;
    QHBoxLayout *subInputLayout1 = new QHBoxLayout;
    QHBoxLayout *subInputLayout2 = new 
    QHBoxLayout;
    QHBoxLayout *subInputLayout3 = new QHBoxLayout;
    QHBoxLayout *subInputLayout4 = new QHBoxLayout;
    QHBoxLayout *subInputLayout5 = new QHBoxLayout;
    QHBoxLayout *subOutputLayout = new QHBoxLayout;
    QHBoxLayout *subControlLayout = new QHBoxLayout;

    mainLayout->setMargin(MAIN_LAYOUT_MARGIN);
    subFunctionLayout->setMargin(0);
    subFunctionLayout->setSpacing(MAIN_LAYOUT_MARGIN);
    subInputLayout1->setMargin(0);
    subInputLayout1->setSpacing(MAIN_LAYOUT_MARGIN);
    subInputLayout2->setMargin(0);
    subInputLayout2->setSpacing(MAIN_LAYOUT_MARGIN);
    subInputLayout3->setMargin(0);
    subInputLayout3->setSpacing(MAIN_LAYOUT_MARGIN);
    subInputLayout4->setMargin(0);
    subInputLayout4->setSpacing(MAIN_LAYOUT_MARGIN);
    subInputLayout5->setMargin(0);
    subInputLayout5->setSpacing(MAIN_LAYOUT_MARGIN);
    subOutputLayout->setMargin(0);
    subOutputLayout->setSpacing(MAIN_LAYOUT_MARGIN);
    subControlLayout->setMargin(0);
    subControlLayout->setSpacing(MAIN_LAYOUT_MARGIN);

    // sub-layout
    subFunctionLayout->addWidget(functionBtn);
    subFunctionLayout->addWidget(resetBtn);

    subInputLayout1->addWidget(nLabel);
    subInputLayout1->addWidget(nEdit);
    subInputLayout1->addStretch();
    subInputLayout1->addWidget(tournamentLabel);
    subInputLayout1->addWidget(tournamentEdit);

    subInputLayout2->addWidget(leftValLabel);
    subInputLayout2->addWidget(leftValEdit);
    subInputLayout2->addStretch();
    subInputLayout2->addWidget(rightValLabel);
    subInputLayout2->addWidget(rightValEdit);

    subInputLayout3->addWidget(jLabel);
    subInputLayout3->addWidget(jEdit);
    subInputLayout3->addStretch();
    subInputLayout3->addWidget(popsizeLabel);
    subInputLayout3->addWidget(popsizeEdit);

    subInputLayout4->addWidget(iterationLabel);
    subInputLayout4->addWidget(iterationEdit);
    subInputLayout4->addStretch();
    subInputLayout4->addWidget(precisionLabel);
    subInputLayout4->addWidget(precisionEdit);

    subInputLayout5->addWidget(p_crossLabel);
    subInputLayout5->addWidget(p_crossEdit);
    subInputLayout5->addStretch();
    subInputLayout5->addWidget(p_mutateLabel);
    subInputLayout5->addWidget(p_mutateEdit);


    // main-layout
    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(subFunctionLayout);
    mainLayout->addLayout(subInputLayout1);
    mainLayout->addLayout(subInputLayout2);
    mainLayout->addLayout(subInputLayout3);
    mainLayout->addLayout(subInputLayout5);
    mainLayout->addLayout(subInputLayout4);
    mainLayout->addWidget(trainingScrollArea);
    mainLayout->addWidget(trainBtn);
    mainLayout->addWidget(endingLabel);

    this->setLayout(mainLayout);

    this->show();

    // 重新调整大小
    this->adjustSize();
    // 这样可以使得窗口大小不可以变化
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    // 设置连接槽, 按钮事件
    connect(trainBtn, SIGNAL(clicked()), this, SLOT(TrainBtnClicked()));
    connect(resetBtn, SIGNAL(clicked()), this, SLOT(ResetBtnClicked()));
    connect(functionBtn, SIGNAL(clicked()), this, SLOT(FunctionBtnClicked()));
}


void MyDialog::SwitchFunction()
{
    current_problem_type = (current_problem_type == 0) ? 1 : 0;

    functionBtn->setText(functionNameData[current_problem_type]);
    imageLabel->setPixmap(imageData[current_problem_type]);

    if (current_problem_type == 0)
    {
        leftValEdit->setText(QString("%1").arg(LEFT_VAL_1));
        rightValEdit->setText(QString("%1").arg(RIGHT_VAL_1));
        nEdit->setReadOnly(true);
        jEdit->setReadOnly(false);
        tournamentEdit->setReadOnly(true);
    }
    else
    {
        leftValEdit->setText(QString("%1").arg(LEFT_VAL_2));
        rightValEdit->setText(QString("%1").arg(RIGHT_VAL_2));
        nEdit->setReadOnly(false);
        jEdit->setReadOnly(true);
        tournamentEdit->setReadOnly(false);
    }
}

// Button Clicked 按钮事件
void MyDialog::TrainBtnClicked()
{
    Genetic genetic;

    /* 设置参数 */
    genetic.SetPopsize(atoi(popsizeEdit->text().toStdString().c_str()));
    genetic.SetPrecision(atoi(precisionEdit->text().toStdString().c_str()));
    genetic.SetPcross(atof(p_crossEdit->text().toStdString().c_str()));
    genetic.SetPmutate(atof(p_mutateEdit->text().toStdString().c_str()));
    genetic.SetLeftVal(atof(leftValEdit->text().toStdString().c_str()));
    genetic.SetRightVal(atof(rightValEdit->text().toStdString().c_str()));
    genetic.SetIterationTime(atoi(iterationEdit->text().toStdString().c_str()));
    genetic.SetJ(atof(jEdit->text().toStdString().c_str()));
    genetic.SetN(atoi(nEdit->text().toStdString().c_str()));
    genetic.SetPercentage(atof(tournamentEdit->text().toStdString().c_str()));


    /* 训练 */
    genetic.Train(current_problem_type);

    vector< vector<double> > result = genetic.GetResult();

    string result_str = "<训练结果>\n";

    char temp1[40];
    result_str += "\n第";
    sprintf(temp1, "%d次迭代后的函数最小值: ", (int)result.size());
    result_str += temp1;

    long cutInt = (long)(result[result.size()-1][0] * pow(10, atoi(precisionEdit->text().toStdString().c_str())));
    double val =  cutInt / pow(10, atoi(precisionEdit->text().toStdString().c_str()));
    sprintf(temp1, "%.15lf\n\n", val);
    result_str += temp1;

    for (unsigned int i = 0; i < result.size(); ++i)
    {
        char temp2[40];

        result_str += "第";
        sprintf(temp2, "%d", i + 1);
        result_str += temp2;
        result_str += "次迭代.......... 平均最小值: ";

        long cutInt = (long)(result[i][0] * pow(10, atoi(precisionEdit->text().toStdString().c_str())));
        double val =  cutInt / pow(10, atoi(precisionEdit->text().toStdString().c_str()));
        sprintf(temp2, "%.15lf", val);
        result_str += temp2;
        result_str += "     杂交产生: ";
        sprintf(temp2, "%d", (int)result[i][1]);
        result_str += temp2;
        result_str += "个, 变异产生: ";
        sprintf(temp2, "%d", (int)result[i][2]);
        result_str += temp2;
        result_str += "个\n";
    }

    // 更新显示训练结果
    trainingResultLabel->setText(result_str.c_str());
    trainingResultLabel->adjustSize();
}

void MyDialog::FunctionBtnClicked()
{
    SwitchFunction();
}

void MyDialog::ResetBtnClicked()
{
    trainingResultLabel->setText("<训练结果>");
    trainingResultLabel->adjustSize();
    
    popsizeEdit->setText(QString("%1").arg(POPSIZE));

    precisionEdit->setText(QString("%1").arg(PRECISION));

    p_crossEdit->setText(QString("%1").arg(P_CROSS));

    p_mutateEdit->setText(QString("%1").arg(P_MUTATE));

    iterationEdit->setText(QString("%1").arg(ITERATION_TIME));

    jEdit->setText(QString("%1").arg(J));

    leftValEdit->setText(QString("%1").arg(LEFT_VAL_1));

    rightValEdit->setText(QString("%1").arg(RIGHT_VAL_1));

    nEdit->setText(QString("%1").arg(N_2));
    nEdit->setReadOnly(true);

    tournamentEdit->setText(QString("%1").arg(PERCENTAGE));
    tournamentEdit->setReadOnly(true);
}