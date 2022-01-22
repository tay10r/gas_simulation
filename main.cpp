#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QTranslator>

int
main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  a.setApplicationName(QObject::tr("Gas Simulator"));

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString& locale : uiLanguages) {
    const QString baseName = "gsim_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  MainWindow w;
#ifdef __EMSCRIPTEN__
  w.showFullScreen();
#else
  w.showMaximized();
#endif
  w.setWindowTitle(a.applicationName());
  return a.exec();
}
