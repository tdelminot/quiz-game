#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream> 

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
    
    // Melanger les questions
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);
    
    int score = 0;
    std::string reponse;
    
    auto debut = std::chrono::steady_clock::now();


    for (const auto& q : questions) {
        std::cout << "\nQuestion: " << q.texte << std::endl;
        std::cout << "Votre reponse: ";
        std::getline(std::cin, reponse);
        
        if (reponse == q.reponse) {
            std::cout << "Bonne reponse!" << std::endl;
            score++;
        } else {
            std::cout << "Mauvaise reponse. La bonne etait: " << q.reponse << std::endl;
        }
    }
    
     auto fin = std::chrono::steady_clock::now();
     auto duree = std::chrono::duration_cast<std::chrono::seconds>(fin - debut);
     std::cout << "\n⏱️ Temps total : " << duree.count() << " secondes\n";

    std::cout << "\nScore final: " << score << "/" << questions.size() << std::endl;

    std::cout << "Score max possible : " << questions.size() << "\n";
    
    
    // Sauvegarde du score
    std::ofstream sauvegarde("dernier_score.txt");
    if (sauvegarde.is_open()) {
    sauvegarde << score << "/" << questions.size() << "\n";
    sauvegarde.close();
    std::cout << "Score sauvegardé dans dernier_score.txt\n";
}
    
    
    
    return 0;
}
