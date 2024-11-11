#include <QtWidgets/QApplication>
#include <QScreen>
#include <QThread>
#include <QDebug>
#include <QIcon>
#include "AppWrapper.h"

AppWrapper::AppWrapper(QObject *parent) : QObject(parent),
    sPort(new SerialPort),
    dataProfile(new DataProfile(this))
{
    connect(sPort, SIGNAL(resetQmlSPortSignal()), this, SLOT(resetQmlSerialPort()));
    connect(&sPort->commEPSM, SIGNAL(updateProfileLiveData(LiveData&)), dataProfile, SLOT(updateLiveData(LiveData&)));
    connect(&sPort->commEPSM, SIGNAL(updateProfileSettingsDataMaster(SettingsDataMaster&)), dataProfile, SLOT(updateSettingsDataMaster(SettingsDataMaster&)));
}

void AppWrapper::initialize(void)
{
    QRect DisplayRect = QGuiApplication::primaryScreen()->availableGeometry();
    QSizeF DisplaySize = QGuiApplication::primaryScreen()->physicalSize();
    qreal DisplayDpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();
    qDebug() << "Display Width: " << DisplayRect.width();
    qDebug() << "Display Height: " << DisplayRect.height();
    qDebug() << "Display Physical Width: " << DisplaySize.width();
    qDebug() << "Display Physical Height: " << DisplaySize.height();
    qDebug() << "Display DPI: " << DisplayDpi;

    resetQmlSerialPort();
    viewer.engine()->rootContext()->setContextProperty("dataProfile", dataProfile);

// The following are needed to make examples run without having to install the module in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif

    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(), QString::fromLatin1("qml")));

    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);
    viewer.setSource(QUrl(MAIN_QML));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    Qt::WindowFlags flags = Qt::Window;
    viewer.setFlags(flags);
    viewer.setMinimumWidth(viewer.width());
    viewer.setMinimumHeight(viewer.height());
    viewer.setMaximumWidth(viewer.width());
    viewer.setMaximumHeight(viewer.height());
    viewer.setIcon(QIcon(":/icon.ico"));
    viewer.show();
}

void AppWrapper::resetQmlSerialPort()
{
    viewer.engine()->rootContext()->setContextProperty("sPort", sPort);
}
