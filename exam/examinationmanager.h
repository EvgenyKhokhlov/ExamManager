#ifndef EXAMINATIONMANAGER_H
#define EXAMINATIONMANAGER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class ExaminationManager;
}

class ExaminationManager : public QWidget
{
    Q_OBJECT

public:
    explicit ExaminationManager(QWidget *parent = nullptr);
    ~ExaminationManager();

private:
    Ui::ExaminationManager *ui;

private:
    void openExamMenu(QWidget *examMenu);

public slots:
    void createExamination(QWidget *examCreationMenu);
    void editExamination(QWidget *examEditionMenu);
    void startExamination();
};

#endif // EXAMINATIONMANAGER_H
