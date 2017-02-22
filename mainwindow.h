#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_exit();

    void on_digitButton_clicked();
    void on_unaryButton_clicked();
    void on_additiveButton_clicked();
    void on_multiplicationButton_clicked();
    void on_pointButtom_clicked();
    void on_equalButton_clicked();
    void on_changeSignButton_clicked();
    void on_backspaceButton_clicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();

private:
    Ui::MainWindow *ui;
    void abortOperation();
    bool Calculate(double RightOperand, const QString &pandingOperator);

    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pandingAdditiveOperator;
    QString pandingMultiplicationOperator;
    bool waitingForOperand;
};

#endif // MAINWINDOW_H
