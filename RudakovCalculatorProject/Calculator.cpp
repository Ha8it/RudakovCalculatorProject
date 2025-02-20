#include <iostream>
#include <string>
#include <vector>

bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
bool is_letter(char c) {
    return std::isalpha(static_cast<unsigned char>(c));  // Проверяем, является ли символ буквой
}
double apply_operator(double a, double b, char arifmeticOp) {
    switch (arifmeticOp) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: exit;
    }
}

//Проверка на то, является ли символ орефметическим оператором и проверка приоретета в выполнении
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

//Извлечение числа из строки с проверкой индекса и цельности числа
double parse_number(const std::string& expr, size_t& index) {
    std::string num = "";

    if (expr[index] == '-') {
        num += expr[index++];
    }
    while (index < expr.size() && (isdigit(expr[index]) || expr[index] == '.')) {
        num += expr[index++];
    }

    return std::stod(num);
}

double evaluate_expression(const std::string& expr) {
    std::vector<double> values;
    std::vector<char> ops;

    size_t i = 0;
    while (i < expr.size()) {
        char c = expr[i];

        if (c == ' ') {
            i++;
            continue;
        }
        //Проверка чем является текущий символ
        //parse_number используется для парсина математических выражений для математических расчетов строки
       //(isdigit(c) проверка символа на то, является ли он числом (вроде десятичной от 0 до 9) в противном случае должен вернуться 0
        if (isdigit(c) || c == '.' || (c == '-' && (i == 0 || is_operator(expr[i - 1]) || expr[i - 1] == '('))) {
            values.push_back(parse_number(expr, i));
        }
        //УРА! СКОБОЧКИ! ЭТО СКОБОЧКИ! РАБОЧИЕ СКОБОЧКИ!
        else if (c == '(') {
            ops.push_back(c);
            i++;
        }
        //открытая и закрытая скобка 
        else if (c == ')') {
            while (!ops.empty() && ops.back() != '(') {
                double b = values.back(); values.pop_back();
                double a = values.back(); values.pop_back();
                char op = ops.back(); ops.pop_back();
                values.push_back(apply_operator(a, b, op));
            }
            ops.pop_back();
            i++;
        }

        //Выставление приорететов оператора 
        else if (is_operator(c)) {
            while (!ops.empty() && precedence(ops.back()) >= precedence(c)) {
                double b = values.back(); values.pop_back();
                double a = values.back(); values.pop_back();
                char op = ops.back(); ops.pop_back();
                values.push_back(apply_operator(a, b, op));
            }
            ops.push_back(c);
            i++;
        }

    }
    //Используется для того, что бы итоговым действием было только результат действий пользователя без знаков (если только число не отрицательное) пременяя операторы
    while (!ops.empty()) {
        double b = values.back(); values.pop_back();
        double a = values.back(); values.pop_back();
        char op = ops.back(); ops.pop_back();
        values.push_back(apply_operator(a, b, op));
    }

    return values.back();
}

int main() {

    system("chcp 1251");
    std::string math;
    double result;
    do {
        system("cls");
        std::cout << "Введите арифметическое выражение: ";
        std::getline(std::cin, math);

        try {
            result = evaluate_expression(math);
            std::cout << "Ответ: " << result << std::endl;

        }
        catch (...) {
            std::cerr << "Ошибка при вычислении выражения!" << std::endl;
        }
        system("pause");
    } while (result != 0);
    return 0;
}