#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QtDebug>


class MainWindow : public QMainWindow
{
    Q_OBJECT    

    QLineEdit *m_pLine = nullptr;
    QLabel *m_pAnswer = new QLabel("тут будет ответ");

    int m_SS1 = 0;
    int m_SS2 = 0;

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
    void slotSS1(const QString &text);
    void slotSS2(const QString &text);




};
#endif // MAINWINDOW_H
