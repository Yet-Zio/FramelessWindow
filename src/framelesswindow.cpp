#include "framelesswindow.h"
#include "ui_FramelessWindow.h"

FramelessWindow::FramelessWindow(QWidget *parent) : QWidget(parent), ui(new Ui::FramelessWindow){
    if (file.open(QFile::ReadOnly))
    {
        filedata = file.readAll();
        setStyleSheet(filedata);
        QRegularExpressionMatch maxmatch = titleMaxExp.match(filedata);
        if(maxmatch.hasMatch()){
            titleMaxStyle = "#titleBar" + maxmatch.captured(0).remove("titleMaxStyle");
        }
        file.close();
    }

    ui->setupUi(this);

    setupFrWindow();

    setupTitleButtons();
    setupSizeRetain();
    setupSizeGrip();

    sysinfo = new QSysInfo;
    ui->appTitle->setText("Frameless Window");

}

void FramelessWindow::maximize_restore(){

    if(getGlobalState() == 0){
        if(sysinfo->productType() != "windows"){
            normalRect = rect();
            normalRect.setX(x());
            normalRect.setY(y());
            normalRect.setWidth(width());
            normalRect.setHeight(height());
        }

        showMaximized();
        GLOBAL_STATE = 1;

        setContentsMargins(0, 0, 0, 0);
        ui->titleBar->setStyleSheet(titleMaxStyle);
        ui->maxBtn->setIcon(QIcon(m_restres));
        ui->maxBtn->setToolTip("Restore");
    }
    else{
        GLOBAL_STATE = 0;
        showNormal();

        if(sysinfo->productType() != "windows"){
            setGeometry(normalRect);
        }

        resize(width()+1, height()+1);
        setContentsMargins(0, 0, 0, 0);

        ui->titleBar->setStyleSheet(filedata);
        ui->maxBtn->setIcon(QIcon(m_maxres));
        ui->maxBtn->setToolTip("Maximize");
    }
}

void FramelessWindow::fullsc_restore(){
    if(getFullSCState() == 0){
        ui->titleBar->hide();
        showFullScreen();
        FULLSC_STATE = 1;
    }
    else{
        ui->titleBar->show();
        ui->titleBar->setStyleSheet(titleMaxStyle);
        showMaximized();
        GLOBAL_STATE = 1;
        FULLSC_STATE = 0;
    }
}

void FramelessWindow::rollup_down(){

    if(getRollState() == 0){
        ui->bottom_bar->hide();
        ui->centralWidget->hide();
        ROLL_STATE = 1;

        ui->rollBtn->setIcon(QIcon(m_rolldown));
        ui->rollBtn->setToolTip("Roll down");
    }
    else{
        ROLL_STATE = 0;
        ui->centralWidget->show();
        ui->bottom_bar->show();

        ui->rollBtn->setIcon(QIcon(m_rollup));
        ui->rollBtn->setToolTip("Roll up");
    }
}

void FramelessWindow::setupFrWindow(){
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_Hover);

    setMouseTracking(true);
}

void FramelessWindow::setupTitleButtons(){
    ui->rollBtn->setToolTip("Roll up");
    QObject::connect(ui->rollBtn, &QPushButton::clicked, this, &FramelessWindow::rollup_down);

    ui->maxBtn->setToolTip("Maximize");
    QObject::connect(ui->maxBtn, &QPushButton::clicked, this, &FramelessWindow::maximize_restore);

    ui->minBtn->setToolTip("Minimize");
    QObject::connect(ui->minBtn, &QPushButton::clicked, this, &FramelessWindow::showMinimized);

    ui->closeBtn->setToolTip("Close");
    QObject::connect(ui->closeBtn, &QPushButton::clicked, this, &FramelessWindow::close);
}

void FramelessWindow::setupSizeRetain(){
    QSizePolicy bottomsp_retain = ui->bottom_bar->sizePolicy();
    bottomsp_retain.setRetainSizeWhenHidden(true);
    ui->bottom_bar->setSizePolicy(bottomsp_retain);

    QSizePolicy centralsp_retain = ui->centralWidget->sizePolicy();
    centralsp_retain.setRetainSizeWhenHidden(true);
    ui->centralWidget->setSizePolicy(centralsp_retain);
}

void FramelessWindow::setupSizeGrip(){

    QSizeGrip *btrightsizegrip = new QSizeGrip(ui->btrightgrip);
    btrightsizegrip->setStyleSheet(filedata);
    btrightsizegrip->setToolTip("Resize");

    QSizeGrip *btleftsizegrip = new QSizeGrip(ui->btleftgrip);
    btleftsizegrip->setStyleSheet(filedata);
    btleftsizegrip->setToolTip("Resize");

    QSizeGrip *tprightsizegrip = new QSizeGrip(ui->tprightgrip);
    tprightsizegrip->setStyleSheet(filedata);
    tprightsizegrip->setToolTip("Resize");

    QSizeGrip *tpleftsizegrip = new QSizeGrip(ui->tpleftgrip);
    tpleftsizegrip->setStyleSheet(filedata);
    tpleftsizegrip->setToolTip("Resize");
}

void FramelessWindow::setTitle(QString title){
    ui->appTitle->setText(title);
}

void FramelessWindow::setTitleFont(QFont font){
    ui->appTitle->setFont(font);
}

void FramelessWindow::setTitleStyle(QString stylesheet){
    ui->appTitle->setStyleSheet(stylesheet);
}

void FramelessWindow::setTitleBarMode(TitleMode flag){
    switch(flag){
        case CleanTitle:
            ui->appTool->setHidden(true);
            ui->minBtn->setHidden(true);
            ui->maxBtn->setHidden(true);
            ui->closeBtn->setHidden(true);
            break;
        case OnlyCloseButton:
            ui->appTool->setHidden(true);
            ui->minBtn->setHidden(true);
            ui->maxBtn->setHidden(true);
            break;
        case IconOff:
            ui->appTool->setHidden(true);
            break;
        case MaxMinOff:
            ui->minBtn->setHidden(true);
            ui->maxBtn->setHidden(true);
            break;
        case MaxMinRollOff:
            ui->minBtn->setHidden(true);
            ui->maxBtn->setHidden(true);
            ui->rollBtn->setHidden(true);
            break;
        case FullScreenMode:
            fullsc_restore();
            break;
        case MaxOff:
            ui->maxBtn->setHidden(true);
            break;
        case MinOff:
            ui->minBtn->setHidden(true);
            break;
        case RollOff:
            ui->rollBtn->setHidden(true);
            break;
        case FullTitle:
            ui->appTool->setVisible(true);
            ui->rollBtn->setVisible(true);
            ui->minBtn->setVisible(true);
            ui->maxBtn->setVisible(true);
            ui->closeBtn->setVisible(true);
            break;
    }
}

void FramelessWindow::setAppIcon(QIcon appicon){
    ui->appTool->setIcon(appicon);
}

void FramelessWindow::setMinIcon(QIcon minicon){
    ui->minBtn->setIcon(minicon);
}

void FramelessWindow::setMaxIcon(QString maxicon, QString resicon){
    m_maxres = maxicon;
    m_restres = resicon;

    if(getGlobalState() == 1){
        ui->maxBtn->setIcon(QIcon(m_restres));
    }
    else{
        ui->maxBtn->setIcon(QIcon(m_maxres));
    }
}

void FramelessWindow::setRollIcon(QString rollup, QString rolldown){
    m_rollup = rollup;
    m_rolldown = rolldown;

    if(getRollState() == 1){
        ui->rollBtn->setIcon(QIcon(m_rolldown));
    }
    else{
        ui->rollBtn->setIcon(QIcon(m_rollup));
    }
}

void FramelessWindow::setCloseIcon(QIcon closeicon){
    ui->closeBtn->setIcon(closeicon);
}

void FramelessWindow::setMenuBar(QMenuBar *menuBar, bool hidden){
    if(menuBar != nullptr){
        auto menus = menuBar->actions();

        for(auto mu: menus){
            ui->menubar->addMenu(mu->menu());
        }

        if(hidden){
            ui->menubar->hide();
        }
    }
}

void FramelessWindow::hideMenuBar(bool y){
    (y)?ui->menubar->hide():ui->menubar->show();
}

void FramelessWindow::setCentralWidget(QWidget *centralWidget){
    ui->centralLayout->addWidget(centralWidget);
}

void FramelessWindow::handleEdgeHit(){
    if(sysinfo->productType() != "windows"){
        if(screen()->geometry().top() == geometry().top()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().top() > geometry().top()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().bottom() == geometry().bottom()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().bottom() < geometry().bottom()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().left() == geometry().left()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().left() > geometry().left()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().right() == geometry().right()){
           move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().right() < geometry().right()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
    }
    else{
        if(screen()->geometry().top() == geometry().top()){
            move(x(), screen()->geometry().top() + 1);
        }
        else if(screen()->geometry().top() > geometry().top()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().bottom() == geometry().bottom()){
            move(x(), screen()->geometry().bottom() - 1);
        }
        else if(screen()->geometry().bottom() < geometry().bottom()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().left() == geometry().left()){
            move(screen()->geometry().left() + 1, y());
        }
        else if(screen()->geometry().left() > geometry().left()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
        else if(screen()->geometry().right() == geometry().right()){
            move(screen()->geometry().right() - 1, y());
        }
        else if(screen()->geometry().right() < geometry().right()){
            move((screen()->geometry().width() - width()) /2, (screen()->geometry().height() - height()) /2);
        }
    }
}

void FramelessWindow::moveWindow(QMouseEvent *event){

    if(getGlobalState() == 1){
        maximize_restore();
    }

    if(event->buttons() == Qt::LeftButton){
        if(cursor().shape() == Qt::SizeHorCursor){
            int dx = event->position().toPoint().x() - localPos.x();
            QRect rect;
            if(mapToGlobal(event->position().toPoint()).x() < geometry().right() - 20){
                rect.setX(x() + dx);
                rect.setY(y());
                rect.setWidth(width() - dx);
                rect.setHeight(height());
                setGeometry(rect);
                event->accept();
            }
            else if(mapToGlobal(event->position().toPoint()).x() > geometry().left() + 20){
                rect.setX(x());
                rect.setY(y());
                rect.setWidth(width() + dx);
                rect.setHeight(height());
                setGeometry(rect);
                localPos = event->position().toPoint();
                event->accept();
            }
        }
        else if(cursor().shape() == Qt::SizeVerCursor){
            int dy = event->position().toPoint().y() - localPos.y();
            QRect rect;
            if(mapToGlobal(event->position().toPoint()).y() < geometry().bottom() - 20){
                rect.setX(x());
                rect.setY(y() + dy);
                rect.setWidth(width());
                rect.setHeight(height() - dy);
                setGeometry(rect);
                event->accept();
            }
            else if(mapToGlobal(event->position().toPoint()).y() > geometry().top() + 20){
                rect.setX(x());
                rect.setY(y());
                rect.setWidth(width());
                rect.setHeight(height() + dy);
                setGeometry(rect);
                localPos = event->position().toPoint();
                event->accept();
            }
        }
        else{
            if((screen()->geometry().left() == geometry().left() or screen()->geometry().left() > geometry().left()
                or screen()->geometry().right() == geometry().right() or screen()->geometry().right() < geometry().right())
                    or (screen()->geometry().top() == geometry().top() or screen()->geometry().top() > geometry().top()
                        or screen()->geometry().bottom() == geometry().bottom() or screen()->geometry().bottom() < geometry().bottom())){
                handleEdgeHit();

                dragPos = event->globalPosition().toPoint();
                localPos = event->position().toPoint();
                event->accept();
            }
            else{
                move(pos() + event->globalPosition().toPoint() - dragPos);
                dragPos = event->globalPosition().toPoint();
                localPos = event->position().toPoint();
                event->accept();
            }
        }
    }
}

void FramelessWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_F11){
        fullsc_restore();
    }
    else{
        QWidget::keyPressEvent(event);
    }
}

void FramelessWindow::mouseMoveEvent(QMouseEvent *event){
    moveWindow(event);
}


void FramelessWindow::mousePressEvent(QMouseEvent *event){
    dragPos = event->globalPosition().toPoint();
    localPos = event->position().toPoint();
}

bool FramelessWindow::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void FramelessWindow::hoverMove(QHoverEvent *event){
    QRect titleRect = ui->titleBar->geometry();
    QPoint titlePoint(titleRect.x(), titleRect.top());

    if(mapToGlobal(event->position().toPoint()).x() == geometry().left() or mapToGlobal(event->position().toPoint()).x() == geometry().right()){
        setCursor(Qt::SizeHorCursor);
    }
    else if(mapToGlobal(event->position().toPoint()).y() == geometry().bottom() or
            mapToGlobal(event->position().toPoint()).y() == mapToGlobal(titlePoint).y()){
        setCursor(Qt::SizeVerCursor);
    }
    else if((mapToGlobal(event->position().toPoint()).x() > geometry().left() + resizeLookout and mapToGlobal(event->position().toPoint()).x() < geometry().right() - resizeLookout) and
            (mapToGlobal(event->position().toPoint()).y() > mapToGlobal(titlePoint).y() + resizeLookout and mapToGlobal(event->position().toPoint()).y() < frameGeometry().bottom() - resizeLookout)){
        unsetCursor();
    }
}


void FramelessWindow::dropShadow(bool on){
    if(on){
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setXOffset(0);
        shadow->setYOffset(0);
        shadow->setColor(QColor(0, 0, 0, 100));

        setGraphicsEffect(shadow);
    }
}
