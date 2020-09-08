#include "novaembed.h"
#include "ui_novaembed.h"
#include <QFileDialog>
#include <QTreeView>
#include <QDebug>
#include <QDir>
#include <QStatusBar>
#include <QMessageBox>
#include <QPixmap>
#include <QSettings>
#include <QUrl>
#include <QtCore>
#include <QDesktopServices>
//#include <QHostInfo>
#include <QDirIterator>
#include <QMovie>
#include <iostream>


extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString CfgBitDefaultValue;
extern  QString _Board_comboBox;
extern  QString Last_M9_BSPFactoryFile;
extern  QString LVDSVideo;
extern  QString Quad;
extern  QString instpath;
extern  QString Kernel;
extern  QString system_editor;

QString M9_GPIO2_B1_comboBox="GPIO2_B1";
QString M9_GPIO2_B2_comboBox="GPIO2_B2";
QString M9_GPIO1_A0_comboBox="GPIO1_A0";
QString M9_GPIO1_A1_comboBox="GPIO1_A1";
QString M9_GPIO1_A3_comboBox="GPIO1_A3";
QString M9_GPIO1_A4_comboBox="GPIO1_A4";
QString M9_GPIO1_B0_comboBox="GPIO1_B0";
QString M9_GPIO1_A7_comboBox="GPIO1_A7";
QString M9_GPIO1_B1_comboBox="GPIO1_B1";
QString M9_GPIO4_A4_comboBox="GPIO4_A4";
QString M9_GPIO4_A5_comboBox="GPIO4_A5";
QString M9_GPIO4_A3_comboBox="GPIO4_A3";
QString M9_GPIO4_A6_comboBox="GPIO4_A6";
QString M9_GPIO3_D4_comboBox="GPIO3_D4";

QString M9_GPIO4_C0_comboBox="GPIO4_C0";
QString M9_GPIO4_C1_comboBox="GPIO4_C1";
QString M9_GPIO1_C2_comboBox="GPIO1_C2";
QString M9_GPIO1_C6_comboBox="GPIO1_C6";
QString M9_GPIO1_C7_comboBox="GPIO1_C7";
QString M9_GPIO1_D0_comboBox="GPIO1_D0";
QString M9_GPIO1_B2_comboBox="GPIO1_B2";
QString M9_GPIO4_C5_comboBox="GPIO4_C5";
QString M9_GPIO4_A0_comboBox="GPIO4_A0";
QString M9_GPIO4_A7_comboBox="GPIO4_A7";
QString M9_GPIO3_D5_comboBox="GPIO3_D5";
QString M9_GPIO3_D6_comboBox="GPIO3_D6";

QString M9_I2C6Speed="100000";
QString M9_HDMI_checkBox;
QString M9_eDPI_checkBox;
QString M9_DSI_checkBox;
QString M9_SPDIF_checkBox;
QString M9_PCIe_checkBox;
QString M9_CAM1_checkBox;
QString M9_CAM2_checkBox;

QString M9_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}

void NOVAembed::M9_load_BSPF_File(QString fileName)
{
QString strKeyFunc("M9_IOMUX/");

    on_M9_Clear_pushButton_clicked();
    QSettings *func_settings = new QSettings( fileName, QSettings::IniFormat );
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_SPI1_checkBox") == "true" )
    {
        on_M9_SPI1_checkBox_toggled(true);
        if ( M9_getvalue(strKeyFunc, func_settings , "M9_SPIdev_checkBox") == "false" )
            ui->M9_SPIdev_checkBox->setChecked(false);
        else
            ui->M9_SPIdev_checkBox->setChecked(true);
        on_M9_I2C6_checkBox_toggled(true);
    }
    else
    {
        ui->M9_SPIdev_checkBox->setChecked(false);
        ui->M9_SPIdev_checkBox->setEnabled(false);
        on_M9_SPI1_checkBox_toggled(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_GPIO2_B1_comboBox") == "SDA6" )
    {
        on_M9_I2C6_checkBox_toggled(true);
        QString speed = M9_getvalue(strKeyFunc, func_settings , "M9_I2C2Speed");
        ui->M9_I2C6Speed_lineEdit->setText(M9_getvalue(strKeyFunc, func_settings , "M9_I2C2Speed"));
    }
    else
        on_M9_I2C6_checkBox_toggled(false);

    if ( M9_getvalue(strKeyFunc, func_settings , "M9_GPIO4_C0_comboBox") == "SDA3" )
    {
        on_M9_I2C3_checkBox_toggled(true);
        QString speed = M9_getvalue(strKeyFunc, func_settings , "M9_I2C3Speed");
        ui->M9_I2C3Speed_lineEdit->setText(M9_getvalue(strKeyFunc, func_settings , "M9_I2C3Speed"));
    }
    else
        on_M9_I2C3_checkBox_toggled(false);

    if ( M9_getvalue(strKeyFunc, func_settings , "M9_GPIO1_B0_comboBox") == "UART4_TX" )
    {
        ui->M9_UART4_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_UART4_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_GPIO4_C0_comboBox") == "UART2_TX" )
    {
        ui->M9_UART2_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_UART2_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_HDMI_checkBox") == "true" )
    {
        ui->M9_HDMI_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_HDMI_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_eDP_checkBox") == "true" )
    {
        ui->M9_eDP_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_eDP_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_DSI_checkBox") == "true" )
    {
        ui->M9_DSI_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_DSI_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_SPDIF_checkBox") == "true" )
    {
        ui->M9_SPDIF_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_SPDIF_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_PCIE_checkBox") == "true" )
    {
        ui->M9_PCIE_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_PCIE_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_Cam1_checkBox") == "true" )
    {
        ui->M9_Cam1_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_Cam1_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_Cam2_checkBox") == "true" )
    {
        ui->M9_Cam2_checkBox->setChecked(true);
    }
    else
    {
        ui->M9_Cam2_checkBox->setChecked(false);
    }
    if ( M9_getvalue(strKeyFunc, func_settings , "M9_PCM_checkBox") == "true" )
    {
        ui->M9_PCM_checkBox->setChecked(true);
        on_M9_PCM_checkBox_toggled(true);
    }
    else
    {
        ui->M9_PCM_checkBox->setChecked(false);
        on_M9_PCM_checkBox_toggled(false);
    }

}

void NOVAembed::M9_save_helper(QString fileName)
{
    QFileInfo fin(fileName);
    QString bspfbase = fin.baseName();
    QString fullpathname = "";

    fullpathname = instpath+"/DtbUserWorkArea/M9Class_bspf/"+ bspfbase+".bspf";

    QFile file(fullpathname);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file "),file.errorString());
        return;
    }

    QTextStream out(&file);
    out << QString("[M9_IOMUX]\n");

    out << QString("M9_GPIO2_B1_comboBox="+M9_GPIO2_B1_comboBox+"\n");;
    out << QString("M9_GPIO2_B2_comboBox="+M9_GPIO2_B2_comboBox+"\n");;
    out << QString("M9_GPIO1_A0_comboBox="+M9_GPIO1_A0_comboBox+"\n");;
    out << QString("M9_GPIO1_A1_comboBox="+M9_GPIO1_A1_comboBox+"\n");;
    out << QString("M9_GPIO1_A3_comboBox="+M9_GPIO1_A3_comboBox+"\n");;
    out << QString("M9_GPIO1_A4_comboBox="+M9_GPIO1_A4_comboBox+"\n");;
    out << QString("M9_GPIO1_B0_comboBox="+M9_GPIO1_B0_comboBox+"\n");;
    out << QString("M9_GPIO1_A7_comboBox="+M9_GPIO1_A7_comboBox+"\n");;
    out << QString("M9_GPIO1_B1_comboBox="+M9_GPIO1_B1_comboBox+"\n");;
    out << QString("M9_GPIO4_A4_comboBox="+M9_GPIO4_A4_comboBox+"\n");;
    out << QString("M9_GPIO4_A5_comboBox="+M9_GPIO4_A5_comboBox+"\n");;
    out << QString("M9_GPIO4_A3_comboBox="+M9_GPIO4_A3_comboBox+"\n");;
    out << QString("M9_GPIO4_A6_comboBox="+M9_GPIO4_A6_comboBox+"\n");;
    out << QString("M9_GPIO3_D4_comboBox="+M9_GPIO3_D4_comboBox+"\n");;
    out << QString("M9_GPIO4_C0_comboBox="+M9_GPIO4_C0_comboBox+"\n");;
    out << QString("M9_GPIO4_C1_comboBox="+M9_GPIO4_C1_comboBox+"\n");;
    out << QString("M9_GPIO1_C2_comboBox="+M9_GPIO1_C2_comboBox+"\n");;
    out << QString("M9_GPIO1_C6_comboBox="+M9_GPIO1_C6_comboBox+"\n");;
    out << QString("M9_GPIO1_C7_comboBox="+M9_GPIO1_C7_comboBox+"\n");;
    out << QString("M9_GPIO1_D0_comboBox="+M9_GPIO1_D0_comboBox+"\n");;
    out << QString("M9_GPIO1_B2_comboBox="+M9_GPIO1_B2_comboBox+"\n");;
    out << QString("M9_GPIO4_C5_comboBox="+M9_GPIO4_C5_comboBox+"\n");;
    out << QString("M9_GPIO4_A0_comboBox="+M9_GPIO4_A0_comboBox+"\n");;
    out << QString("M9_GPIO4_A7_comboBox="+M9_GPIO4_A7_comboBox+"\n");;
    out << QString("M9_GPIO3_D5_comboBox="+M9_GPIO3_D5_comboBox+"\n");;
    out << QString("M9_GPIO3_D6_comboBox="+M9_GPIO3_D6_comboBox+"\n");;

    if ( ui->M9_I2C6Speed_lineEdit->text().isEmpty() )
        ui->M9_I2C6Speed_lineEdit->setText("100000");
    M9_I2C6Speed = ui->M9_I2C6Speed_lineEdit->text();
    out << QString("M9_I2C2Speed="+M9_I2C6Speed+"\n");
    if ( ui->M9_HDMI_checkBox->isChecked() )
        out << QString("M9_HDMI_checkBox=true\n");
    else
        out << QString("M9_HDMI_checkBox=false\n");
    if ( ui->M9_eDP_checkBox->isChecked() )
        out << QString("M9_eDP_checkBox=true\n");
    else
        out << QString("M9_eDP_checkBox=false\n");
    if ( ui->M9_DSI_checkBox->isChecked() )
        out << QString("M9_DSI_checkBox=true\n");
    else
        out << QString("M9_DSI_checkBox=false\n");
    if ( ui->M9_SPDIF_checkBox->isChecked() )
        out << QString("M9_SPDIF_checkBox=true\n");
    else
        out << QString("M9_SPDIF_checkBox=false\n");
    if ( ui->M9_PCIE_checkBox->isChecked() )
        out << QString("M9_PCIE_checkBox=true\n");
    else
        out << QString("M9_PCIE_checkBox=false\n");
    if ( ui->M9_Cam1_checkBox->isChecked() )
        out << QString("M9_Cam1_checkBox=true\n");
    else
        out << QString("M9_Cam1_checkBox=false\n");
    if ( ui->M9_Cam2_checkBox->isChecked() )
        out << QString("M9_Cam2_checkBox=true\n");
    else
        out << QString("M9_Cam2_checkBox=false\n");

    if ( ui->M9_SPI1_checkBox->isChecked() )
    {
        out << QString("M9_SPI1_checkBox=true\n");
        if ( ui->M9_SPIdev_checkBox->isChecked() )
            out << QString("M9_SPIdev_checkBox=true\n");
        else
            out << QString("M9_SPIdev_checkBox=false\n");
    }
    else
        out << QString("M9_SPI1_checkBox=false\n");

    if ( ui->M9_PCM_checkBox->isChecked() )
        out << QString("M9_PCM_checkBox=true\n");
    else
        out << QString("M9_PCM_checkBox=false\n");

    out << QString("\n[M9_CONF]\n");
    file.close();
    update_status_bar("File "+Last_M9_BSPFactoryFile+" saved");
    Last_M9_BSPFactoryFile = bspfbase;
    storeNOVAembed_ini();
}

void NOVAembed::on_M9_Clear_pushButton_clicked()
{
    M9_GPIO2_B1_comboBox="GPIO2_B1";
    M9_GPIO2_B2_comboBox="GPIO2_B2";
    M9_GPIO1_A0_comboBox="GPIO1_A0";
    M9_GPIO1_A1_comboBox="GPIO1_A1";
    M9_GPIO1_A3_comboBox="GPIO1_A3";
    M9_GPIO1_A4_comboBox="GPIO1_A4";
    M9_GPIO1_B0_comboBox="GPIO1_B0";
    M9_GPIO1_A7_comboBox="GPIO1_A7";
    M9_GPIO1_B1_comboBox="GPIO1_B1";
    M9_GPIO4_A4_comboBox="GPIO4_A4";
    M9_GPIO4_A5_comboBox="GPIO4_A5";
    M9_GPIO4_A3_comboBox="GPIO4_A3";
    M9_GPIO4_A6_comboBox="GPIO4_A6";
    M9_GPIO3_D4_comboBox="GPIO3_D4";

    M9_GPIO4_C0_comboBox="GPIO4_C0";
    M9_GPIO4_C1_comboBox="GPIO4_C1";
    M9_GPIO1_C2_comboBox="GPIO1_C2";
    M9_GPIO1_C6_comboBox="GPIO1_C6";
    M9_GPIO1_C7_comboBox="GPIO1_C7";
    M9_GPIO1_D0_comboBox="GPIO1_D0";
    M9_GPIO1_B2_comboBox="GPIO1_B2";
    M9_GPIO4_C5_comboBox="GPIO4_C5";
    M9_GPIO4_A0_comboBox="GPIO4_A0";
    M9_GPIO4_A7_comboBox="GPIO4_A7";
    M9_GPIO3_D5_comboBox="GPIO3_D5";
    M9_GPIO3_D6_comboBox="GPIO3_D6";

    ui->M9_I2C6_checkBox->setChecked(false);
    ui->M9_UART2_checkBox->setChecked(false);
    ui->M9_I2C6Speed_lineEdit->setText("100000");
    ui->M9_I2C6Speed_lineEdit->setEnabled(false);
    ui->M9_HDMI_checkBox->setChecked(false);
    ui->M9_eDP_checkBox->setChecked(false);
    ui->M9_DSI_checkBox->setChecked(false);
    ui->M9_SPDIF_checkBox->setChecked(false);
    ui->M9_PCIE_checkBox->setChecked(false);
    ui->M9_Cam1_checkBox->setChecked(false);
    ui->M9_Cam2_checkBox->setChecked(false);
    ui->M9_SPI1_checkBox->setChecked(false);
    ui->M9_SPIdev_checkBox->setEnabled(false);
    ui->M9_SPIdev_checkBox->setChecked(false);

    on_M9_I2C3_checkBox_toggled(false);
    on_M9_I2C6_checkBox_toggled(false);
    on_M9_SPI1_checkBox_toggled(false);
    on_M9_SPDIF_checkBox_toggled(false);
    on_M9_UART4_checkBox_toggled(false);
    on_M9_UART2_checkBox_toggled(false);
    on_M9_PCM_checkBox_toggled(false);
}


void NOVAembed::on_M9_Load_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), instpath+"/DtbUserWorkArea/M9Class_bspf",tr("BSP Factory Files (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        M9_load_BSPF_File(fileName);
        update_status_bar("File "+Last_M9_BSPFactoryFile+" loaded");
        QFileInfo fi(fileName);
        ui->M9_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->M9_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
    }
}

void NOVAembed::on_M9_Save_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/M9Class_bspf",tr(".bspf (*.bspf)"));
    if ( fileName.isEmpty() )
        return;
    QFileInfo fi(fileName);
    ui->M9_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
    ui->M9_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
    M9_save_helper(fileName);
}

extern      int skip_filesave_on_Generate_pushButton_clicked;
extern      QString FileNameIfSkipped;
extern      int generate_dtb_result;

void NOVAembed::on_M9_Generate_pushButton_clicked()
{
QFile scriptfile("/tmp/script");
QString dtc_file;
QFileInfo fi;

QString ForceClone="CHECK";
    if ( ui->ForceKernelClone_checkBox->isChecked())
        ForceClone="FORCE";

    if ( CheckIfKernelsPresent(ForceClone) == 1 )
    {
        update_status_bar("Kernel "+Kernel+" not present, please download it.");
        return;
    }

    dtc_file= instpath+"/Kernels/"+Kernel.toLatin1()+"/scripts/dtc/dtc";
    QFile dtc_compiler(dtc_file);
    if ( ! dtc_compiler.exists() )
    {
        update_status_bar("dtc executable not present, probably "+Kernel+" has not yet compiled. Please compile it.");
        return;
    }
    if ( skip_filesave_on_Generate_pushButton_clicked == 0)
    {
        // Save .bspf and Generate .dtb
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/M9Class_bspf",tr(".bspf (*.bspf)"));
        if ( fileName.isEmpty() )
            return;
        QFileInfo fiLocal(fileName);
        fi = fiLocal;
        ui->M9_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->M9_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
        M9_save_helper(fileName);
        Last_M9_BSPFactoryFile = fi.baseName();
    }
    else
    {
        QString fileName = FileNameIfSkipped;
        QFileInfo fiLocal(fileName);
        fi = fiLocal;
        M9_save_helper(fileName);
        Last_M9_BSPFactoryFile = fi.baseName();
    }

    update_status_bar("Generating dtb "+Last_M9_BSPFactoryFile+".dtb ...");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    if ( ui->U_EditBeforeGenerate_checkBox->isChecked())
        update_status_bar("User editing dtsi file");

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("[ ! -d "+instpath+"/DtbUserWorkArea ] && mkdir "+instpath+"/DtbUserWorkArea\n");
    out << QString("rm -f "+instpath+"/DtbUserWorkArea/"+Last_M9_BSPFactoryFile+".dtb \n");
    out << QString("cd "+instpath+"/Utils\n");
    out << QString(instpath+"/Qt/NOVAembed/NOVAembed_M9_Parser/bin/Debug/NOVAembed_M9_Parser "+instpath+"/DtbUserWorkArea/M9Class_bspf/"+Last_M9_BSPFactoryFile+".bspf | tee "+instpath+"/Logs/M9_bspf.log\n");
    if ( ui->M9_EditBeforeGenerate_checkBox->isChecked())
        out << QString(system_editor+" "+instpath+"/DtbUserWorkArea/"+Last_M9_BSPFactoryFile+".dts\n");
    out << QString("./user_dtb_compile "+Last_M9_BSPFactoryFile+" M9 "+RK_M9_KERNEL+" | tee -a "+instpath+"/Logs/M9_bspf.log\n");
    out << QString("if [ -f "+instpath+"/DtbUserWorkArea/"+Last_M9_BSPFactoryFile+".dtb ]; then\n");
    out << QString("    rm -f "+instpath+"/Deploy/M9_dtb.dtb\n");
    out << QString("    ln -s "+instpath+"/DtbUserWorkArea/"+Last_M9_BSPFactoryFile+".dtb -t "+instpath+"/Deploy\n");
    out << QString("    mv "+instpath+"/Deploy/"+Last_M9_BSPFactoryFile+".dtb "+instpath+"/Deploy/m9_dtb.dtb\n");
    out << QString("fi\n");
    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar(fi.baseName()+".dtb compiled, dtb is in "+instpath+"/DtbUserWorkArea folder as "+Last_M9_BSPFactoryFile+".dtb");
        NOVAsom_Params_helper();
        generate_dtb_result=0;
    }
    else
    {
        update_status_bar("Error compiling "+fi.baseName()+".dtb");
        generate_dtb_result=1;
    }
}

void NOVAembed::on_M9_ViewDtbCompileLog_pushButton_clicked()
{
    system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/M9_bspf.log");
}

void NOVAembed::on_M9_SPI1_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        M9_GPIO1_B0_comboBox="SPI1_TXD";
        M9_GPIO1_A7_comboBox="SPI1_RXD";
        M9_GPIO1_B1_comboBox="SPI1_CLK";
        M9_GPIO1_B2_comboBox="SPI1_SS0";
        ui->M9_SPI1_checkBox->setChecked(true);
        ui->M9_SPIdev_checkBox->setEnabled(true);
        ui->M9_UART4_checkBox->setEnabled(false);
    }
    else
    {
        M9_GPIO1_B0_comboBox="GPIO1_B0";
        M9_GPIO1_A7_comboBox="GPIO1_A7";
        M9_GPIO1_B1_comboBox="GPIO1_B1";
        M9_GPIO1_B2_comboBox="GPIO1_B2";
        ui->M9_SPI1_checkBox->setChecked(false);
        ui->M9_SPIdev_checkBox->setEnabled(false);
        ui->M9_SPIdev_checkBox->setChecked(false);
        ui->M9_UART4_checkBox->setEnabled(true);
    }
    ui->label_M9_GPIO1_B0->setText(M9_GPIO1_B0_comboBox);
    ui->label_M9_GPIO1_A7->setText(M9_GPIO1_A7_comboBox);
    ui->label_M9_GPIO1_B1->setText(M9_GPIO1_B1_comboBox);
    ui->label_M9_GPIO1_B2->setText(M9_GPIO1_B2_comboBox);
}

void NOVAembed::on_M9_I2C6_checkBox_toggled(bool checked)
{

    if ( checked )
    {
        ui->M9_I2C6_checkBox->setChecked(true);
        ui->M9_I2C6Speed_lineEdit->setEnabled(true);
        M9_GPIO2_B1_comboBox="SDA6";
        M9_GPIO2_B2_comboBox="SCL6";
    }
    else
    {
        ui->M9_I2C6_checkBox->setChecked(false);
        ui->M9_I2C6Speed_lineEdit->setEnabled(false);
        M9_GPIO2_B1_comboBox="GPIO2_B1";
        M9_GPIO2_B2_comboBox="GPIO2_B2";
    }
    ui->label_M9_GPIO2_B1->setText(M9_GPIO2_B1_comboBox);
    ui->label_M9_GPIO2_B2->setText(M9_GPIO2_B2_comboBox);
}

void NOVAembed::on_M9_I2C3_checkBox_toggled(bool checked)
{
    if ( checked == true )
    {
        M9_GPIO4_C0_comboBox="SDA3";
        M9_GPIO4_C1_comboBox="SCL3";
        ui->M9_I2C3Speed_lineEdit->setEnabled(true);
        ui->M9_UART2_checkBox->setEnabled(false);
    }
    else
    {
        M9_GPIO4_C0_comboBox="GPIO4_C0";
        M9_GPIO4_C1_comboBox="GPIO4_C1";
        ui->M9_I2C3Speed_lineEdit->setEnabled(false);
        ui->M9_UART2_checkBox->setEnabled(true);
    }
    ui->label_M9_GPIO4_C0->setText(M9_GPIO4_C0_comboBox);
    ui->label_M9_GPIO4_C1->setText(M9_GPIO4_C1_comboBox);
}
void NOVAembed::on_M9_UART2_checkBox_toggled(bool checked)
{
    if ( checked == true )
    {
        M9_GPIO4_C0_comboBox="UART2_TX";
        M9_GPIO4_C1_comboBox="UART2_RX";
        ui->M9_I2C3Speed_lineEdit->setEnabled(false);
        ui->M9_I2C3_checkBox->setEnabled(false);
    }
    else
    {
        M9_GPIO4_C0_comboBox="GPIO4_C0";
        M9_GPIO4_C1_comboBox="GPIO4_C1";
        ui->M9_I2C3Speed_lineEdit->setEnabled(false);
        ui->M9_I2C3_checkBox->setEnabled(true);
    }
    ui->label_M9_GPIO4_C0->setText(M9_GPIO4_C0_comboBox);
    ui->label_M9_GPIO4_C1->setText(M9_GPIO4_C1_comboBox);
}

void NOVAembed::on_M9_UART4_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        M9_GPIO1_B0_comboBox="UART4_TX";
        M9_GPIO1_A7_comboBox="UART4_RX";
        M9_GPIO1_B1_comboBox="GPIO1_B1";
        M9_GPIO1_B2_comboBox="GPIO1_B2";
        ui->M9_SPI1_checkBox->setEnabled(false);
        ui->M9_SPIdev_checkBox->setEnabled(false);
    }
    else
    {
        M9_GPIO1_B0_comboBox="GPIO1_B0";
        M9_GPIO1_A7_comboBox="GPIO1_A7";
        M9_GPIO1_B1_comboBox="GPIO1_B1";
        M9_GPIO1_B2_comboBox="GPIO1_B2";
        ui->M9_SPI1_checkBox->setEnabled(true);
        ui->M9_SPIdev_checkBox->setEnabled(false);
    }
    ui->label_M9_GPIO1_B0->setText(M9_GPIO1_B0_comboBox);
    ui->label_M9_GPIO1_A7->setText(M9_GPIO1_A7_comboBox);
    ui->label_M9_GPIO1_B1->setText(M9_GPIO1_B1_comboBox);
    ui->label_M9_GPIO1_B2->setText(M9_GPIO1_B2_comboBox);
}

void NOVAembed::on_M9_SPDIF_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        M9_GPIO4_C5_comboBox="SPDIF";
    }
    else
    {
        M9_GPIO4_C5_comboBox="GPIO4_C5";
    }
    ui->label_M9_GPIO4_C5->setText(M9_GPIO4_C5_comboBox);
}

void NOVAembed::on_M9_PCM_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        M9_GPIO4_A4_comboBox="LRCK_RX";
        M9_GPIO4_A5_comboBox="LRCK_TX";
        M9_GPIO4_A3_comboBox="SCLK";
        M9_GPIO4_A6_comboBox="SDI";
        M9_GPIO4_A0_comboBox="CLK";
        M9_GPIO4_A7_comboBox="SDO";
        ui->M9_PCM_checkBox->setChecked(true);
    }
    else
    {
        M9_GPIO4_A4_comboBox="GPIO4_A4";
        M9_GPIO4_A5_comboBox="GPIO4_A5";
        M9_GPIO4_A3_comboBox="GPIO4_A3";
        M9_GPIO4_A6_comboBox="GPIO4_A6";
        M9_GPIO4_A0_comboBox="GPIO4_A0";
        M9_GPIO4_A7_comboBox="GPIO4_A7";
        ui->M9_PCM_checkBox->setChecked(false);
    }
    ui->label_M9_GPIO4_A4->setText(M9_GPIO4_A4_comboBox);
    ui->label_M9_GPIO4_A5->setText(M9_GPIO4_A5_comboBox);
    ui->label_M9_GPIO4_A3->setText(M9_GPIO4_A3_comboBox);
    ui->label_M9_GPIO4_A6->setText(M9_GPIO4_A6_comboBox);
    ui->label_M9_GPIO4_A0->setText(M9_GPIO4_A0_comboBox);
    ui->label_M9_GPIO4_A7->setText(M9_GPIO4_A7_comboBox);
}

void NOVAembed::on_M9_HDMI_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->M9_HDMI_comboBox->setEnabled(true);
    }
    else
    {
        ui->M9_HDMI_comboBox->setEnabled(false);
    }
}

void NOVAembed::on_M9_eDP_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->M9_EDP_comboBox->setEnabled(true);
    }
    else
    {
        ui->M9_EDP_comboBox->setEnabled(false);

    }
}

void NOVAembed::on_M9_DSI_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->M9_DSI_comboBox->setEnabled(true);
    }
    else
    {
        ui->M9_DSI_comboBox->setEnabled(false);

    }
}

