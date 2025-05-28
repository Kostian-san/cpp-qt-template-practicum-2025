#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <cmath>

#include <optional>

using namespace std::literals;

#include "calculator.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

}

MainWindow::~MainWindow() {
    delete ui;
}

// Методы для изменения текста:
void MainWindow::SetInputText(const std::string &text) {
    ui->l_result->setStyleSheet(""); // восстанавливает цвет шрифта
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string &text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string &text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string &text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (!key.has_value()) {
        ui->tb_extra->setText("");
        ui->tb_extra->hide();
    } else {
        ui->tb_extra->show();
        ui->tb_extra->setText(QString::fromStdString(key.value()));
    }
}

void MainWindow::on_pushButton_12_clicked() { // обрабатываем клик по "1" и далее ...
    digitKeyCallback_(1);
}

void MainWindow::on_pushButton_15_clicked() {
    digitKeyCallback_(2);
}

void MainWindow::on_pushButton_18_clicked() {
    digitKeyCallback_(3);
}

void MainWindow::on_pushButton_11_clicked() {
    digitKeyCallback_(4);
}

void MainWindow::on_pushButton_14_clicked() {
    digitKeyCallback_(5);
}

void MainWindow::on_pushButton_17_clicked() {
    digitKeyCallback_(6);
}

void MainWindow::on_pushButton_8_clicked() {
    digitKeyCallback_(7);
}

void MainWindow::on_pushButton_9_clicked() {
    digitKeyCallback_(8);
}

void MainWindow::on_pushButton_10_clicked() {
    digitKeyCallback_(9);
}

void MainWindow::on_pushButton_16_clicked() {
    digitKeyCallback_(0);
}


void MainWindow::on_pushButton_21_clicked() { // обрабатываем клик по "+"
    ProcessOperationKeyCallback_(Operation::ADDITION);
}

void MainWindow::on_pushButton_22_clicked() { //"-"
    ProcessOperationKeyCallback_(Operation::SUBTRACTION);
}

void MainWindow::on_pushButton_20_clicked() { // "*"
    ProcessOperationKeyCallback_(Operation::MULTIPLICATION);
}

void MainWindow::on_pushButton_7_clicked() { // "/"
    ProcessOperationKeyCallback_(Operation::DIVISION);
}

void MainWindow::on_pushButton_3_clicked() { // "^"
    ProcessOperationKeyCallback_(Operation::POWER);
}

// СМЕНА ЗНАКА ЧИСЛА
void MainWindow::on_pushButton_6_clicked()
{
    ProcessControlKeyCallback_(ControlKey::PLUS_MINUS);
}

// НАЖАТИЕ кнопки "C"
void MainWindow::on_pushButton_5_clicked()
{
    ProcessControlKeyCallback_(ControlKey::CLEAR);
}

// ОТРАБОТКА клика по знаку "="
void MainWindow::on_pushButton_23_clicked() {
    ProcessControlKeyCallback_(ControlKey::EQUALS);
}

// кнопка удаления знака
void MainWindow::on_pushButton_19_clicked() {
    ProcessControlKeyCallback_(ControlKey::BACKSPACE);
}

// сохранение числа в память
void MainWindow::on_pushButton_4_clicked() {
    ProcessControlKeyCallback_(ControlKey::MEM_SAVE);
}

// вывод числа, содержащегося в памяти
void MainWindow::on_pushButton_2_clicked() {
    ProcessControlKeyCallback_(ControlKey::MEM_LOAD);
}

// очистка памяти
void MainWindow::on_pushButton_1_clicked(){
    ProcessControlKeyCallback_(ControlKey::MEM_CLEAR);
}

void MainWindow::on_tb_extra_clicked() {
    ProcessControlKeyCallback_(ControlKey::EXTRA_KEY);
}

void MainWindow::on_cmb_controller_currentTextChanged(const QString &arg1) {
    if (arg1 == "int") {
        ui->tb_extra->hide();
        ControllerCallback_(ControllerType::INT);
    }
    if (arg1 == "double") {
        ui->tb_extra->show();
        ControllerCallback_(ControllerType::DOUBLE);
    }
    if (arg1 == "int64_t") {
        ui->tb_extra->hide();
        ControllerCallback_(ControllerType::INT64_T);
    }
    if (arg1 == "uint8_t") {
        ui->tb_extra->hide();
        ControllerCallback_(ControllerType::UINT8_T);
    }
    if (arg1 == "size_t") {
        ui->tb_extra->hide();
        ControllerCallback_(ControllerType::SIZE_T);
    }
    if (arg1 == "float") {
        ui->tb_extra->show();
        ControllerCallback_(ControllerType::FLOAT);
    }
    if (arg1 == "Rational") {
        ui->tb_extra->show();
        ControllerCallback_(ControllerType::RATIONAL);
    }

    qDebug() << "type не распознан";
}
