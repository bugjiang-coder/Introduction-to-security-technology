#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include "des.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void encrypt(QString originFile, QString keyStr, QString encryptedFile);
    void decrypt(QString originFile, QString keyStr, QString decryptedFile);
    ~MainWindow();

private slots:


    void on_en_select_btn_clicked();


    void on_de_select_btn_clicked();

    void on_en_btn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QString en_file;
    QString de_file;
    DES tool;

};

#endif // MAINWINDOW_H
