#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->openPopupButton, &QPushButton::clicked, this, [this] {
        auto* popup = new QDialog(this);
        popup->setObjectName("popup");
        auto* label = new QLabel("Popup!", popup);
        label->setFont(ui->fontComboBox->currentFont());
        popup->show();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}
