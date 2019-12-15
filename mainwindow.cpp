#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *pMainWidget = new QWidget();
    this->setCentralWidget( pMainWidget );

    QVBoxLayout *pMainLayout = new QVBoxLayout();
    pMainWidget->setLayout( pMainLayout );
    pMainLayout->addLayout( createHeaderLayout() );
    pMainLayout->addLayout( createInOutLayout() );
    pMainLayout->addLayout( createKeypadLayout() );
}

MainWindow::~MainWindow()
{
}

QPushButton *MainWindow::createButton(const QString &str)
{
    QPushButton *pButton = new QPushButton(str);
    connect(pButton, &QPushButton::clicked, this, &MainWindow::slotNumber);
    return pButton;
}

QLayout *MainWindow::createHeaderLayout()
{
    QLabel *pLblIcon = new QLabel("Вместо иконки");
    QLabel *pLblName = new QLabel("Калькулятор счисления");
    QLabel *pLblSetting = new QLabel("Настройки");

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget( pLblIcon );
    headerLayout->addWidget( pLblName );
    headerLayout->addWidget( pLblSetting );

    return headerLayout;
}

QLayout *MainWindow::createInOutLayout()
{
    QVBoxLayout *pInOutLayout = new QVBoxLayout();
    pInOutLayout->addLayout( createLineEditLayout() ); // строка ввода данных и кнопка Enter
    pInOutLayout->addLayout( createChoiceLayout() ); // выбор сс

    return pInOutLayout;
}

QLayout *MainWindow::createLineEditLayout()
{
    m_pLine = new QLineEdit("101");
    connect(m_pLine, &QLineEdit::returnPressed, this, &MainWindow::slotEnter);

    QPushButton *pBtn = new QPushButton("Enter");
    connect(pBtn, &QPushButton::clicked, this, &MainWindow::slotEnter);

    QHBoxLayout *pInLayout = new QHBoxLayout();
    pInLayout->addWidget( m_pLine );
    pInLayout->addWidget( pBtn );

    return pInLayout;
}

QLayout *MainWindow::createChoiceLayout()
{
    QStringList numberSystem;
//    numberSystem << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10";   // << "11" << "12" << "13" << "14" << "15" << "16";
    numberSystem << "2" << "8" << "10";

    QComboBox *pComboBox1 = new QComboBox();
    pComboBox1->addItems( numberSystem );
    m_SS1 = pComboBox1->currentText().toInt();

    connect(pComboBox1, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotSS1);

    QComboBox *pComboBox2 = new QComboBox();
    pComboBox2->addItems( numberSystem );
    m_SS2 = pComboBox2->currentText().toInt();

    connect(pComboBox2, QOverload<const QString &>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotSS2);

//    QPixmap pix;
//    QLabel *pPix = new QLabel();

//    if (pix.load(":/pixes/pix1.png"))
//        pPix->setPixmap(pix);
//    qWarning() << "Беда. Картинка не загрузилась ((";

    QHBoxLayout *pChoiceLayout = new QHBoxLayout();
    pChoiceLayout->addWidget( pComboBox1 );
//    pChoiceLayout->addWidget( pPix );
    pChoiceLayout->addWidget( pComboBox2 );

    return pChoiceLayout;
}

QLayout *MainWindow::createKeypadLayout()
{
    QString aButton[5][4] = {
        {"0", "A", "B", "C",},
        {"1", "2", "3", "D",},
        {"4", "5", "6", "E",},
        {"7", "8", "9", "F",},
    };

    QGridLayout *pKeypadLayout = new QGridLayout;
    QPushButton *pCE = new QPushButton("CE");
    connect(pCE, &QPushButton::clicked, this, &MainWindow::slotCE);
    QPushButton *pDel = new QPushButton("del");
    connect(pDel, &QPushButton::clicked, this, &MainWindow::slotNumDel);

    pKeypadLayout->addWidget( m_pAnswer, 0,0 );
    pKeypadLayout->addWidget( pCE, 0,2 );
    pKeypadLayout->addWidget( pDel, 0,3 );

    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            pKeypadLayout->addWidget( createButton(aButton[i][j]), i+1,j );
        }
    }

    return pKeypadLayout;
}





void MainWindow::slotEnter()
{
    QString numberStr = m_pLine->text();

    bool ok;
    auto number{ numberStr.toInt(&ok, m_SS1) };

    if( ok )
        m_pAnswer->setText( QString::number(number, m_SS2) );
    else
       qWarning() << "slotEnter Ошибка приведения типа к int";
}

void MainWindow::slotNumber()
{
    QObject *btn = sender();
    QPushButton * pushButton = qobject_cast<QPushButton *>( btn );
    QString number = pushButton->text();
    m_pLine->setText( m_pLine->text() + number );
}

void MainWindow::slotNumDel()
{
    QString delText = m_pLine->text();
    delText.chop(1);
    m_pLine->setText( delText );
}

void MainWindow::slotCE()
{
    m_pLine->setText("");
}

void MainWindow::slotSS1(const QString &text)
{
    m_SS1 = text.toInt();
}

void MainWindow::slotSS2(const QString &text)
{
    m_SS2 = text.toInt();
}


// возможность работы с дробями ;  показывать решение
