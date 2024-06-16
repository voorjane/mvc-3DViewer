#include "mainwindow.h"

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QTabBar>
#include <QTimer>

#include "Controller/controller.h"
#include "Model/objparser.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  ui_->Screenshot->hide();
  ui_->Gif->hide();
  ui_->SettingsTab->tabBar()->hide();

  model_ = new s21::MyGLWidget(ui_->openGLWidget);
  s21::Controller::ModelResize(model_);

  updateUi();
  s21::Controller::ModelUpdate(model_);
}

MainWindow::~MainWindow() {
  delete model_;
  delete ui_;
}

void MainWindow::on_BackgroundColor_clicked() {
  for (auto observer : observers_) {
    observer->BackgroundColorChange();
  }

  QColorDialog dialog;

  dialog.setOption(QColorDialog::ShowAlphaChannel);

  if (dialog.exec() == QDialog::Accepted) {
    QColor color = dialog.selectedColor();
    if (color.isValid()) {
      QString qss = QString(
                        "background-color: %1;\n border:1px solid;\n "
                        "border-color: black;")
                        .arg(color.name());
      ui_->BackgroundColor->setStyleSheet(qss);

      s21::Controller::ModelBackgroundColorSetSettings(model_, color);
      s21::Controller::ModelUpdate(model_);
    }
  }
}

void MainWindow::on_ProjectionButton_clicked() {
  ui_->SettingsTab->setCurrentIndex(0);
}

void MainWindow::on_VertexButton_clicked() {
  ui_->SettingsTab->setCurrentIndex(1);
}

void MainWindow::on_EdgeButton_clicked() {
  ui_->SettingsTab->setCurrentIndex(2);
}

void MainWindow::on_LittleProjection_clicked() {
  for (auto observer : observers_) {
    observer->ProjectionChange();
  }

  QString temp_string = ui_->LittleProjection->text();

  ui_->LittleProjection->setText(ui_->BigProjection->text());
  ui_->BigProjection->setText(temp_string);

  s21::Controller::ModelProjectionSetSettings(model_, temp_string);
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_VertexColor_clicked() {
  for (auto observer : observers_) {
    observer->VertexChange();
  }

  QColorDialog dialog;

  dialog.setOption(QColorDialog::ShowAlphaChannel);

  if (dialog.exec() == QDialog::Accepted) {
    QColor color = dialog.selectedColor();
    if (color.isValid()) {
      QString qss = QString(
                        "background-color: %1;\n border:1px solid;\n "
                        "border-color: black;")
                        .arg(color.name());
      ui_->VertexColor->setStyleSheet(qss);

      s21::Controller::ModelVertexColorSetSettings(model_, color);
      s21::Controller::ModelUpdate(model_);
    }
  }
}

void MainWindow::on_VertexSize_textChanged() {
  for (auto observer : observers_) {
    observer->VertexChange();
  }

  ui_->VertexSize->setMaxLength(3);

  s21::Controller::ModelVertexSizeSetSettings(model_,
                                              ui_->VertexSize->text().toInt());
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_TopVertex_clicked() {
  for (auto observer : observers_) {
    observer->VertexChange();
  }

  QString temp_string_top = ui_->TopVertex->text();
  QString temp_string_central = ui_->CentralVertex->text();

  ui_->CentralVertex->setText(temp_string_top);
  ui_->TopVertex->setText(ui_->BottomVertex->text());
  ui_->BottomVertex->setText(temp_string_central);

  s21::Controller::ModelVertexTypeSetSettings(model_, temp_string_top);
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_BottomVertex_clicked() {
  for (auto observer : observers_) {
    observer->VertexChange();
  }

  QString temp_string_bottom = ui_->BottomVertex->text();
  QString temp_string_central = ui_->CentralVertex->text();

  ui_->CentralVertex->setText(temp_string_bottom);
  ui_->BottomVertex->setText(ui_->TopVertex->text());
  ui_->TopVertex->setText(temp_string_central);

  s21::Controller::ModelVertexTypeSetSettings(model_, temp_string_bottom);
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_EdgeColor_clicked() {
  for (auto observer : observers_) {
    observer->EdgeChange();
  }

  QColorDialog dialog;

  dialog.setOption(QColorDialog::ShowAlphaChannel);

  if (dialog.exec() == QDialog::Accepted) {
    QColor color = dialog.selectedColor();
    if (color.isValid()) {
      QString qss =
          QString(
              "background-color: %1;\nborder:1px solid;\n border-color: black;")
              .arg(color.name());
      ui_->EdgeColor->setStyleSheet(qss);

      s21::Controller::ModelEdgeColorSetSettings(model_, color);
      s21::Controller::ModelUpdate(model_);
    }
  }
}

void MainWindow::on_EdgeThickness_textChanged() {
  for (auto observer : observers_) {
    observer->EdgeChange();
  }

  ui_->EdgeThickness->setMaxLength(3);

  s21::Controller::ModelEdgeThicknessSetSettings(
      model_, ui_->EdgeThickness->text().toInt());
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_LittleEdge_clicked() {
  for (auto observer : observers_) {
    observer->EdgeChange();
  }

  QString temp_string = ui_->LittleEdge->text();

  ui_->LittleEdge->setText(ui_->BigEdge->text());
  ui_->BigEdge->setText(temp_string);

  s21::Controller::ModelEdgeSizeSetSettings(model_, temp_string);
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_Open_clicked() {
  QString path = QDir::currentPath();
  QString filename_q =
      QFileDialog::getOpenFileName(this, tr("Open obj file"), path + "../../",
                                   tr("Obj Files (*.obj)"))
          .toUtf8()
          .constData();

  if (!filename_q.isEmpty() && !filename_q.isNull()) {
    std::string filename = filename_q.toStdString();

    s21::Controller::ModelInitAfterOpen(filename, model_);

    ui_->Filename->setText(filename_q.section("/", -1, -1));
    ui_->CountOfVertices->setText(
        QString::number(s21::Controller::ModelGetVSize(model_) / 3));
    ui_->CountOfEdges->setText(
        QString::number(s21::Controller::ModelGetFSize(model_) / 4));

    s21::Controller::ModelUpdate(model_);
  } else {
  }
}

void MainWindow::on_Increase_clicked() {
  for (auto observer : observers_) {
    observer->ModelTransformed();
  }

  s21::Controller::ModelIncrease(model_);

  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_Decrease_clicked() {
  for (auto observer : observers_) {
    observer->ModelTransformed();
  }

  s21::Controller::ModelDecrease(model_);

  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_Reset_clicked() {
  for (auto observer : observers_) {
    observer->ModelReset();
  }

  s21::Controller::ClearAndLoadSettings(model_);

  updateUi();
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_ShowMenu_clicked() {
  if (!ui_->Screenshot->isVisible() && !ui_->Gif->isVisible()) {
    ui_->ShowMenu->setText("↓");
    ui_->Screenshot->show();
    ui_->Gif->show();
  } else if (ui_->Screenshot->isVisible() && ui_->Gif->isVisible()) {
    ui_->ShowMenu->setText("↑");
    ui_->Screenshot->hide();
    ui_->Gif->hide();
  }
}

void MainWindow::on_Screenshot_clicked() {
  QString save_image = QFileDialog::getSaveFileName(
      this, nullptr, nullptr, "JPEG (*.jpeg) ;; BMP (*.bmp");

  if (!save_image.isEmpty() && !save_image.isNull()) {
    model_->grabFramebuffer().save(save_image, nullptr, 100);

    for (auto observer : observers_) {
      observer->ScreenshotTaken();
    }
  }
}

void MainWindow::on_Gif_clicked() {
  frames_ = 0;
  gif_ = new QGifImage;
  timer_ = new QTimer(this);

  ui_->Gif->setStyleSheet(
      "color: red;\n border-radius: 1px;\n border-bottom: 1px solid grey;\n "
      "background-color: rgb(64, 64, 64);");

  gif_->setDefaultDelay(100);
  connect(timer_, SIGNAL(timeout()), this, SLOT(saveGif()));
  timer_->start(100);
}

void MainWindow::saveGif() {
  QPixmap pix = QPixmap::fromImage(model_->grabFramebuffer());
  QPixmap scaled_pix = pix.scaled(QSize(640, 480), Qt::IgnoreAspectRatio,
                                  Qt::SmoothTransformation);
  gif_->addFrame(scaled_pix.toImage());

  if (frames_ == 50) {
    timer_->stop();
    QString gif_path = QFileDialog::getSaveFileName(
        this, ("Save as GIF"), "image.gif", "GIF Image Files (*.gif)");

    if (!gif_path.isEmpty()) {
      gif_->save(gif_path);
    }

    delete timer_;
    delete gif_;

    for (auto observer : observers_) {
      observer->GifMade();
    }
  }
  frames_++;

  ui_->Gif->setStyleSheet(
      "color: rgb(154, 154, 154);\n border-radius: 1px;\n border-bottom: 1px "
      "solid grey;\n background-color: rgb(64, 64, 64);");
}

void MainWindow::mouseMoveEvent(QMouseEvent *cursor_position) {
  if (left_button_pressed_) {
    int rx = (cursor_position->pos().y() - click_pos_.y()) / 3;
    int ry = (cursor_position->pos().x() - click_pos_.x()) / 3;

    s21::Controller::ModelRotate(model_, rx, ry);

  } else if (right_button_pressed_) {
    int mx = (cursor_position->pos().x() - click_pos_.x()) / 12;
    int my = (click_pos_.y() - cursor_position->pos().y()) / 12;

    s21::Controller::ModelMove(model_, mx, my);
  }

  click_pos_.setX(cursor_position->pos().x());
  click_pos_.setY(cursor_position->pos().y());

  s21::Controller::ModelUpdate(model_);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  click_pos_ = event->pos();

  if (event->button() == Qt::LeftButton) {
    left_button_pressed_ = true;
  } else if (event->button() == Qt::RightButton) {
    right_button_pressed_ = true;
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Z) {
    z_pressed_ = true;
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *cursor_position) {
  left_button_pressed_ = false;
  right_button_pressed_ = false;

  click_pos_ = cursor_position->pos();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) { z_pressed_ = false; }

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0 && z_pressed_) {
    s21::Controller::ModelMoveZ(model_, event);
  } else if (event->angleDelta().y() < 0 && z_pressed_) {
    s21::Controller::ModelMoveZ(model_, event);
  }

  if (event->angleDelta().y() > 0) {
    on_Increase_clicked();

  } else if (event->angleDelta().y() < 0) {
    on_Decrease_clicked();
  }
}

void MainWindow::updateUi() {
  ui_->BackgroundColor->setStyleSheet(
      QString(
          "background-color: %1;\n border:1px solid;\n border-color: black;")
          .arg(s21::Controller::ModelGetBackgroundColorSetting(model_).name()));
  if (s21::Controller::ModelGetProjectionSetting(model_) == "Central" ||
      ui_->BigProjection->text() == "Central") {
    QString temp_string = ui_->LittleProjection->text();

    ui_->LittleProjection->setText(ui_->BigProjection->text());
    ui_->BigProjection->setText(temp_string);
  }

  ui_->VertexColor->setStyleSheet(
      QString(
          "background-color: %1;\n border:1px solid;\n border-color: black;")
          .arg(s21::Controller::ModelGetVertexColorSetting(model_).name()));
  ui_->VertexSize->setText(
      QString::number(s21::Controller::ModelGetVertexSizeSetting(model_)));

  if (s21::Controller::ModelGetVertexTypeSetting(model_) == "Absent" ||
      ui_->CentralVertex->text() == "Square") {
    QString temp_string_top = ui_->TopVertex->text();
    QString temp_string_central = ui_->CentralVertex->text();

    ui_->CentralVertex->setText(temp_string_top);
    ui_->TopVertex->setText(ui_->BottomVertex->text());
    ui_->BottomVertex->setText(temp_string_central);
  } else if (s21::Controller::ModelGetVertexTypeSetting(model_) == "Square" ||
             ui_->CentralVertex->text() == "Absent") {
    QString temp_string_bottom = ui_->BottomVertex->text();
    QString temp_string_central = ui_->CentralVertex->text();

    ui_->CentralVertex->setText(temp_string_bottom);
    ui_->BottomVertex->setText(ui_->TopVertex->text());
    ui_->TopVertex->setText(temp_string_central);
  }

  ui_->EdgeColor->setStyleSheet(
      QString("background-color: %1;\nborder:1px solid;\n border-color: black;")
          .arg(s21::Controller::ModelGetEdgeColorSetting(model_).name()));
  ui_->EdgeThickness->setText(
      QString::number(s21::Controller::ModelGetEdgeThicknessSetting(model_)));

  if (s21::Controller::ModelGetEdgeTypeSetting(model_) == "Dashed" ||
      ui_->BigEdge->text() == "Dashed") {
    QString temp_string = ui_->LittleEdge->text();

    ui_->LittleEdge->setText(ui_->BigEdge->text());
    ui_->BigEdge->setText(temp_string);
  }
}

void MainWindow::on_XSlider_valueChanged(int value) {
  s21::Controller::ModelRotate(model_, ui_->XSlider->value(),
                               ui_->YSlider->value());
  s21::Controller::ModelUpdate(model_);
}

void MainWindow::on_YSlider_valueChanged(int value) {
  s21::Controller::ModelRotate(model_, ui_->XSlider->value(),
                               ui_->YSlider->value());
  s21::Controller::ModelUpdate(model_);
}
