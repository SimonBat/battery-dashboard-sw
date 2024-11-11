#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QQuickStyle>
#include <QDebug>
#include "AppWrapper.h"

int main(int argc, char *argv[])
{
    if(!QString::compare(MAIN_QML, "qrc:/BiApplicationRpi.qml", Qt::CaseInsensitive))
    {
        qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
        qputenv("QML_IMPORT_PATH", QByteArray(PROJECT_PATH_VK));
        qputenv("QML2_IMPORT_PATH", QByteArray(PROJECT_PATH_VK));
        qputenv("QT_VIRTUALKEYBOARD_STYLE", QByteArray("vkBi"));
    }

    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QCoreApplication::setAttribute(Qt::AA_Use96Dpi);
    QCoreApplication::setAttribute(Qt::AA_ForceRasterWidgets);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setDesktopSettingsAware(true);
    QQuickStyle::setStyle("Material");

    QApplication app(argc, argv);
    QThread::currentThread()->setPriority(QThread::HighPriority);

    app.setWindowIcon(QIcon(":/icon.ico"));
    app.setApplicationName("Battery Dashboard v1.0");
    app.setOrganizationName("SimonBat");
    app.setOrganizationDomain("SimonBat");
    AppWrapper appWrapper;
    appWrapper.initialize();

    return app.exec();
}
