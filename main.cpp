#include <iostream>
#include <cstdlib>
#include <time.h>
#include "head/main.h"
using namespace std;

void generateWorld(world &newWorld) {
    srand(time(0)); // Nimmt aktuelle Zeit als Seed. Braucht man, sonst kommt immer der selbe Seed heraus.
    int relique_x = rand() % 5;
    int relique_y = rand() % 5;
    int _rc = newWorld.getRc();
    newWorld.play[relique_x][relique_y].type = relique;
    newWorld.play[relique_x][relique_y].visited = false;
    newWorld.setRc(_rc + 1);
    for(int x = 0; x < 5; x++) {
        for(int y = 0; y < 5; y++) {
            if(x == relique_x && y == relique_y) {
                continue;
            }
            int rng = rand() % 10;

            if(rng < 4) {
                newWorld.play[x][y].type= empt;
            }
            else if(rng < 7) {
                newWorld.play[x][y].type = danger;
            }
            else if(rng < 8) {
                newWorld.play[x][y].type = fountain;
            }
            else if(rng < 9) {
                newWorld.play[x][y].type = relique;
                ++_rc;
                newWorld.setRc(_rc + 1);
            } else {
                newWorld.play[x][y].type= empt;
            }
            newWorld.play[x][y].visited = false;
        }
    }
}

int fieldTest() {
    int rng = 3;
    int input;

    while(true) {
        cout << "Rate eine Zahl zwischen 1-5, wenn du richtig liegst hast du bestanden!" << endl;
        cin >> input;
        if(input < 1 || input > 4) {
            cout << "Falscher Input, Pech gehabt" << endl;
            break;
        }
        if(rng == input) {
            return 1;
        }
        break;
    }
    return 0;
}

void attributeLPBoost(world &newWorld) {
    double newLP = newWorld.player1.getLP();
        if (newWorld.attribute.getLPBoost() == 0) {
            newWorld.player1.setLP(newLP + 1);
        }
        if (newWorld.attribute.getLPBoost() == 1) {
            newWorld.player1.setLP(newLP + 1.25);
        }
        else if (newWorld.attribute.getLPBoost() == 2) {
            newWorld.player1.setLP(newLP + 1.5);
        }
        else if (newWorld.attribute.getLPBoost() == 3) {
            newWorld.player1.setLP(newLP + 1.75);
        }
        else if (newWorld.attribute.getLPBoost() == 4) {
            newWorld.player1.setLP(newLP + 2);
        }
}

void attributeShield(world &newWorld) {
    double newLP = newWorld.player1.getLP();

    if (newWorld.attribute.getShield() == 0) {
        newWorld.player1.setLP(newLP + 0.1);
    }
    if (newWorld.attribute.getShield() == 1) {
        newWorld.player1.setLP(newLP + 0.2);
    }
    else if (newWorld.attribute.getShield() == 2) {
        newWorld.player1.setLP(newLP + 0.3);
    }
    else if (newWorld.attribute.getShield() == 3) {
        newWorld.player1.setLP(newLP + 0.4);
    }
    else if (newWorld.attribute.getShield() == 4) {
        newWorld.player1.setLP(newLP + 0.5);
    }
}

void attributeResistance(world &newWorld) {
    double newLP = newWorld.player1.getLP();

    if (newWorld.attribute.getResistance() == 1) {
        newWorld.player1.setLP(newLP + 0.2);
    }
    else if (newWorld.attribute.getResistance() == 2) {
        newWorld.player1.setLP(newLP + 0.3);
    }
    else if (newWorld.attribute.getResistance() == 3) {
        newWorld.player1.setLP(newLP + 0.4);
    }
    else if (newWorld.attribute.getResistance() == 4) {
        newWorld.player1.setLP(newLP + 0.5);
    }
}

void fieldEvaluate(world &newWorld, int new_x, int new_y) {
    double _lp = newWorld.player1.getLP();
    int _rc = newWorld.getRc();
    int _rp = newWorld.player1.getRP();
    int _dmg = newWorld.player1.getDmg();
    int _healed = newWorld.player1.getHealed();
    double _lpboost = newWorld.attribute.getLPBoost();
    double _shield = newWorld.attribute.getShield();
    double _resistance = newWorld.attribute.getResistance();

    if (newWorld.play[new_x][new_y].type == fountain) {
        {
            if (fieldTest()) {
                newWorld.attribute.setLPBoost(_lpboost + 1);
            }

            attributeLPBoost(newWorld);
            cout << "LP-Boost Attribute: " << newWorld.attribute.getLPBoost() << endl;
            newWorld.player1.setHealed(_healed + 1);
            cout << "Du bekommst 1 LP" << endl;
            cout << "LP: " << newWorld.player1.getLP() << endl;
            cout << "--------------------------------" << endl;
        }
    }

    if (newWorld.play[new_x][new_y].type == danger) {
        {
            if (fieldTest()) {
                newWorld.attribute.setShield(_shield + 1);
            }  else {
                newWorld.player1.setLP(_lp - 1);
                newWorld.player1.setDmg(_dmg -1);
                cout << "Du bekommst Schaden vom Gegner!" << endl;
            }
            attributeShield(newWorld);
            cout << "LP-Boost Attribute: " << newWorld.attribute.getShield() << endl;
            newWorld.player1.setHealed(_healed + 1);
            cout << "LP: " << newWorld.player1.getLP() << endl;
            cout << "--------------------------------" << endl;
        }
    }

    if (newWorld.play[new_x][new_y].type == relique) {
        {
            if (fieldTest()) {
                newWorld.attribute.setResistance(_resistance + 1);
            }
            newWorld.player1.setRP(_rp + 1);
            newWorld.rp_collected++;
            cout << "Du bekommst 1 RP" << endl;
            cout << "RP: " << newWorld.player1.getRP() << endl;
        }
    }
}

void setupEnemy(world &newWorld) {
    int enemy_x = rand() % 5;
    int enemy_y = rand() % 5;

    if(enemy_x != 0 && enemy_y != 0) {
        newWorld.enemy1.setX(enemy_x);
        newWorld.enemy1.setY(enemy_y);
    } else {
        newWorld.enemy1.setX(3);
        newWorld.enemy1.setY(3);
    }
}

void setupEnemy2(world &newWorld) {
    int enemy2_x = rand() % 5;
    int enemy2_y = rand() % 5;
    if(enemy2_x != 0 && enemy2_y != 0) {
        newWorld.enemy2.setX(enemy2_x);
        newWorld.enemy2.setY(enemy2_y);
    } else {
        newWorld.enemy2.setX(2);
        newWorld.enemy2.setY(2);
    }
}

void movementEnemy(world &newWorld) {
    int _x = newWorld.enemy1.getX();
    int _y = newWorld.enemy1.getY();

    if(newWorld.enemy1.getX() < newWorld.player1.getX()) {
        newWorld.enemy1.setX(_x + 1);
        if(newWorld.enemy1.getX() == 4) {
            newWorld.enemy1.setX(4);
        }
    }

    if(newWorld.enemy1.getX() > newWorld.player1.getX()) {
        newWorld.enemy1.setX(_x - 1);
        if(newWorld.enemy1.getX() == 0) {
            newWorld.enemy1.setX(0);
        }
    }


    if(newWorld.enemy1.getY() < newWorld.player1.getY()) {
        newWorld.enemy1.setY(_y + 1);
        if(newWorld.enemy1.getY() == 4) {
            newWorld.enemy1.setY(4);
        }
    }

    if(newWorld.enemy1.getY() > newWorld.player1.getY()) {
        newWorld.enemy1.setY(_y - 1);
        if(newWorld.enemy1.getY() == 0) {
            newWorld.enemy1.setY(0);
        }
    }
}

void movementEnemy2(world &newWorld) {
    int enemy2_x = rand() % 5;
    int enemy2_y = rand() % 5;

    newWorld.enemy2.setX(enemy2_x);
    newWorld.enemy2.setY(enemy2_y);
}

void enemyAttack(world &newWorld, int new_x, int new_y) {
    int rng = rand() % 5;
    int _lp = newWorld.player1.getLP();
    int _dmg = newWorld.player1.getDmg();

    if(newWorld.enemy1.getX() == new_x && newWorld.enemy1.getY() == new_y) {
        attributeResistance(newWorld);
        newWorld.player1.setDmg(_dmg + 1);
        newWorld.player1.setLP(_lp - 1);
        cout << "Der Gegner hat dich mit einem Pfeil getroffen!" << endl;
        cout << "" << newWorld.player1.getLP() << endl;
    }
    if(rng == 3) {
        attributeResistance(newWorld);
        newWorld.player1.setDmg(_dmg + 1);
        newWorld.player1.setLP(_lp - 1);
        cout << "Der Gegner hat dich mit einem Pfeil getroffen!" << endl;
        cout << "Leben gesamt: " << newWorld.player1.getLP() << endl;
    }
}

void displayWorld(world &newWorld) {
    int empt = 0;
    int danger = 1;
    int fountain = 2;
    int relique = 3;
    int player = 7;
    int enemy = 9;

    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            int type = 0;
            if (newWorld.play[x][y].visited == false) {
                if (newWorld.play[x][y].type == empt) {
                    type = empt;
                }
                else if (newWorld.play[x][y].type == danger) {
                    type = danger;
                }
                else if (newWorld.play[x][y].type == fountain) {
                    type = fountain;
                }
                else if (newWorld.play[x][y].type == relique) {
                    type = relique;
                }
            }

            if (newWorld.player1.getX() == x && newWorld.player1.getY() == y) {
                type = player;
            }

            if (newWorld.enemy1.getX() == x && newWorld.enemy1.getY() == y) {
                type = enemy;
            }
            if(newWorld.getLvl() == 3) {
                if (newWorld.enemy2.getX() == x && newWorld.enemy2.getY() == y) {
                    type = enemy;
                }
            }
            cout << type << " ";
        }
        cout << endl;
    }
}

void showStats(world &newWorld) {
        cout << "--------------------------------" << endl;
        cout << "Statistik:" << endl;
        cout << "--------------------------------" << endl;
        cout << "Relikte gefunden: " << newWorld.rp_collected << endl;
        cout << "Leben gesamt: " << newWorld.player1.getLP() << endl;
        cout << "Leben verloren: " << newWorld.player1.getDmg() << endl;
        cout << "Leben bekommen: " << newWorld.player1.getHealed() << endl;
        cout << "--------------------------------" << endl;
}

void levelUp(world &newWorld) {
    int _level = newWorld.getLvl();
    newWorld.setLvl(_level + 1);
    if(newWorld.getLvl() < 4) {
        if(newWorld.getLvl() == 3) {
            setupEnemy2(newWorld);
        }
        generateWorld(newWorld);
        newWorld.player1.setLP(5);
        newWorld.player1.setRP(0);
        cout << "--------------------------------" << endl;
        cout << "LEVEL " << newWorld.getLvl() << endl;
        cout << "--------------------------------" << endl;
        cout << "Relikte Gesamt: " << newWorld.getRc() << endl;
        cout << "Leben Gesamt: " << newWorld.player1.getLP() << endl;
        cout << "--------------------------------" << endl;
    }
}

int checkInput(char input) {
    while(true) {
        if(input == 'w' || input == 'a' || input == 's' || input == 'd') {
            return 0;
        }
        else {
            cout << "Falsche Eingabe!" << endl;
            cin >> input;
        }
    }
}

void movementWorld(world &newWorld) {
    int new_x = newWorld.player1.getX();
    int new_y = newWorld.player1.getY();
    char input;
    cout << "--------------------------------" << endl;
    cout << "Relikte Gesamt: " << newWorld.getRc() << endl;
    cout << "Leben Gesamt: " << newWorld.player1.getLP() << endl;
    cout << "--------------------------------" << endl;

    while(newWorld.player1.getLP() > 0) {
        displayWorld(newWorld);
        cout << "Welche Richtung? (w, a, s, d)" << endl;
        cin >> input;
        checkInput(input);
        if(input == 's') {
            if(new_x >= 0 && new_x < 4) {
                new_x++;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
            }
            if(newWorld.play[new_x][new_y].visited == true)
            {
                cout << "Feld schon besucht" << endl;
            } else {
                fieldEvaluate(newWorld, new_x, new_y);
                newWorld.play[new_x][new_y].visited = true;
            }
        }

        else if(input == 'a') {
            if(new_y > 0 && new_y <= 4) {
                new_y--;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
            }
            if(newWorld.play[new_x][new_y].visited == true)
            {
                cout << "Feld schon besucht" << endl;
            } else {
                fieldEvaluate(newWorld, new_x, new_y);
                newWorld.play[new_x][new_y].visited = true;
            }
        }

        else if(input == 'w') {
            if(new_x > 0 && new_x <= 4) {
                new_x--;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
            }
            if(newWorld.play[new_x][new_y].visited == true)
            {
                cout << "Feld schon besucht" << endl;
            } else {
                fieldEvaluate(newWorld, new_x, new_y);
                newWorld.play[new_x][new_y].visited = true;
            }
        }


        else if(input == 'd') {
            if(new_y >= 0 && new_y < 4) {
                new_y++;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
            }
            if(newWorld.play[new_x][new_y].visited == true)
            {
                cout << "Feld schon besucht" << endl;
            } else {
                fieldEvaluate(newWorld, new_x, new_y);
                newWorld.play[new_x][new_y].visited = true;
            }
        }

        movementEnemy(newWorld);
        if(newWorld.getLvl() == 3) {
            movementEnemy2(newWorld);
        }
        newWorld.player1.setX(new_x);
        newWorld.player1.setY(new_y);

        enemyAttack(newWorld, new_x, new_y);

        if(newWorld.player1.getRP() == newWorld.getRc()) {
            newWorld.setRc(0);
            levelUp(newWorld);
        }
        if(newWorld.getLvl() == 4) {
            cout << "Game durchgespielt!" << endl;
            break;
        }
    }
    if(newWorld.player1.getLP() <= 0) {
        cout << "Du hast kein Leben mehr!";
    }
}

void displayRules(world &newWorld) {
    char input = 0;
    cout << "1. Du startest mit 5 Lebenspunkten." << endl;
    cout << "2. Es gibt mehrere Feldertypen die unterschiedliche Effekte haben." << endl;
    cout << "3. Dich verfolgen Gegner die dir Schaden zufügen wenn sie dich erwischen." << endl;
    cout << "4. Es gibt 3 verschiedene Tränke." << endl;
    cout << "" << endl;
    cout << "Beim Unsichtbarkeitstrank entkommst du einem Gefahrenfeld." << endl;
    cout << "Beim LP-Trank bekommst du ein zusätzlichen Lebenspunkt auf einem Brunnenfeld." << endl;
    cout << "Beim Schild wehrst du den Gegner ab." << endl;
    cout << "" << endl;
    cout << "Es gibt insgesamt 3 Level (Level 1: Alle Felder & 1 Gegner, Level 2: Keine Brunnen mehr, Level 3: Ein 2.Gegner der springt)." << endl;
    cout << "" << endl;
    cout << "Feldertypen:" << endl;
    cout << "0 = Leeres Feld (nichts passiert)" << endl;
    cout << "1 = Gefahren Feld (Du verlierst mit einer gewissen Wahrscheinlichkeit ein Leben." << endl;
    cout << "2 = Brunnen Feld (Du bekommst ein Leben)" << endl;
    cout << "3 = Relikt Feld (Du bekommst ein Relikt)" << endl;
    cout << "7 = Spieler" << endl;
    cout << "9 = Gegner" << endl;
    cout << "" << endl;
    cout << "Das Ziel ist es, alle Relikte zu finden bevor du kein Leben mehr hast." << endl;
    cout << "" << endl;
    cout << "Drücke s und ENTER um zu starten" << endl;


    while(input != 's') {
        cin >> input;
    }
}

int main() {
    world newWorld;
    setupEnemy(newWorld);
    displayRules(newWorld);
    generateWorld(newWorld);
    movementWorld(newWorld);
    showStats(newWorld);
}