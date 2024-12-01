#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player {
    int ballScores[12];
    char playerName[50];
    int totalScore;
};

void validateScore(int *score) {
    if (*score < 0 || *score > 6) {
        printf("Invalid score! Score is 0.\n");
        *score = 0;
    }
}

void playGame(struct player *player, int ball) {
    if (ball >= 12) { 
        return;
    }
    int score;
    printf("Enter the score for %s on ball %d: ", player->playerName, ball + 1);
    scanf("%d", &score);

    validateScore(&score);
    player->ballScores[ball] = score;
    player->totalScore += score;

    playGame(player, ball + 1); 
}

void findWinner(struct player player1, struct player player2) {
    if (player1.totalScore > player2.totalScore) {
        printf("Winner: %s with %d runs!\n", player1.playerName, player1.totalScore);
    } else if (player1.totalScore < player2.totalScore) {
        printf("Winner: %s with %d runs!\n", player2.playerName, player2.totalScore);
    } else {
        printf("It's a tie! Both players scored %d runs.\n", player1.totalScore);
    }
}

void displayMatchScoreboard(struct player player1, struct player player2) {
    struct player players[] = {player1, player2};
    for (int i = 0; i < 2; i++) {
        struct player player = players[i];
        printf("Player: %s\n", player.playerName);
        printf("Ball Scores: ");
        for (int j = 0; j < 12; j++) {
            printf("%d ", player.ballScores[j]);
        }
        printf("\nTotal Score: %d\n", player.totalScore);
        printf("Average Score: %.2f\n\n", player.totalScore / 12.0);
    }
}

int main() {
    struct player player1 = {{0}, "", 0};
    struct player player2 = {{0}, "", 0};

    printf("Enter name of Player 1: ");
    fgets(player1.playerName, sizeof(player1.playerName), stdin);
    player1.playerName[strcspn(player1.playerName, "\n")] = 0;

    printf("Enter name of Player 2: ");
    fgets(player2.playerName, sizeof(player2.playerName), stdin);
    player2.playerName[strcspn(player2.playerName, "\n")] = 0;

    printf("\nPlayer 1's Turn\n");
    playGame(&player1, 0);

    printf("\nPlayer 2's Turn\n");
    playGame(&player2, 0);

    displayMatchScoreboard(player1, player2);
    findWinner(player1, player2);

    return 0;
}
