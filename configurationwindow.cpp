#include "configurationwindow.h"
#include "ui_configurationwindow.h"
#include <QKeyEvent>

ConfigurationWindow::ConfigurationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigurationWindow)
{
    ui->setupUi(this);
}

ConfigurationWindow::~ConfigurationWindow()
{
    delete ui;
}

void ConfigurationWindow::on_pushButtonReturn_clicked()
{
    this->hide();
}

void ConfigurationWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Back:
        this->hide();
    }
}
