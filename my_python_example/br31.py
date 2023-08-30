# Baskin Robbins 31 Game

import random

def player_turn(total):
    while True:
        try:
            pick = int(input("Enter 1, 2, or 3: "))
            if pick < 1 or pick > 3:
                print("Invalid input. Please choose 1, 2, or 3.")
                continue
            if total + pick > 31:
                print("Invalid move. Try again.")
                continue
            return pick
        except ValueError:
            print("Invalid input. Please enter a number.")

def computer_turn(total):
    max_pick = min(3, 31 - total)
    return random.randint(1, max_pick)

def main():
    total = 0
    player_turns = True

    print("Welcome to Baskin Robbins 31!")

    while total < 31:
        if player_turns:
            print(f"Current total: {total}")
            pick = player_turn(total)
        else:
            pick = computer_turn(total)
            print(f"Computer picks: {pick}")

        total += pick
        player_turns = not player_turns

    if player_turns:
        print("You win!")
    else:
        print("Computer wins!")

if __name__ == "__main__":
    main()