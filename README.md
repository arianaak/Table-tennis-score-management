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

## 🛠 Running the Program

### Option 1: Open with Code::Blocks (Recommended)

1. Open Code::Blocks.
2. Go to **File → Open**.
3. Select the `.cbp` project file (e.g., `table_tennis.cbp`).
4. Click **Build and Run** (or press `F9`).

### Option 2: Compile Manually (Alternative)

If you prefer to compile outside Code::Blocks using GCC:

```bash
gcc main.c -o table_tennis
./table_tennis
