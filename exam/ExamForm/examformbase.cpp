#include "examformbase.h"
#include "ui_examformbase.h"

ExamFormBase::ExamFormBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamFormBase)
{
    ui->setupUi(this);
}

ExamFormBase::~ExamFormBase()
{
    delete ui;
}

void ExamFormBase::clearLayout(QLayout *layout)
{
    while(layout->count() > 0){
        QLayoutItem *item = layout->takeAt(0);
        QWidget* widget = item->widget();
        if(widget)
            delete widget;
        delete item;
    }
}

void ExamFormBase::ClearForm()
{
    image = QImage();
    ui->screen->update();

    questionType = nullptr;
}

void ExamFormBase::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setViewport(ui->screen->geometry().x(), ui->screen->geometry().y(), ui->screen->geometry().width(),
                        ui->screen->geometry().height());
    painter.drawImage(20, 100, image);
}
