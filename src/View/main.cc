#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow &w = MainWindow::GetMainWindow();

  Ui::Observer observer;
  w.AttachObserver(&observer);

  w.setWindowTitle("3DViewer");
  w.show();

  return a.exec();
}
