#include "mydialog.h"

#include <QtGui>
#include <string>
#include <iostream>
#include <set>
#include <vector>

#include "genetic.h"

using namespace std;

// 定义些常量

// 宽度
static const int LINE_EDIT_WIDTH = 195;
static const int TRAINING_LABEL_WIDTH = 400;
static const int PREDICT_LABEL_WIDTH = 400;
// 高度
static const int LINE_EDIT_HEIGHT = 30;
static const int NORMAL_BUTTON_HEIGHT = 60;
static const int TEXT_EDIT_HEIGHT = 140;
static const int TRAINING_LABEL_HEIGHT = 140;
static const int TRAINING_LABEL_INDENT = 3;
static const int PREDICT_LABEL_HEIGHT = 57;
static const int PREDICT_LABEL_INDENT = 3;
static const int LABEL_HEIGHT = 25;
static const int MAIN_LAYOUT_MARGIN = 10;
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
    
    // 图片
    QPixmap *introImage = new QPixmap;
    introImage->load(":/images/genetic.jpg");

    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(*introImage);
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

    QLabel *jLabel = new QLabel("j值:");
    jLabel->setFont(*labelFont);
    jLabel->setFixedHeight(LABEL_HEIGHT);

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
    popsizeEdit->setText("8");

    precisionEdit = new QLineEdit;
    precisionEdit->setFixedWidth(LINE_EDIT_WIDTH);
    precisionEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    precisionEdit->setFont(*textFont);
    precisionEdit->setText("0.000001");

    p_crossEdit = new QLineEdit;
    p_crossEdit->setFixedWidth(LINE_EDIT_WIDTH);
    p_crossEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    p_crossEdit->setFont(*textFont);
    p_crossEdit->setText("0.75");

    p_mutateEdit = new QLineEdit;
    p_mutateEdit->setFixedWidth(LINE_EDIT_WIDTH);
    p_mutateEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    p_mutateEdit->setFont(*textFont);
    p_mutateEdit->setText("0.02");

    iterationEdit = new QLineEdit;
    iterationEdit->setFixedWidth(LINE_EDIT_WIDTH);
    iterationEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    iterationEdit->setFont(*textFont);
    iterationEdit->setText("100");

    jEdit = new QLineEdit;
    jEdit->setFixedWidth(LINE_EDIT_WIDTH);
    jEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    jEdit->setFont(*textFont);
    jEdit->setText("2");

    // All Buttons
    QFont *btnFont = new QFont;
    btnFont->setPointSize(BUTTON_BIG_FONT_SIZE);
    // QFont *btnBigFont = new QFont;
    // btnBigFont->setPointSize(BUTTON_BIG_FONT_SIZE);

    QPushButton *trainBtn = new QPushButton("训练");
    trainBtn->setFont(*btnFont);
    trainBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);


    // sampleTextEdit = new QTextEdit;
    // sampleTextEdit->setFixedHeight(TEXT_EDIT_HEIGHT);
    // sampleTextEdit->setFont(*textFont);
    // sampleTextEdit->setText("请用矩阵形式; 特征由空格隔开; 样本由换行分开; 类别在第一列.");

    // // TrainingResultLabel
    // QScrollArea *trainingScrollArea = new QScrollArea;
    // trainingScrollArea->setFixedWidth(TRAINING_LABEL_WIDTH);
    // trainingScrollArea->setFixedHeight(TRAINING_LABEL_HEIGHT);
    // trainingResultLabel = new QLabel;
    // trainingResultLabel->setScaledContents(true);
    // trainingResultLabel->setFont(*textFont);
    // trainingResultLabel->setIndent(TRAINING_LABEL_INDENT);
    // trainingResultLabel->setText("<空>");
    // trainingScrollArea->setWidget(trainingResultLabel);

    // // PredictLineEdit
    // predictLineEdit = new QLineEdit;
    // predictLineEdit->setFixedWidth(LINE_EDIT_WIDTH);
    // predictLineEdit->setFixedHeight(LINE_EDIT_HEIGHT);
    // predictLineEdit->setFont(*textFont);
    // predictLineEdit->setPlaceholderText("特征值1 特征值2 ... 特征值n");

    // // PredictResultLabel
    // QScrollArea *predictScrollArea = new QScrollArea;
    // predictScrollArea->setFixedWidth(PREDICT_LABEL_WIDTH);
    // predictScrollArea->setFixedHeight(PREDICT_LABEL_HEIGHT);
    // predictResultLabel = new QLabel;
    // predictResultLabel->setScaledContents(true);
    // predictResultLabel->setFont(*textFont);
    // predictResultLabel->setIndent(PREDICT_LABEL_INDENT);
    // predictResultLabel->setText("<空>");
    // predictScrollArea->setWidget(predictResultLabel);

    // All Buttons
    // QFont *btnFont = new QFont;
    // btnFont->setPointSize(BUTTON_FONT_SIZE);
    // QFont *btnBigFont = new QFont;
    // btnBigFont->setPointSize(BUTTON_BIG_FONT_SIZE);

    // QPushButton *sampleImportBtn = new QPushButton("导入txt");
    // sampleImportBtn->setFont(*btnFont);
    // sampleImportBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    // QPushButton *sampleClearBtn = new QPushButton("清空数据");
    // sampleClearBtn->setFont(*btnFont);
    // sampleClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    // QPushButton *trainingBtn = new QPushButton("训练 Go");
    // trainingBtn->setFont(*btnFont);
    // trainingBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    // QPushButton *trainingClearBtn = new QPushButton("丢弃模型");
    // trainingClearBtn->setFont(*btnFont);
    // trainingClearBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    // QPushButton *predictBtn = new QPushButton("预测 Go");
    // predictBtn->setFont(*btnFont);
    // predictBtn->setFixedHeight(NORMAL_BUTTON_HEIGHT);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subInputLayout1 = new QHBoxLayout;
    QHBoxLayout *subInputLayout2 = new 
    QHBoxLayout;
    QHBoxLayout *subInputLayout3 = new QHBoxLayout;
    QHBoxLayout *subOutputLayout = new QHBoxLayout;
    QHBoxLayout *subControlLayout = new QHBoxLayout;

    mainLayout->setMargin(MAIN_LAYOUT_MARGIN);
    subInputLayout1->setMargin(0);
    subInputLayout1->setSpacing(MAIN_LAYOUT_MARGIN);
    subInputLayout2->setMargin(0);
    subInputLayout2->setSpacing(MAIN_LAYOUT_MARGIN);
    subInputLayout3->setMargin(0);
    subInputLayout3->setSpacing(MAIN_LAYOUT_MARGIN);
    subOutputLayout->setMargin(0);
    subOutputLayout->setSpacing(MAIN_LAYOUT_MARGIN);
    subControlLayout->setMargin(0);
    subControlLayout->setSpacing(MAIN_LAYOUT_MARGIN);

    // sub-layout
    subInputLayout1->addWidget(popsizeLabel);
    subInputLayout1->addWidget(popsizeEdit);
    subInputLayout1->addStretch();
    subInputLayout1->addWidget(precisionLabel);
    subInputLayout1->addWidget(precisionEdit);

    subInputLayout2->addWidget(p_crossLabel);
    subInputLayout2->addWidget(p_crossEdit);
    subInputLayout2->addStretch();
    subInputLayout2->addWidget(p_mutateLabel);
    subInputLayout2->addWidget(p_mutateEdit);


    subInputLayout3->addWidget(iterationLabel);
    subInputLayout3->addWidget(iterationEdit);
    subInputLayout3->addStretch();
    subInputLayout3->addWidget(jLabel);
    subInputLayout3->addWidget(jEdit);



    // main-layout
    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(subInputLayout1);
    mainLayout->addLayout(subInputLayout2);
    mainLayout->addLayout(subInputLayout3);

    // mainLayout->addWidget(trainingScrollArea);

    // mainLayout->addLayout(subPredictLayout);
    // mainLayout->addWidget(predictScrollArea);

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

    // connect(sampleClearBtn, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
}


// Button Clicked 按钮事件
void MyDialog::TrainBtnClicked()
{
    Genetic genetic;
    genetic.Train();
}


// // 训练模型清空
// void MyDialog::onTrainingClearButtonClicked()
// {
//     bayes = NULL;
//     trainingResultLabel->setText("<空>");
//     trainingResultLabel->adjustSize();
// }


// // 消息框
// void MyDialog::criticalMessage(QString msg)
// {
//     QMessageBox::StandardButton reply;
//     reply = QMessageBox::critical(this, "错误",
//                                   msg,
//                                   QMessageBox::Ok);
// }