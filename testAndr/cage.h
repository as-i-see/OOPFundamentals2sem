#ifndef CAGE_H
#define CAGE_H
#include <QVector3D>
#include <vector>

class Cage {
public:
  Cage(int);
  std::vector<QVector3D> dots;
  QVector3D FTL, FBL, FBR, FTR, BTL, BBL, BBR, BTR;
};

#endif // CAGE_H
