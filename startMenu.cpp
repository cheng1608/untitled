#include "startMenu.h"


StartMenu::StartMenu()
    :magic("magicFire")
{
    QFontDatabase::addApplicationFont(":/font/fusion-pixel-proportional.ttf");
    setFixedSize(1500, 1000);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关垂直滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条
    //按钮样式表
    QFile fileButtonStyle(":/style.qss");
    fileButtonStyle.open(QFile::ReadOnly);
    QString buttonStyle;
    if (fileButtonStyle.isOpen()) {
        buttonStyle = QLatin1String(fileButtonStyle.readAll());
        fileButtonStyle.close();
    }

    //#############################################################################################################################

    QGraphicsScene *pointLogin = new QGraphicsScene(this);
    setScene(pointLogin);

    pointLogin->setSceneRect(0, 0, 1500, 1000);
    pointLogin->addPixmap(QPixmap(":/images/ABackground.png"));

    QLineEdit *accountLineEdit = new QLineEdit();
    QLineEdit *passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    QPushButton *loginButton = new QPushButton("Login");

    QGraphicsProxyWidget *proxyAccountLineEdit = pointLogin->addWidget(accountLineEdit);
    QGraphicsProxyWidget *proxyPasswordLineEdit = pointLogin->addWidget(passwordLineEdit);
    QGraphicsProxyWidget *proxyLoginButton = pointLogin->addWidget(loginButton);

    proxyAccountLineEdit->setGeometry(QRectF(500, 300, 200, 30));
    proxyPasswordLineEdit->setGeometry(QRectF(500, 350, 200, 30));
    proxyLoginButton->setGeometry(QRectF(500, 400, 200, 30));

    connect(this, &StartMenu::loginSuccess , this, &StartMenu::openMainPage);

    connect(loginButton, &QPushButton::clicked, this, [=]() {
        account = accountLineEdit->text();
        QString password = passwordLineEdit->text();

        sendLoginRequest(account, password);
    });


    //##############################################################################################################################

    pointMain = new QGraphicsScene(this);

    pointMain->setSceneRect(0, 0, 1500, 1000);
    pointMain->addPixmap(QPixmap(":/images/ABackground.png"));

    QPushButton *mainStartButton = new QPushButton("start");
    mainStartButton->move(550, 600);
    mainStartButton->resize(100, 50);
    mainStartButton->setStyleSheet(buttonStyle);
    connect(mainStartButton, &QPushButton::clicked, this, [=](){
        sendGetCoinRequest(account);
        openPreparePage();
    });
    pointMain->addWidget(mainStartButton);

    //################################################################################################################################

    pointPrepare = new QGraphicsScene(this);
    pointPrepare->setSceneRect(0,0,1500,1000);
    pointPrepare->addPixmap(QPixmap(":/images/ABackground.png"));

    QPushButton *prepareBackButton = new QPushButton("back");
    pointPrepare->addWidget(prepareBackButton);
    prepareBackButton->move(50, 50);
    prepareBackButton->resize(100, 50);
    prepareBackButton->setStyleSheet(buttonStyle);
    connect(prepareBackButton, &QPushButton::clicked, this, &StartMenu::openMainPage);

    QPushButton *prepareStartButton = new QPushButton("Start Game");
    pointPrepare->addWidget(prepareStartButton);
    prepareStartButton->setStyleSheet(buttonStyle);
    prepareStartButton->resize(220, 110);
    prepareStartButton->move(530, 480);
    connect(prepareStartButton, &QPushButton::clicked, this, [=](){
        emit startGame();//发送开始信号，进入gameEngine
        deleteLater();
    });

    QPushButton *buyMagicFireButton = new QPushButton("magicFire");
    pointPrepare->addWidget(buyMagicFireButton);
    buyMagicFireButton->move(730,600);
    buyMagicFireButton->resize(200, 50);
    buyMagicFireButton->setStyleSheet(buttonStyle);
    connect(buyMagicFireButton, &QPushButton::clicked, this,[=](){
        magic="magicFire";
        int tmpCoinCount=coinCount.toInt();
        tmpCoinCount-=10;
        if(tmpCoinCount<0){
            tmpCoinCount=0;
        }
        coinCount=QString::number(tmpCoinCount);
        sendChangeCoinRequest(account,coinCount);
        updateCoinLabel(coinCount);
    });


    coinText = new QGraphicsTextItem("Coins: 0");
    coinText->setFont(QFont("fusion pixel proportional", 16));
    coinText->setDefaultTextColor(Qt::red);
    coinText->setPos(800, 200);
    pointPrepare->addItem(coinText);


}

StartMenu::StartMenu(QString accountLast){
    QFontDatabase::addApplicationFont(":/font/fusion-pixel-proportional.ttf");
    setFixedSize(1500, 1000);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关垂直滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条
    //按钮样式表
    QFile fileButtonStyle(":/style.qss");
    fileButtonStyle.open(QFile::ReadOnly);
    QString buttonStyle;
    if (fileButtonStyle.isOpen()) {
        buttonStyle = QLatin1String(fileButtonStyle.readAll());
        fileButtonStyle.close();
    }

    account=accountLast;

    //##############################################################################################################################

    pointMain = new QGraphicsScene(this);
    setScene(pointMain);
    pointMain->setSceneRect(0, 0, 1500, 1000);
    pointMain->addPixmap(QPixmap(":/images/ABackground.png"));

    QPushButton *mainStartButton = new QPushButton("start");
    mainStartButton->move(550, 600);
    mainStartButton->resize(100, 50);
    mainStartButton->setStyleSheet(buttonStyle);
    connect(mainStartButton, &QPushButton::clicked, this, [=](){
        sendGetCoinRequest(account);
        openPreparePage();
    });
    pointMain->addWidget(mainStartButton);

    //################################################################################################################################

    pointPrepare = new QGraphicsScene(this);
    pointPrepare->setSceneRect(0,0,1500,1000);
    pointPrepare->addPixmap(QPixmap(":/images/ABackground.png"));

    QPushButton *prepareBackButton = new QPushButton("back");
    pointPrepare->addWidget(prepareBackButton);
    prepareBackButton->move(50, 50);
    prepareBackButton->resize(100, 50);
    prepareBackButton->setStyleSheet(buttonStyle);
    connect(prepareBackButton, &QPushButton::clicked, this, &StartMenu::openMainPage);

    QPushButton *prepareStartButton = new QPushButton("Start Game");
    pointPrepare->addWidget(prepareStartButton);
    prepareStartButton->setStyleSheet(buttonStyle);
    prepareStartButton->resize(220, 110);
    prepareStartButton->move(530, 480);
    connect(prepareStartButton, &QPushButton::clicked, this, [=](){
        emit startGame();
        deleteLater();
    });

    QPushButton *buyMagicFireButton = new QPushButton("magicFire");
    pointPrepare->addWidget(buyMagicFireButton);
    buyMagicFireButton->move(730,600);
    buyMagicFireButton->resize(200, 50);
    buyMagicFireButton->setStyleSheet(buttonStyle);
    connect(buyMagicFireButton, &QPushButton::clicked, this,[=](){
        magic="magicFire";
        int tmpCoinCount=coinCount.toInt();
        tmpCoinCount-=10;
        if(tmpCoinCount<0)tmpCoinCount=0;
        coinCount=QString::number(tmpCoinCount);
        sendChangeCoinRequest(account,coinCount);
        qDebug()<<"send change";

        updateCoinLabel(coinCount);
    });

    coinText = new QGraphicsTextItem("Coins: 0");
    coinText->setFont(QFont("fusion pixel proportional", 16));
    coinText->setDefaultTextColor(Qt::red);
    coinText->setPos(800, 200);
    pointPrepare->addItem(coinText);
}


void StartMenu::openPreparePage(){
    setScene(pointPrepare);
}

void StartMenu::openMainPage(){
    setScene(pointMain);
}

void StartMenu::sendGetCoinRequest(QString account) {
    QTcpSocket socket;
    socket.connectToHost("localhost", 8080);

    if (socket.waitForConnected()) {
        QByteArray request = "GET /get_coin_value?account=" + account.toUtf8() + " HTTP/1.1\r\n"
                                                                                 "Host: localhost:8080\r\n"
                                                                                 "Connection: Close\r\n"
                                                                                 "\r\n";

        socket.write(request);
        socket.waitForBytesWritten();
        socket.waitForReadyRead();

        QByteArray response = socket.readAll();
        QString responseString(response);
        int index = responseString.indexOf("\r\n\r\n");
        if (index == -1) {
            qWarning() << "Invalid response received: " << responseString;
            return;
        }
        QString header = responseString.left(index);
        QStringList headerLines = header.split("\r\n");
        int contentLength = -1;
        foreach (QString line, headerLines) {
            if (line.startsWith("Content-Length:")) {
                contentLength = line.mid(QString("Content-Length:").length()).trimmed().toInt();
            }
        }
        if (contentLength == -1) {
            qWarning() << "Invalid response received: " << responseString;
            return;
        }
        QString coinValueString = responseString.mid(index + 4, contentLength);
        QString coinValue = coinValueString.trimmed();


        qDebug() << "Coin value:" << coinValue;
        coinCount = coinValue.trimmed();
        updateCoinLabel(coinCount);

    } else {
        qWarning() << "Failed to connect server";
    }
    socket.disconnectFromHost();
}



void StartMenu::sendLoginRequest(QString account, QString password)
{
    // 创建一个 TCP 套接字
    QTcpSocket *socket = new QTcpSocket(this);

    // 连接到服务器
    socket->connectToHost("localhost", 8080);
    if (!socket->waitForConnected(3000)) {
        qWarning() << "Failed to connect to server: " << socket->errorString();
        return;
    }

    QByteArray requestData = "POST /login?account=" + account.toUtf8() + "&password=" + password.toUtf8() + " HTTP/1.1\r\n\r\n";

    socket->write(requestData);
    socket->waitForBytesWritten();

    if (!socket->waitForReadyRead(10000)) {
        qWarning() << "Failed to receive response from server: " << socket->errorString();
        return;
    }

    // 读取服务器返回的响应
    QByteArray responseData = socket->readAll();
    QString responseString(responseData);

    // 检查登录是否成功
    if (responseString.contains("true")) {
        emit loginSuccess(); // 登录成功，发送信号
    } else {
        qWarning() << "Login failed";
    }

    // 关闭连接
    socket->disconnectFromHost();
}

void StartMenu::sendChangeCoinRequest(QString account, QString targetCoin)
{
    QTcpSocket *socket = new QTcpSocket(this);

    socket->connectToHost("localhost", 8080);
    if (!socket->waitForConnected(3000)) {
        qWarning() << "Failed to connect to server: " << socket->errorString();
        return;
    }

    QByteArray requestData = "POST /updateCoins?account=" + account.toUtf8() + "&targetCoins=" + targetCoin.toUtf8() + " HTTP/1.1\r\n\r\n";

    socket->write(requestData);
    socket->waitForBytesWritten();

    if (!socket->waitForReadyRead(3000)) {
        qWarning() << "Failed to receive response from server: " << socket->errorString();
        return;
    }

    QByteArray responseData = socket->readAll();
    QString responseString(responseData);

    if (responseString.contains("true")) {
        qDebug()<<"Change Successly";
    } else {
    qWarning() << "Change failed";
    }

    socket->disconnectFromHost();
}


void StartMenu::updateCoinLabel(QString coinCount) {
    coinText->setPlainText("Coins: " + coinCount);
}




