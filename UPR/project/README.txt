SPACE INVADERS

jak projekt zkompilovat

Vytvoříme složku pro sestavení projektu a sestavíme Makefile

mkdir build
cd build
cmake ..

poté stačí program přeložit

make

spustit

./project

--------------------------

ovládání

< pohyb do doleva
> pohyb do prava
↑     vystřelit
SPACE vystřelit
ESC vypnout

Poznámky

- Spodní mimozemšťani +1, střední +2, horní +3, vesmírná loď +10-50 bodů
- Maximální skóre je ukládáno do `topScore.txt`.
- Tento projekt vyžaduje knihovnu SDL2.
- Před spuštěním projektu se ujistěte, že máte správně nastavené adresáře a soubory s texturami v CMakeLists.txt (`assets/`, `assets/ARIALBD.TTF`).