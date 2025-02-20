#include <iostream>
#include <string>
#include <vector>

bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
bool is_letter(char c) {
    return std::isalpha(static_cast<unsigned char>(c));  // ���������, �������� �� ������ ������
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

//�������� �� ��, �������� �� ������ �������������� ���������� � �������� ���������� � ����������
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

//���������� ����� �� ������ � ��������� ������� � ��������� �����
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
        //�������� ��� �������� ������� ������
        //parse_number ������������ ��� ������� �������������� ��������� ��� �������������� �������� ������
       //(isdigit(c) �������� ������� �� ��, �������� �� �� ������ (����� ���������� �� 0 �� 9) � ��������� ������ ������ ��������� 0
        if (isdigit(c) || c == '.' || (c == '-' && (i == 0 || is_operator(expr[i - 1]) || expr[i - 1] == '('))) {
            values.push_back(parse_number(expr, i));
        }
        //���! ��������! ��� ��������! ������� ��������!
        else if (c == '(') {
            ops.push_back(c);
            i++;
        }
        //�������� � �������� ������ 
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

        //����������� ����������� ��������� 
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
    //������������ ��� ����, ��� �� �������� ��������� ���� ������ ��������� �������� ������������ ��� ������ (���� ������ ����� �� �������������) �������� ���������
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
        std::cout << "������� �������������� ���������: ";
        std::getline(std::cin, math);

        try {
            result = evaluate_expression(math);
            std::cout << "�����: " << result << std::endl;

        }
        catch (...) {
            std::cerr << "������ ��� ���������� ���������!" << std::endl;
        }
        system("pause");
    } while (result != 0);
    return 0;
}