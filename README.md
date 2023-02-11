# boids_project
Behaviour of boid-composed-flocks simulation

Sul terminale di comando, per compilare ed eseguire il programma si esegue il comando: <br>
 g++ vector.cpp boids.cpp main.cpp -std=c++17 -Wall -Wextra -fsanitize=address -lsfml-graphics -lsfml-window -lsfml-system && ./a.out <br>
Per testare la classe Vector, si esegue il comando: <br>
g++ vector.cpp vector.test.cpp -std=c++17 -Wall -Wextra -fsanitize=address && ./a.out <br>
Per testare le classi Boid, Flock e MultiFlock e relativi metodi, e le funzioni contenute in rules.hpp,
si esegue il comando: <br>
g++ vector.cpp boids.cpp boids.test.cpp -std=c++17 -Wall -Wextra -fsanitize=address && ./a.out <br>
Per la compilazione di graphics.cpp è necessaria la libreria grafica SFML, che si può liberamente 
scaricare al link: https://www.sfml-dev.org/. <br>
# boids
