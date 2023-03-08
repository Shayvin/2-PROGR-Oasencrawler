enum fieldType {
    empt = 0, danger = 1, fountain = 2, relique = 3
};

class stats {
    private:
        double lpboost = 0;
        double shield = 0;
        double resistance = 0;
    public:
        void setLPBoost(double _lpboost){
            lpboost = _lpboost;
        }
        void setShield(double _shield){
            shield = _shield;
        }
        void setResistance(double _resistance) {
            resistance = _resistance;
        }
        double getLPBoost() {
            return lpboost;
        }
        double getShield() {
            return shield;
        }
        double getResistance() {
            return resistance;
        }
    };

class field {
public:
    fieldType type;
    bool visited = false;
};


class player {
private:
    int x = 0;
    int y = 0;
    double lp = 5; // Life-Points
    int dmg = 0;
    int rp = 0; // Relique-Points
    int healed = 0;
public:
    void setX(int _x) {
        x = _x;
    }
    void setY(int _y) {
        y = _y;
    }
    void setLP(double _lp) {
        lp = _lp;
    }
    void setDmg(int _dmg) {
        dmg = _dmg;
    }
    void setRP(int _rp) {
        rp = _rp;
    }
    void setHealed(int _healed) {
        healed = _healed;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    double getLP() {
        return lp;
    }
    int getDmg() {
        return dmg;
    }
    int getRP() {
        return rp;
    }
    int getHealed() {
        return healed;
    }
};


class enemy {
private:
    int x = 0;
    int y = 0;
public:
    void setX(int _x) {
        x = _x;
    }
    void setY(int _y) {
        y = _y;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }

};


class world {
private:
    int level = 1;
    int relique_count = 0;
public:
    field play[5][5];
    player player1;
    enemy enemy1;
    enemy enemy2;
    int rp_collected = 0;
    stats attribute;

    void setLvl(int _level) {
        level = _level;
    }
    void setRc(int _rc) {
        relique_count = _rc;
    }
    int getLvl() {
        return level;
    }
    int getRc() {
        return relique_count;
    }
};
