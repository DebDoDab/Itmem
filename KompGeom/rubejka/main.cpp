#include <bits/stdc++.h>

using namespace std;

class Village {
private:
    string name;
    unsigned long long population;

public:
    Village(string name_, unsigned long long population_) {
        name = name_;
        population = population_;
    }

    string getName() const {
        return name;
    }

    unsigned long long getPopulation() const {
        return population;
    }
};


class City {
private:
    string name;
    unsigned long long population;

public:
    City(string name_, unsigned long long population_) {
        name = name_;
        population = population_;
    }

    string getName() const {
        return name;
    }

    unsigned long long getPopulation() const {
        return population;
    }
};


class Region {
private:
    string name;
    unsigned long long population;

public:
    Region(string name_, const vector<Village>& villages, const vector<City>& cities) {
        name = name_;
        population = 0;
        for (const Village& village : villages) {
            population += village.getPopulation();
        }
        for (const City& city : cities) {
            population += city.getPopulation();
        }
    }

    string getName() const {
        return name;
    }

    unsigned long long getPopulation() const {
        return population;
    }
};


class Country {
private:
    string name;
    unsigned long long population;

public:
    Country(string name_, const vector<Region>& regions) {
        name = name_;
        for (const Region& region : regions) {
            population += region.getPopulation();
        }
    }

    string getName() const {
        return name;
    }

    unsigned long long getPopulation() const {
        return population;
    }
};

int main() {
    Village x("asd", 123);
    Village y("qwe", 321);
    City z("sasd", 4123);
    City a("sdsads", 1233);
    City g("hasd", 10000);
    Region t ("hell", {x}, {z});
    Region t2("asd", {y}, {a, g});
    Country er("bel", {t, t2});

    cout << x.getPopulation() << endl;
    cout << y.getPopulation() << endl;
    cout << z.getPopulation() << endl;
    cout << a.getPopulation() << endl;
    cout << g.getPopulation() << endl;
    cout << t.getPopulation() << endl;
    cout << t2.getPopulation() << endl;
    cout << er.getPopulation() << endl;
}
