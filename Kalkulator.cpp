#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printHelp() {
    cout << "======================================================" << endl;
    cout << "          Мультипликативный калькулятор               " << endl;
    cout << "======================================================" << endl;
    cout << "Поддерживаемые операции:" << endl;
    cout << "  multiply - произведение всех чисел" << endl;
    cout << "  divide   - деление первого числа на остальные" << endl;
    cout << "  help     - показать эту справку" << endl;
    cout << endl;
    cout << "Принимается от 2 до 4 чисел." << endl;
    cout << endl;
    cout << "Формат запуска:" << endl;
    cout << "  ./Kalkulator -o <операция> <числа...>" << endl;
    cout << "  ./Kalkulator --operation <операция> <числа...>" << endl;
    cout << "  ./Kalkulator -h | --help" << endl;
    cout << endl;
    cout << "Примеры:" << endl;
    cout << "  ./Kalkulator -o multiply 3 4 5" << endl;
    cout << "  ./Kalkulator --operation divide 60 3 2" << endl;
    cout << "======================================================" << endl;
}

class MultiCalc {
private:
    vector<double> nums;
    double answer;
public:
    MultiCalc() : answer(1.0) {}
    void push(double v) {
        nums.push_back(v);
    }
    size_t size() const {
        return nums.size();
    }
    void doMultiply() {
        answer = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            answer = answer * nums[i];
        }
        cout << "Результат: " << answer << endl;
    }
    void doDivide() {
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == 0.0) {
                cout << "Ошибка - деление на ноль!" << endl;
                return;
            }
        }
        answer = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            answer = answer / nums[i];
        }
        cout << "Результат: " << answer << endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }
    string op;
    MultiCalc mc;
    for (int i = 1; i < argc; ++i) {
        string cur = argv[i];
        if (cur == "-h" || cur == "--help") {
            printHelp();
            return 0;
        }
        if (cur == "-o" || cur == "--operation") {
            if (i + 1 < argc) {
                op = argv[++i];
            }
        }
        else if (cur.rfind("--operation=", 0) == 0) {
            op = cur.substr(12);
        }
        else if (cur.rfind("-o=", 0) == 0) {
            op = cur.substr(3);
        }
        else {
            mc.push(stod(cur));
        }
    }
    if (op.empty()) {
        cerr << "Ошибка. Не указана операция!" << endl;
        printHelp();
        return 1;
    }
    if (mc.size() < 2 || mc.size() > 4) {
        cerr << "Ошибка. Нужно от 2 до 4 чисел! Вы ввели: " << mc.size() << endl;
        return 1;
    }
    if (op != "multiply" && op != "divide") {
        cerr << "Ошибка. Неизвестная операция!" << endl;
        printHelp();
        return 1;
    }
    if (op == "multiply") {
        mc.doMultiply();
    } else {
        mc.doDivide();
    }
    return 0;
}
