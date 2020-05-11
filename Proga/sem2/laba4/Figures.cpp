//
// Created by vadim on 7.02.20.
//
#include <bits/stdc++.h>
#include "Figures.h"

bool Rectangle::operator==(const IPhysObject& x) const {
    return getMass() == x.getMass();
}

bool Rectangle::operator<(const IPhysObject& x) const {
    return getMass() < x.getMass();
}

double Rectangle::getSquare() const {
    return a * b;
}

double Rectangle::getPerimeter() const {
    return (a + b) * 2.;
}

double Rectangle::getMass() const {
    return mass;
}

Vector2D Rectangle::getPosition() const {
    return position;
}

void Rectangle::draw() const {
    cout << "name = " << name << ";\na = " << a << ", b = " << b << ";\n";
    cout << "mass = " << mass << ";\nsize = " << getSize() << ";\n";
    cout << "position: x = " << position.x << ", y = " << position.y << ";\n\n";
}

void Rectangle::initFromDialogue() {
    double a_, b_, mass_;
    Vector2D position_;
    cout << "Enter Rectangles sides: a, b; Then enter mass and position (x and y)\n";
    cin >> a_ >> b_ >> mass_ >> position_.x >> position_.y;
    a = a_; b = b_;
    mass = mass_;
    position = position_;
    cout << "Created successfully.\n";
}

string Rectangle::getClassName() const {
    return name;
}

unsigned Rectangle::getSize() const {
    return sizeof(*this);
}

Rectangle::Rectangle() {
    a = b = mass = 0;
    position.x = position.y = 0;
}

Rectangle::Rectangle(const double& a_, const double& b_, const double& mass_, const Vector2D& position_) {
    a = a_; b = b_;
    mass = mass_;
    position = position_;
}

Rectangle::Rectangle(const Rectangle& x) {
    a = x.a, b = x.b;
    mass = x.mass;
    position = x.position;
}


bool Parallelogram::operator==(const IPhysObject& x) const {
    return getMass() == x.getMass();
}

bool Parallelogram::operator<(const IPhysObject& x) const {
    return getMass() < x.getMass();
}

double Parallelogram::getSquare() const {
    return a * b * sin(alpha);
}

double Parallelogram::getPerimeter() const {
    return (a + b) * 2.;
}

double Parallelogram::getMass() const {
    return mass;
}

Vector2D Parallelogram::getPosition() const {
    return position;
}

void Parallelogram::draw() const {
    cout << "name = " << name << ";\na = " << a << ", b = " << b << "; angle = " << alpha << "\n";
    cout << "mass = " << mass << ";\nsize = " << getSize() << ";\n";
    cout << "position: x = " << position.x << ", y = " << position.y << ";\n\n";
}

void Parallelogram::initFromDialogue() {
    double a_, b_, alpha_, mass_;
    Vector2D position_;
    cout << "Enter Parallelogram sides: a, b and angle (0; Pi); Then enter mass and position (x and y)\n";
    cin >> a_ >> b_ >> alpha_ >> mass_ >> position_.x >> position_.y;
    a = a_; b = b_;
    alpha = alpha_;
    mass = mass_;
    position = position_;
    cout << "Created successfully.\n";
}

string Parallelogram::getClassName() const {
    return name;
}

unsigned Parallelogram::getSize() const {
    return sizeof(*this);
}

Parallelogram::Parallelogram() {
    a = b = mass = 0;
    alpha = acos(-1.) / 2.;
    position.x = position.y = 0;
}

Parallelogram::Parallelogram(const double& a_, const double& b_, const double& alpha_,
        const double& mass_, const Vector2D& position_) {
    a = a_; b = b_;
    alpha = alpha_;
    mass = mass_;
    position = position_;
}

Parallelogram::Parallelogram(const Parallelogram& x) {
    a = x.a, b = x.b;
    alpha = x.alpha;
    mass = x.mass;
    position = x.position;
}

Vector2D::Vector2D() {
    x = y = 0;
}
