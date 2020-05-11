//
// Created by vadim on 7.02.20.
//
#include <bits/stdc++.h>
using namespace std;
#pragma once

class IGeoFig {
public:
    virtual double getSquare() const = 0;
    virtual double getPerimeter() const = 0;
};

class Vector2D {
public:
    double x, y;

    Vector2D();
};

class IPhysObject {
public:
    virtual double getMass() const = 0;
    virtual Vector2D getPosition() const = 0;
    virtual bool operator==(const IPhysObject&) const = 0;
    virtual bool operator<(const IPhysObject&) const = 0;
};

class IPrintable {
public:
    virtual void draw() const = 0;
};

class IDialogueInitiable {
public:
    virtual void initFromDialogue() = 0;
};

class IBaseObject {
public:
    virtual string getClassName() const = 0;
    virtual unsigned getSize() const = 0;
};




class IFigure : public IGeoFig, public IPhysObject, public IPrintable, public IDialogueInitiable, public IBaseObject {
public:

};



class Rectangle : public IFigure {
private:
    const string name = "Rectangle";
    double a, b;
    double mass;
    Vector2D position{};

public:

    bool operator==(const IPhysObject&) const override;

    bool operator<(const IPhysObject&) const override;

    double getSquare() const override;

    double getPerimeter() const override;

    double getMass() const override;

    Vector2D getPosition() const override;

    void draw() const override;

    void initFromDialogue() override;

    string getClassName() const override;

    unsigned getSize() const override;

    Rectangle();

    Rectangle(const double&, const double&,
            const double&, const Vector2D&);

    Rectangle(const Rectangle&);
};

class Parallelogram : public IFigure {
private:
    const string name = "Parallelogram";
    double a, b, alpha;
    double mass;
    Vector2D position{};

public:

    bool operator==(const IPhysObject&) const override;

    bool operator<(const IPhysObject&) const override;

    double getSquare() const override;

    double getPerimeter() const override;

    double getMass() const override;

    Vector2D getPosition() const override;

    void draw() const override;

    void initFromDialogue() override;

    string getClassName() const override;

    unsigned getSize() const override;

    Parallelogram();

    Parallelogram(const double&, const double&, const double&,
            const double&, const Vector2D&);

    Parallelogram(const Parallelogram&);
};
