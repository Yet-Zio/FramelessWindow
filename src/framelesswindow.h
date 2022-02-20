#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QWidget>
#include <QFile>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QMenuBar>
#include <QSizeGrip>
#include <QHoverEvent>
#include <QSysInfo>
#include <QRegularExpression>

namespace Ui{
    class FramelessWindow;
}

/*! \class FramelessWindow
    \brief Unique Frameless window or Titlebar class built in Qt 6 with customization in mind.
           Inherits QWidget*/
class FramelessWindow: public QWidget{
    Q_OBJECT

public:

    /*!
     * \brief Enum for various title bar modes
     */
    enum TitleMode {
        CleanTitle, /*!< Hides everything except the title text */
        OnlyCloseButton, /*!< Hides everything except the close button and title text */
        IconOff, /*!< Hides only the app icon */
        MaxMinRollOff, /*!< Hides the maximize, minimize and roll button */
        MaxMinOff, /*!< Hides the maximize and minimize button */
        FullScreenMode, /*!< Window becomes fullscreen */
        MaxOff, /*!< Hides maximize button */
        MinOff, /*!< Hides minimize button */
        RollOff, /*!< Hides roll button */
        FullTitle /*!< Nothing is hidden, default mode */ };

    /*!
     * \brief FramelessWindow
     * \param parent a QWidget
     */
    explicit FramelessWindow(QWidget *parent = nullptr);

    /*!
     * \fn void dropShadow(bool on = true)
     * \brief Enables drop shadow effect
     * \param on a boolean
     */
    void dropShadow(bool on = true);

    /*!
     * \fn int getGlobalState
     * \brief Helps in knowing whether window is maximized or in restored state
     * \return an integer
     */
    int getGlobalState(){
        return GLOBAL_STATE;
    }

    /*!
     * \fn void getFullSCState()
     * \brief Helps in knowing whether window is fullscreen or in restored state
     * \return
     */
    int getFullSCState(){
        return FULLSC_STATE;
    }

    /*!
     * \fn int getRollState()
     * \brief Helps in knowing whether window is rolled up or rolled down
     * \return an integer
     */
    int getRollState(){
        return ROLL_STATE;
    }

    /*!
     * \fn void setTitle(QString title);
     * \brief Sets the titlebar text
     * \param title a QString
     */
    void setTitle(QString title);

    /*!
     * \fn void setTitleFont(QFont font);
     * \brief Sets the titlebar font to font
     * \param font a QFont
     */
    void setTitleFont(QFont font);

    /*!
     * \fn void setTitleStyle(QString stylesheet)
     * \brief Sets the titlebar text stylesheet to stylesheet
     * \param stylesheet a QString
     */
    void setTitleStyle(QString stylesheet);

    /*!
     * \fn void setTitleBarMode(TitleMode flag)
     * \brief Sets the title bar mode from flag
     * \param flag a TitleMode
     */
    void setTitleBarMode(TitleMode flag);

    /*!
     * \fn void setAppIcon(QIcon appicon)
     * \brief Sets the app icon to appicon
     * \param appicon a QIcon
     */
    void setAppIcon(QIcon appicon);

    /*!
     * \fn void setMinIcon(QIcon minicon)
     * \brief Sets the minimize icon to minicon
     * \param minicon a QIcon
     */
    void setMinIcon(QIcon minicon);

    /*!
     * \fn void setMaxIcon(QString maxres = ":/app_max.png", QString restres = ":/app_rest.png")
     * \brief Sets the maximize and restore icons to maxres and restres, provided both are resources
     * \param maxres a QString
     * \param restres a QString
     */
    void setMaxIcon(QString maxres = ":/app_max.png", QString restres = ":/app_rest.png");

    /*!
     * \fn void setRollIcon(QString rollup = ":/rollup.png", QString rolldown = ":/rolldown.png");
     * \brief Sets the roll up and roll down icons to rollup and rolldown, provided both are resources
     * \param rollup a QString
     * \param rolldown a QString
     */
    void setRollIcon(QString rollup = ":/rollup.png", QString rolldown = ":/rolldown.png");

    /*!
     * \fn void setCloseIcon(QIcon closeIcon)
     * \brief Sets the close icon to closeIcon
     * \param closeicon a QIcon
     */
    void setCloseIcon(QIcon closeicon);

    /*!
     * \fn void setMenuBar(QMenuBar *menuBar = nullptr, bool hidden = false)
     * \brief Sets the menubar of the frameless window from a given menu bar. Parameter "hidden" is set to false by default. If set to true, menubar will be hidden.
     * \param menuBar a QMenuBar*
     * \param hidden a boolean
     */
    void setMenuBar(QMenuBar *menuBar = nullptr, bool hidden = false);

    /*!
     * \fn void hideMenuBar(bool y = true)
     * \brief Hides the menu bar
     * \param y a boolean
     */
    void hideMenuBar(bool y = true);

    /*!
     * \fn void setCentralWidget(QWidget *centralWidget)
     * \brief Sets the central widget to centralWidget
     * \param centralWidget a *QWidget
     */
    void setCentralWidget(QWidget *centralWidget);

private:
    Ui::FramelessWindow *ui = nullptr;

    /*!
     * \fn void setupFrWindow()
     * \brief Sets up the frameless window
     */
    void setupFrWindow();

    /*!
     * \fn void setupTitleButtons()
     * \brief Sets up the title bar buttons
     */
    void setupTitleButtons();

    /*!
     * \fn void setupSizeRetain()
     * \brief Sets up size retain for certain widgets
     */
    void setupSizeRetain();

    /*!
     * \fn void setupSizeGrip
     * \brief Sets up size grip on all corners for corner resizing
     */
    void setupSizeGrip();

    void keyPressEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void hoverMove(QHoverEvent *event);

    bool event(QEvent *e);

    int GLOBAL_STATE = 0; /*!< Stores the window state */
    int FULLSC_STATE = 0; /*!< Stores full screen state */
    int ROLL_STATE = 0; /*!< Stores the roll state */


    QPoint dragPos; /*!< Stores the global position */
    QPoint localPos; /*!< Stores the local position */

    int resizeLookout = 15; /*!< Default value to lookout while mouse is near the edges */

    QRect normalRect; /*!< Stores the normal window state. On systems other than Windows, this helps in restoring the window state */
    QSysInfo *sysinfo; /*!< Stores system information */

    QFile file{":/framelesswindow.css"}; /*!< CSS file used for the window's style */
    QString filedata; /*!< Data read from the CSS file */

    QRegularExpression titleMaxExp = QRegularExpression("(titleMaxStyle.*{[\\s\\S]*?})"); /*!< RegExp to get title bar's maximize style */
    QString titleMaxStyle; /*!< Stores title bar's maximize style */

    QString m_maxres = ":/app_max.png"; /*!< Default maximize icon */
    QString m_restres = ":/app_rest.png"; /*!< Default restore icon */

    QString m_rollup = ":/rollup.png"; /*!< Default roll up icon */
    QString m_rolldown = ":/rolldown.png"; /*!< Default roll down icon */

private slots:
    /*!
     * \fn void maximize_restore()
     * \brief Slot that deals with maximizing and restoring the window
     */
    void maximize_restore();

    /*!
     * \fn void fullsc_restore()
     * \brief Slot that deals with fullscreen and restoring the window
     */
    void fullsc_restore();

    /*!
     * \fn void rollup_down()
     * \brief Slot that deals with roll up and down operations on the window
     */
    void rollup_down();

protected:

    /*!
     * \fn void handleEdgeHit()
     * \brief Handles edge hit while moving or resizing window.
     */
    void handleEdgeHit();

    /*!
     * \fn void moveWindow(QMouseEvent *event)
     * \brief Function that deals with moving the window
     * \param event a QMouseEvent*
     */
    void moveWindow(QMouseEvent *event);
};

#endif // FRAMELESSWINDOW_H
