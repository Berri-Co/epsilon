#include "zoom_parameter_controller.h"
#include <assert.h>
#include <math.h>

namespace Shared {

ZoomParameterController::ZoomParameterController(Responder * parentResponder, InteractiveCurveViewRange * interactiveRange, CurveView * curveView) :
  ViewController(parentResponder),
  m_contentView(ContentView(curveView)),
  m_interactiveRange(interactiveRange)
{
}

const char * ZoomParameterController::title() const {
  return "Zoom interactif";
}

View * ZoomParameterController::view() {
  return &m_contentView;
}

bool ZoomParameterController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Plus) {
    m_interactiveRange->zoom(1.0f/3.0f);
    m_contentView.curveView()->reload();
    return true;
  }
  if (event == Ion::Events::Minus) {
    m_interactiveRange->zoom(3.0f/4.0f);
    m_contentView.curveView()->reload();
    return true;
  }
  if (event == Ion::Events::Up) {
    m_interactiveRange->panWithVector(0.0f, m_interactiveRange->yGridUnit());
    m_contentView.curveView()->reload();
    return true;
  }
  if (event == Ion::Events::Down) {
    m_interactiveRange->panWithVector(0.0f, -m_interactiveRange->yGridUnit());
    m_contentView.curveView()->reload();
    return true;
  }
  if (event == Ion::Events::Left) {
    m_interactiveRange->panWithVector(-m_interactiveRange->xGridUnit(), 0.0f);
    m_contentView.curveView()->reload();
    return true;
  }
  if (event == Ion::Events::Right) {
    m_interactiveRange->panWithVector(m_interactiveRange->xGridUnit(), 0.0f);
    m_contentView.curveView()->reload();
    return true;
  }

  return false;
}

void ZoomParameterController::didBecomeFirstResponder() {
  m_contentView.layoutSubviews();
}

/* Content View */

ZoomParameterController::ContentView::ContentView(CurveView * curveView) :
  m_curveView(curveView)
{
}

int ZoomParameterController::ContentView::numberOfSubviews() const {
  return 2;
}

View * ZoomParameterController::ContentView::subviewAtIndex(int index) {
  assert(index >= 0 && index < 2);
  if (index == 0) {
    return m_curveView;
  }
  return &m_legendView;
}

void ZoomParameterController::ContentView::layoutSubviews() {
  m_curveView->setFrame(bounds());
  m_legendView.setFrame(KDRect(0, bounds().height() - k_legendHeight, bounds().width(), k_legendHeight));
}

CurveView * ZoomParameterController::ContentView::curveView() {
  return m_curveView;
}

/* Legend View */

ZoomParameterController::ContentView::LegendView::LegendView() :
  m_legends{PointerTextView(KDText::FontSize::Small, "ZOOM+", 0.0f, 0.5f, KDColorBlack, Palette::GreyBright),
    PointerTextView(KDText::FontSize::Small, "HAUT", 0.0f, 0.5f, KDColorBlack, Palette::GreyBright),
    PointerTextView(KDText::FontSize::Small, "GAUCHE", 0.0f, 0.5f, KDColorBlack, Palette::GreyBright),
    PointerTextView(KDText::FontSize::Small, "ZOOM-", 1.0f, 0.5f, KDColorBlack, Palette::GreyBright),
    PointerTextView(KDText::FontSize::Small, "BAS", 1.0f, 0.5f, KDColorBlack, Palette::GreyBright),
    PointerTextView(KDText::FontSize::Small, "DROITE", 1.0f, 0.5f, KDColorBlack, Palette::GreyBright)}
{
}

void ZoomParameterController::ContentView::LegendView::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(KDRect(0, bounds().height() - k_legendHeight, bounds().width(), k_legendHeight), Palette::GreyBright);
}

int ZoomParameterController::ContentView::LegendView::numberOfSubviews() const {
  return 6;
}

View * ZoomParameterController::ContentView::LegendView::subviewAtIndex(int index) {
  assert(index >= 0 && index < 6);
  return &m_legends[index];
}

void ZoomParameterController::ContentView::LegendView::layoutSubviews() {
  KDCoordinate width = bounds().width();
  KDCoordinate heigth = bounds().height();
  for (int row = 0; row < 3; row++) {
    m_legends[row].setFrame(KDRect(k_tokenWidth, row*heigth/3, width/2 - k_tokenWidth, heigth/3));
    m_legends[3+row].setFrame(KDRect(width/2, row*heigth/3, width/2 - k_tokenWidth, heigth/3));
  }
}

}