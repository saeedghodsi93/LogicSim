#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class Widget;
class NumericIO;
class Multiplexer;
class Counter;

enum MainWindowType{numericioMainWindow,multiplexerMainWindow,counterMainWindow};

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(NumericIO *gate, QWidget *parent = 0);
    explicit MainWindow(Multiplexer *gate, QWidget *parent = 0);
    explicit MainWindow(Counter *gate, QWidget *parent = 0);

    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void on_Bits_currentIndexChanged(int index);
    void on_Ok_clicked();
    void on_Cancel_clicked();

private:
    Ui::MainWindow *ui;

    int bits;
    MainWindowType type;
    NumericIO *numericio;
    Multiplexer *multiplexer;
    Counter *counter;
};

#endif // MAINWINDOW_H
