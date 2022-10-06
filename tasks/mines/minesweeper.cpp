#include "minesweeper.h"

bool PutMine(size_t i, size_t j, size_t height, size_t width, size_t mines_count) {
    size_t cells_left = (width - j) + (height - i - 1) * width;
    size_t rnd = rand() % cells_left;
    return rnd < mines_count;
}

std::set<std::pair<size_t, size_t>> Minesweeper::GenerateMines(size_t width, size_t height, size_t mines_count) const {
    std::set<std::pair<size_t, size_t>> result;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (PutMine(i, j, height, width, mines_count)) {
                result.insert({j, i});
            }
        }
    }
    return result;
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    field_.clear();
    field_.resize(height);
    for (size_t i = 0; i < height; ++i) {
        field_[i].resize(width);
    }
    for (const auto& [x, y] : GenerateMines(width, height, mines_count)) {
        field_[y][x].mine = true;
    }
    time_ = std::time(0);
    status_ = GameStatus::IN_PROGRESS;
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    *this = Minesweeper(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Minesweeper::Cell>& cells_with_mines) {
    field_.clear();
    field_.resize(height);
    for (size_t i = 0; i < height; ++i) {
        field_[i].resize(width);
    }
    for (const auto& cell : cells_with_mines) {
        field_[cell.y][cell.x].mine = true;
    }
    time_ = std::time(0);
    status_ = GameStatus::IN_PROGRESS;
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Minesweeper::Cell>& cells_with_mines) {
    *this = Minesweeper(width, height, cells_with_mines);
}

bool Minesweeper::GameEnded() const {
    return (status_ == GameStatus::DEFEAT || status_ == GameStatus::VICTORY);
}

void Minesweeper::MarkCell(const Minesweeper::Cell& cell) {
    if (GameEnded()) {
        return;
    }
    field_[cell.y][cell.x].flag = !field_[cell.y][cell.x].flag;
}

int Minesweeper::MinesNear(int i, int j) const {
    int cnt = 0;
    for (int k = -1; k < 2; ++k) {
        for (int l = -1; l < 2; ++l) {
            if (k == 0 && l == 0) {
                continue;
            }
            cnt += (((i + k) >= 0) && ((j + l) >= 0) && ((i + k) < static_cast<int>(field_.size())) &&
                    ((j + l) < static_cast<int>(field_[0].size())) && field_[i + k][j + l].mine);
        }
    }
    return cnt;
}

char Minesweeper::GetChar(size_t i, size_t j) const {
    if (!field_[i][j].open) {
        if (field_[i][j].flag) {
            return '?';
        }
        return '-';
    }
    if (field_[i][j].mine) {
        return '*';
    }
    int num = MinesNear(i, j);
    return (num == 0 ? '.' : static_cast<char>('0' + num));
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    Minesweeper::RenderedField result(field_.size());
    for (size_t i = 0; i < field_.size(); ++i) {
        for (size_t j = 0; j < field_[0].size(); ++j) {
            result[i] += GetChar(i, j);
        }
    }
    return result;
}

time_t Minesweeper::GetGameTime() const {
    return time_;
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return status_;
}

void Minesweeper::OpenSafeCell(Minesweeper::Cell cell) {
    field_[cell.y][cell.x].open = true;
    int num = MinesNear(cell.y, cell.x);
    if (num == 0) {
        for (int k = -1; k < 2; ++k) {
            for (int l = -1; l < 2; ++l) {
                if (k == 0 && l == 0) {
                    continue;
                }
                if ((static_cast<int>(cell.x) + l) >= 0 && (static_cast<int>(cell.y) + k) >= 0 &&
                    (static_cast<int>(cell.x) + l) < static_cast<int>(field_[0].size()) &&
                    (static_cast<int>(cell.y) + k) < static_cast<int>(field_.size())) {
                    OpenSafeCell({cell.x + l, cell.y + k});
                }
            }
        }
    }
}

void Minesweeper::OpenCell(const Minesweeper::Cell& cell) {
    if (GameEnded() || field_[cell.y][cell.x].flag) {
        return;
    }
    if (field_[cell.y][cell.x].mine) {
        status_ = GameStatus::DEFEAT;
        return;
    }
    OpenSafeCell(cell);
}