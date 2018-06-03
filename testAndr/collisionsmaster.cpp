#include "collisionsmaster.h"
#include <cmath>

CollisionsMaster::CollisionsMaster(int cageRadius) {
  this->cage = new Cage(cageRadius);
}

int CollisionsMaster::handleCollisions(std::vector<Ball *> &balls) {
  this->balls = balls;
  auto collisions = collisionsOccured();
  for (auto collision : collisions) {
    if (collision.second < 6) {
      Ball *ball = this->balls[collision.first - 6];
      int plane = collision.second;
      switch (plane) {
      case 0:
      case 3:
        ball->direction.setY(ball->direction.y() * (-1));
        break;
      case 1:
      case 2:
        ball->direction.setX(ball->direction.x() * (-1));
        break;
      case 4:
      case 5:
        ball->direction.setZ(ball->direction.z() * (-1));
        break;
      }
    } else {
      resolveBallsCollision(collision.first, collision.second);
    }
  }
  return collisions.size();
}

std::vector<std::pair<int, int>> CollisionsMaster::collisionsOccured() {
  std::vector<std::pair<int, int>> collisions;
  std::vector<QVector3D> centers = {
      this->balls[0]->toMatrix() * QVector3D(0, 0, 0),
      this->balls[1]->toMatrix() * QVector3D(0, 0, 0),
      this->balls[2]->toMatrix() * QVector3D(0, 0, 0)};

  for (int i = 0; i < 3; i++) {
    float dist0 = (float)fabs(
        centers[i].distanceToPlane(cage->FTL, cage->BTL, cage->BTR));
    if (dist0 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 0});
    float dist1 = (float)fabs(
        centers[i].distanceToPlane(cage->FTR, cage->BBR, cage->BTR));
    if (dist1 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 1});
    float dist2 = (float)fabs(
        centers[i].distanceToPlane(cage->FTL, cage->BTL, cage->BBL));
    if (dist2 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 2});
    float dist3 = (float)fabs(
        centers[i].distanceToPlane(cage->FBL, cage->BBL, cage->BBR));
    if (dist3 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 3});
    float dist4 = (float)fabs(
        centers[i].distanceToPlane(cage->FTL, cage->FTR, cage->FBR));
    if (dist4 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 4});
    float dist5 = (float)fabs(
        centers[i].distanceToPlane(cage->BTL, cage->BTR, cage->BBR));
    if (dist5 <= this->balls[i]->radius)
      collisions.push_back({6 + i, 5});
  }

  float dist67 = centers[0].distanceToPoint(centers[1]);
  if (dist67 <= this->balls[0]->radius + this->balls[1]->radius)
    collisions.push_back({6, 7});

  float dist68 = centers[0].distanceToPoint(centers[2]);
  if (dist68 <= this->balls[0]->radius + this->balls[2]->radius)
    collisions.push_back({6, 8});

  float dist78 = centers[1].distanceToPoint(centers[2]);
  if (dist78 <= this->balls[1]->radius + this->balls[2]->radius)
    collisions.push_back({7, 8});

  return collisions;
}

void CollisionsMaster::resolveBallsCollision(int bi1, int bi2) {
  double theta2, phi2, st, ct, sp, cp, vx1r, vy1r, vz1r, fvz1r, thetav, phiv,
      dr, alpha, beta, sbeta, cbeta, a, dvz2, vx2r, vy2r, vz2r, vx_cm, vy_cm,
      vz_cm;

  /// **************************
  ///   initialize some variables
  QVector3D center(0.0, 0.0, 0.0);
  Ball *b1 = this->balls[bi1 - 6];
  Ball *b2 = this->balls[bi2 - 6];
  QVector3D c1 = b1->toMatrix() * center;
  QVector3D c2 = b2->toMatrix() * center;
  double r12 = b1->radius + b2->radius;
  double m1 = b1->radius;
  double m2 = b2->radius;
  double vx1 = b1->direction.x();
  double vy1 = b1->direction.y();
  double vz1 = b1->direction.z();
  double vx2 = b2->direction.x();
  double vy2 = b2->direction.y();
  double vz2 = b2->direction.z();

  double m21 = m2 / m1;
  double x21 = c2.x() - c1.x();
  double y21 = c2.y() - c1.y();
  double z21 = c2.z() - c1.z();
  double vx21 = vx2 - vx1;
  double vy21 = vy2 - vy1;
  double vz21 = vz2 - vz1;

  vx_cm = (m1 * vx1 + m2 * vx2) / (m1 + m2);
  vy_cm = (m1 * vy1 + m2 * vy2) / (m1 + m2);
  vz_cm = (m1 * vz1 + m2 * vz2) / (m1 + m2);

  /// **************************
  ///   calculate relative distance and relative speed ***
  double d = sqrt(x21 * x21 + y21 * y21 + z21 * z21);
  double v = sqrt(vx21 * vx21 + vy21 * vy21 + vz21 * vz21);

  /// **************************
  ///   return if relative speed = 0
  if (v == 0)
    return;

  /// **************************
  ///   shift coordinate system so that ball 1 is at the origin
  b2->setTranslation(x21, y21, z21);
  c2 = b2->toMatrix() * center;

  /// **************************
  ///   boost coordinate system so that ball 2 is resting
  b1->direction = QVector3D(-1 * vx21, -1 * vy21, -1 * vz21);
  vx1 = b1->direction.x();
  vy1 = b1->direction.y();
  vz1 = b1->direction.z();

  /// **************************
  ///   find the polar coordinates of the location of ball 2
  theta2 = acos(c2.z() / d);
  if (c2.x() == 0 && c2.y() == 0) {
    phi2 = 0;
  } else {
    phi2 = atan2(c2.y(), c2.x());
  }
  st = sin(theta2);
  ct = c2.z() / d;
  sp = sin(phi2);
  cp = cos(phi2);

  /// **************************
  ///   express the velocity vector of ball 1 in a rotated coordinate
  ///          system where ball 2 lies on the z-axis
  vx1r = ct * cp * vx1 + ct * sp * vy1 - st * vz1;
  vy1r = cp * vy1 - sp * vx1;
  vz1r = st * cp * vx1 + st * sp * vy1 + ct * vz1;
  fvz1r = vz1r / v;
  if (fvz1r > 1) {
    fvz1r = 1;
  } // fix for possible rounding errors
  else if (fvz1r < -1) {
    fvz1r = -1;
  }
  thetav = acos(fvz1r);
  if (vx1r == 0 && vy1r == 0) {
    phiv = 0;
  } else {
    phiv = atan2(vy1r, vx1r);
  }

  /// **************************
  ///   calculate the normalized impact parameter
  dr = d * sin(thetav) / r12;

  /// **************************
  ///   calculate impact angles
  alpha = asin(-dr);
  beta = phiv;
  sbeta = sin(beta);
  cbeta = cos(beta);

  /// **************************
  ///   update positions and reverse the coordinate shift ATTENTION
  b2->setTranslation(c2.x() + c1.x(), c2.y() + c1.y(), c2.z() + c1.z());

  /// **************************
  ///   update velocities
  a = tan(thetav + alpha);

  dvz2 = 2 * (vz1r + a * (cbeta * vx1r + sbeta * vy1r)) /
         ((1 + a * a) * (1 + m21));

  vz2r = dvz2;
  vx2r = a * cbeta * dvz2;
  vy2r = a * sbeta * dvz2;
  vz1r = vz1r - m21 * vz2r;
  vx1r = vx1r - m21 * vx2r;
  vy1r = vy1r - m21 * vy2r;
  /// **************************
  ///   rotate the velocity vectors back and add the initial velocity
  ///           vector of ball 2 to retrieve the original coordinate system
  b1->direction = QVector3D((ct * cp * vx1r - sp * vy1r + st * cp * vz1r + vx2),
                            (ct * sp * vx1r + cp * vy1r + st * sp * vz1r + vy2),
                            (ct * vz1r - st * vx1r + vz2));
  b2->direction = QVector3D((ct * cp * vx2r - sp * vy2r + st * cp * vz2r + vx2),
                            (ct * sp * vx2r + cp * vy2r + st * sp * vz2r + vy2),
                            (ct * vz2r - st * vx2r + vz2));

  b1->direction = QVector3D(((b1->direction.x() - vx_cm) * R + vx_cm),
                            ((b1->direction.y() - vy_cm) * R + vy_cm),
                            ((b1->direction.z() - vz_cm) * R + vz_cm));
  b2->direction = QVector3D(((b2->direction.x() - vx_cm) * R + vx_cm),
                            ((b2->direction.y() - vy_cm) * R + vy_cm),
                            ((b2->direction.z() - vz_cm) * R + vz_cm));
}
