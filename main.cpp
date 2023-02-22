#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

enum fieldType {
    empt, danger, fountain, relique
};

typedef struct {
    int type;
    bool visited = false;
    enum fieldType ft;
} field;

typedef struct {
    int lp = 5; // Life-Points
    int rp = 0; // Relique-Points
    int x = 0;
    int y = 0;
} player;

typedef struct {
    field play[5][5];
    player player1;
} world;

void generateWorld(world &newWorld) {
    srand(time(0)); // Nimmt aktuelle Zeit als Seed. Braucht man, sonst kommt immer der selbe Seed heraus.
    int relique_x = rand() % 5;
    int relique_y = rand() % 5;
    newWorld.play[relique_x][relique_y].type = relique;
    newWorld.play[relique_x][relique_y].visited = false;
    
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            int relique = 1; // Soll maximal 1 geben
            const int rng = rand() % 10;

            if(rng < 4) {
                newWorld.play[i][j].type= empt;
            }
            else if(rng < 8) {
                newWorld.play[i][j].type = danger;
            }
            else if(rng < 9) {
                newWorld.play[i][j].type = fountain;
            }
            newWorld.play[i][j].visited = false;
        }
    }
}

void fieldEvaluate(world &newWorld, int new_y, int new_x) {
    if (newWorld.play[new_y][new_x].type == fountain) {
        {
            newWorld.player1.lp++;
            cout << "Du bekommst 1 LP" << endl;
            cout << "LP: " << newWorld.player1.lp << endl;
        }
    }

        if (newWorld.play[new_y][new_x].type == danger) {
        {
            int rng = rand() % 6 + 1;
            if(rng == 1) {
            newWorld.player1.lp--;
            cout << "Du verlierst 1 LP" << endl;
            cout << "LP: " << newWorld.player1.lp << endl;
            } else {
                cout << "Glück gehabt! Du verlierst kein LP" << endl;
            }
        }
    }

        if (newWorld.play[new_y][new_x].type == relique) {
        {
            newWorld.player1.rp++;
            cout << "Du bekommst 1 RP" << endl;
            cout << "RP: " << newWorld.player1.rp << endl;
        }
    }
}

void movementWorld(world &newWorld) {
    int new_x = newWorld.player1.x;
    int new_y = newWorld.player1.y;
    char input;
    cout << "Aktuelle Position: " << newWorld.player1.y << " " << newWorld.player1.x << endl;
    world NewWorld;

    while(true) {

        cout << "Welche Richtung? (w, a, s, d)" << endl;
        cin >> input;
        if(input == 'w') {
            if(new_y >= 0 && new_y < 4) {
                new_y++;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
        }
        if(newWorld.play[new_y][new_x].visited == true)
        {
            cout << "Feld schon besucht" << endl;
        } else {
            fieldEvaluate(newWorld, new_y, new_x);
            newWorld.play[new_y][new_x].visited = true;
        }
        }

        else if(input == 'a') {
            if(new_x > 0 && new_x <= 4) {
                new_x--;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
        }
        if(newWorld.play[new_y][new_x].visited == true)
        {
            cout << "Feld schon besucht" << endl;
        } else {
            fieldEvaluate(newWorld, new_y, new_x);
            newWorld.play[new_y][new_x].visited = true;
        }
        }

        else if(input == 's') {
            if(new_y > 0 && new_y <= 4) {
                new_y--;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
        }
        if(newWorld.play[new_y][new_x].visited == true)
        {
            cout << "Feld schon besucht" << endl;
        } else {
            fieldEvaluate(newWorld, new_y, new_x);
            newWorld.play[new_y][new_x].visited = true;
        }
        }

        else if(input == 'd') {
            if(new_x >= 0 && new_x < 4) {
                new_x++;
            } else {
                cout << "Du bist ausserhalb des Spielfeldes, bitte wähle einen anderen Move" << endl;
            }
        if(newWorld.play[new_y][new_x].visited == true)
        {
            cout << "Feld schon besucht" << endl;
        } else {
            fieldEvaluate(newWorld, new_y, new_x);
            newWorld.play[new_y][new_x].visited = true;
        }
        }
            newWorld.player1.x = new_x;
            newWorld.player1.y = new_y;
            cout << "Aktuelle Position: " << newWorld.player1.y << " " << newWorld.player1.x << endl;
            if(newWorld.player1.lp == 0)
            {
                cout << "Du hast kein Leben mehr! Du hast verloren!" << endl;
                break;
            }
            if(newWorld.player1.rp == 1)
            {
                cout << "Du hast das Relikt gefunden! Du hast gewonnen!" << endl;
                break;
            }
        }
    }


int main() {
    world newWorld;
    generateWorld(newWorld);
    movementWorld(newWorld);
}