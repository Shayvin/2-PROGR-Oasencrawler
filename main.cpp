#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


enum fieldType {
    empt = 0, danger = 1, fountain = 2, relique = 3
};

class stats {
    public:
        int vanish = 0;
        int lpboost = 0;
        int shield = 0;
};

class field {
    public:
        fieldType type;
        bool visited = false;
};


class player {
    public:
        int lp = 5; // Life-Points
        int rp = 0; // Relique-Points
        int x = 0;
        int y = 0;
        int healed = 0;
        int dmg = 0;
};


class enemy {
    public:
        int x = 4;
        int y = 4;
};


class world {
    public:
        field play[5][5];
        player player1;
        enemy enemy1;
        enemy enemy2;
        int relique_count = 0;
        int level = 1;
        int rp_collected = 0;
        stats attribute;
};


void generateWorld(world &newWorld) {
    srand(time(0)); // Nimmt aktuelle Zeit als Seed. Braucht man, sonst kommt immer der selbe Seed heraus.
    int relique_x = rand() % 5;
    int relique_y = rand() % 5;
    newWorld.play[relique_x][relique_y].type = relique;
    newWorld.play[relique_x][relique_y].visited = false;
    newWorld.relique_count++;
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
            else if(newWorld.level == 1) {
                if(rng < 8) {
                    newWorld.play[x][y].type = fountain;
                }
            }

            else if(rng < 9) {
                newWorld.play[x][y].type = relique;
                newWorld.relique_count++;
            } else {
                newWorld.play[x][y].type= empt;
            }
            newWorld.play[x][y].visited = false;
        }
    }
}


void fieldEvaluate(world &newWorld, int new_x, int new_y) {

    if (newWorld.play[new_x][new_y].type == empt) {
        int rng = rand() % 10;
        if(rng == 1) {
            newWorld.attribute.lpboost++;
            cout << "Du bekommst 1 LP-Trank" << endl;
        }
        else if(rng == 2) {
            newWorld.attribute.vanish++;
            cout << "Du bekommst 1 Unsichtbarkeitstrank" << endl;
        }
        else if(rng == 3) {
            newWorld.attribute.shield++;
            cout << "Du bekommst 1 Schild" << endl;
        }
    }
    if (newWorld.play[new_x][new_y].type == fountain) {
        {
            if(newWorld.attribute.lpboost > 0) {
                newWorld.player1.lp++;
                cout << "Du bekommst 1 zusätzlichen LP, dank deines LP-Tranks" << endl;
                newWorld.attribute.lpboost--;
                cout << "Anzahl LP-Tränke: " << newWorld.attribute.lpboost <<  endl;
            }
            newWorld.player1.lp++;
            newWorld.player1.healed++;
            cout << "Du bekommst 1 LP" << endl;
            cout << "LP: " << newWorld.player1.lp << endl;
        }
    }


    if (newWorld.play[new_x][new_y].type == danger) {
        {
            int rng = rand() % 6 + 1;
            if(rng < 5) {
                if(newWorld.attribute.vanish > 0) {
                    cout << "Du benutzt deinen Unsichtbarkeitstrank und verlierst kein Leben" << endl;
                    newWorld.attribute.vanish--;
                    cout << "Anzahl Unsichtbarkeits-Tränke: " << newWorld.attribute.vanish <<  endl;
                } else {
                    newWorld.player1.lp--;
                    newWorld.player1.dmg++;
                    cout << "Du verlierst 1 LP" << endl;
                    cout << "LP: " << newWorld.player1.lp << endl;
                }
            } else {
                cout << "Glück gehabt! Du verlierst kein LP" << endl;
            }
        }
    }


    if (newWorld.play[new_x][new_y].type == relique) {
        {
            newWorld.player1.rp++;
            newWorld.rp_collected++;
            cout << "Du bekommst 1 RP" << endl;
            cout << "RP: " << newWorld.player1.rp << endl;
        }
    }
}


void setupEnemy(world &newWorld) {
    int enemy_x = rand() % 5;
    int enemy_y = rand() % 5;

    if(enemy_x != 0 && enemy_y != 0) {
        newWorld.enemy1.x = enemy_x;
        newWorld.enemy1.y = enemy_y;
    } else {
        newWorld.enemy1.x = 3;
        newWorld.enemy1.y = 3;
    }
}

void setupEnemy2(world &newWorld) {
    int enemy2_x = rand() % 5;
    int enemy2_y = rand() % 5;
    if(enemy2_x != 0 && enemy2_y != 0) {
        newWorld.enemy2.x = enemy2_x;
        newWorld.enemy2.y = enemy2_y;
    } else {
        newWorld.enemy2.x = 2;
        newWorld.enemy2.y = 2;
    }
}


void movementEnemy(world &newWorld) {
    if(newWorld.enemy1.x < newWorld.player1.x) {
        newWorld.enemy1.x++;
        if(newWorld.enemy1.x == 4) {
            newWorld.enemy1.x = 4;
        }
    }

    if(newWorld.enemy1.x > newWorld.player1.x) {
        newWorld.enemy1.x--;
        if(newWorld.enemy1.x == 0) {
            newWorld.enemy1.x = 0;
        }
    }


    if(newWorld.enemy1.y < newWorld.player1.y) {
        newWorld.enemy1.y++;
        if(newWorld.enemy1.y == 4) {
            newWorld.enemy1.y = 4;
        }
    }

    if(newWorld.enemy1.y > newWorld.player1.y) {
        newWorld.enemy1.y--;
        if(newWorld.enemy1.y == 0) {
            newWorld.enemy1.y = 0;
        }
    }
}

void movementEnemy2(world &newWorld) {
    int enemy2_x = rand() % 5;
    int enemy2_y = rand() % 5;

    newWorld.enemy2.x = enemy2_x;
    newWorld.enemy2.y = enemy2_y;
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

            if (newWorld.player1.x == x && newWorld.player1.y == y) {
                type = player;
            }

            if (newWorld.enemy1.x == x && newWorld.enemy1.y == y) {
                type = enemy;
            }
            if(newWorld.level == 3) {
                if (newWorld.enemy2.x == x && newWorld.enemy2.y == y) {
                    type = enemy;
                }
            }
            cout << type << " ";
        }
        cout << endl;
    }
}


void showStats(world &newWorld) {
    if(newWorld.player1.rp == newWorld.relique_count) {
        cout << "--------------------------------" << endl;
        cout << "Statistik:" << endl;
        cout << "--------------------------------" << endl;
        cout << "Relikte gefunden: " << newWorld.rp_collected << endl;
        cout << "Leben gesamt: " << newWorld.player1.lp << endl;
        cout << "Leben verloren: " << newWorld.player1.dmg << endl;
        cout << "Leben bekommen: " << newWorld.player1.healed << endl;
        cout << "--------------------------------" << endl;
    }
}

void levelUp(world &newWorld) {
    newWorld.level++;
    if(newWorld.level < 4) {
        if(newWorld.level == 3) {
            setupEnemy2(newWorld);
        }
        generateWorld(newWorld);
        newWorld.player1.lp = 5;
        newWorld.player1.rp = 0;
        cout << "--------------------------------" << endl;
        cout << "LEVEL " << newWorld.level << endl;
        cout << "--------------------------------" << endl;
        cout << "Relikte Gesamt: " << newWorld.relique_count << endl;
        cout << "Leben Gesamt: " << newWorld.player1.lp << endl;
        cout << "--------------------------------" << endl;
    }
}

void movementWorld(world &newWorld) {
    int new_x = newWorld.player1.x;
    int new_y = newWorld.player1.y;
    char input;
    cout << "--------------------------------" << endl;
    cout << "Relikte Gesamt: " << newWorld.relique_count << endl;
    cout << "Leben Gesamt: " << newWorld.player1.lp << endl;
    cout << "--------------------------------" << endl;

    while(newWorld.player1.lp != 0) {
        displayWorld(newWorld);
        cout << "Welche Richtung? (w, a, s, d)" << endl;
        cin >> input;

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
        if(newWorld.level == 3) {
            movementEnemy2(newWorld);
        }
        newWorld.player1.x = new_x;
        newWorld.player1.y = new_y;


        if(newWorld.enemy1.x == new_x && newWorld.enemy1.y == new_y) {

            if(newWorld.attribute.shield > 0) {
                newWorld.attribute.shield--;
                cout << "Dein Schild hat dich beschützt, du bekommst kein Schaden." << endl;
            } else {
                newWorld.player1.lp--;
                cout << "Der Gegner fügt dir 1 Schaden zu!" << endl;
                cout << "Leben gesamt: " << newWorld.player1.lp << endl;
            }
        }

        if(newWorld.player1.rp == newWorld.relique_count) {
            showStats(newWorld);
            newWorld.relique_count = 0;
            levelUp(newWorld);
        }
        if(newWorld.level == 4) {
            showStats(newWorld);
            cout << "Game durchgespielt!";
            break;
        }
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
}