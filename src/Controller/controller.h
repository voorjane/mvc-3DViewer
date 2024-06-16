#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "View/mainwindow.h"

namespace s21 {
class Controller {
 public:
  static void ModelResize(MyGLWidget *model);
  static void ModelUpdate(MyGLWidget *model);
  static void ModelBackgroundColorSetSettings(MyGLWidget *model, QColor color);
  static void ModelProjectionSetSettings(MyGLWidget *model, QString type);
  static void ModelVertexColorSetSettings(MyGLWidget *model, QColor color);
  static void ModelVertexSizeSetSettings(MyGLWidget *model, int size);
  static void ModelVertexTypeSetSettings(MyGLWidget *model, QString type);
  static void ModelEdgeColorSetSettings(MyGLWidget *model, QColor color);
  static void ModelEdgeThicknessSetSettings(MyGLWidget *model, int size);
  static void ModelEdgeSizeSetSettings(s21::MyGLWidget *model, QString type);
  static void ModelInitAfterOpen(std::string filename, MyGLWidget *model);
  static int ModelGetVSize(s21::MyGLWidget *model);
  static int ModelGetFSize(s21::MyGLWidget *model);
  static void ModelIncrease(s21::MyGLWidget *model);
  static void ModelDecrease(s21::MyGLWidget *model);
  static void ClearAndLoadSettings(s21::MyGLWidget *model);
  static void ModelRotate(MyGLWidget *model, int rx, int ry);
  static void ModelMove(s21::MyGLWidget *model, int mx, int my);
  static void ModelMoveZ(s21::MyGLWidget *model, QWheelEvent *event);
  static QString ModelGetProjectionSetting(s21::MyGLWidget *model);
  static QColor ModelGetBackgroundColorSetting(s21::MyGLWidget *model);
  static QColor ModelGetVertexColorSetting(s21::MyGLWidget *model);
  static int ModelGetVertexSizeSetting(s21::MyGLWidget *model);
  static QString ModelGetVertexTypeSetting(s21::MyGLWidget *model);
  static QColor ModelGetEdgeColorSetting(s21::MyGLWidget *model);
  static int ModelGetEdgeThicknessSetting(s21::MyGLWidget *model);
  static QString ModelGetEdgeTypeSetting(s21::MyGLWidget *model);
};
}  // namespace s21

#endif  // CONTROLLER_H
