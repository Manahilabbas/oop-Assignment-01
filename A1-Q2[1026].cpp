#include <iostream>
#include <string>

using namespace std;

class Robot {
private:
    string name;
    int hits;
public:
    Robot(string n) : name(n), hits(0) {}

    void hitBall(int &ballX, int &ballY, const string &direction) {
        hits++;
        if (direction == "up") {
            ballY++;
        } else if (direction == "down") {
            ballY--;
        } else if (direction == "right") {
            ballX++;
        } else if (direction == "left") {
            ballX--;
        }
    }

    int getHits() const { return hits; }
    string getName() const { return name; }
};

class Ball {
private:
    int x, y;
public:
    Ball() : x(0), y(0) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    pair<int, int> getPosition() const {
        return {x, y};
    }
};

class GoalPosition {
private:
    const int x, y;
public:
    GoalPosition() : x(3), y(3) {}

    bool isGoalReached(int ballX, int ballY) const {
        return (ballX == x && ballY == y);
    }

    void displayGOAL() const {
        cout << "Goal is at (" << x << ", " << y << ")\n";
    }
    
};

class Team {
private:
    string teamName;
    Robot* player;
public:
    Team(string name, string robotName) : teamName(name) {
        player = new Robot(robotName);
    }

    ~Team() { delete player; }

    string getTeamName() const { return teamName; }
    Robot* getRobot() const { return player; }
};

class Game {
private:
    Team *teamA, *teamB;
    Ball ball;
    GoalPosition goal;

public:
    Game(string team1, string robot1, string team2, string robot2) {
        teamA = new Team(team1, robot1);
        teamB = new Team(team2, robot2);
    }

    ~Game() {
        delete teamA;
        delete teamB;
    }

    void play(Team *team) {
        Robot *robot = team->getRobot();

        while (!goal.isGoalReached(ball.getX(), ball.getY())) {
            string move;
            cout << team->getTeamName() << "'s turn. Enter move (up/down/left/right): ";
            cin >> move;
            int ballX = ball.getX();
            int ballY = ball.getY();
            robot->hitBall(ballX, ballY, move);
            ball.move(ballX - ball.getX(), ballY - ball.getY());

            if (goal.isGoalReached(ball.getX(), ball.getY())) {
                cout << "Goal reached!\n";
            } else {
                cout << team->getTeamName() << "'s robot " << robot->getName()
                     << " moved ball to (" << ball.getX() << "," << ball.getY() << ")\n";
            }
        }
        cout << "-----------------------------------------------------------\n";
    }

    void startGame() {
        cout << "Game started!\n";
        goal.displayGOAL(); 
        
        play(teamA);
        int hitsTeamOne = teamA->getRobot()->getHits();
        
        ball = Ball(); 
        cout << "Resetting ball position for next team...\n";
        
        goal.displayGOAL(); 
        play(teamB);
        int hitsTeamTwo = teamB->getRobot()->getHits();
    
        declareWinner(hitsTeamOne, hitsTeamTwo);
    }

    void declareWinner(int hits1, int hits2) {
        cout << "\nResults:\n";
        cout << teamA->getTeamName() << "'s Robot Hits: " << hits1 << endl;
        cout << teamB->getTeamName() << "'s Robot Hits: " << hits2 << endl;
        cout << "***";
        if (hits1 < hits2)
            cout << teamA->getTeamName() << " Wins!***\n";
        else if (hits2 < hits1)
            cout << teamB->getTeamName() << " Wins!***\n";
        else
            cout << "It's a Tie!***\n";
    }
};

int main() {
    string team1, robot1, team2, robot2;
    char choice;

    while(true) {
        cout << "Enter Team 1 name: ";
        cin >> team1;
        cout << "Enter Team 1 Robot name: ";
        cin >> robot1;

        cout << "Enter Team 2 name: ";
        cin >> team2;
        cout << "Enter Team 2 Robot name: ";
        cin >> robot2;

        Game game(team1, robot1, team2, robot2);
        game.startGame();

        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        if(choice == 'n' || choice == 'N')
        break;
    } 

    cout << "Thanks for playing!\n";
    return 0;
}
