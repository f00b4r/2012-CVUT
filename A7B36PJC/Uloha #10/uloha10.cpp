#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class Mobility {
public:

    bool is_wheeled() {
        return false;
    }

    bool is_tracked() {
        return false;
    }

    bool is_foot() {
        return false;
    }

    virtual string type() = 0;
};

class Unit {
protected:
    Mobility* mobility;
public:

    void salut() {
        cout << "I am " << name() << ". My type is " << type() << ". My mobility is " << (mobility != NULL ? mobility->type() : "unknown") << "." << endl;
    }

    virtual string name() = 0;
    virtual string type() = 0;

    ~Unit() {
        delete mobility;
    }
};

class Tracked : public Mobility {
public:

    bool is_tracked() {
        return true;
    }

    virtual string type() {
        return "track";
    }
};

class Wheeled : public Mobility {
public:

    bool is_wheeled() {
        return true;
    }

    virtual string type() {
        return "wheel";
    }
};

class Foot : public Mobility {
public:

    bool is_foot() {
        return true;
    }

    virtual string type() {
        return "foot";
    }
};

class Harvest : public Unit {
public:

    virtual string type() {
        return "Harvest";
    }
};

class Attack : public Unit {
public:

    virtual string type() {
        return "Attack";
    }
};

class Infantry : public Attack {
public:

    Infantry() {
        this->mobility = new Foot();
    }

    virtual string name() {
        return "infantry";
    }
};

class Quad : public Attack {
public:

    Quad() {
        this->mobility = new Tracked();
    }

    virtual string name() {
        return "quad";
    }
};

class Trike : public Attack {
public:

    Trike() {
        this->mobility = new Wheeled();
    }

    virtual string name() {
        return "trike";
    }
};

class Harvester : public Harvest {
public:

    Harvester() {
        this->mobility = new Tracked();
    }

    virtual string name() {
        return "harvester";
    }
};

class UnitFactory {
public:

    Quad* create_quad() {
        return new Quad();
    }

    Trike* create_trike() {
        return new Trike();
    }

    Infantry* create_infantry() {
        return new Infantry();
    }

    Harvester* create_harvester() {
        return new Harvester();
    }
};

int main(int argc, char **argv) {

    UnitFactory factory;
    Unit * units[5];

    units[0] = factory.create_harvester();
    units[1] = factory.create_infantry();
    units[2] = factory.create_trike();
    units[3] = factory.create_infantry();
    units[4] = factory.create_quad();

    for (int i = 0; i < 5; i++) {
        units[i]->salut();
    }
    for (int i = 0; i < 5; i++) {
        delete units[i];
    }

    return 0;
}




