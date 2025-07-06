# Table Tennis Match Manager (C Program)

This is a simple C program to manage and track Table Tennis matches. It allows users to record new matches, view player statistics, check the leaderboard, and browse all match history — all stored in a file-based system.

---

## 🏓 Features

1. **Add a New Match**  
   - Input player names and scores  
   - Automatically stores match data in a file  

2. **Search Player Statistics**  
   - Enter a player’s name to view their win/loss record, matches played, etc.

3. **Leaderboard**  
   - Displays a ranking of players based on performance (e.g., wins)

4. **View All Past Matches**  
   - Lists all matches recorded so far with details

---

## 💾 Data Handling

- Match data is stored in a text file (e.g., `matches.txt`)
- Each match includes:
  - Player 1 name
  - Player 2 name
  - Scores
  - Winner

---

## 🛠 Compilation & Running

### Compile

```bash
gcc main.c -o table_tennis
