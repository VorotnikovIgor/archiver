#include "unixpath.h"
#include <vector>

std::vector<std::string_view> SplitPath(std::string_view &path) {
    std::vector<std::string_view> result;
    size_t last = 0;
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '/') {
            if (i != 0 && path[i - 1] != '/') {
                result.push_back(path.substr(last, i - last));
            }
            last = i + 1;
        } else if (i == path.size() - 1) {
            if (path[i] != '/') {
                result.push_back(path.substr(last, i + 1 - last));
            }
        }
    }
    return result;
}

std::vector<std::string_view> ClearPath(std::vector<std::string_view> path1, std::vector<std::string_view> path2) {
    std::vector<std::string_view> result;
    for (const auto &rep : path1) {
        if (rep == "..") {
            if (!result.empty()) {
                result.pop_back();
            }
        } else if (rep != ".") {
            result.push_back(rep);
        }
    }
    for (const auto &rep : path2) {
        if (rep == "..") {
            if (!result.empty()) {
                result.pop_back();
            }
        } else if (rep != ".") {
            result.push_back(rep);
        }
    }
    return result;
}

std::string GetAnswer(std::vector<std::string_view> path) {
    std::string answer;
    for (const auto &rep : path) {
        answer += '/' + static_cast<std::string>(rep);
    }
    if (answer.empty()) {
        answer = '/';
    }
    return answer;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (path[0] == '/') {
        return GetAnswer(ClearPath(SplitPath(path), {}));
    }
    return GetAnswer(ClearPath(SplitPath(current_working_dir), SplitPath(path)));
}
