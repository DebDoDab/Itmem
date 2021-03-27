#include <bits/stdc++.h>
#include "Figures.h"
using namespace std;


int main() {
    vector<IFigure*> A;
    string s;
    cout << "Write 'add %Figure_name%' to add that figure\n";
    cout << "%Figure_name% should ne 'parallelogram' or 'rectangle'\n";
    cout << "Write 'showAll' to draw all figures\n";
    cout << "Write 'sortByMass' to sort objects by mass\n";
    cout << "Write 'sumSquare' or 'sumPerimeter' to get summary square or perimeter respectively\n";
    cout << "Write 'sumSize' to get summary size of all objects\n";
    cout << "Write 'massCenter' to get mass center vector(x, y)\n";

    while (cin >> s) {
        if (s == "add") {
            cin >> s;
            transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(c); });
            if (s == "parallelogram") {
                A.push_back(new Parallelogram());
            } else if (s == "rectangle") {
                A.push_back(new Rectangle());
            } else {
                cout << "Wrong figure name; you entered '" << s << "'; try again\n";
                continue;
            }
            A.back()->initFromDialogue();
        } else if (s == "showAll") {
            for (auto &x : A) {
                x->draw();
            }
        } else if (s == "sumSquare") {
            double ans = 0;
            for (auto& x : A) {
                ans += x->getSquare();
            }
            cout << "Summary square = " << ans << "\n";
        } else if (s == "sumPerimeter") {
            double ans = 0;
            for (auto& x : A) {
                ans += x->getPerimeter();
            }
            cout << "Summary perimeter = " << ans << "\n";
        } else if (s == "sumSize") {
            double ans = 0;
            for (auto& x : A) {
                ans += x->getSize();
            }
            cout << "Summary size = " << ans << "\n";
        } else if (s == "sortByMass") {
            sort(A.begin(), A.end(), [](IFigure* x, IFigure* y) {return *x < *y;});
            cout << "Sorted.\n";
        } else if (s == "massCenter") {
            Vector2D center;
            double massSum = 0;
            for (auto& x : A) {
                center.x += x->getPosition().x * x->getMass();
                center.y += x->getPosition().y * x->getMass();
                massSum += x->getMass();
            }
            center.x /= massSum;
            center.y /= massSum;
            cout << "Mass center = (" << center.x << "; " << center.y << ")\n";
        } else {
            cout << "wrong command; you entered '" << s << "'; try again\n";
            continue;
        }


    }
}
