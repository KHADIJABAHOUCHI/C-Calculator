#include <iostream>
#include <stack>
#include <string>

// Fonction pour déterminer la priorité des opérateurs
int precedance(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Fonction pour effectuer les calculs en fonction de l'opérateur
double appliquerOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0;
    }
}

// Fonction pour convertir une chaîne de caractère en nombre
double convertirEnNombre(const std::string& str) {
    double result = 0;
    bool isDecimal = false;
    double decimalPlace = 1.0;

    for (char c : str) {
        if (c >= '0' && c <= '9') {
            if (isDecimal) {
                decimalPlace /= 10;
                result += (c - '0') * decimalPlace;
            }
            else {
                result = result * 10 + (c - '0');
            }
        }
        else if (c == '.') {
            isDecimal = true;
        }
        else {
            // Caractère non valide trouvé
            std::cerr << "Caractère invalide dans le nombre: " << c << std::endl;
            return 0;
        }
    }
    return result;
}

// Fonction d'évaluation d'une expression infixe
double evaluerExpression(const std::string& expression) {
    std::stack<double> valeurs;  // Pile pour les valeurs
    std::stack<char> operateurs;  // Pile pour les opérateurs
    std::string temp;

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];

        // Si c'est un espace, on continue
        if (c == ' ') {
            continue;
        }

        // Si c'est un chiffre ou un point pour le nombre flottant
        if ((c >= '0' && c <= '9') || c == '.') {
            temp += c;
        }
        else {
            if (!temp.empty()) {
                // Convertir le nombre en valeur et l'empiler
                valeurs.push(convertirEnNombre(temp));
                temp.clear();
            }

            // Si c'est un opérateur, on le traite
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                while (!operateurs.empty() && precedance(operateurs.top()) >= precedance(c)) {
                    double b = valeurs.top();
                    valeurs.pop();
                    double a = valeurs.top();
                    valeurs.pop();
                    char op = operateurs.top();
                    operateurs.pop();

                    valeurs.push(appliquerOperation(a, b, op));  // Effectuer l'opération
                }
                operateurs.push(c);  // Empiler l'opérateur
            }
        }
    }

    if (!temp.empty()) {
        // Empiler la dernière valeur si c'est un nombre
        valeurs.push(convertirEnNombre(temp));
    }

    // Effectuer les opérations restantes
    while (!operateurs.empty()) {
        double b = valeurs.top();
        valeurs.pop();
        double a = valeurs.top();
        valeurs.pop();
        char op = operateurs.top();
        operateurs.pop();

        valeurs.push(appliquerOperation(a, b, op));  // Effectuer l'opération
    }

    // La seule valeur restante dans la pile est le résultat
    return valeurs.top();
}

int main() {
    std::string expression;

    std::cout << "Entrez une expression mathématique : ";
    std::getline(std::cin, expression);

    double resultat = evaluerExpression(expression);

    std::cout << "Le résultat de l'expression est : " << resultat << std::endl;

    return 0;
}
