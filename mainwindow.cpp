#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(actionExit,SIGNAL(Trigged()),this,SLOT(close()));
    connect(ui->digitButton0,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton1,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton2,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton3,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton4,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton5,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton6,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton7,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton8,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->digitButton9,SIGNAL(clicked()),this,SLOT(on_digitButton_clicked()));
    connect(ui->backSpaceButton,SIGNAL(clicked()),this,SLOT(on_backspaceButton_clicked()));
    connect(ui->clearButton,SIGNAL(clicked()),this,SLOT(clear()));
    connect(ui->clearAllButton,SIGNAL(clicked()),this,SLOT(clearAll()));
    connect(ui->mcButton,SIGNAL(clicked()),this,SLOT(clearMemory()));
    connect(ui->mrButton,SIGNAL(clicked()),this,SLOT(readMemory()));
    connect(ui->msButton,SIGNAL(clicked()),this,SLOT(setMemory()));
    connect(ui->mplusButton,SIGNAL(clicked()),this,SLOT(addToMemory()));
    connect(ui->pointButton,SIGNAL(clicked()),this,SLOT(on_pointButtom_clicked()));
    connect(ui->changeSignButton,SIGNAL(clicked()),this,SLOT(on_changeSignButton_clicked()));
    connect(ui->divisionButton,SIGNAL(clicked()),this,SLOT(on_multiplicationButton_clicked()));
    connect(ui->timesButton,SIGNAL(clicked()),this,SLOT(on_multiplicationButton_clicked()));
    connect(ui->plusButton,SIGNAL(clicked()),this,SLOT(on_additiveButton_clicked()));
    connect(ui->minusButton,SIGNAL(clicked()),this,SLOT(on_additiveButton_clicked()));
    connect(ui->squareButton,SIGNAL(clicked()),this,SLOT(on_unaryButton_clicked()));
    connect(ui->powerButton,SIGNAL(clicked()),this,SLOT(on_unaryButton_clicked()));
    connect(ui->reciprocalButton,SIGNAL(clicked()),this,SLOT(on_unaryButton_clicked()));
    connect(ui->equalButton,SIGNAL(clicked()),this,SLOT(on_equalButton_clicked()));
    ui->display->setText("0");
    ui->changeSignButton->setText(tr("\302\261"));
    ui->powerButton->setText(tr("x\302\262"));
    sumInMemory=0.0;
    sumSoFar=0.0;
    factorSoFar=0.0;
    waitingForOperand=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::close();
    //this->destroy(true,true);
}

void MainWindow::on_exit()
{
    MainWindow::close();//menuBar()->actions().length()
}

void MainWindow::on_digitButton_clicked()
{
    QToolButton *clickedButton=qobject_cast<QToolButton *>(sender());
    int digitValue=clickedButton->text().toInt();
    if(digitValue==0 && ui->display->text()=="0")return;
    if(waitingForOperand){
        ui->display->clear();
        waitingForOperand=false;
    }
    ui->display->setText(ui->display->text()+QString::number(digitValue));
}

void MainWindow::on_backspaceButton_clicked()
{
    if(waitingForOperand)return;
    QString text=ui->display->text();
    text.chop(1);
    if(text.isEmpty())
    {
        text="0";
        waitingForOperand=true;
    }
    ui->display->setText(text);
}

void MainWindow::clear()
{
    if(waitingForOperand)return;
    ui->display->setText("0");
    waitingForOperand=true;
}

void MainWindow::clearAll()
{
    ui->display->setText("0");
    sumInMemory=0.0;
    sumSoFar=0.0;
    factorSoFar=0.0;
    pandingAdditiveOperator.clear();
    pandingMultiplicationOperator.clear();
    waitingForOperand=true;
}

void MainWindow::clearMemory()
{
    sumInMemory=0.0;
}

void MainWindow::readMemory()
{
    ui->display->setText(QString::number(sumInMemory));
    waitingForOperand=true;
}

void MainWindow::setMemory()
{
    on_equalButton_clicked();
    sumInMemory=ui->display->text().toDouble();
}

void MainWindow::addToMemory()
{
    on_equalButton_clicked();
    sumInMemory+=ui->display->text().toDouble();
}

void MainWindow::on_additiveButton_clicked()
{
    QToolButton *clickedButton=qobject_cast<QToolButton *>(sender());
    QString clickedOperator=clickedButton->text();
    double operand=ui->display->text().toDouble();

    if(!pandingMultiplicationOperator.isEmpty()){
        if(!Calculate(operand,pandingMultiplicationOperator))
        {
            abortOperation();
            return;
        }
    ui->display->setText(QString::number(factorSoFar));
    operand=factorSoFar;
    factorSoFar=0.0;
    pandingMultiplicationOperator.clear();
    }

    if(!pandingAdditiveOperator.isEmpty()){
        if(!Calculate(operand,pandingAdditiveOperator))
        {
            abortOperation();
            return;
        }
    ui->display->setText(QString::number(sumSoFar));
    }
    else
    {
        sumSoFar=operand;
    }

    pandingAdditiveOperator=clickedOperator;
    waitingForOperand=true;
}

void MainWindow::on_multiplicationButton_clicked()
{
    QToolButton *clickedButton=qobject_cast<QToolButton *>(sender());
    QString clickedOperator=clickedButton->text();
    double operand=ui->display->text().toDouble();

    if(!pandingMultiplicationOperator.isEmpty())
    {
        if(!Calculate(operand,pandingMultiplicationOperator))
        {
            abortOperation();
            return;
        }
        ui->display->setText(QString::number(factorSoFar));
    }
    else
    {
        factorSoFar=operand;
    }

    pandingMultiplicationOperator=clickedOperator;
    waitingForOperand=true;
}

void MainWindow::on_pointButtom_clicked()
{
    if(waitingForOperand)
        ui->display->setText("0");
    if(!ui->display->text().contains('.'))
        ui->display->setText(ui->display->text()+".");
    waitingForOperand=false;
}

void MainWindow::on_changeSignButton_clicked()
{
    QString text=ui->display->text();
    double value=text.toDouble();

    if(value>0.0){
        text.prepend('-');
    }else if (value<0.0) {
        text.remove(0,1);
    }
    ui->display->setText(text);
}

void MainWindow::on_equalButton_clicked()
{
    double operand=ui->display->text().toDouble();

    if(!pandingMultiplicationOperator.isEmpty())
    {
        if(!Calculate(operand,pandingMultiplicationOperator))
        {
            abortOperation();
            return;
        }
        operand=factorSoFar;
        factorSoFar=0.0;
        pandingMultiplicationOperator.clear();
    }

    if(!pandingAdditiveOperator.isEmpty())
    {
        if(!Calculate(operand,pandingAdditiveOperator))
        {
            abortOperation();
            return;
        }
        pandingAdditiveOperator.clear();
    }
    else
    {
        sumSoFar=operand;
    }

    ui->display->setText(QString::number(sumSoFar));
    sumSoFar=0.0;
    waitingForOperand=true;
}

void MainWindow::on_unaryButton_clicked()
{
    QToolButton *clickedButton=qobject_cast<QToolButton *>(sender());
    QString clickedOperator=clickedButton->text();
    double operand=ui->display->text().toDouble();
    double result=0.0;

    if(clickedOperator == tr("Sqrt"))
    {
        if(operand<0){abortOperation();return;}
        result=std::sqrt(operand);
    }
    else if(clickedOperator == tr("x\302\262"))
    {
        result=std::pow(operand,2.0);
    }
    else if(clickedOperator == tr("1/x"))
    {
        if(operand==0.0){abortOperation();return;}
        result=1.0/operand;
    }

    ui->display->setText(QString::number(result));
    waitingForOperand=true;
}

bool MainWindow::Calculate(double RightOperand, const QString &pandingOperator)
{
    if(pandingOperator==tr("+"))
    {
        sumSoFar+=RightOperand;
    }
    else if(pandingOperator==tr("-"))
    {
        sumSoFar-=RightOperand;
    }
    else if(pandingOperator==tr("\303\227"))
    {
        factorSoFar*=RightOperand;
    }
    else if(pandingOperator==tr("\303\267"))
    {
        if(RightOperand==0.0)
            return false;
    factorSoFar/=RightOperand;
    }
    return true;
}

void MainWindow::abortOperation()
{
    clearAll();
    ui->display->setText(tr("####"));
}
