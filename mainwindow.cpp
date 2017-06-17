#include "widget.h"
#include "numericio.h"
#include "multiplexer.h"
#include "counter.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(NumericIO *gate, QWidget *parent)
    : numericio(gate),QMainWindow(parent),ui(new Ui::MainWindow)
{
    bits=0;
    type=numericioMainWindow;
    ui->setupUi(this);
}

MainWindow::MainWindow(Multiplexer *gate, QWidget *parent)
    : multiplexer(gate),QMainWindow(parent),ui(new Ui::MainWindow)
{
    bits=0;
    type=multiplexerMainWindow;
    ui->setupUi(this);
}

MainWindow::MainWindow(Counter *gate, QWidget *parent)
    : counter(gate),QMainWindow(parent),ui(new Ui::MainWindow)
{
    bits=0;
    type=counterMainWindow;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    Widget::simulator()->setEnabled(true);
}

void MainWindow::on_Bits_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        bits=0;
        break;

    case 1:
        bits=2;
        ui->note->setText("");
        break;

    case 2:
        bits=4;
        ui->note->setText("");
        break;

    case 3:
        bits=8;
        ui->note->setText("");
        break;

    case 4:
        bits=16;
        ui->note->setText("");
        break;

    default:
        bits=0;
        break;
    }
}

void MainWindow::on_Ok_clicked()
{
    if(bits==0)
        ui->note->setText("<-- Please Set Bits");
    else
    {
        switch(type)
        {
        case numericioMainWindow:
            numericio->Draw(bits);
            break;

        case multiplexerMainWindow:
            multiplexer->Draw(bits);
            break;

        case counterMainWindow:
            counter->Draw(bits);
            break;

        default:
            break;
        }
        close();
    }
}

void MainWindow::on_Cancel_clicked()
{
    close();
}
