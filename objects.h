#pragma once
#define _USE_MATH_DEFINES
#include <cstdint>
#include <stdexcept>
#include <cmath>
#include <string>



namespace obj {

    struct Point {
        Point() = default;
        Point(double x, double y, double z)
            : x(x)
            , y(y)
            , z(z) {
        }
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };

    class Object {
    public:

        virtual ~Object() = default;

        virtual Point GetPoint(double t) const = 0;
        virtual Point Getderivative(double t) const = 0;
        virtual double GetRadius() const = 0;
        virtual std::string GetType() const = 0;
    };

    class Circle : public Object {
    public:

        Circle& SetRadius(double radius) {
            if (radius < 0) {
                throw std::invalid_argument("Negative radius");
            }
            radius_ = radius;
            return *this;
        }

        Point GetPoint(double t) const override {
            Point result;
            result.x = radius_ * cos(t);
            result.y = radius_ * sin(t);
            result.z = 0.0;
            return result;
        }
        Point Getderivative(double t) const override {
            Point result;
            result.x = radius_ * -sin(t);
            result.y = radius_ * cos(t);
            result.z = 0.0;
            return result;
        }
        double GetRadius() const override {
            return radius_;
        }

        std::string GetType() const override { return "Circle"; };

    private:

        double radius_;
    };

    class Ellipse : public Object {
    public:
        Ellipse& SetRadiuses(double radius1, double radius2) {
            if (radius1 < 0 || radius2 < 0) {
                throw std::invalid_argument("Negative radius");
            }
            radius1_ = radius1;
            radius2_ = radius2;
            return *this;
        }

        Point GetPoint(double t) const override {
            Point result;
            result.x = radius1_ * cos(t);
            result.y = radius2_ * sin(t);
            result.z = 0.0;
            return result;
        }
        Point Getderivative(double t) const override {
            Point result;
            result.x = radius1_ * -sin(t);
            result.y = radius2_ * cos(t);
            result.z = 0.0;
            return result;
        }
        std::pair<double, double> GetRadii() {
            return std::pair<double, double>(radius1_, radius2_);
        }

        std::string GetType() const override { return "Ellipse"; };

        double GetRadius() const override {
            return radius1_;
        }

    private:
        double radius1_;
        double radius2_;
    };

    class Helix : public Object {
    public:
        /*Helix(double radius, double step) {
            if (radius < 0) {
                throw std::invalid_argument("Negative radius");
            }
            radius_ = radius;
            step_ = step;
        }*/

        Helix& SetRadius(double radius) {
            if (radius < 0) {
                throw std::invalid_argument("Negative radius");
            }
            radius_ = radius;
            return *this;
        }

        Helix& SetStep(double step) {
            if (step < 0) {
                throw std::invalid_argument("Negative step");
            }
            step_ = step;
            return *this;
        }

        Point GetPoint(double t) const override {
            Point result;
            result.x = radius_ * cos(t);
            result.y = radius_ * sin(t);
            result.z = step_ * t / (M_PI * 2);
            return result;
        }
        Point Getderivative(double t) const override {
            Point result;
            result.x = radius_* -sin(t);
            result.y = radius_ * cos(t);
            result.z = step_ / (M_PI * 2);
            return result;
        }

        double GetRadius() const override {
            return radius_;
        }

        std::string GetType() const override { return "Helix"; };

    private:
        double radius_;
        double step_;
    };
}