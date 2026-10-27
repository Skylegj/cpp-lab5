/*************************************
* Автор: Чеботников Александр        *
* Задание: Строки, векторы и словари *
* Вариант: 30                        *
*************************************/

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  constexpr int maxCount = 100;
  constexpr int maxValue = 1000;
  constexpr size_t maxTextLength = 200;
  constexpr size_t maxKeyLength = 40;
  string part;

  if (!getline(cin, part) ||
    (part != "A" && part != "B" && part != "C" && part != "D")) {
    cout << "INVALID\n";
    return 1;
  }

  if (part == "A") {
    string text;
    if (!getline(cin, text) || text.size() > maxTextLength) {
      cout << "INVALID\n";
      return 1;
    }
    for (unsigned char symbol : text) {
      if (symbol > 127) {
        cout << "INVALID\n";
        return 1;
      }
    }

    int pairCount = 0;
    for (size_t index = 1; index < text.size(); ++index) {
      if (text[index] == text[index - 1]) {
        ++pairCount;
      }
    }

    cout << pairCount << "\n";
  } else if (part == "B") {
    string countText;
    if (!(cin >> countText)) {
      cout << "INVALID\n";
      return 1;
    }
    istringstream countInput(countText);
    int count = 0;
    if (!(countInput >> count) || !countInput.eof() ||
      count < 0 || count > maxCount) {
      cout << "INVALID\n";
      return 1;
    }

    vector<int> values;
    for (int index = 0; index < count; ++index) {
      string valueText;
      if (!(cin >> valueText)) {
        cout << "INVALID\n";
        return 1;
      }
      istringstream valueInput(valueText);
      int value = 0;
      if (!(valueInput >> value) || !valueInput.eof() ||
        value < -maxValue || value > maxValue) {
        cout << "INVALID\n";
        return 1;
      }
      values.push_back(value);
    }

    for (int index = 0; index < count && index < 2; ++index) {
      values.push_back(values[index]);
    }

    if (values.empty()) {
      cout << "EMPTY\n";
    } else {
      for (size_t index = 0; index < values.size(); ++index) {
        if (index > 0) {
          cout << " ";
        }
        cout << values[index];
      }
      cout << "\n";
    }
  } else if (part == "C") {
    string countText;
    if (!getline(cin, countText)) {
      cout << "INVALID\n";
      return 1;
    }
    istringstream countInput(countText);
    int count = 0;
    if (!(countInput >> count) || count < 0 || count > maxCount) {
      cout << "INVALID\n";
      return 1;
    }
    countInput >> ws;
    if (!countInput.eof()) {
      cout << "INVALID\n";
      return 1;
    }

    map<string, int> values;
    for (int index = 0; index < count; ++index) {
      string pairText;
      if (!getline(cin, pairText)) {
        cout << "INVALID\n";
        return 1;
      }
      istringstream pairInput(pairText);
      string key;
      int value = 0;
      if (!(pairInput >> key >> value) || key.size() > maxKeyLength ||
        value < -maxValue || value > maxValue) {
        cout << "INVALID\n";
        return 1;
      }
      pairInput >> ws;
      if (!pairInput.eof()) {
        cout << "INVALID\n";
        return 1;
      }
      for (unsigned char symbol : key) {
        if (symbol > 127) {
          cout << "INVALID\n";
          return 1;
        }
      }
      values[key] = value;
    }

    string thresholdText;
    if (!getline(cin, thresholdText)) {
      cout << "INVALID\n";
      return 1;
    }
    istringstream thresholdInput(thresholdText);
    int threshold = 0;
    if (!(thresholdInput >> threshold) ||
      threshold < -maxValue || threshold > maxValue) {
      cout << "INVALID\n";
      return 1;
    }
    thresholdInput >> ws;
    if (!thresholdInput.eof()) {
      cout << "INVALID\n";
      return 1;
    }

    map<string, int> result;
    for (const auto& entry : values) {
      if (entry.second >= threshold) {
        result[entry.first] = entry.second;
      }
    }

    if (result.empty()) {
      cout << "EMPTY\n";
    } else {
      for (const auto& entry : result) {
        cout << entry.first << " " << entry.second << "\n";
      }
    }
  } else {
    string countText;
    if (!getline(cin, countText)) {
      cout << "INVALID\n";
      return 1;
    }
    istringstream countInput(countText);
    int count = 0;
    if (!(countInput >> count) || count < 0 || count > maxCount) {
      cout << "INVALID\n";
      return 1;
    }
    countInput >> ws;
    if (!countInput.eof()) {
      cout << "INVALID\n";
      return 1;
    }

    vector<map<string, string>> records;
    for (int index = 0; index < count; ++index) {
      string team;
      string goals;
      if (!getline(cin, team) || !getline(cin, goals)) {
        cout << "INVALID\n";
        return 1;
      }
      records.push_back({{"team", team}, {"goals", goals}});
    }

    bool valid = true;
    for (const auto& record : records) {
      auto teamField = record.find("team");
      auto goalsField = record.find("goals");
      if (teamField == record.end() || goalsField == record.end()) {
        valid = false;
        break;
      }
      for (const string& field : {teamField->second, goalsField->second}) {
        if (field.empty() || field.size() > maxTextLength) {
          valid = false;
          break;
        }
        if (field.front() == ' ' || field.back() == ' ') {
          valid = false;
          break;
        }
        for (unsigned char symbol : field) {
          if (symbol > 127) {
            valid = false;
            break;
          }
        }
        if (!valid) {
          break;
        }
      }
      if (!valid) {
        break;
      }

      const string& goalsText = goalsField->second;
      if (goalsText.size() > 1 && goalsText.front() == '0') {
        valid = false;
        break;
      }
      int goals = 0;
      for (char symbol : goalsText) {
        if (symbol < '0' || symbol > '9') {
          valid = false;
          break;
        }
        goals = goals * 10 + (symbol - '0');
        if (goals > maxValue) {
          valid = false;
          break;
        }
      }
      if (!valid) {
        break;
      }
    }
    if (!valid) {
      cout << "INVALID\n";
      return 1;
    }

    map<string, int> matchCounts;
    map<string, long long> totalGoals;
    map<string, int> maximumGoals;
    for (const auto& record : records) {
      const string& team = record.at("team");
      int goals = stoi(record.at("goals"));
      ++matchCounts[team];
      totalGoals[team] += goals;
      if (goals > maximumGoals[team]) {
        maximumGoals[team] = goals;
      }
    }

    vector<string> result;
    for (const auto& entry : matchCounts) {
      const string& team = entry.first;
      result.push_back(team + " " + to_string(entry.second) + " " + to_string(totalGoals.at(team)) + " " + to_string(maximumGoals.at(team)));
    }

    if (result.empty()) {
      cout << "EMPTY\n";
    } else {
      for (const string& line : result) {
        cout << line << "\n";
      }
    }
  }

  return 0;
}