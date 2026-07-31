#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <clocale>
#include <limits>
#include <cstdlib>
#include <ctime>

std::map<std::string, double> lagu_vars;

// Извлечение аргументов из скобок
std::vector<double> getArgs(const std::string& token) {
    std::vector<double> args;
    size_t openParen = token.find('(');
    size_t closeParen = token.find_last_of(')');
    if (openParen == std::string::npos || closeParen == std::string::npos) return args;

    std::string inner = token.substr(openParen + 1, closeParen - openParen - 1);
    std::stringstream ss(inner);
    std::string arg;
    
    while (std::getline(ss, arg, ',')) {
        if (arg.empty()) continue;
        arg.erase(0, arg.find_first_not_of(" \t"));
        arg.erase(arg.find_last_not_of(" \t") + 1);
        
        if (lagu_vars.count(arg)) {
            args.push_back(lagu_vars[arg]);
        } else if (!arg.empty()) {
            try {
                args.push_back(std::stod(arg));
            } catch (...) {
                args.push_back(0);
            }
        }
    }
    return args;
}

// Парсер для твоей уникальной команды rdch(...)
double evaluateRdch(std::string expr) {
    size_t open = expr.find('(');
    size_t close = expr.find_last_of(')');
    if (open == std::string::npos || close == std::string::npos) return 0;
    
    // Текст внутри скобок: "50, 1, 5, 5, 1050" (мы заменяем 'to' на запятые при парсинге в коде)
    std::string inner = expr.substr(open + 1, close - open - 1);
    
    // Очищаем строку от слов 'to', чтобы превратить их в обычные числа
    size_t toPos;
    while ((toPos = inner.find("to")) != std::string::npos) {
        inner.replace(toPos, 2, ",");
    }
    
    std::stringstream ss(inner);
    std::string token;
    std::vector<int> vals;
    while (std::getline(ss, token, ',')) {
        if (token.empty() || token.find_first_not_of(" \t") == std::string::npos) continue;
        vals.push_back(std::stoi(token));
    }
    
    // Нам нужно минимум 5 чисел: [шанс1, от1, до1, от2, до2]
    if (vals.size() < 5) return 0;
    
    int chance1 = vals[0];
    int min1 = vals[1];
    int max1 = vals[2];
    int min2 = vals[3];
    int max2 = vals[4];
    
    // Бросаем виртуальный кубик на 100 процентов
    int roll = 1 + (std::rand() % 100);
    
    if (roll <= chance1) {
        // Выпал первый диапазон (например, до 5)
        return min1 + (std::rand() % (max1 - min1 + 1));
    } else {
        // Выпал второй диапазон (например, до 1050)
        return min2 + (std::rand() % (max2 - min2 + 1));
    }
}

// Движок ультра-короткой математики Lagu
double evaluateLaguMath(std::string expr) {
    if(!expr.empty()) {
        expr.erase(0, expr.find_first_not_of(" \t"));
        expr.erase(expr.find_last_not_of(" \t") + 1);
    }

    if (expr.rfind("rdch(", 0) == 0) return evaluateRdch(expr);
    if (expr.rfind("po(", 0) == 0) { auto args = getArgs(expr); if (args.size() == 2) return std::pow(args[0], args[1]); }
    if (expr.rfind("sq(", 0) == 0) { auto args = getArgs(expr); if (!args.empty()) return std::sqrt(args[0]); }
    if (expr.rfind("ab(", 0) == 0) { auto args = getArgs(expr); if (!args.empty()) return std::abs(args[0]); }
    if (expr.rfind("rn(", 0) == 0) { auto args = getArgs(expr); if (!args.empty()) return std::round(args[0]); }
    if (expr.rfind("cl(", 0) == 0) { auto args = getArgs(expr); if (!args.empty()) return std::ceil(args[0]); }
    if (expr.rfind("fl(", 0) == 0) { auto args = getArgs(expr); if (!args.empty()) return std::floor(args[0]); }
    if (expr.rfind("rd(", 0) == 0) { auto args = getArgs(expr); if (args.size() == 2) return (int)args[0] + (std::rand() % ((int)args[1] - (int)args[0] + 1)); }

    if (lagu_vars.count(expr)) return lagu_vars[expr];
    try { return std::stod(expr); } catch (...) { return 0; }
}

void executeSingleCommand(std::string cmd) {
    if (cmd.empty()) return;
    cmd.erase(0, cmd.find_first_not_of(" \t"));
    cmd.erase(cmd.find_last_not_of(" \t") + 1);

    if (cmd.rfind("dis(", 0) == 0) {
        size_t open = cmd.find('(');
        size_t close = cmd.find_last_of(')');
        if (open == std::string::npos || close == std::string::npos) return;
        std::string content = cmd.substr(open + 1, close - open - 1);
        
        if (content.rfind("po(", 0) == 0 || content.rfind("sq(", 0) == 0 || 
            content.rfind("ab(", 0) == 0 || content.rfind("rn(", 0) == 0 ||
            content.rfind("cl(", 0) == 0 || content.rfind("fl(", 0) == 0 || 
            content.rfind("rd(", 0) == 0 || content.rfind("rdch(", 0) == 0 || lagu_vars.count(content)) {
            std::cout << evaluateLaguMath(content) << std::endl;
        } else {
            if (!content.empty() && content.front() == '"' && content.back() == '"') {
                content = content.substr(1, content.length() - 2);
            }
            std::cout << content << std::endl;
        }
    }
    else if (cmd.rfind("lac(", 0) == 0) {
        size_t open = cmd.find('(');
        size_t close = cmd.find_last_of(')');
        if (open == std::string::npos || close == std::string::npos) return;
        std::string varName = cmd.substr(open + 1, close - open - 1);
        if (!varName.empty() && varName.front() == '"' && varName.back() == '"') varName = varName.substr(1, varName.length() - 2);
        
        double val;
        if (std::cin >> val) {
            lagu_vars[varName] = val;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void runLaguCode(const std::string& sourceCode) {
    std::stringstream ss(sourceCode);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;

        if (line.rfind("fo(", 0) == 0 || line.rfind("cycle(", 0) == 0) {
            size_t open = line.find('(');
            size_t close = line.find(')');
            size_t dash = line.find('-');
            if (open != std::string::npos && close != std::string::npos && dash != std::string::npos) {
                std::vector<double> args = getArgs(line.substr(0, close + 1));
                std::string action = line.substr(dash + 1);
                if (line.rfind("fo(", 0) == 0 && args.size() == 2) {
                    for (int i = (int)args[0]; i <= (int)args[1]; ++i) { lagu_vars["i"] = i; executeSingleCommand(action); }
                } else if (!args.empty()) {
                    for (int c = 0; c < (int)args[0]; ++c) { executeSingleCommand(action); }
                }
            }
        } else {
            executeSingleCommand(line);
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::srand(std::time(0));

    // Тестируем твою умную систему шансов в цикле!
    std::string myLaguCode = 
        "dis(--- Тестируем систему шансов rdch ---)\n"
        "dis(Выбрасываем 10 чисел с шансом 50 на 50 (до 5 или от 5 до 1050):)\n"
        "fo(1, 10) - dis(rdch(50, 1 to 5, 5 to 1050))"; 

    std::cout << "--- Запуск Lagu v0.9 (Система шансов) ---\n\n";
    runLaguCode(myLaguCode);
    return 0;
}