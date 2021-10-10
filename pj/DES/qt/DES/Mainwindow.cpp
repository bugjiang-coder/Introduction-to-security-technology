#include "Mainwindow.h"
#include "ui_mainwindow.h"
#include "DES.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("DES加解密程序");
}

void MainWindow::encrypt(QString originFile, QString keyStr, QString encryptedFile){

        int cnt = 0 , i=0;
        char originBlock[8], encryptedBlock[8], keyBlock[8];
        char key[64];
        char keys[16][48];


        QFile origin(originFile);
        if(!origin.open(QIODevice::ReadOnly))
            return;

        QFile encrypted(encryptedFile);
        if(!encrypted.open(QIODevice::WriteOnly))
            return;


        char * temp = keyStr.toLatin1().data();
        for(i = 0;i<8;++i)
            keyBlock[i] = temp[i];

        tool.Char8ToBit64(keyBlock, key);
        tool.initEncryptKey(key, keys);

        while (!origin.atEnd())
        {
            if ((cnt = origin.read(originBlock, 8)) == 8)
            {
                tool.DES_Encrypt(originBlock, encryptedBlock, keys);
                encrypted.write(encryptedBlock,8);
            }
        }

        if (cnt > 0)
        {
            for(i =cnt;i<7;++i)
                originBlock[i] = 0;
            originBlock[7] = 8 - cnt;
            tool.DES_Encrypt(originBlock, encryptedBlock, keys);
            encrypted.write(encryptedBlock,8);
        }

        origin.close();
        encrypted.close();

}



void MainWindow::decrypt(QString originFile, QString keyStr, QString decryptedFile){
        int cnt = 0, fileLen, i = 0;
        char originBlock[8], decryptedBlock[8], keyBlock[8];
        char key[64];
        char keys[16][48];

        QFile origin(originFile);
        if(!origin.open(QIODevice::ReadOnly))
            return;

        QFile decrypted(decryptedFile);
        if(!decrypted.open(QIODevice::WriteOnly))
            return;

        char * temp = keyStr.toLatin1().data();
        for(i = 0;i<8;++i)
            keyBlock[i] = temp[i];

        tool.Char8ToBit64(keyBlock, key);
        tool.initDecryptKey(key, keys);


        fileLen = origin.size();

        while (1)
        {
            origin.read(originBlock,  8);
            tool.DES_Decrypt(originBlock, decryptedBlock, keys);
            cnt += 8;
            if (cnt < fileLen)
                decrypted.write(decryptedBlock, 8);
            else
                break;
        }

        if (decryptedBlock[7] < 8)
        {
            for (i = 8 - decryptedBlock[7]; i < 7; ++i)
            {
                if (decryptedBlock[i] != 0)
                {
                    break;
                }
            }
        }
        if (i == 7)
        {
            decrypted.write(decryptedBlock, 8 - decryptedBlock[7]);
        }
        else
        {
            decrypted.write(decryptedBlock, 8);
        }

        origin.close();
        decrypted.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_en_select_btn_clicked()
{
    en_file =  QFileDialog::getOpenFileName(this,"选择加密文件","./");
    ui->lineEdit->setText(en_file);
}

void MainWindow::on_de_select_btn_clicked()
{
    de_file =  QFileDialog::getOpenFileName(this,"选择解密文件","./");
    ui->lineEdit_2->setText(de_file);
}

void MainWindow::on_en_btn_clicked()
{
    en_file = ui->lineEdit->text();
    QFile file(en_file);     //构建文件对象 对文件做相关操作
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"错误","文件打开失败");
        return;
    }
    file.close();

    QString out_filename =  QFileDialog::getSaveFileName(this,"文件加密到","./encrypt_output");

    if(!out_filename.size())
        return;

    QString key = ui->key->text();
    QString K;
    if(key.size() > 8){
        QMessageBox::warning(this,"警告","密钥只会取前8字节");
        for(int i = 0;i<8;++i){
            K[i] = key[i];
        }

    }
    else{
        for(int i = 0;i<key.size();++i)
            K[i] = key[i];


        if(key.size() < 8){
            QMessageBox::warning(this,"警告","密钥会自行补充至8字节");
            for(int i = key.size();i<8;++i)
                K[i] = 'A'; //自动补充不足密钥
        }
    }
    MainWindow::encrypt(en_file,K,out_filename);

}

void MainWindow::on_pushButton_2_clicked()
{
    de_file = ui->lineEdit_2->text();
    QFile file(de_file);     //构建文件对象 对文件做相关操作
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"错误","文件打开失败");
        return;
    }
    file.close();

    QString out_filename =  QFileDialog::getSaveFileName(this,"文件解密到","./decrypt_output");
    if(!out_filename.size())
        return;

    QString key = ui->key->text();
    QString K;
    if(key.size() > 8){
        QMessageBox::warning(this,"警告","密钥只会取前8字节");
        for(int i = 0;i<8;++i){
            K[i] = key[i];
        }

    }
    else{
        for(int i = 0;i<key.size();++i)
            K[i] = key[i];


        if(key.size() < 8){
            QMessageBox::warning(this,"警告","密钥会自行补充至8字节");
            for(int i = key.size();i<8;++i)
                K[i] = 'A'; //自动补充不足密钥
        }
    }


    MainWindow::decrypt(de_file,K,out_filename);
}
