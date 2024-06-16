#include "myglwidget.h"

void s21::MyGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void s21::MyGLWidget::paintGL() {
  glClearColor(settings.background_color.redF(),
               settings.background_color.greenF(),
               settings.background_color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glVertexPointer(3, GL_DOUBLE, 0, vector_v_.data());
  glEnableClientState(GL_VERTEX_ARRAY);

  if (settings.projection == "Central") {
    glFrustum(-1, 2.55, -1, 1, 1, 15);
    glTranslated(0, 0, -10);
  } else if (settings.projection == "Parallel") {
    glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
  }

  setEdges();
  setVertices();

  glDisableClientState(GL_VERTEX_ARRAY);
}

void s21::MyGLWidget::setVertices() const {
  glPointSize((float)settings.vertex_size);
  glColor3f(settings.vertex_color.redF(), settings.vertex_color.greenF(),
            settings.vertex_color.blueF());

  if (settings.vertex_type == "Circle") {
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, (int)vector_v_.size() / 3);
    glDisable(GL_POINT_SMOOTH);
  } else if (settings.vertex_type == "Square") {
    glDrawArrays(GL_POINTS, 0, (int)vector_v_.size() / 3);
  }
}

void s21::MyGLWidget::setEdges() {
  if (settings.edge_type == "Solid") {
    glDisable(GL_LINE_STIPPLE);
  } else if (settings.edge_type == "Dashed") {
    glLineStipple(1, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  }

  glLineWidth((float)settings.edge_thickness);
  glColor3f(settings.edge_color.redF(), settings.edge_color.greenF(),
            settings.edge_color.blueF());

  glDrawElements(GL_LINES, (int)vector_f_.size(), GL_UNSIGNED_INT,
                 vector_f_.data());
}
