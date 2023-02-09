#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadMainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMainMenu()
{
    mainMenu = new QWidget();

    QFont font;
    font.setPointSize(12);

    auto mainLayout = new QHBoxLayout();
    auto startExamButton = new QPushButton("Start Examination");
    startExamButton->setFont(font);
    startExamButton->setMinimumHeight(100);
    startExamButton->setMaximumWidth(400);

    auto openExamMenuButton = new QPushButton("Edit Examination");
    openExamMenuButton->setFont(font);
    openExamMenuButton->setMinimumHeight(100);
    openExamMenuButton->setMaximumWidth(400);

    auto openResultMenuButton = new QPushButton("Open Result");
    openResultMenuButton->setFont(font);
    openResultMenuButton->setMinimumHeight(100);
    openResultMenuButton->setMaximumWidth(400);

    connect(startExamButton, &QPushButton::clicked, this, &MainWindow::loadExamChooseMenu);
    connect(openExamMenuButton, &QPushButton::clicked, this, &MainWindow::loadExaminationMenu);
    connect(openResultMenuButton, &QPushButton::clicked, this, &MainWindow::loadExamResulMenu);

    mainLayout->addWidget(openExamMenuButton);
    mainLayout->addWidget(startExamButton);
    mainLayout->addWidget(openResultMenuButton);
    mainMenu->setLayout(mainLayout);

    setCentralWidget(mainMenu);
}

void MainWindow::loadExaminationMenu()
{
    examMenu = new QWidget();

    QFont font;
    font.setPointSize(12);

    auto vertLayout = new QVBoxLayout();
    auto horLayout = new QHBoxLayout();
    auto horLayoutBack = new QHBoxLayout();
    auto createExamButton = new QPushButton("New Examination");
    createExamButton->setFont(font);
    createExamButton->setMinimumHeight(100);
    createExamButton->setMaximumWidth(400);

    auto editExamButton = new QPushButton("Edit Examination");
    editExamButton->setFont(font);
    editExamButton->setMinimumHeight(100);
    editExamButton->setMaximumWidth(400);

    auto backButton = new QPushButton("Back");
    backButton->setFont(font);
    backButton->setMinimumHeight(50);
    backButton->setMaximumWidth(300);

    auto emptyWidget = new QWidget;

    connect(backButton, &QPushButton::clicked, this, &MainWindow::loadMainMenu);
    connect(createExamButton, &QPushButton::clicked, this, &MainWindow::loadExamCreationMenu);
    connect(editExamButton, &QPushButton::clicked, this, &MainWindow::loadExamChooseMenu);

    horLayout->addWidget(createExamButton);
    horLayout->addWidget(editExamButton);

    horLayoutBack->addWidget(emptyWidget);
    horLayoutBack->addWidget(backButton);

    vertLayout->addLayout(horLayout);
    vertLayout->addLayout(horLayoutBack);

    examMenu->setLayout(vertLayout);
    setCentralWidget(examMenu);
}

void MainWindow::loadExamCreationMenu()
{
    examManager = new ExamEditor;
    connect(examManager, &ExamEditor::loadMainMenu, this, &MainWindow::loadMainMenu);

    setCentralWidget(examManager);
}

void MainWindow::loadExamChooseMenu()
{
    ExamManager ex;
    QVector<QString> *input = new QVector<QString>;
    *input = ex.getExamList();

    DialogExam *dialog = new DialogExam(input);
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if( button != nullptr ){
        if(button->text() == "Edit Examination")
            connect(dialog, &DialogExam::onDialogExit, this, &MainWindow::loadExamEditorMenu);
        if(button->text() == "Start Examination")
            connect(dialog, &DialogExam::onDialogExit, this, &MainWindow::loadPersonalDialog);
    }

    dialog->exec();
}

void MainWindow::loadExamResulMenu()
{
    resultManager = new ExamResultManager;
    connect(resultManager, &ExamResultManager::loadMainMenu, this, &MainWindow::loadMainMenu);

    setCentralWidget(resultManager);
}

void MainWindow::loadExamEditorMenu(QString examName)
{
    examManager = new ExamEditor(examName);
    connect(examManager, &ExamEditor::loadMainMenu, this, &MainWindow::loadMainMenu);

    setCentralWidget(examManager);
}

void MainWindow::loadPersonalDialog(QString examName)
{
    examinationName = new QString;
    *examinationName = examName;
    DialogPersonalData *dialog = new DialogPersonalData;
    connect(dialog, &DialogPersonalData::onDialogExit, this, &MainWindow::loadExamPasser);
    dialog->exec();
}

void MainWindow::loadExamPasser(QString name, QString surname, int age)
{
    ExamPasser *examPasser = new ExamPasser(name, surname, age, *examinationName);
    connect(examPasser, &ExamPasser::loadMainMenu, this, &MainWindow::loadMainMenu);

    setCentralWidget(examPasser);
}


