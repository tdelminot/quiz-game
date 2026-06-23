#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

// Version simplifiée des fonctions du jeu
vector<std::string> chargerQuestions(const std::string& fichier) {
    vector<std::string> questions;
    ifstream file(fichier);
    string ligne;
    while (std::getline(file, ligne)) {
        if (ligne.find('|') != std::string::npos) {
            questions.push_back(ligne);
        }
    }
    return questions;
}

int main() {
    // Test 1 : Chargement du fichier
    ofstream testFile("test_questions.txt");
    testFile << "Question 1|Réponse 1\n";
    testFile << "Question 2|Réponse 2\n";
    testFile.close();
    
    auto questions = chargerQuestions("test_questions.txt");
    assert(questions.size() == 2);
    cout << " Test 1 passé : chargement des questions\n";
    
    // Test 2 : Format correct
    assert(questions[0].find('|') != std::string::npos);
    cout << " Test 2 passé : format correct\n";
    
    // Test 3 : Fichier inexistant
    auto vide = chargerQuestions("fichier_inexistant.txt");
    assert(vide.empty());
    cout << " Test 3 passé : fichier inexistant\n";
    
    cout << "\n🎉 Tous les tests passés !\n";
    return 0;
}