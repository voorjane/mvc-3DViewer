#include "controller.h"

#include <utility>

#include "Model/objparser.h"
#include "Model/transformation.h"

void s21::Controller::ModelResize(MyGLWidget *model) {
  model->resize(800, 800);
}

void s21::Controller::ModelUpdate(s21::MyGLWidget *model) { model->update(); }

void s21::Controller::ModelBackgroundColorSetSettings(MyGLWidget *model,
                                                      QColor color) {
  model->settings.background_color = color;
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelProjectionSetSettings(s21::MyGLWidget *model,
                                                 QString type) {
  model->settings.projection = std::move(type);
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelVertexColorSetSettings(MyGLWidget *model,
                                                  QColor color) {
  model->settings.vertex_color = color;
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelVertexSizeSetSettings(MyGLWidget *model, int size) {
  model->settings.vertex_size = size;
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelVertexTypeSetSettings(s21::MyGLWidget *model,
                                                 QString type) {
  model->settings.vertex_type = std::move(type);
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelEdgeColorSetSettings(s21::MyGLWidget *model,
                                                QColor color) {
  model->settings.edge_color = color;
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelEdgeThicknessSetSettings(MyGLWidget *model,
                                                    int size) {
  model->settings.edge_thickness = size;
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelEdgeSizeSetSettings(s21::MyGLWidget *model,
                                               QString type) {
  model->settings.edge_type = std::move(type);
  model->settings.SaveFileSettings();
}

void s21::Controller::ModelInitAfterOpen(std::string filename,
                                         MyGLWidget *model) {
  s21::ObjParser parser(std::move(filename));
  std::pair<std::vector<double>, std::vector<unsigned>> vector_v_f_pair =
      parser.Parse();
  model->vector_v_ = vector_v_f_pair.first;
  model->vector_f_ = vector_v_f_pair.second;

  s21::Transformation transformation(model->vector_v_);
  model->vector_v_ = transformation.GetVector();
}

int s21::Controller::ModelGetVSize(s21::MyGLWidget *model) {
  return model->vector_v_.size();
}

int s21::Controller::ModelGetFSize(s21::MyGLWidget *model) {
  return model->vector_f_.size();
}

void s21::Controller::ModelIncrease(s21::MyGLWidget *model) {
  s21::TransformationFacade transformation(model->vector_v_);
  transformation.Scale(110);
  model->vector_v_ = transformation.GetVector();
}

void s21::Controller::ModelDecrease(s21::MyGLWidget *model) {
  s21::TransformationFacade transformation(model->vector_v_);
  transformation.Scale(90);
  model->vector_v_ = transformation.GetVector();
}

void s21::Controller::ClearAndLoadSettings(s21::MyGLWidget *model) {
  model->settings.ClearFileSettings();
  model->settings.LoadFileSettings();
}

void s21::Controller::ModelRotate(MyGLWidget *model, int rx, int ry) {
  s21::TransformationFacade transformation(model->vector_v_);
  transformation.Rotate((float)rx, (float)ry);

  model->vector_v_ = transformation.GetVector();
}

void s21::Controller::ModelMove(s21::MyGLWidget *model, int mx, int my) {
  s21::TransformationFacade transformation(model->vector_v_);
  transformation.Move((float)mx, (float)my, 0);

  model->vector_v_ = transformation.GetVector();
}

void s21::Controller::ModelMoveZ(s21::MyGLWidget *model, QWheelEvent *event) {
  s21::TransformationFacade transformation(model->vector_v_);
  transformation.Move(0, 0, event->angleDelta().y() / 12);
  model->vector_v_ = transformation.GetVector();
}

QString s21::Controller::ModelGetProjectionSetting(s21::MyGLWidget *model) {
  return model->settings.projection;
}

QColor s21::Controller::ModelGetBackgroundColorSetting(s21::MyGLWidget *model) {
  return model->settings.background_color;
}

QColor s21::Controller::ModelGetVertexColorSetting(s21::MyGLWidget *model) {
  return model->settings.vertex_color;
}

int s21::Controller::ModelGetVertexSizeSetting(s21::MyGLWidget *model) {
  return model->settings.vertex_size;
}

QString s21::Controller::ModelGetVertexTypeSetting(s21::MyGLWidget *model) {
  return model->settings.vertex_type;
}

QColor s21::Controller::ModelGetEdgeColorSetting(s21::MyGLWidget *model) {
  return model->settings.edge_color;
}

int s21::Controller::ModelGetEdgeThicknessSetting(s21::MyGLWidget *model) {
  return model->settings.edge_thickness;
}

QString s21::Controller::ModelGetEdgeTypeSetting(s21::MyGLWidget *model) {
  return model->settings.edge_type;
}
