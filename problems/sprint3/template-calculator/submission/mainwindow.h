#pragma once

#include "calculator.h"
#include "enums.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    //Новые методы вывода текста
    void SetInputText(const std::string &text);

    void SetErrorText(const std::string &text);

    void SetFormulaText(const std::string &text);

    void SetMemText(const std::string &text);

    void SetExtraKey(const std::optional<std::string> &key);

    void UpdateExtraButtonVisibility(ControllerType type);


    // методы для установки колбэков в объект
    void SetDigitKeyCallback(std::function<void(int key)> cb) {
        digitKeyCallback_ = cb;
    }

    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
        ProcessOperationKeyCallback_ = cb;
    }

    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
        ProcessControlKeyCallback_ = cb;
    }

    void SetControllerCallback(std::function<void(ControllerType controller)> cb) {
        ControllerCallback_ = cb;
    }


private slots:

    void on_pushButton_12_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_1_clicked();

    void on_tb_extra_clicked();

    void on_cmb_controller_currentTextChanged(const QString &arg1);

private:

    Ui::MainWindow* ui;

    // поля для сохранения колбэков:
    std::function<void(int key)> digitKeyCallback_;
    std::function<void(Operation key)> ProcessOperationKeyCallback_;
    std::function<void(ControlKey key)> ProcessControlKeyCallback_;
    std::function<void(ControllerType controller)> ControllerCallback_;
};


