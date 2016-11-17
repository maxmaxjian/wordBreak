#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <iterator>

class solution {
  public:
    std::vector<std::string> wordBreak(const std::string & s, const std::unordered_set<std::string> & dict) {
        std::vector<std::string> result;
        auto paths = getPaths(s, dict, std::vector<std::string>());
        for (auto & path : paths)
            result.push_back(std::accumulate(path.begin(), path.end(), std::string(),
                                             [](const std::string & s, const std::string & t){
                                                 return s.empty() ? t : s+" "+t;
                                             }));
        return result;
    }

  private:
    std::vector<std::vector<std::string>> getPaths(const std::string & s, const std::unordered_set<std::string> & dict, const std::vector<std::string> & curr) {
        std::vector<std::vector<std::string>> result;
        if (getLength(curr) == s.size())
            result.push_back(curr);
        else {
            std::vector<std::string> next = getNext(s, dict, curr);
            for (auto nx : next) {
                auto curr_cpy = curr;
                curr_cpy.push_back(nx);
                auto dict_cpy = dict;
                dict_cpy.erase(nx);
                auto temp = getPaths(s, dict_cpy, curr_cpy);
                std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
            }
        }
        return result;
    }

    std::vector<std::string> getNext(const std::string & s, const std::unordered_set<std::string> & dict, const std::vector<std::string> & curr) {
        std::vector<std::string> next;
        size_t start = getLength(curr);
        if (start < s.size()) {
            for (auto it = dict.begin(); it != dict.end(); ++it) {
                if (s.find(*it, start) == start)
                    next.push_back(*it);
            }
        }
        return next;
    }

    size_t getLength(const std::vector<std::string> & vec) {
        return std::accumulate(vec.begin(), vec.end(), 0,
                               [](size_t i, const std::string & s){
                                   return i+s.size();
                               });
    }
};

int main() {
    std::string s{"catsanddog"};
    std::unordered_set<std::string> dict{"cat", "cats", "and", "sand", "dog"};

    solution soln;
    auto strs = soln.wordBreak(s, dict);
    std::copy(strs.begin(), strs.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
