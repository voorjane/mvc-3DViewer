#include "settings.h"

void s21::Settings::SaveFileSettings() {
  QSettings settingsFile("s21", "3DViewer");

  settingsFile.setValue("backgroundColor", background_color.name());
  settingsFile.setValue("projection", projection);

  settingsFile.setValue("vertexColor", vertex_color.name());
  settingsFile.setValue("vertexSize", vertex_size);
  settingsFile.setValue("vertexType", vertex_type);

  settingsFile.setValue("edgeColor", edge_color.name());
  settingsFile.setValue("edgeThickness", edge_thickness);
  settingsFile.setValue("edgeType", edge_type);
}

void s21::Settings::LoadFileSettings() {
  QSettings settingsFile("s21", "3DViewer");

  background_color =
      settingsFile.value("backgroundColor", background_color.name()).toString();
  projection = settingsFile.value("projection", projection).toString();

  vertex_color =
      settingsFile.value("vertexColor", vertex_color.name()).toString();
  vertex_size = settingsFile.value("vertexSize", vertex_size).toInt();
  vertex_type = settingsFile.value("vertexType", vertex_type).toString();

  edge_color = settingsFile.value("edgeColor", edge_color.name()).toString();
  edge_thickness = settingsFile.value("edgeThickness", edge_thickness).toInt();
  edge_type = settingsFile.value("edgeType", edge_type).toString();
}

void s21::Settings::ClearFileSettings() {
  QSettings settingsFile("s21", "3DViewer");

  settingsFile.clear();
}