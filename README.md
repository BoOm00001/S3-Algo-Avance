TP1 - Algorithmique avancee (SquareFinder)
==========================================

Cours : 420-W31-SF - Algorithmique avancee  
Cegep de Sainte-Foy  
---------------------------------------------------------

Objectif du projet
------------------
Ce projet vise a resoudre differents problemes dans un nuage de points cartesien en utilisant des approches algorithmiques avancees.  
L'objectif est de lire des points 2D depuis un fichier, d'identifier tous les carres possibles, et de comparer la performance entre deux methodes : une approche par force brute et une approche optimisee.

---------------------------------------------------------

Taches principales
------------------

1. Lecture et stockage des donnees  
   - Lire les coordonnees (X, Y) d'un fichier texte.  
   - Convertir chaque ligne en objet Dot et l'ajouter a la memoire.  
   - Adapter la methode loadDotsFromMemory pour utiliser addDot.

2. Recherche de carres - Methode de la force brute  
   - Implementer findSquaresBruteForce pour tester toutes les combinaisons possibles de 4 points.  
   - Determiner si quatre points forment un carre (cotes egaux et diagonales egales).  
   - Enregistrer les carres trouves et leur nombre total.  
   - Cette methode est simple mais peu performante pour de grands ensembles.

3. Recherche de carres - Methode optimisee  
   - Implementer profFindSquaresOptimized pour ameliorer l'efficacite.  
   - Utiliser les techniques de tri et de recherche pour reduire la complexite.  
   - Produire les memes resultats que la methode brute mais avec un meilleur temps d'execution.  
   - Permettre de basculer entre les deux algorithmes a l'aide des touches 1 et 2.

4. Tests unitaires  
   - Produire une description des cas de test dans le document DescriptionsTests.docx.  
   - Implementer les tests unitaires dans TestSquareFinder.cpp.  
   - Ajouter un commentaire avant chaque test indiquant la situation testee.

---------------------------------------------------------

Conseils
--------
- L'algorithme de force brute ne permet pas de traiter un grand volume de points.  
- L'approche optimisee doit permettre de detecter efficacement les carres meme dans des ensembles importants.  
- Utiliser des techniques de pretraitement, de tri et de recherche pour ameliorer la performance.  
- Le projet doit compiler sans avertissement et respecter les bonnes pratiques de codage.

---------------------------------------------------------

Technologies utilisees
----------------------
- C++  
- Programmation oriente objet (classes, methodes, encapsulation)  
- Algorithmes de tri et de recherche  
- Manipulation de fichiers texte  
- Tests unitaires (C++ ou framework libre)  
- IDE : Visual Studio / VS Code

---------------------------------------------------------

Auteur
------
Cherif - Etudiant AEC Programmation, bases de donnees et serveurs  
Cegep de Sainte-Foy  
GitHub : https://github.com/BoOm00001  
LinkedIn : https://www.linkedin.com/in/cherif-ouattara/
