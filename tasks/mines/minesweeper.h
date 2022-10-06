#pragma once

#include <string>
#include <vector>
#include <set>
#include <ctime>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    struct CellInformation {
        bool flag = false;
        bool open = false;
        bool mine = false;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;
    using Information = std::vector<std::vector<CellInformation>>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

    bool GameEnded() const;
    char GetChar(size_t i, size_t j) const;
    int MinesNear(int i, int j) const;
    void OpenSafeCell(Cell cell);
    std::set<std::pair<size_t, size_t>> GenerateMines(size_t width, size_t height, size_t mines_count) const;
private:
    int closed_;
    Information field_;
    GameStatus status_ = GameStatus::NOT_STARTED;
    time_t time_ = std::time(0);
};
