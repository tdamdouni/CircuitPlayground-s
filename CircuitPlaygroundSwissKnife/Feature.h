#ifndef FEATURE_H
#define FEATURE_H

class Feature {
public:
  virtual ~Feature() {}

  virtual void loop() = 0;
  virtual void startPressed() = 0;
  virtual void modePressed() = 0;
  virtual void tapDetected() = 0;
};

// Linear interpolation function is handy for all the modes to use.
float lerp(float x, float xmin, float xmax, float ymin, float ymax) {
  if (x >= xmax) {
    return ymax;
  }
  if (x <= xmin) {
    return ymin;
  }
  return ymin + (ymax-ymin)*((x-xmin)/(xmax-xmin));
}

#endif
