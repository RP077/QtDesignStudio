#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTask();
    void editTask();
    void deleteTask();

private:
    Ui::MainWindow *ui;
    QTableWidget *taskTable;
    QLineEdit *taskTitle;
    QDateEdit *dueDate;
    QComboBox *priorityBox;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;

    void setupUI();
};
#endif // MAINWINDOW_H
