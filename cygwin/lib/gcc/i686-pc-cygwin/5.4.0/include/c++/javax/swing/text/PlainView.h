
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_text_PlainView__
#define __javax_swing_text_PlainView__

#pragma interface

#include <javax/swing/text/View.h>
#include <gcj/array.h>

extern "Java"
{
  namespace java
  {
    namespace awt
    {
        class Color;
        class Component;
        class Font;
        class FontMetrics;
        class Graphics;
        class Rectangle;
        class Shape;
    }
  }
  namespace javax
  {
    namespace swing
    {
      namespace event
      {
          class DocumentEvent;
      }
      namespace text
      {
          class Element;
          class PlainView;
          class Position$Bias;
          class Segment;
          class ViewFactory;
      }
    }
  }
}

class javax::swing::text::PlainView : public ::javax::swing::text::View
{

public:
  PlainView(::javax::swing::text::Element *);
public: // actually protected
  virtual void updateMetrics();
  virtual ::java::awt::Rectangle * lineToRect(::java::awt::Shape *, jint);
public:
  virtual ::java::awt::Shape * modelToView(jint, ::java::awt::Shape *, ::javax::swing::text::Position$Bias *);
public: // actually protected
  virtual void drawLine(jint, ::java::awt::Graphics *, jint, jint);
  virtual jint drawSelectedText(::java::awt::Graphics *, jint, jint, jint, jint);
  virtual jint drawUnselectedText(::java::awt::Graphics *, jint, jint, jint, jint);
public:
  virtual void paint(::java::awt::Graphics *, ::java::awt::Shape *);
public: // actually protected
  virtual jint getTabSize();
public:
  virtual jfloat nextTabStop(jfloat, jint);
public: // actually package-private
  virtual jfloat determineMaxLineLength();
public:
  virtual jfloat getPreferredSpan(jint);
  virtual jint viewToModel(jfloat, jfloat, ::java::awt::Shape *, JArray< ::javax::swing::text::Position$Bias * > *);
public: // actually protected
  virtual void updateDamage(::javax::swing::event::DocumentEvent *, ::java::awt::Shape *, ::javax::swing::text::ViewFactory *);
public:
  virtual void insertUpdate(::javax::swing::event::DocumentEvent *, ::java::awt::Shape *, ::javax::swing::text::ViewFactory *);
  virtual void removeUpdate(::javax::swing::event::DocumentEvent *, ::java::awt::Shape *, ::javax::swing::text::ViewFactory *);
  virtual void changedUpdate(::javax::swing::event::DocumentEvent *, ::java::awt::Shape *, ::javax::swing::text::ViewFactory *);
public: // actually protected
  virtual void damageLineRange(jint, jint, ::java::awt::Shape *, ::java::awt::Component *);
  virtual ::javax::swing::text::Segment * getLineBuffer();
private:
  void findLongestLine(jint, jint);
  jint getLineLength(jint);
public: // actually package-private
  ::java::awt::Color * __attribute__((aligned(__alignof__( ::javax::swing::text::View)))) selectedColor;
  ::java::awt::Color * unselectedColor;
  ::java::awt::Color * disabledColor;
  jint selectionStart;
  jint selectionEnd;
  ::java::awt::Font * font;
  jfloat maxLineLength;
  ::javax::swing::text::Element * longestLine;
public: // actually protected
  ::java::awt::FontMetrics * metrics;
private:
  ::javax::swing::text::Segment * lineBuffer;
  jint tabBase;
  jint tabSize;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_text_PlainView__
