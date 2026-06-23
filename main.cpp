#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

struct Question {
    std::string texte;
    std::string reponse;
};

std::vector<Question> chargerQuestions(const std::string& fichier) {
    std::vector<Question> questions;
    std::ifstream file(fichier);
    std::string ligne;
    
    while (std::getline(file, ligne)) {
        size_t separateur = ligne.find('|');
        if (separateur != std::string::npos) {
            questions.push_back({ligne.substr(0, separateur), 
                                 ligne.substr(separateur + 1)});
        }
    }
    return questions;
}

int main() {
    std::vector<Question> questions = chargerQuestions("questions.txt");
    
    // Mélanger les questions
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);
    
    int score = 0;
    std::string reponse;
    
    for (const auto& q : questions) {
        std::cout << "\n❓ " << q.texte << "\nRéponse : ";
        std::getline(std::cin, reponse);
        
        // Ignorer la casse
        std::transform(reponse.begin(), reponse.end(), reponse.begin(), ::tolower);
        std::string bonneRep = q.reponse;
        std::transform(bonneRep.begin(), bonneRep.end(), bonneRep.begin(), ::tolower);
        
        if (reponse == bonneRep) {
            std::cout << "✅ Correct !\n";
            score++;
        } else {
            std::cout << "❌ Faux ! La réponse était : " << q.reponse << "\n";
        }
    }
    
    std::cout << "\n=== Score final : " << score << "/" << questions.size() << " ===\n";
    return 0;
}