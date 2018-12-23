# Arduino 
*Robo Class -> Matrix* 

 ***RACING GAME***

**Componente:**
* Arduion UNO
* Cablu Arduino USB
* Matrice de leduri 8x8 
* Joystick
* Driver MAX7219
* Display LCD
* Buton (Push Button)
* Condensator 10 uF
* Rezistente 10K, 220 Ohm
* Condensator 0.1 uF
* Trei breadboard-uri (1 mare, 2 mici)
* Fire de conexiune

**Instructiuni:**

Folosind joystick-ul, jucatorul trebuie sa miste masina (conturata aprinzand 4 led-uri pe matrice, de forma unui patrat) astfel incat sa se fereasca de obstacole. Obstacolele reprezinta puncte (1 punct, 1 led) animate pe matrice. Jocul are 3 viteze, fiecare viteza va fi setata folosind butonul, astfel:
* prima apasare -> prima viteza
* a 2a apasare -> a doua viteza: obstacolele se deplaseaza mai repede si jucatorul trebuie sa miste masina mult mai repede
* a 3a apasare -> a treia viteza: mai repede decat a doua viteza setata
* a 4a apasare -> pauza
* a 5a apasare -> jocul reincepe;

Pe LCD vor fi afisate:
* numele jocului: RACING GAME
* instructiunile de joc (apar la putin timp dupa afisarea numelui jocului)
* mesajul SA INCEAPA JOCUL, care specifica faptul ca jucatorul poate incepe sa isi seteze viteza si sa joace.
* vitezele : SPEED UP 1, SPEED UP 2, SPEED UP 3;

Pe matrice vor fi afisate led-urile necesare jocului, precum si litera P necesara in momentul de pauza al jocului.
