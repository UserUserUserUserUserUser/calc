#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLabel>
#include <QtDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QPixmap>
#include <QPushButton>


class MainWindow : public QMainWindow
{
    Q_OBJECT    

    QLineEdit *m_pLine = nullptr;
    QLabel *m_pAnswer = new QLabel("тут будет ответ");

    int m_SS1 = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPushButton *createButton(const QString& str);


private:
    QLayout *createHeaderLayout();
    QLayout *createInOutLayout();
    QLayout *createLineEditLayout();
    QLayout *createChoiceLayout();
    QLayout *createKeypadLayout();


private slots:
    void slotEnter();
    void slotNumber();
    void slotNumDel();
    void slotCE();


};
#endif // MAINWINDOW_H
