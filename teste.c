#include <stdio.h>
#include <stdlib.h>

#define FLOOR_SIZE 50
#define DIRECTIONS 4

typedef struct _Turtle {
    short unsigned pen;
    short unsigned direction;
    short unsigned position[2]; // X and Y
} Turtle;

void printFloor(short unsigned[FLOOR_SIZE][FLOOR_SIZE]);
void handleWalk(Turtle *, unsigned short, short unsigned[FLOOR_SIZE][FLOOR_SIZE]);
void menuScreen();

int main()
{
    unsigned short floor[FLOOR_SIZE][FLOOR_SIZE] = {0};

    Turtle turtle;
    turtle.pen = 0;
    turtle.direction = 0;
    turtle.position[0] = 0;
    turtle.position[1] = 0;

    int option;

    menuScreen();
    printf("Input the desired option: ");
    scanf("%d", &option);
    printf("\n");

    while (option != 9) {

        switch (option) {
            case 1:
                turtle.pen = 0;
                printf("Pen lifted.\n");
                break;
            case 2:
                turtle.pen = 1;
                printf("Pen down.\n");
                break;
            case 3:
                turtle.direction = turtle.direction == 0 ? 3 : turtle.direction - 1;
                printf("Turned left.\n");
                break;
            case 4:
                turtle.direction = (turtle.direction + 1) % DIRECTIONS;
                printf("Turned right.\n");
                break;
            case 5:
                int distance;
                printf("Input the walk distance: ");
                scanf("%d", &distance);
                printf("\n");

                if (distance < 0) {
                    printf("Input a valid distance\n");
                } else {
                    handleWalk(&turtle, distance, floor);
                    printf("Moved %d spaces.\n", distance);
                }
                break;
            case 6:
                printFloor(floor);
                break;
            default:
                menuScreen();
                break;
        }

        printf("Input the desired option: ");
        scanf("%d", &option);
    }

    return 0;
}

void menuScreen() {
    printf("=====================================================================\n"
           "Command                   Action\n"
           "=====================================================================\n"
           "1                         Pen up\n"
           "2                         Pen down\n"
           "3                         Right turn\n"
           "4                         Left turn\n"
           "5                         Move X spaces forward\n"
           "6                         Print floor\n"
           "7                         Show menu\n"
           "9                         End of input\n"
           "=====================================================================\n");
}

void handleWalk(Turtle *turtle, unsigned short distance, short unsigned floor[FLOOR_SIZE][FLOOR_SIZE])
{
    for (int i = 0; i <= distance; i++) {
        switch ((*turtle).direction) {
            case 0:
                if ((*turtle).position[1] + 1 < FLOOR_SIZE) {
                    if ((*turtle).pen == 1) {
                        floor[(*turtle).position[1]][(*turtle).position[0]] = 1;
                    }
                    (*turtle).position[1]++;
                } else {
                    printf("Not enough space left to walk input distance\n");
                    return;
                }
                break;
            case 1:
                if ((*turtle).position[0] + 1 < FLOOR_SIZE) {
                    if ((*turtle).pen == 1) {
                        floor[(*turtle).position[1]][(*turtle).position[0]] = 1;
                    }
                    (*turtle).position[0]++;
                } else {
                    printf("Not enough space left to walk input distance\n");
                    return;
                }
                break;
            case 2:
                if ((*turtle).position[1] - 1 >= 0) {
                    if ((*turtle).pen == 1) {
                        floor[(*turtle).position[1]][(*turtle).position[0]] = 1;
                    }
                    (*turtle).position[1]--;
                } else {
                    printf("Not enough space left to walk input distance\n");
                    return;
                }
                break;
            case 3:
                if ((*turtle).position[0] - 1 >= 0) {
                    if ((*turtle).pen == 1) {
                        floor[(*turtle).position[1]][(*turtle).position[0]] = 1;
                    }
                    (*turtle).position[0]--;
                } else {
                    printf("Not enough space left to walk input distance\n");
                    return;
                }
                break;
        }
    }
}

void printFloor(short unsigned floor[][FLOOR_SIZE]) {
    for (int i = 0; i < FLOOR_SIZE; i++) {
        for (int j = 0; j < FLOOR_SIZE; j++) {
            if (floor[i][j] == 1) {
                printf(" * ");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}